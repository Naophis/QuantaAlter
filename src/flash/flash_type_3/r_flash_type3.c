#include "../r_flash_rx_if.h"
#if (FLASH_TYPE == FLASH_TYPE_3)
#include <machine.h>
#include <string.h>     // memcpy()
#include "../r_flash_rx_config.h"
#include "r_flash_type3_if.h"
#include <stddef.h>

typedef __evenaccess                                           volatile uint8_t *FCU_BYTE_PTR;
typedef __evenaccess                                           volatile uint16_t *FCU_WORD_PTR;
typedef __evenaccess                                           volatile uint32_t *FCU_LONG_PTR;

typedef enum {
	FLASH_LOCKBIT_MODE_NORMAL,
	FLASH_LOCKBIT_MODE_OVERRIDE,
	FLASH_LOCKBIT_MODE_END_ENUM
} lkbit_mode_t;

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#define FLASH_RETURN_IF_PCFG_NULL   if ((pcfg == NULL) || (pcfg == FIT_NO_PTR))     \
                                    {                                               \
                                        return FLASH_ERR_NULL_PTR;                  \
                                    }
#define FLASH_RETURN_IF_BGO_AND_NO_CALLBACK     // in blocking mode (non-BGO)

#define FCU_COMMAND_AREA          (0x007E0000)
#define FCU_FIRMWARE_STORAGE_AREA (0xFEFFF000)
#define FCU_RAM_AREA              (0x007F8000)
#define FCU_RAM_SIZE              (4096)

#define FLASH_FACI_CMD_PROGRAM              0xE8
#define FLASH_FACI_CMD_PROGRAM_CF           0x80
#define FLASH_FACI_CMD_PROGRAM_DF           0x02
#define FLASH_FACI_CMD_BLOCK_ERASE          0x20
#define FLASH_FACI_CMD_PE_SUSPEND           0xB0
#define FLASH_FACI_CMD_PE_RESUME            0xD0
#define FLASH_FACI_CMD_STATUS_CLEAR         0x50
#define FLASH_FACI_CMD_FORCED_STOP          0xB3
#define FLASH_FACI_CMD_BLANK_CHECK          0x71
#define FLASH_FACI_CMD_CONFIG_SET_1         0x40
#define FLASH_FACI_CMD_CONFIG_SET_2         0x08
#define FLASH_FACI_CMD_LOCK_BIT_PGM         0x77
#define FLASH_FACI_CMD_LOCK_BIT_READ        0x71
#define FLASH_FACI_CMD_FINAL                0xD0

#define FLASH_FENTRYR_TIMEOUT   (4)

#define FLASH_FRDY_CMD_TIMEOUT          (9600)

#define FLASH_DBFULL_TIMEOUT (540)

FCU_BYTE_PTR g_pfcu_cmd_area = (uint8_t *) FCU_COMMAND_AREA;

flash_err_t flash_init();
flash_err_t flash_clock_config(uint32_t);
flash_err_t flash_fcuram_codecopy();
flash_err_t flash_reset();
flash_err_t flash_stop();
flash_err_t flash_interrupt_config(bool state, void *pCallback);
flash_err_t flash_api_lockbit_set(flash_block_address_t block_address,
		uint32_t num_blocks);
flash_err_t flash_lockbit_write(flash_block_address_t block_address,
		uint32_t num_blocks);
flash_err_t flash_lockbit_read(flash_block_address_t block_address,
		flash_res_t *lock_state_result);
flash_err_t flash_lockbit_ignore(bool state);
flash_err_t flash_pe_mode_enter(flash_type_t flash_type);
flash_err_t flash_pe_mode_exit();
flash_err_t flash_erase(uint32_t block_address, uint32_t block_count);
flash_err_t flash_write(uint32_t *src_start_address,
		uint32_t *dest_start_address, uint32_t *num_bytes);
flash_err_t flash_blankcheck(uint32_t start_address, uint32_t num_bytes,
		flash_res_t *blank_check_result);
flash_err_t flash_lock_state(flash_states_t new_state);
flash_err_t flash_get_status(void);
void flash_release_state(void);
flash_err_t check_cf_block_total(flash_block_address_t block_start_address,
		uint32_t num_blocks);

/* State variable for the Flash API. */
extern flash_states_t g_flash_state;
lkbit_mode_t g_lkbit_mode = FLASH_LOCKBIT_MODE_NORMAL;

flash_int_cb_args_t g_flash_int_ready_cb_args; // Callback argument structure for flash READY interrupt
flash_int_cb_args_t g_flash_int_error_cb_args; // Callback argument structure for flash ERROR interrupt

flash_err_t flash_api_open(void) {
	flash_err_t err;
	if ((MCU_CFG_FCLK_HZ > 60000000) || (MCU_CFG_FCLK_HZ < 4000000)) {
		return FLASH_ERR_FREQUENCY;
	}
	/* Allow Initialization if not initialized or
	 * if no operation is ongoing and re-initialization is desired */
	if (FLASH_SUCCESS != flash_lock_state(FLASH_INITIALIZATION)) {
		/* API already initialized */
		return FLASH_ERR_BUSY;
	}

	err = flash_init();
	if (FLASH_SUCCESS != err) {
		return err;
	}

	g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_INITIALIZED;

	// Set the parameters struct based on the config file settings
	g_current_parameters.bgo_enabled_cf = FLASH_CFG_CODE_FLASH_BGO;
	g_current_parameters.bgo_enabled_df = FLASH_CFG_DATA_FLASH_BGO;

	/*Interrupts are enabled by default on this MCU.
	 * Disable Interrupts*/
	flash_interrupt_config(false, NULL);
	/* Release state so other operations can be performed. */
	flash_release_state();
	return FLASH_SUCCESS;
}

flash_err_t flash_api_write(uint32_t src_address, uint32_t dest_address,
		uint32_t num_bytes) {
	flash_err_t err;

	if (num_bytes == 0) {
		return FLASH_ERR_BYTES;
	}

	FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;

	if (g_flash_state != FLASH_READY) {
		return FLASH_ERR_BUSY;
	}
	if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING)) {
		return FLASH_ERR_BUSY;
	}

	if (((dest_address > (uint32_t) FLASH_CF_BLOCK_INVALID))
			&& (!(dest_address & (FLASH_CF_MIN_PGM_SIZE - 1)))) {
		if ((num_bytes - 1 + (dest_address) > (uint32_t) FLASH_CF_BLOCK_END)
				|| (num_bytes & (FLASH_CF_MIN_PGM_SIZE - 1))
				|| (num_bytes - 1 + (dest_address)
						< (uint32_t) FLASH_CF_BLOCK_INVALID))      // Overflowed

				{
			err = FLASH_ERR_BYTES;
		} else {
			if (g_current_parameters.bgo_enabled_cf == true) {
				g_current_parameters.current_operation = FLASH_CUR_CF_BGO_WRITE;
			} else {
				g_current_parameters.current_operation = FLASH_CUR_CF_WRITE;
				g_current_parameters.wait_cnt = WAIT_MAX_ROM_WRITE;
			}
			g_current_parameters.min_pgm_size = (FLASH_CF_MIN_PGM_SIZE >> 1);
			/*There are no parameter errors. Switch to the CF PE mode*/
			err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
		}

	} else if (((dest_address >= FLASH_DF_BLOCK_0)
			&& (dest_address < FLASH_DF_BLOCK_INVALID))
			&& (!(dest_address & (FLASH_DF_MIN_PGM_SIZE - 1)))) {
		if ((num_bytes + (dest_address) > FLASH_DF_BLOCK_INVALID)
				|| (num_bytes & (FLASH_DF_MIN_PGM_SIZE - 1))) {
			err = FLASH_ERR_BYTES;
		} else {
			if (g_current_parameters.bgo_enabled_df == true) {
				g_current_parameters.current_operation = FLASH_CUR_DF_BGO_WRITE;
			} else {
				g_current_parameters.current_operation = FLASH_CUR_DF_WRITE;
			}
			g_current_parameters.wait_cnt = WAIT_MAX_DF_WRITE;
			g_current_parameters.min_pgm_size = (FLASH_DF_MIN_PGM_SIZE >> 1);
			err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
		}
	} else {
		err = FLASH_ERR_ADDRESS;
	}
	if (FLASH_SUCCESS != err) {
		flash_release_state();
		return err;
	}

	err = flash_write(&src_address, &dest_address, &num_bytes);
	if (FLASH_SUCCESS != err) {
		flash_reset();
		flash_release_state();
		return err;
	}

	if ((g_current_parameters.current_operation == FLASH_CUR_CF_WRITE)
			|| (g_current_parameters.current_operation == FLASH_CUR_DF_WRITE)) {
		err = flash_pe_mode_exit();
		if (FLASH_SUCCESS != err) {
			flash_reset();
		}
		flash_release_state();
	}
	return err;
}

flash_err_t flash_api_erase(flash_block_address_t block_start_address,
		uint32_t num_blocks) {
	flash_err_t err;

	FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;
	if (g_flash_state != FLASH_READY) {
		/* API not initialized or busy with another operation*/
		return FLASH_ERR_BUSY;
	}
	if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING)) {
		return FLASH_ERR_BUSY;
	}
	if ((block_start_address <= FLASH_CF_BLOCK_0)
			&& (block_start_address > FLASH_CF_BLOCK_INVALID)) {
		if ((num_blocks > FLASH_NUM_BLOCKS_CF) || (num_blocks <= 0)) {
			err = FLASH_ERR_BLOCKS;
		} else if ((err = check_cf_block_total(block_start_address, num_blocks))
				== FLASH_SUCCESS) { /*No errors in parameters. Enter Code Flash PE mode*/
			err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
			if (g_current_parameters.bgo_enabled_cf == true) {
				g_current_parameters.current_operation = FLASH_CUR_CF_BGO_ERASE;
			} else {
				g_current_parameters.current_operation = FLASH_CUR_CF_ERASE;
			}
		}
	} else if ((block_start_address >= FLASH_DF_BLOCK_0)
			&& (block_start_address < FLASH_DF_BLOCK_INVALID)) {
		if ((num_blocks > FLASH_NUM_BLOCKS_DF) || (num_blocks <= 0)) {
			err = FLASH_ERR_BLOCKS;
		} else if ((block_start_address & (FLASH_DF_BLOCK_SIZE - 1)) != 0) {
			err = FLASH_ERR_BOUNDARY;
		} else if ((block_start_address + (num_blocks * FLASH_DF_BLOCK_SIZE) - 1)
				>= FLASH_DF_BLOCK_INVALID) {
			err = FLASH_ERR_BLOCKS;
		} else { /*No errors in parameters. Enter Data Flash PE mode*/
			err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
			if (g_current_parameters.bgo_enabled_df == true) {
				g_current_parameters.current_operation = FLASH_CUR_DF_BGO_ERASE;
			} else {
				g_current_parameters.current_operation = FLASH_CUR_DF_ERASE;
			}
		}
	} else {
		err = FLASH_ERR_ADDRESS;
	}

	if (FLASH_SUCCESS != err) {
		flash_release_state();
		return err;
	}

	err = flash_erase((uint32_t) block_start_address, num_blocks);
	if (FLASH_SUCCESS != err) {
		flash_reset();
		flash_release_state();
		return err;
	}

	if ((g_current_parameters.current_operation == FLASH_CUR_CF_ERASE)
			|| (g_current_parameters.current_operation == FLASH_CUR_DF_ERASE)) {
		err = flash_pe_mode_exit();
		if (FLASH_SUCCESS != err) {
			flash_reset();
		}
		flash_release_state();
	}
	return err;
}

/***********************************************************************************************************************
 * Function Name: check_cf_block_total
 * Description  : This function checks to see if the start address plus the number of blocks
 *                remain in valid code flash address range.
 * Arguments    : block_start_address -
 *                    Start address for erase or lock bit
 *                num_blocks -
 *                    Number of blocks to erase or lock
 * Return Value : FLASH_SUCCESS -
 *                    Valid start address and number of blocks
 *                FLASH_ERR_BLOCKS -
 *                    Number of blocks would exceed legal address range
 *                FLASH_ERR_ADRRESS -
 *                    Start address is not on block boundary
 ***********************************************************************************************************************/
flash_err_t check_cf_block_total(flash_block_address_t block_start_address,
		uint32_t num_blocks) {
	return FLASH_ERR_FAILURE;
}

#pragma section // end section FRAM

flash_err_t flash_api_blankcheck(uint32_t address, uint32_t num_bytes,
		flash_res_t *result) {
	flash_err_t err = FLASH_SUCCESS;

	FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;

	if (g_flash_state != FLASH_READY) {
		/* API not initialized or busy with another operation*/
		return FLASH_ERR_BUSY;
	}
	if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING)) {
		return FLASH_ERR_BUSY;
	}

	if (((address >= FLASH_DF_BLOCK_0) && (address < FLASH_DF_BLOCK_INVALID))) {
		/*Check if the range is valid, num_bytes is a multiple of 4, is larger than 0 and less than 65536*/
		if (((num_bytes + address) > FLASH_DF_BLOCK_INVALID)
				|| (num_bytes & (FLASH_DF_MIN_PGM_SIZE - 1)) || (num_bytes == 0)
				|| (num_bytes > 65536)) {
			err = FLASH_ERR_BYTES;
		} else if ((address & (FLASH_DF_MIN_PGM_SIZE - 1)) != 0) {
			err = FLASH_ERR_BOUNDARY;
		}
	} else {
		err = FLASH_ERR_ADDRESS;

	}

	if (FLASH_SUCCESS != err) {
		flash_release_state();
		return err;
	}

	if (g_current_parameters.bgo_enabled_df == true) {
		g_current_parameters.current_operation = FLASH_CUR_DF_BGO_BLANKCHECK;
	} else {
		g_current_parameters.current_operation = FLASH_CUR_DF_BLANKCHECK;
	}

	g_current_parameters.wait_cnt = (WAIT_MAX_BLANK_CHECK * (num_bytes >> 2));

	err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
	if (FLASH_SUCCESS != err) {
		flash_reset();
		flash_release_state();
		return err;
	}

	*result = FLASH_RES_INVALID;

	err = flash_blankcheck(address, num_bytes, result);
	if (g_current_parameters.bgo_enabled_df == false) {
		if (FLASH_SUCCESS != err) {
			flash_reset();
			flash_release_state();
			return err;
		}
		err = flash_pe_mode_exit();
		g_current_parameters.current_operation = FLASH_CUR_IDLE;
		if (FLASH_SUCCESS != err) {
			flash_reset();
		}
		flash_release_state();
	}
	return err;

}

flash_err_t flash_blankcheck(uint32_t start_address, uint32_t num_bytes,
		flash_res_t *result) {
	flash_err_t err = FLASH_SUCCESS;

	FLASH.FBCCNT.BYTE = 0x00;
	FLASH.FSADDR.LONG = start_address;
	FLASH.FEADDR.LONG = (start_address + num_bytes - 1);
	*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLANK_CHECK;
	*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

	if (g_current_parameters.bgo_enabled_df == true) {
		return err;
	}
	while (1 != FLASH.FSTATR.BIT.FRDY) {
		if (g_current_parameters.wait_cnt-- <= 0) {
			err = flash_stop();
			if (FLASH_SUCCESS != err) {
				return err;
			} else {
				return FLASH_ERR_TIMEOUT;
			}

		}
	}

	if (0 != FLASH.FASTAT.BIT.CMDLK) {
		if ((0x0002 & FLASH.FPESTAT.WORD)
				&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
			err = FLASH_ERR_FAILURE;
		} else {
			err = FLASH_ERR_CMD_LOCKED;
		}
		return err;
	}
	if (FLASH.FBCSTAT.BYTE == 0x01) {
		*result = FLASH_RES_NOT_BLANK;
	} else {
		*result = FLASH_RES_BLANK;
	}

	return err;
}

flash_err_t flash_init() {

	flash_err_t err = FLASH_SUCCESS;

	g_current_parameters.current_operation = FLASH_CUR_FCU_INIT;
	FLASH.FWEPROR.BYTE = 0x01;
	FLASH.FPCKAR.WORD = ((0x1E00) + ((MCU_CFG_FCLK_HZ / 1000000)));
	err = flash_fcuram_codecopy();
	return err;
}

flash_err_t flash_fcuram_codecopy() {
	uint8_t *p_src;
	uint8_t *p_dest;
	volatile int32_t wait_cnt;      // Timeout counter.

	p_src = (uint8_t *) FCU_FIRMWARE_STORAGE_AREA;
	p_dest = (uint8_t *) FCU_RAM_AREA;

	if (FLASH.FENTRYR.WORD != 0x0000) {
		FLASH.FENTRYR.WORD = 0xAA00;
		wait_cnt = FLASH_FENTRYR_TIMEOUT;

		while (0x0000 != FLASH.FENTRYR.WORD) {
			if (wait_cnt-- <= 0) {
				return FLASH_ERR_TIMEOUT;
			}
		}
	}

	FLASH.FCURAME.WORD = 0xC403; // FCURAM Access Enabled, High Speed Write Enabled
	memcpy(p_dest, p_src, FCU_RAM_SIZE);
	FLASH.FCURAME.WORD = 0xC400;      // FCURAM Access Disabled

	return FLASH_SUCCESS;
}

flash_err_t flash_interrupt_config(bool state, void *pcfg) {
	flash_interrupt_config_t *int_cfg = pcfg;

	if (true == state) {
		if ((NULL == int_cfg->pcallback)
				|| (FIT_NO_FUNC == int_cfg->pcallback)) {
			return FLASH_ERR_NULL_PTR;
		}
		flash_ready_isr_handler = int_cfg->pcallback;
		flash_error_isr_handler = int_cfg->pcallback;

		FLASH.FAEINT.BYTE = 0x99;
		FLASH.FRDYIE.BYTE = 0x01;
		IR(FCU,FRDYI)= 0;
		IR(FCU,FIFERR)= 0;
		IPR(FCU,FIFERR)= int_cfg->int_priority;
		IPR(FCU,FRDYI)= int_cfg->int_priority;
		IEN (FCU,FIFERR)= 1;
		IEN (FCU,FRDYI)= 1;

	}
	else if (false == state)
	{
		FLASH.FAEINT.BYTE = 0x00;
		FLASH.FRDYIE.BYTE = 0x00;
		IR(FCU,FRDYI) = 0;
		IR(FCU,FIFERR) = 0;
	}

	return FLASH_SUCCESS;
}

flash_err_t flash_api_control(flash_cmd_t cmd, void *pcfg) {
	flash_err_t err = FLASH_SUCCESS;
	flash_lockbit_config_t *lockbit_cfg;
	uint32_t *plocal_pcfg;

	if (cmd == FLASH_CMD_RESET) {
		err = flash_reset();
		flash_release_state();
		return err;
	}

	if (g_flash_state != FLASH_READY) {
		return FLASH_ERR_BUSY;
	}

	switch (cmd) {

	case FLASH_CMD_LOCKBIT_ENABLE:
		g_lkbit_mode = FLASH_LOCKBIT_MODE_NORMAL;
		break;
	case FLASH_CMD_LOCKBIT_DISABLE:
		g_lkbit_mode = FLASH_LOCKBIT_MODE_OVERRIDE;
		break;
	case FLASH_CMD_STATUS_GET:
		err = flash_get_status();
		break;
	case FLASH_CMD_LOCKBIT_READ:
		FLASH_RETURN_IF_PCFG_NULL
		;
		FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;
		lockbit_cfg = pcfg;
		err = flash_lockbit_read(lockbit_cfg->block_start_address,
				&(lockbit_cfg->result));
		break;
	case FLASH_CMD_LOCKBIT_WRITE:
		FLASH_RETURN_IF_PCFG_NULL
		;
		FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;
		lockbit_cfg = pcfg;
		err = flash_api_lockbit_set(lockbit_cfg->block_start_address,
				lockbit_cfg->num_blocks);
		break;
	case FLASH_CMD_CONFIG_CLOCK:
		FLASH_RETURN_IF_PCFG_NULL
		;
		plocal_pcfg = pcfg;
		if ((*plocal_pcfg >= 4000000) && (*plocal_pcfg <= 60000000)) {
			err = flash_clock_config(*plocal_pcfg);
		} else {
			err = FLASH_ERR_FREQUENCY;
		}
		break;
	default:
		err = FLASH_ERR_PARAM;
	}
	flash_release_state();
	return err;
}

flash_err_t flash_clock_config(uint32_t cur_fclk) {
	uint32_t speed_mhz;

	speed_mhz = cur_fclk / 1000000;
	if ((cur_fclk % 1000000) != 0) {
		speed_mhz++;    // must round up to nearest MHz
	}

	/*Set the Clock*/
	FLASH.FPCKAR.WORD = (uint16_t) (0x1E00) + (uint16_t) speed_mhz;
	return FLASH_SUCCESS;
}
flash_err_t flash_pe_mode_enter(flash_type_t flash_type) {
	flash_err_t err = FLASH_SUCCESS;

	if (flash_type == FLASH_TYPE_DATA_FLASH) {
		FLASH.FENTRYR.WORD = 0xAA80;  //Transition to DF P/E mode
		if (FLASH.FENTRYR.WORD == 0x0080) {
			err = FLASH_SUCCESS;
		} else {
			err = FLASH_ERR_FAILURE;
		}
	} else if (flash_type == FLASH_TYPE_CODE_FLASH) {
		FLASH.FENTRYR.WORD = 0xAA01;    //Transition to CF P/E mode
		if (FLASH.FENTRYR.WORD == 0x0001) {
			err = FLASH_SUCCESS;

			if (g_lkbit_mode == FLASH_LOCKBIT_MODE_OVERRIDE) {
				FLASH.FPROTR.WORD = 0x5501;
			}
		} else {
			err = FLASH_ERR_FAILURE;
		}
	} else {
		err = FLASH_ERR_PARAM;
	}

	return err;
}

flash_err_t flash_pe_mode_exit() {
	flash_err_t err = FLASH_SUCCESS;
	flash_err_t temp_err = FLASH_SUCCESS;
	volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

	while (1 != FLASH.FSTATR.BIT.FRDY) {
		if (wait_cnt-- <= 0) {
			return FLASH_ERR_TIMEOUT;
		}
	}

	if (0 != FLASH.FASTAT.BIT.CMDLK) {
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_STATUS_CLEAR;
		temp_err = FLASH_ERR_CMD_LOCKED;
	}

	FLASH.FENTRYR.WORD = 0xAA00;
	if (FLASH.FENTRYR.WORD == 0x0000) {
		err = FLASH_SUCCESS;
	} else {
		err = FLASH_ERR_FAILURE;
	}

	if (FLASH_ERR_CMD_LOCKED == temp_err) {
		return temp_err;
	} else {
		return err;
	}

}
flash_err_t flash_stop() {
	volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

	g_current_parameters.current_operation = FLASH_CUR_STOP;

	*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FORCED_STOP;

	while (1 != FLASH.FSTATR.BIT.FRDY) {
		if (wait_cnt-- <= 0) {
			return FLASH_ERR_TIMEOUT;
		}
	}
	if (0 != FLASH.FASTAT.BIT.CMDLK) {
		return FLASH_ERR_CMD_LOCKED;
	}

	return FLASH_SUCCESS;
}

flash_err_t flash_erase(uint32_t block_address, uint32_t num_blocks) {
	flash_err_t err = FLASH_SUCCESS;

	g_current_parameters.dest_addr = block_address;
	g_current_parameters.total_count = num_blocks;

	if (g_current_parameters.dest_addr < (uint32_t) FLASH_DF_BLOCK_INVALID) {
		g_current_parameters.wait_cnt = WAIT_MAX_ERASE_DF;
	} else if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7) {
		g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_32K;
	} else {
		g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_8K;
	}

	FLASH.FCPSR.WORD = 0x0001;
	for (g_current_parameters.current_count = 0;
			g_current_parameters.current_count
					< g_current_parameters.total_count;
			g_current_parameters.current_count++) {
		FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLOCK_ERASE;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

		if ((g_current_parameters.current_operation == FLASH_CUR_CF_BGO_ERASE)
				|| (g_current_parameters.current_operation
						== FLASH_CUR_DF_BGO_ERASE)) {
			return err;
		}
		while (1 != FLASH.FSTATR.BIT.FRDY) {
			if (g_current_parameters.wait_cnt-- <= 0) {
				flash_stop();
				return FLASH_ERR_TIMEOUT;
			}
		}

		if (0 != FLASH.FASTAT.BIT.CMDLK) {
			if ((0x0001 & FLASH.FPESTAT.WORD)
					&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_LOCKBIT_SET;
			} else if ((0x0002 & FLASH.FPESTAT.WORD)
					&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_FAILURE;
			} else {
				err = FLASH_ERR_CMD_LOCKED;
			}
			return err;
		}

		if (FLASH.FENTRYR.WORD == 0x0080) {
			g_current_parameters.dest_addr += FLASH_DF_BLOCK_SIZE;
			g_current_parameters.wait_cnt = WAIT_MAX_ERASE_DF;
		} else if (FLASH.FENTRYR.WORD == 0x0001) {
			if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7) {
				g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
				g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_32K;
			} else {
				g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
				g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_8K;
			}

		} else {
			//should never get here
			return FLASH_ERR_FAILURE;
		}
	}

	return err;
}

flash_err_t flash_write(uint32_t *src_start_address,
		uint32_t *dest_start_address, uint32_t *num_bytes) {
	flash_err_t err = FLASH_SUCCESS;
	uint32_t wait_cnt = FLASH_DBFULL_TIMEOUT;

	g_current_parameters.total_count = (*num_bytes) >> 1; //Since two bytes will be written at a time
	g_current_parameters.dest_addr = *dest_start_address;
	g_current_parameters.src_addr = *src_start_address;
	g_current_parameters.current_count = 0;

	while (g_current_parameters.total_count > 0) {
		FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_PROGRAM;
		*g_pfcu_cmd_area = (uint8_t) g_current_parameters.min_pgm_size;
		while (g_current_parameters.current_count++
				< g_current_parameters.min_pgm_size) {
			*(FCU_WORD_PTR) g_pfcu_cmd_area =
					*(uint16_t *) g_current_parameters.src_addr;

			while (FLASH.FSTATR.BIT.DBFULL == 1) {
				if (wait_cnt-- <= 0) {
					err = flash_stop();
					if (FLASH_SUCCESS != err) {
						return err;
					} else {
						return FLASH_ERR_TIMEOUT;
					}
				}
			}
			g_current_parameters.src_addr += 2;
			g_current_parameters.dest_addr += 2;
			g_current_parameters.total_count--;
		}
		g_current_parameters.current_count = 0;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;
		if ((g_current_parameters.current_operation == FLASH_CUR_CF_BGO_WRITE)
				|| (g_current_parameters.current_operation
						== FLASH_CUR_DF_BGO_WRITE)) {
			return err;
		}
		if (*src_start_address < FLASH_DF_BLOCK_INVALID) {
			g_current_parameters.wait_cnt = WAIT_MAX_DF_WRITE;
		} else {
			g_current_parameters.wait_cnt = WAIT_MAX_ROM_WRITE;
		}

		while (1 != FLASH.FSTATR.BIT.FRDY) {
			if (g_current_parameters.wait_cnt-- <= 0) {
				flash_stop();
				return FLASH_ERR_TIMEOUT;
			}
		}

		if (0 != FLASH.FASTAT.BIT.CMDLK) {
			if ((0x0001 & FLASH.FPESTAT.WORD)
					&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_LOCKBIT_SET;
			} else if ((0x0002 & FLASH.FPESTAT.WORD)
					&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_FAILURE;
			} else {
				err = FLASH_ERR_CMD_LOCKED;
			}
			return err;
		}
	}

	return err;
}

flash_err_t flash_lockbit_read(flash_block_address_t block_address,
		flash_res_t *lock_state) {
	flash_err_t err = FLASH_SUCCESS;
	volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

	if (((block_address > FLASH_CF_BLOCK_0)
			|| (block_address <= FLASH_CF_BLOCK_INVALID))) {
		return FLASH_ERR_ADDRESS;
	}

	if ((block_address >= FLASH_CF_BLOCK_7)
			&& ((block_address & (FLASH_CF_SMALL_BLOCK_SIZE - 1)) != 0)) {
		return FLASH_ERR_BOUNDARY;
	} else if ((block_address < FLASH_CF_BLOCK_7)
			&& ((block_address & (FLASH_CF_MEDIUM_BLOCK_SIZE - 1)) != 0)) {
		return FLASH_ERR_BOUNDARY;
	}

	if (FLASH_SUCCESS != flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH)) {
		return FLASH_ERR_FAILURE;
	}

	if (g_current_parameters.bgo_enabled_cf == true) {
		g_current_parameters.current_operation = FLASH_CUR_CF_BGO_READ_LOCKBIT;
	}

	FLASH.FSADDR.LONG = block_address;
	/*Issue two part Lockbit Read commands*/
	*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_LOCK_BIT_READ;
	*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

	if (g_current_parameters.bgo_enabled_cf == true) {
		return err;
	}
	/* Read FRDY bit until it has been set to 1 indicating that the current
	 * operation is complete.*/
	while (1 != FLASH.FSTATR.BIT.FRDY) {
		/* Wait until FRDY is 1 unless timeout occurs. */
		if (wait_cnt-- <= 0) {
			/* if FRDY is not set to 1 after max timeout, issue the stop command and reset*/
			err = FLASH_ERR_TIMEOUT;
			flash_reset();
			return err;
		}
	}
	if (0 != FLASH.FASTAT.BIT.CMDLK) {
		flash_reset();
		err = FLASH_ERR_CMD_LOCKED;
		return err;
	} else {
		if (0x01 == FLASH.FLKSTAT.BYTE) {
			*lock_state = FLASH_RES_LOCKBIT_STATE_NON_PROTECTED;
		} else {
			*lock_state = FLASH_RES_LOCKBIT_STATE_PROTECTED;
		}

		/*Transition to read mode*/
		err = flash_pe_mode_exit();
	}

	return err;
}

flash_err_t flash_api_lockbit_set(flash_block_address_t block_address,
		uint32_t num_blocks) {
	flash_err_t err;

	if (((block_address > FLASH_CF_BLOCK_0)
			|| (block_address <= FLASH_CF_BLOCK_INVALID))) {
		return FLASH_ERR_ADDRESS;
	}

	if ((num_blocks > FLASH_NUM_BLOCKS_CF) || (num_blocks <= 0)) {
		return FLASH_ERR_BLOCKS;
	}

	err = check_cf_block_total(block_address, num_blocks);
	if (err != FLASH_SUCCESS) {
		return err;     // block_address + num_blocks out of range
	}

	if (FLASH_SUCCESS != flash_lock_state(FLASH_LOCK_BIT)) {
		return FLASH_ERR_BUSY;
	}

	err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
	if (FLASH_SUCCESS != err) {
		return (err);
	}

	g_current_parameters.current_operation = FLASH_CUR_LOCKBIT_SET;

	err = flash_lockbit_write(block_address, num_blocks);
	if (FLASH_SUCCESS != err) {
		flash_reset();
	}

	flash_pe_mode_exit();
	flash_release_state();

	return err;
}
flash_err_t flash_lockbit_write(flash_block_address_t block_address,
		uint32_t num_blocks) {
	flash_err_t err = FLASH_SUCCESS;
	volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

	if (g_current_parameters.bgo_enabled_cf == true) {
		g_current_parameters.current_operation = FLASH_CUR_CF_BGO_WRITE_LOCKBIT;
	}

	g_current_parameters.dest_addr = block_address;
	g_current_parameters.total_count = num_blocks;

	for (g_current_parameters.current_count = 0;
			g_current_parameters.current_count
					< g_current_parameters.total_count;
			g_current_parameters.current_count++) {
		FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_LOCK_BIT_PGM;
		*g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

		if (g_current_parameters.bgo_enabled_cf == true) {
			return err;
		}
		while (1 != FLASH.FSTATR.BIT.FRDY) {
			if (wait_cnt-- <= 0) {
				flash_stop();
				return FLASH_ERR_TIMEOUT;
			}
		}
		if (0 != FLASH.FASTAT.BIT.CMDLK) {
			if ((0x0001 & FLASH.FPESTAT.WORD) // error due to lockbit on write or erase
			&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_LOCKBIT_SET;
			} else if ((0x0002 & FLASH.FPESTAT.WORD) // error due to non-lockbit error
			&& ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR))) {
				err = FLASH_ERR_FAILURE;
			} else {
				err = FLASH_ERR_CMD_LOCKED;
			}
			return err;
		}

		/* Decrement to start address of next CF block */
		if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7) {
			g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
		} else {
			g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
		}
	}
	return err;
}
flash_err_t flash_reset() {
	if (FLASH.FASTAT.BIT.CFAE == 1) {
		FLASH.FASTAT.BIT.CFAE = 0;
	}
	if (FLASH.FASTAT.BIT.DFAE == 1) {
		FLASH.FASTAT.BIT.DFAE = 0;
	}
	if (g_flash_state == FLASH_READY) {
		flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
	}

	flash_stop();

	FLASH.FENTRYR.WORD = 0xAA00;
	while (FLASH.FENTRYR.WORD != 0x0000)
		;

	return FLASH_SUCCESS;
}

#endif  // FLASH_TYPE_3

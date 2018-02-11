/********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2014 Renesas Electronics Corporation. All rights reserved.
********************************************************************************************************************/
/*******************************************************************************************************************
* File Name : r_flash_type3.c
* Description  : This module implements the Flash API control commands for the RX64M/71M
********************************************************************************************************************/
/*******************************************************************************************************************
* History : DD.MM.YYYY Version Description
*         : 02.18.2014 1.10    Support for RX64M
*           19.12.2014 1.20    Replaced some equate names for FLASH_TYPE_3.
*           20.05.2016 1.30    Added BGO write/erase/blankcheck interrupt operation
*                              Fixed FLASH_CMD_LOCKBIT_DISABLE/ENABLE operation.
*           25.05.2016 1.31    Added BGO lockbit read/write interrupt operation
*           13.06.2016 1.40    Fixed timeouts on flash erase and write.
*           10.08.2016 1.50    Cleaned up flash_fcuram_codecopy() function.
*                              Removed setting of flash lock state just before switch in flash_api_control()
*                                which caused CMD_GET_STATUS to always return BUSY.
*                              Added #if to exclude ISR code when not in BGO mode.
*           12.08.2016 2.00    Modified for BSPless operation.
*           17.11.2016 2.10    Fixed flash_reset() so enters PE mode before issuing a flash_stop()
*                                when in idle state.
*                              Fixed bug where locking multiple blocks would exit in BGO before operation completed.
*                              Fixed bug where driver was not locked in flash_api_lockbit_set().
*                              Fixed bug where interrupt was not handled properly when an internal flash_stop()
*                                was issued.
*                              Fixed bug where rounding was not handled in flash_clock_config().
*                              Fixed bug where where Open() did not check if another operation was in progress
*                                when in BGO mode.
*                              Fixed bug where #if not set properly for FLASH_CFG_CODE_FLASH_ENABLE set to 0.
*                              Moved flash_api_control() and flash_api_lockbit_set() into FRAM so will work when
*                                FLASH_CFG_CODE_FLASH_ENABLE is 1.
*                              Added CF and DF block boundary check to flash_api_erase().
*                              Added DF minimum program size boundary check to flash_api_blankcheck().
*                              Added argument present check for FLASH_CMD_LOCKBIT_READ, FLASH_CMD_LOCKBIT_WRITE, and
*                                FLASH_CMD_CONFIG_CLOCK.
*                              Added CF block boundary check to flash_api_lockbit_read() and flash_api_lockbit_set().
*                              Added check that start address + number blocks does not exceed legal address range
*                                for flash_api_erase(), flash_api_lockbit_set().
*                              Added check that callback function is set in BGO mode for flash_api_blankcheck(),
*                                flash_api_erase(), flash_api_write() and flash_api_control() for FLASH_CMD_LOCKBIT_READ
*                                and FLASH_CMD_LOCKBIT_WRITE.
********************************************************************************************************************/

/********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
********************************************************************************************************************/
/* Includes board and MCU related header files. */
#include "../r_flash_rx_if.h"
#if (FLASH_TYPE == FLASH_TYPE_3)
#include <machine.h>
#include <string.h>     // memcpy()

/* Configuration for this package. */
#include "../r_flash_rx_config.h"

/* Private header file for this package. */
#include "r_flash_type3_if.h"

/* include definition for NULL*/
#include <stddef.h>


/******************************************************************************
Typedef definitions
******************************************************************************/
/* These typedefs are used for guaranteeing correct accesses to memory. When
   working with the FCU sometimes byte or word accesses are required. */
typedef __evenaccess volatile uint8_t  * FCU_BYTE_PTR;
typedef __evenaccess volatile uint16_t * FCU_WORD_PTR;
typedef __evenaccess volatile uint32_t * FCU_LONG_PTR;

typedef enum
{
    FLASH_LOCKBIT_MODE_NORMAL,
    FLASH_LOCKBIT_MODE_OVERRIDE,
    FLASH_LOCKBIT_MODE_END_ENUM
} lkbit_mode_t;


/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
#define FLASH_RETURN_IF_PCFG_NULL   if ((pcfg == NULL) || (pcfg == FIT_NO_PTR))     \
                                    {                                               \
                                        return FLASH_ERR_NULL_PTR;                  \
                                    }
#else
#define FLASH_RETURN_IF_PCFG_NULL   // parameter checking disabled
#endif

#if (((FLASH_CFG_CODE_FLASH_ENABLE == 1) && (FLASH_CFG_CODE_FLASH_BGO == 1)) || FLASH_CFG_DATA_FLASH_BGO)
#define FLASH_RETURN_IF_BGO_AND_NO_CALLBACK     if ((flash_ready_isr_handler == FIT_NO_FUNC) || (flash_ready_isr_handler == NULL))  \
                                                {                                                                                   \
                                                    return FLASH_ERR_FAILURE;                                                       \
                                                }
#else
#define FLASH_RETURN_IF_BGO_AND_NO_CALLBACK     // in blocking mode (non-BGO)
#endif

#define FCU_COMMAND_AREA          (0x007E0000)
#define FCU_FIRMWARE_STORAGE_AREA (0xFEFFF000)
#define FCU_RAM_AREA              (0x007F8000)
#define FCU_RAM_SIZE              (4096)

/*FACI Commands*/
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


/* The number of loops to wait for FENTRYR timeout. */
#define FLASH_FENTRYR_TIMEOUT   (4)

/* The maximum timeout for commands is 100usec when FCLK is 16 MHz i.e. 1600 FCLK cycles.
 * Assuming worst case of ICLK at 120 MHz and FCLK at 4 MHz, and optimization set to max such that
 * each count decrement loop takes only 5 cycles, then ((120/4)*1600)/5 = 9600 */
#define FLASH_FRDY_CMD_TIMEOUT          (9600)

/*Time that it would take for the Data Buffer to be empty (DBFULL Flag) is 90 FCLK cycles.
 * Assuming worst case of ICLK at 120 MHz and FCLK at 4 MHz, and optimization set to max such that
 * each count decrement loop takes only 5 cycles, then ((120/4)*90)/5 = 540 */
#define FLASH_DBFULL_TIMEOUT (540)


/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
FCU_BYTE_PTR g_pfcu_cmd_area = (uint8_t*) FCU_COMMAND_AREA;


flash_err_t flash_init();
flash_err_t flash_clock_config(uint32_t);
flash_err_t flash_fcuram_codecopy();
flash_err_t flash_reset();
flash_err_t flash_stop();
flash_err_t flash_interrupt_config(bool state, void *pCallback);
flash_err_t flash_api_lockbit_set(flash_block_address_t block_address, uint32_t num_blocks);
flash_err_t flash_lockbit_write(flash_block_address_t block_address, uint32_t num_blocks);
flash_err_t flash_lockbit_read(flash_block_address_t block_address, flash_res_t *lock_state_result);
flash_err_t flash_lockbit_ignore(bool state);
flash_err_t flash_pe_mode_enter(flash_type_t flash_type);
flash_err_t flash_pe_mode_exit();
flash_err_t flash_erase(uint32_t block_address, uint32_t block_count);
flash_err_t flash_write(uint32_t *src_start_address, uint32_t * dest_start_address, uint32_t *num_bytes);
flash_err_t flash_blankcheck(uint32_t start_address, uint32_t num_bytes, flash_res_t *blank_check_result);
flash_err_t flash_lock_state (flash_states_t new_state);
flash_err_t flash_get_status (void);
void flash_release_state (void);
flash_err_t check_cf_block_total(flash_block_address_t block_start_address, uint32_t num_blocks);


/* State variable for the Flash API. */
extern flash_states_t g_flash_state;
lkbit_mode_t g_lkbit_mode = FLASH_LOCKBIT_MODE_NORMAL;

flash_int_cb_args_t g_flash_int_ready_cb_args;   // Callback argument structure for flash READY interrupt
flash_int_cb_args_t g_flash_int_error_cb_args;   // Callback argument structure for flash ERROR interrupt



/***********************************************************************************************************************
* Function Name: flash_api_open
* Description  : Function will initialize the flash for the RX64M.
* Arguments    : void
* Return Value : FLASH_SUCCESS -
*                    API initialized successfully.
*                FLASH_ERR_BUSY
*                    API has already been initialized and another operation is ongoing.
*                FLASH_ERR_FAILURE
*                    Initialization failed.
*                    A RESET was performed on the Flash circuit to rectify any internal errors
***********************************************************************************************************************/
flash_err_t flash_api_open(void)
{
    flash_err_t err;
#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
    if ((MCU_CFG_FCLK_HZ > 60000000) || (MCU_CFG_FCLK_HZ < 4000000))
    {
        return FLASH_ERR_FREQUENCY;
    }
#endif
    /* Allow Initialization if not initialized or
     * if no operation is ongoing and re-initialization is desired */
    if (FLASH_SUCCESS != flash_lock_state(FLASH_INITIALIZATION))
    {
        /* API already initialized */
        return FLASH_ERR_BUSY;
    }

    err = flash_init();
    if (FLASH_SUCCESS != err)
    {
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


/*All the functions below need to be placed in RAM if Code Flash programming is to be supported*/
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#pragma section FRAM
#endif

/***********************************************************************************************************************
* Function Name: flash_api_write
* Description  : Function will write to the specified Code or Data Flash memory area.
*      The
*      The function will not perform a blank check before proceeding with
*      the write operation.
* Arguments    : uint32_t src_address -
*                 Source buffer address.
*                uint32_t dest_address -
*                 Destination address.
*                uint32_t num_bytes
*                 Number of bytes to be written
* Return Value : FLASH_SUCCESS -
*                    Write completed successfully; successfully initialized in case of BGO mode.
*                FLASH_ERR_FAILURE -
*                    No callback function set when in BGO mode.
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range or is 0 or is not a valid multiple of the minimum programming
*                    size for the specified flash
*                FLASH_ERR_ADRRESS -
*                    src/dest address is an invalid Code/Data Flash block start address or
*                    address is not aligned with the minimum programming size for the Code/Data Flash
*                    For Code Flash programming the src address HAS to be a RAM address since ROM cannot be accessed
*                    during Code Flash programming
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation or not initialized
*                FLASH_ERR_CMD_LOCKED -
*                    The FCU entered a command locked state and cannot process the operation.
*                    A RESET was performed on the FCU to recover from this state.
*                FLASH_ERR_LOCKBIT_SET
*                    Operation failed because the lockbit was set.
*                    A RESET was performed on the FCU to recover from this state.
*                FLASH_ERR_FAILURE
*                    Code Flash Write operation attempted in BGO mode. This is temporarily not supported
*                    Operation failed for some other reason; RESET was performed on the FCU to recover from this state.
***********************************************************************************************************************/
flash_err_t flash_api_write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes)
{
    flash_err_t err;

#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
    /*See if number of bytes is non-zero*/
    if (num_bytes == 0)
    {
        return FLASH_ERR_BYTES;
    }
#endif

    FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }
    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }

    /*Check address validity and that it is on a Code Flash programming boundary*/
    // Ensure start address is valid and on 256 (for CF) byte boundary
    if (((dest_address > (uint32_t)FLASH_CF_BLOCK_INVALID)) &&  (!(dest_address & (FLASH_CF_MIN_PGM_SIZE-1))))
    {
         /*Check if there is enough space in the destination, and that num_bytes is a multiple of programming size*/
         if ((num_bytes-1 + (dest_address) > (uint32_t)FLASH_CF_BLOCK_END) ||
             (num_bytes & (FLASH_CF_MIN_PGM_SIZE-1)) ||
             (num_bytes-1 + (dest_address) < (uint32_t)FLASH_CF_BLOCK_INVALID))        // Overflowed

        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            if (g_current_parameters.bgo_enabled_cf == true)
            {
                g_current_parameters.current_operation = FLASH_CUR_CF_BGO_WRITE;
            }
            else
            {
                g_current_parameters.current_operation = FLASH_CUR_CF_WRITE;
                g_current_parameters.wait_cnt = WAIT_MAX_ROM_WRITE;
            }
            g_current_parameters.min_pgm_size = (FLASH_CF_MIN_PGM_SIZE >> 1);
            /*There are no parameter errors. Switch to the CF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
        }

    }
    /*Check address validity and that it is on a Data Flash programming boundary*/
    else if (((dest_address >= FLASH_DF_BLOCK_0) && (dest_address < FLASH_DF_BLOCK_INVALID ))
            &&
            (!(dest_address & (FLASH_DF_MIN_PGM_SIZE-1))))
    {
        /*Check if there is enough space in the destination, and that num_bytes is a multiple of programming size*/
        if ((num_bytes + (dest_address) > FLASH_DF_BLOCK_INVALID) || (num_bytes & (FLASH_DF_MIN_PGM_SIZE-1)))
        {
            err = FLASH_ERR_BYTES;
        }
        else
        {
            if (g_current_parameters.bgo_enabled_df == true)
            {
                g_current_parameters.current_operation = FLASH_CUR_DF_BGO_WRITE;
            }
            else
            {
                g_current_parameters.current_operation = FLASH_CUR_DF_WRITE;
            }
            g_current_parameters.wait_cnt = WAIT_MAX_DF_WRITE;
            g_current_parameters.min_pgm_size = (FLASH_DF_MIN_PGM_SIZE >> 1);
            /*There are no parameter errors. Switch to the DF PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
        }
    }
    else
    {
        err = FLASH_ERR_ADDRESS;
    }
    /*If parameters passed are not valid or there was an error entering PE mode,
     * then release the state and return the error condition*/
    if (FLASH_SUCCESS != err)
    {
        flash_release_state();
        return err;
    }

    /*Write the data*/
    err = flash_write(&src_address, &dest_address, &num_bytes);
    if (FLASH_SUCCESS != err)
    {
        /*If there is an error, then reset the FCU: This will clear error flags and exit the P/E mode*/
        flash_reset();
        /*Release the lock*/
        flash_release_state();
        return err;
    }

    /*If in non-BGO mode, then current operation is completed.
     * Exit from PE mode and return status*/
    if ((g_current_parameters.current_operation == FLASH_CUR_CF_WRITE)
            ||
            (g_current_parameters.current_operation == FLASH_CUR_DF_WRITE))
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the FCU: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to idle*/
        flash_release_state();
    }

    /*If BGO is enabled, then
     *return result of started Write process*/
    return err;
}


/***********************************************************************************************************************
* Function Name: flash_api_erase
* Description  : Function will erase the specified Code or Data Flash blocks.
* Arguments    : uint32_t block_start_address -
*                 Start address of the first block. Actual address or entry from "flash_block_address_t" enum can be used
*                uint32_t num_blocks -
*                 Number of blocks to erase.
* Return Value : FLASH_SUCCESS -
*                    Erase completed successfully; successfully initialized in case of BGO mode.
*                FLASH_ERR_FAILURE -
*                    No callback set when in BGO mode.
*                FLASH_ERR_BLOCKS -
*                    Number of blocks exceeds max range or is 0
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Code/Data Flash block start address
*                FLASH_ERR_BOUNDARY -
*                    Start address is not on a block boundary.
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation
*                FLASH_ERR_CMD_LOCKED
*                    The FCU entered a command locked state and cannot process the operation.The function performed a
*                    RESET on the peripheral to recover from this state.
*                FLASH_ERR_FAILURE
*                    Code Flash Erase operation attempted in BGO mode. This is temporarily not supported
***********************************************************************************************************************/
flash_err_t flash_api_erase(flash_block_address_t block_start_address, uint32_t num_blocks)
{
    flash_err_t err;

    FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }
    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }
#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)

#endif
    /*Check address and num_blocks validity and switch to Code Flash or Data Flash P/E mode*/
    if ((block_start_address <= FLASH_CF_BLOCK_0) && (block_start_address > FLASH_CF_BLOCK_INVALID))
    {
        if ((num_blocks > FLASH_NUM_BLOCKS_CF) || (num_blocks <= 0))
        {
            err = FLASH_ERR_BLOCKS;
        }
        else if ((err=check_cf_block_total(block_start_address, num_blocks)) == FLASH_SUCCESS)
        { /*No errors in parameters. Enter Code Flash PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
            if (g_current_parameters.bgo_enabled_cf == true)
            {
                g_current_parameters.current_operation = FLASH_CUR_CF_BGO_ERASE;
            }
            else
            {
                g_current_parameters.current_operation = FLASH_CUR_CF_ERASE;
            }
        }
    }
    else if ((block_start_address >= FLASH_DF_BLOCK_0) && (block_start_address < FLASH_DF_BLOCK_INVALID ))
    {
        if ((num_blocks > FLASH_NUM_BLOCKS_DF) || (num_blocks <= 0))
        {
            err = FLASH_ERR_BLOCKS;
        }
        else if ((block_start_address & (FLASH_DF_BLOCK_SIZE-1)) != 0)
        {
            err = FLASH_ERR_BOUNDARY;
        }
        else if ((block_start_address + (num_blocks * FLASH_DF_BLOCK_SIZE) - 1) >= FLASH_DF_BLOCK_INVALID)
        {
            err = FLASH_ERR_BLOCKS;
        }
        else
        { /*No errors in parameters. Enter Data Flash PE mode*/
            err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
            if (g_current_parameters.bgo_enabled_df == true)
            {
                g_current_parameters.current_operation = FLASH_CUR_DF_BGO_ERASE;
            }
            else
            {
                g_current_parameters.current_operation = FLASH_CUR_DF_ERASE;
            }
        }
    }
    else
    {
        err = FLASH_ERR_ADDRESS;
    }

    if (FLASH_SUCCESS != err)
    {
        flash_release_state();
        return err;
    }

    /*Lock Bit protection not checked here
     * User Should configure it before calling function*/

    /*Erase the Blocks*/
    err = flash_erase((uint32_t)block_start_address, num_blocks);
    if (FLASH_SUCCESS != err)
    {
        /*If there is an error, then reset the FCU: This will clear error flags and exit the P/E mode*/
        flash_reset();
        flash_release_state();
        return err;
    }

    /*If in non-BGO mode, then current operation is completed.
     * Exit from PE mode and return status*/
    if ((g_current_parameters.current_operation == FLASH_CUR_CF_ERASE)
            ||
            (g_current_parameters.current_operation == FLASH_CUR_DF_ERASE))
    {
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        if (FLASH_SUCCESS != err)
        {
            /*Reset the FCU: This will stop any existing processes and exit PE mode*/
            flash_reset();
        }
        /*Release lock and reset the state to Idle*/
        flash_release_state();
    }
    /*If BGO is enabled, then return result of started Erase process*/
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
flash_err_t check_cf_block_total(flash_block_address_t block_start_address, uint32_t num_blocks)
{
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#if FLASH_ERASE_ASCENDING_BLOCK_NUMS
#if FLASH_CFG_PARAM_CHECKING_ENABLE
    uint32_t    tmp, cf_block_size;


    /* Legal number of blocks. See if start address is on block boundary */
    cf_block_size = (block_start_address >= FLASH_CF_BLOCK_7) ? FLASH_CF_SMALL_BLOCK_SIZE : FLASH_CF_MEDIUM_BLOCK_SIZE;
    if ((block_start_address & (cf_block_size - 1)) != 0)
    {
        return FLASH_ERR_ADDRESS;
    }


    /* See if valid (does not go pass address boundary */

    if (block_start_address >= FLASH_CF_BLOCK_7)
    {
        /* set tmp = available number of small blocks to erase */
        tmp = ((block_start_address - FLASH_CF_BLOCK_7) / FLASH_CF_SMALL_BLOCK_SIZE) + 1;
        /* set num_blocks = number of large blocks to erase */
        num_blocks -= (tmp < num_blocks) ? tmp : num_blocks;
        /* adjusted start address for number of large blocks to erase */
        block_start_address = FLASH_CF_BLOCK_8;
    }

    /* set num_blocks = large blocks to erase below start address */
    num_blocks--;
    /* determine if num_blocks goes pass address limit */
    if ((block_start_address - (num_blocks*FLASH_CF_MEDIUM_BLOCK_SIZE)) <= (uint32_t)FLASH_CF_BLOCK_INVALID)
    {
        return FLASH_ERR_BLOCKS;
    }
#endif  // param checking
#endif  // ascending block numbers
    return FLASH_SUCCESS;
#else   // code flash disabled
    return FLASH_ERR_FAILURE;
#endif
}

#pragma section // end section FRAM

/***********************************************************************************************************************
* Function Name: flash_api_blankcheck
* Description  : Function will perform a blank check on the specified Data Flash area.
*                The function will incrementally check the area from the start address onward.
*                The minimum number of bytes is 4 and max is 65536 with increments in 4 byte units.
* Arguments    : uint32_t address -
*                 Start address to perform blank check. Actual address or entry from "flash_block_address_t" enum can be used
*                uint32_t num_blocks -
*                 Number of bytes to perform blank check operation for.
*                flash_res_t *result
*                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
*                 operation
* Return Value : FLASH_SUCCESS
*                 Operation was completed successfully
*                FLASH_ERR_FAILURE -
*                    In BGO mode and no callback function was set.
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range (1-65535) or is not a multiple of 4
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Data Flash Address
*                FLASH_ERR_BOUNDARY -
*                    Start address is not a multiple of the DF minimum program size.
*                FLASH_ERR_LOCKED -
*                    The FCU is in a command locked state and cannot process the operation.The function performed a
*                    RESET on the peripheral to recover from this state.
*                FLASH_ERR_BUSY
*                    Flash peripheral is busy with another operation or not initialized
***********************************************************************************************************************/
flash_err_t flash_api_blankcheck(uint32_t address, uint32_t num_bytes, flash_res_t *result)
{
    flash_err_t err = FLASH_SUCCESS;

    FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }
    /*Grab the current flash state*/
    if (FLASH_SUCCESS != flash_lock_state(FLASH_WRITING))
    {
        /* API busy with another operation*/
        return FLASH_ERR_BUSY;
    }

#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
    if (((address >= FLASH_DF_BLOCK_0) && (address < FLASH_DF_BLOCK_INVALID )))
    {
        /*Check if the range is valid, num_bytes is a multiple of 4, is larger than 0 and less than 65536*/
        if (((num_bytes + address) > FLASH_DF_BLOCK_INVALID)
          || (num_bytes & (FLASH_DF_MIN_PGM_SIZE-1))
          || (num_bytes == 0)
          || (num_bytes > 65536))
        {
            err = FLASH_ERR_BYTES;
        }
        else if ((address & (FLASH_DF_MIN_PGM_SIZE-1)) != 0)
        {
            err = FLASH_ERR_BOUNDARY;
        }
    }
    else
    {
        err = FLASH_ERR_ADDRESS;

    }
#endif

    if (FLASH_SUCCESS != err)
    {
        flash_release_state();
        return err;
    }

    if (g_current_parameters.bgo_enabled_df == true)
    {
        g_current_parameters.current_operation = FLASH_CUR_DF_BGO_BLANKCHECK;
    }
    else
    {
        g_current_parameters.current_operation = FLASH_CUR_DF_BLANKCHECK;
    }

    /*WAIT_MAX_BLANK_CHECK specifies the wait time for a 4 byte blank check,
     * num_bytes is divided by 4 and then multiplied to calculate the wait time for the entire operation*/
    g_current_parameters.wait_cnt = (WAIT_MAX_BLANK_CHECK * (num_bytes >> 2));

    err = flash_pe_mode_enter(FLASH_TYPE_DATA_FLASH);
    /*If there is an error, then reset the FCU: This will clear error flags and exit the P/E mode*/
    if (FLASH_SUCCESS != err)
    {
        flash_reset();
        flash_release_state();
        return err;
    }

    /*Initialize the result*/
    *result = FLASH_RES_INVALID;

    /*Start the Erase operation*/
    err = flash_blankcheck(address, num_bytes, result);
    if (g_current_parameters.bgo_enabled_df == false)
    {
        /*If the return condition of the blank-check operation is not FLASH_SUCCESS then  reset the FCU*/
        if (FLASH_SUCCESS != err)
        {
            flash_reset();
            flash_release_state();
            return err;
        }
        /*Return to read mode*/
        err = flash_pe_mode_exit();
        /*Reset the state to Idle*/
        g_current_parameters.current_operation = FLASH_CUR_IDLE;
        /*If the exit from PE mode is not successful, return the failure code,
         * else return the result of the blank_check*/
        if (FLASH_SUCCESS != err)
        {
            flash_reset();
        }
        flash_release_state();
    }
    /*If BGO is enabled, then
     *return result of started BlankCheck process*/
    return err;

}

/***********************************************************************************************************************
 * Function Name: flash_blankcheck
 * Description  : Function checks if the specified Data Flash address range is blank
 * Arguments    : uint32_t address -
 *                 Start address to perform blank check. Actual address or entry from "flash_block_address_t" enum can be used
 *                uint32_t num_blocks -
 *                 Number of bytes to perform blank check operation for.
 *                flash_res_t *result
 *                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
 *                  operation
 * Return Value : FLASH_ERR_TIMEOUT
 *                Operation timed out. The function issued a STOP to reset the peripheral.
 *                FLASH_ERR_LOCKED
 *                Peripheral in locked state.
 *                FLASH_ERR_FAILURE
 *                Operation failure
 *                FLASH_SUCCESS
 *                Operation started successfully (BGO)
 *                Operation completed (non-BGO)
 * Notes     :   -When using Code Flash in BGO mode, this function must be run from RAM or from the
 *                separate flash block for MCUs that are larger than 2MB. It can be run from ROM if
 *                only a Data Flash operation is ongoing.
 *               -The timeout condition is calculated based on the spec that each 4 byte blank check
 *                operation takes a max of 30 usec
 ***********************************************************************************************************************/
flash_err_t flash_blankcheck(uint32_t start_address, uint32_t num_bytes, flash_res_t *result)
{
  flash_err_t err = FLASH_SUCCESS;

  /*Set the mode to incremental*/
  FLASH.FBCCNT.BYTE = 0x00;
  /*Set the start address for blank checking*/
  FLASH.FSADDR.LONG = start_address;
  /*Set the end address for blank checking*/
  FLASH.FEADDR.LONG = (start_address + num_bytes - 1);
  /*Issue two part Blank Check command*/
  *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLANK_CHECK;
  *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

  /*if in DF BGO mode, exit here; remaining processing if any will be done in ISR*/
  if (g_current_parameters.bgo_enabled_df == true)
  {
    return err;
  }
  /* Read FRDY bit until it has been set to 1 indicating that the current
   * operation is complete.*/
  while (1 != FLASH.FSTATR.BIT.FRDY)
  {
    /* Wait until FRDY is 1 unless timeout occurs. */
    if (g_current_parameters.wait_cnt-- <= 0)
    {
      /* if FRDY is not set to 1 after max timeout, issue the stop command*/
      err = flash_stop();
      /*If the STOP was not successfully issued, then return the error value for the stop action
       * Otherwise return the FLASH_ERR_TIMEOUT error*/
      if (FLASH_SUCCESS != err)
      {
        return err;
      }
      else
      {
        return FLASH_ERR_TIMEOUT;
      }

    }
  }

  /*Check if there were any errors
   * Check if Command Lock bit is set*/
  if (0 != FLASH.FASTAT.BIT.CMDLK)
  {
    if ((0x0002 & FLASH.FPESTAT.WORD)
        && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
    {
      err = FLASH_ERR_FAILURE;
    }
    else
    {
      err = FLASH_ERR_CMD_LOCKED;
    }
    return err;
  }
  if (FLASH.FBCSTAT.BYTE == 0x01)
  {
    *result = FLASH_RES_NOT_BLANK;
  }
  else
  {
    *result = FLASH_RES_BLANK;
  }

  return err;
}


/***********************************************************************************************************************
 * Function Name: flash_init
 * Description  : Function will initialize the FCU, copy the FCU firmware to FCURAM and
 *                set the FCU Clock based on the current FCLK frequency
 * Arguments    :
 * Return Value : FLASH_SUCCESS -
 *                    Peripheral Initialized successfully.
 *                FLASH_ERR_TIMEOUT
 *                  Timed out while attempting to switch to P/E mode or
 *                  while trying to issue a STOP or an ongoing flash operation timed out.
 *                FLASH_ERR_LOCKED
 *                 Switch to Read mode timed out and STOP was attempted to recover. Stop operation failed.
 *                 Peripheral in locked state.
 ***********************************************************************************************************************/
flash_err_t flash_init()
{

  flash_err_t err = FLASH_SUCCESS;

  g_current_parameters.current_operation = FLASH_CUR_FCU_INIT;
  /*Allow Access to the Flash registers*/
  FLASH.FWEPROR.BYTE = 0x01;
  /*Set the Clock*/
  FLASH.FPCKAR.WORD = ((0x1E00) + ((MCU_CFG_FCLK_HZ/1000000)));
  /*Copy the FCU firmware to FCU RAM*/
  err = flash_fcuram_codecopy();
  return err;
}
/***********************************************************************************************************************
 * Function Name: flash_fcuram_codecopy
 * Description  : Function will copy FCU firmware to the FCURAM.
 * Arguments    :
 * Return Value : FLASH_SUCCESS -
 *                    Code copied successfully.
 *                FLASH_ERR_TIMEOUT
 *                  Timed out while attempting to switch to P/E mode or while trying to issue a STOP or
 *                   an ongoing flash operation timed out.
 *                FLASH_ERR_LOCKED
 *                 Switch to Read mode timed out and STOP was attempted to recover. Stop operation failed.
 *                 Peripheral in locked state.
 *                FLASH_ERR_FAILURE
 *                 Unable to enter PE mode
 ***********************************************************************************************************************/

flash_err_t flash_fcuram_codecopy()
{
  uint8_t * p_src;
  uint8_t * p_dest;
  volatile int32_t wait_cnt;      // Timeout counter.

  p_src = (uint8_t*) FCU_FIRMWARE_STORAGE_AREA;
  p_dest = (uint8_t*) FCU_RAM_AREA;

  if (FLASH.FENTRYR.WORD != 0x0000)
  {
    /*Enter Read Mode*/
    FLASH.FENTRYR.WORD = 0xAA00;
    /* Initialize timeout for FENTRYR being written. */
    wait_cnt = FLASH_FENTRYR_TIMEOUT;

    /* Read FENTRYR to ensure it has been set to 0. Note that the top byte
     of the FENTRYR register is not retained and is read as 0x00. */
    while (0x0000 != FLASH.FENTRYR.WORD) {
      /* Wait until FENTRYR is 0 unless timeout occurs. */
      if (wait_cnt-- <= 0)
      {
        /* This should not happen when copying code over to FCURAM.
         * FENTRYR getting written to 0 should  only take 2-4 PCLK cycles.  */
        return FLASH_ERR_TIMEOUT;
      }
    }
  }

  FLASH.FCURAME.WORD = 0xC403;      // FCURAM Access Enabled, High Speed Write Enabled

  /* Copy over the 4K from storage area to FCURAM */
  memcpy(p_dest, p_src, FCU_RAM_SIZE);

  FLASH.FCURAME.WORD = 0xC400;      // FCURAM Access Disabled

  return FLASH_SUCCESS;
}


/***********************************************************************************************************************
 * Function Name: flash_interrupt_config
 * Description  : Function to enable of disable flash interrupts.
 * Arguments    : bool
 *               - true: Enable Interrupts (BGO mode)
 *               - false: Disable interrupts (non-BGO mode)
 *               *pCallback
 *               - Callback function that needs to be called from the ISR in case of an error or after operation
 *               is complete.
 *               - This argument can be a NULL if interrupts are being disabled (non-BGO mode)
 * Return Value : FLASH_SUCCESS -
 *                Interrupts configured successfully.
 *                FLASH_ERR_NULL_PTR -
 *                Invalid callback function pointer passed when enabling interrupts
 * Note     :
 ***********************************************************************************************************************/
flash_err_t flash_interrupt_config(bool state, void *pcfg)
{
  flash_interrupt_config_t *int_cfg = pcfg;

  /*Enable the Interrupts*/
  if (true == state)
  {
    /* Assign the callback if not NULL*/
    if ((NULL == int_cfg->pcallback) || (FIT_NO_FUNC == int_cfg->pcallback))
    {
      return FLASH_ERR_NULL_PTR;
    }
    flash_ready_isr_handler = int_cfg->pcallback;
    flash_error_isr_handler = int_cfg->pcallback;

    FLASH.FAEINT.BYTE = 0x99;
    FLASH.FRDYIE.BYTE = 0x01;
    /*Clear Flash Ready Interrupt Request*/
    IR(FCU,FRDYI)= 0;
    /*Clear Flash Error Interrupt Request*/
    IR(FCU,FIFERR)= 0;
    /*Set Flash Error Interrupt Priority*/
    IPR(FCU,FIFERR)= int_cfg->int_priority;
    /*Set Flash Ready Interrupt Priority*/
    IPR(FCU,FRDYI)= int_cfg->int_priority;
    /*Enable Flash Error Interrupt*/
    IEN (FCU,FIFERR)= 1;
    /*Enable Flash Ready Interrupt*/
    IEN (FCU,FRDYI)= 1;

  }
  /*Disable the Interrupts*/
  else if (false == state)
  {
    FLASH.FAEINT.BYTE = 0x00;
    FLASH.FRDYIE.BYTE = 0x00;
    /*Clear any pending Flash Ready Interrupt Request*/
    IR(FCU,FRDYI) = 0;
    /*Clear any pending Flash Error Interrupt Request*/
    IR(FCU,FIFERR) = 0;
  }

  return FLASH_SUCCESS;
}

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
/*All the functions below need to be placed in RAM if Code Flash programming is to be supported
 * in non-BGO mode*/
#pragma section FRAM
#endif

/***********************************************************************************************************************
* Function Name: flash_api_control
* Description  : This function supports additional configuration operations.
*      The supported commands are listed in the flash_cmd_t enum.
* Arguments    : flash_cmd_t cmd -
*                 command.
*                void *pcfg -
*                 Pointer to configuration. This argument can be NULL for
*                 commands that do not require a configuration.
*
*                Command                                |   Argument
*                FLASH_CMD_RESET------------------------| NULL
*                FLASH_CMD_STATUS_GET-------------------| NULL
*                FLASH_CMD_LOCKBIT_WRITE----------------| flash_lockbit_config_t
*                FLASH_CMD_LOCKBIT_READ-----------------| flash_lockbit_config_t
*                FLASH_CMD_LOCKBIT_ENABLE---------------| NULL
*                FLASH_CMD_LOCKBIT_DISABLE--------------| NULL
*                FLASH_CMD_BGO_ENABLE_DF----------------| void (*pcallback)(void *)
*                FLASH_CMD_BGO_DISABLE_DF---------------| NULL
*                FLASH_CMD_BGO_ENABLE_CF----------------| NULL
*                FLASH_CMD_BGO_DISABLE_CF---------------| void (*pcallback)(void *)
*                FLASH_CMD_CONFIG_CLOCK-----------------| uint32_t *
* Return Value : FLASH_SUCCESS -
*                    Operation completed successfully.
*                FLASH_ERR_FAILURE -
*                    No callback function set when in BGO mode.
*                FLASH_ERR_BYTES -
*                    Number of blocks exceeds max range
*                FLASH_ERR_ADRRESS -
*                    Address is an invalid Code/Data Flash block start address
*                FLASH_ERR_NULL_PTR -
*                    Pointer was NULL for a command that expects a configuration structure
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation or not initialized
*                FLASH_ERR_LOCKED -
*                    The FCU was in a command locked state and has been reset
*                FLASH_ERR_FREQUENCY
*                    Illegal Frequency parameter passed for FLASH_CMD_CONFIG_CLOCK command
***********************************************************************************************************************/
flash_err_t flash_api_control(flash_cmd_t cmd, void *pcfg)
{
    flash_err_t err = FLASH_SUCCESS;
    flash_lockbit_config_t *lockbit_cfg;
    uint32_t *plocal_pcfg;

    /*If the command is to reset the FCU, then no attempt is made to grab the lock
     * before executing the reset since the assumption is that the RESET command
     * is used to terminate any existing operation*/
    if (cmd == FLASH_CMD_RESET)
    {
        err = flash_reset();
        flash_release_state();
        return err;
    }

    /*Check if API is busy*/
    if(g_flash_state != FLASH_READY)
    {
        /* API not initialized or busy with another operation*/
        return FLASH_ERR_BUSY;
    }

    switch (cmd)
    {
        // If BGO (Data Flash or Code Flash) is enabled, then allow user to set a callback isr
#if (FLASH_CFG_CODE_FLASH_BGO == 1)  || (FLASH_CFG_DATA_FLASH_BGO == 1)
        case FLASH_CMD_SET_BGO_CALLBACK:
            err = flash_interrupt_config(true, pcfg);
        break;
#endif

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
        FLASH_RETURN_IF_PCFG_NULL;
        FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;
        lockbit_cfg = pcfg;
        err = flash_lockbit_read(lockbit_cfg->block_start_address, &(lockbit_cfg->result));
        break;
    case FLASH_CMD_LOCKBIT_WRITE:
        FLASH_RETURN_IF_PCFG_NULL;
        FLASH_RETURN_IF_BGO_AND_NO_CALLBACK;
        lockbit_cfg = pcfg;
        err = flash_api_lockbit_set(lockbit_cfg->block_start_address, lockbit_cfg->num_blocks);
        break;
    case FLASH_CMD_CONFIG_CLOCK:
        FLASH_RETURN_IF_PCFG_NULL;
        plocal_pcfg =pcfg;
        if ((*plocal_pcfg >= 4000000) && (*plocal_pcfg <=60000000))
        {
            err = flash_clock_config(*plocal_pcfg);
        }
        else
        {
            err = FLASH_ERR_FREQUENCY;
        }
        break;
    default:
        err = FLASH_ERR_PARAM;
    }
    flash_release_state();
    return err;
}


/***********************************************************************************************************************
 * Function Name: flash_clock_config
 * Description  : Function sets the internal FCu register to the current FCLK frequency
 * Arguments    : uint32_t : Specify current FCLK frequency
 * Return Value : FLASH_SUCCESS -
 *                Switched successfully.
 * NOTE         : Legal values are 4000000 - 60000000 (4 MHz to 60 MHz)
 ***********************************************************************************************************************/
flash_err_t flash_clock_config(uint32_t cur_fclk)
{
    uint32_t    speed_mhz;

    speed_mhz = cur_fclk / 1000000;
    if ((cur_fclk % 1000000) != 0)
    {
        speed_mhz++;    // must round up to nearest MHz
    }

    /*Set the Clock*/
    FLASH.FPCKAR.WORD = (uint16_t)(0x1E00) + (uint16_t)speed_mhz;
    return FLASH_SUCCESS;
}
/***********************************************************************************************************************
 * Function Name: flash_pe_mode_enter
 * Description  : Function switches the peripheral to P/E mode for Code Flash or Data Flash.
 * Arguments    : flash_type_t : Specify Code Flash or Data Flash
 * Return Value : FLASH_SUCCESS -
 *                Switched successfully.
 *                FLASH_ERR_FAILURE -
 *                Unable to Switch to P/E Mode.
 *                FLASH_ERR_PARAM -
 *                Illegal parameter passed
 * NOTE         : This function must run from RAM if Code Flash non-BGO is used
 ***********************************************************************************************************************/
flash_err_t flash_pe_mode_enter(flash_type_t flash_type)
{
    flash_err_t err = FLASH_SUCCESS;

    if (flash_type == FLASH_TYPE_DATA_FLASH)
    {
        FLASH.FENTRYR.WORD = 0xAA80;  //Transition to DF P/E mode
        if (FLASH.FENTRYR.WORD == 0x0080)
        {
            err = FLASH_SUCCESS;
        }
        else
        {
            err = FLASH_ERR_FAILURE;
        }
    }
    else if (flash_type == FLASH_TYPE_CODE_FLASH)
    {
        FLASH.FENTRYR.WORD = 0xAA01;    //Transition to CF P/E mode
        if (FLASH.FENTRYR.WORD == 0x0001)
        {
            err = FLASH_SUCCESS;

            if (g_lkbit_mode == FLASH_LOCKBIT_MODE_OVERRIDE)
            {
                FLASH.FPROTR.WORD = 0x5501;
            }
        }
        else
        {
            err = FLASH_ERR_FAILURE;
        }
    }
    else
    {
        err = FLASH_ERR_PARAM;
    }

  return err;
}


/***********************************************************************************************************************
 * Function Name: flash_pe_mode_exit
 * Description  : Function switches the peripheral from P/E mode for Code Flash or Data Flash to Read mode
 *
 * Arguments    : None.
 * Return Value : FLASH_SUCCESS -
 *                Switched successfully.
 *                FLASH_ERR_TIMEOUT
 *                Operation timed out. Ongoing flash operation failed.
 *                FLASH_ERR_LOCKED
 *                Peripheral in locked state. Operation failed.
 * Notes     :    -When performing Code Flash operations, this function must be run from RAM or from the
 *                separate flash block for MCUs that are larger than 2MB. It can be run from ROM if
 *                only a Data Flash operation is ongoing.
 *                -This function should generally be called only after any current operation is complete.
 *                To allow for the worst case where this function is called immediately after a 32K code Flash
 *                erase operation has started a timeout of 580 ms is used.
 ***********************************************************************************************************************/
flash_err_t flash_pe_mode_exit()
{
  flash_err_t err = FLASH_SUCCESS;
  flash_err_t temp_err = FLASH_SUCCESS;
  /* Timeout counter. */
  volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

  /* Read FRDY bit until it has been set to 1 indicating that the current
   * operation is complete.*/
  while (1 != FLASH.FSTATR.BIT.FRDY)
  {
    /* Wait until FRDY is 1 unless timeout occurs. */
    if (wait_cnt-- <= 0)
    {
      /* if FRDY is not set to 1 after max timeout, return timeout status*/
      return FLASH_ERR_TIMEOUT;
    }
  }

  /*Check if Command Lock bit is set*/
  if (0 != FLASH.FASTAT.BIT.CMDLK)
  {
    /*Issue a Status Clear to clear Command Locked state*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_STATUS_CLEAR;
    temp_err = FLASH_ERR_CMD_LOCKED;
  }

  /*Transition to Read mode*/
  FLASH.FENTRYR.WORD = 0xAA00;
  if (FLASH.FENTRYR.WORD == 0x0000)
  {
    err = FLASH_SUCCESS;
  }
  else
  {
    err = FLASH_ERR_FAILURE;
  }

  /*If a command locked state was detected earlier, then return that error*/
  if (FLASH_ERR_CMD_LOCKED == temp_err)
  {
    return temp_err;
  }
  else
  {
    return err;
  }

}
/***********************************************************************************************************************
 * Function Name: flash_stop
 * Description  : Function issue the STOP command and check the state of the Command Lock bit.
 * Arguments    :
 * Return Value : FLASH_SUCCESS -
 *                Stop issued successfully.
 *                FLASH_ERR_TIMEOUT
 *                Timed out
 *                FLASH_ERR_LOCKED
 *                Peripheral in locked state
 ***********************************************************************************************************************/
flash_err_t flash_stop()
{
  /* Timeout counter. */
  volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

  g_current_parameters.current_operation = FLASH_CUR_STOP;

  /*Issue stop command to flash command area*/
  *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FORCED_STOP;

  /* Read FRDY bit until it has been set to 1 indicating that the current
   * operation is complete.*/
  while (1 != FLASH.FSTATR.BIT.FRDY)
  {
    /* Wait until FRDY is 1 unless timeout occurs. */
    if (wait_cnt-- <= 0)
    {
      /* This should not happen normally.
       * FRDY should get set in 15-20 ICLK cycles on STOP command*/
      return FLASH_ERR_TIMEOUT;
    }
  }
  /*Check that Command Lock bit is cleared*/
  if (0 != FLASH.FASTAT.BIT.CMDLK)
  {
    return FLASH_ERR_CMD_LOCKED;
  }

  return FLASH_SUCCESS;
}

/***********************************************************************************************************************
 * Function Name: flash_erase
 * Description  : Function erases a block of Code or Data Flash
 ** Arguments   : uint32_t block address
 * Return Value : FLASH_SUCCESS -
 *                Block Erased successfully.
 *                FLASH_ERR_TIMEOUT
 *                Erase operation timed out. The function issued a STOP to reset the peripheral.
 *                FLASH_ERR_LOCKED
 *                Erase operation timed out and STOP was attempted to recover. Stop operation failed.
 *                Peripheral in locked state.
 *                FLASH_ERR_LOCKBIT_SET
 *                Failed while trying to erase a block because lockbit was set and lockbit protection was enabled
 *                FLASH_ERR_FAILURE
 *                Erase operation failed for some other reason
 * Notes     :   -When using Code Flash in BGO mode, this function must be run from RAM or from the
 *                separate flash block for MCUs that are larger than 2MB. It can be run from ROM if
 *                only a Data Flash operation is ongoing.
 *              - The timeout condition is set to allow for the worst case erasing time as follows
 *                32KB Code Flash 580 ms
 *                8KB Code Flash  145 ms
 *                64B Data Flash 40 ms
 ***********************************************************************************************************************/
flash_err_t flash_erase(uint32_t block_address, uint32_t num_blocks)
{
  flash_err_t err = FLASH_SUCCESS;

  /*Set current operation parameters */
  g_current_parameters.dest_addr = block_address;
  g_current_parameters.total_count = num_blocks;

  if (g_current_parameters.dest_addr < (uint32_t) FLASH_DF_BLOCK_INVALID)
  {
      g_current_parameters.wait_cnt = WAIT_MAX_ERASE_DF;
  }
  else if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7)
  {
    g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_32K;
  }
  else
  {
    g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_8K;
  }

  /*Set Erasure Priority Mode*/
  FLASH.FCPSR.WORD = 0x0001;
  for (g_current_parameters.current_count = 0;
      g_current_parameters.current_count    < g_current_parameters.total_count;
      g_current_parameters.current_count++)
  {
    /*Set block start address*/
    FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
    /*Issue two part Block Erase commands*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLOCK_ERASE;
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

    /*if in BGO mode, exit here; remaining processing if any will be done in ISR*/
    if ((g_current_parameters.current_operation == FLASH_CUR_CF_BGO_ERASE)
        ||
        (g_current_parameters.current_operation == FLASH_CUR_DF_BGO_ERASE))
    {
      return err;
    }
    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete.*/
    while (1 != FLASH.FSTATR.BIT.FRDY)
    {
      /* Wait until FRDY is 1 unless timeout occurs. */
      if (g_current_parameters.wait_cnt-- <= 0)
      {
        /* if FRDY is not set to 1 after max timeout, issue the stop command*/
        flash_stop();
        return FLASH_ERR_TIMEOUT;
      }
    }

    /*Check if there were any errors
     * Check if Command Lock bit is set*/
    if (0 != FLASH.FASTAT.BIT.CMDLK)
    {
      /*Check if there is a lockbit error*/
      if ((0x0001 & FLASH.FPESTAT.WORD)
          && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
      {
        err = FLASH_ERR_LOCKBIT_SET;
      }
      /*Check if there is an error caused by something other than lockbit*/
      else if ((0x0002 & FLASH.FPESTAT.WORD)
          && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
      {
        err = FLASH_ERR_FAILURE;
      }
      else
      {
        err = FLASH_ERR_CMD_LOCKED;
      }
      return err;
    }

    /*If current mode is Data Flash PE, increment to the next block starting address
     * by adding 64 (DF Block Size)
     * Else if the current mode is Code Flash PE, increment to the next block
     * starting address by adding 32K or 8K depending on the current block address
     * Also adjust the timeout depending on the block size*/
    if (FLASH.FENTRYR.WORD == 0x0080)
    {
      g_current_parameters.dest_addr += FLASH_DF_BLOCK_SIZE;
      g_current_parameters.wait_cnt = WAIT_MAX_ERASE_DF;
    }
    else if (FLASH.FENTRYR.WORD == 0x0001)
    {
      if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7)
      {
        g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
        g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_32K;
      }
      else
      {
        g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
        g_current_parameters.wait_cnt = WAIT_MAX_ERASE_CF_8K;
      }

    }
    else
    {
      //should never get here
      return FLASH_ERR_FAILURE;
    }
  }

  return err;
}

/***********************************************************************************************************************
 * Function Name: flash_write
 * Description  : Function writes a  of Code or Data Flash
 ** Arguments   : uint32_t block address
 * Return Value : FLASH_SUCCESS -
 *                Block Erased successfully.
 *                FLASH_ERR_TIMEOUT
 *                Erase operation timed out. The function issued a STOP to reset the peripheral.
 *                FLASH_ERR_LOCKED
 *                Erase operation timed out and STOP was attempted to recover. Stop operation failed.
 *                Peripheral in locked state.
 *                FLASH_ERR_LOCKBIT_SET
 *                Failed while trying to write to a block because lockbit was set and lockbit protection was enabled
 *                FLASH_ERR_FAILURE
 *                Erase operation failed for some other reason
 * Notes     :   -When using Code Flash in BGO mode, this function must be run from RAM or from the
 *                separate flash block for MCUs that are larger than 2MB. It can be run from ROM if
 *                only a Data Flash operation is ongoing.
 *               -The timeout condition is dynamically switched to allow for the worst case
 *                erasing time as follows
 *                32KB Code Flash 580 ms
 *                8KB Code Flash  145 ms
 *                64B Data Flash 40 ms
 ***********************************************************************************************************************/
flash_err_t flash_write(uint32_t *src_start_address,
    uint32_t * dest_start_address, uint32_t *num_bytes)
{
  flash_err_t err = FLASH_SUCCESS;
  uint32_t wait_cnt = FLASH_DBFULL_TIMEOUT;

  g_current_parameters.total_count = (*num_bytes) >> 1; //Since two bytes will be written at a time
  g_current_parameters.dest_addr = *dest_start_address;
  g_current_parameters.src_addr = *src_start_address;
  g_current_parameters.current_count = 0;

  /* Iterate through the number of data bytes */
  while (g_current_parameters.total_count > 0)
  {
    /*Set block start address*/
    FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
    /*Issue two part Write commands*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_PROGRAM;
    *g_pfcu_cmd_area = (uint8_t) g_current_parameters.min_pgm_size;
    /*Write one line (4 bytes for DF, 256 bytes for CF)*/
    while (g_current_parameters.current_count++
        < g_current_parameters.min_pgm_size)
    {
      /* Copy data from source address to destination area */
      *(FCU_WORD_PTR) g_pfcu_cmd_area = *(uint16_t *) g_current_parameters.src_addr;

      while (FLASH.FSTATR.BIT.DBFULL == 1)
      {
        /* Wait until DBFULL is 0 unless timeout occurs. */
        if (wait_cnt-- <= 0)
        {
          /* if DBFULL is not set to 0 after max timeout, issue the stop command*/
          err = flash_stop();
          /*If the STOP was not successfully issued, then return the error value for the stop action
           * Otherwise return the FLASH_ERR_TIMEOUT error*/
          if (FLASH_SUCCESS != err)
          {
            return err;
          }
          else
          {
            return FLASH_ERR_TIMEOUT;
          }
        }
      }
      g_current_parameters.src_addr += 2;
      g_current_parameters.dest_addr += 2;
      g_current_parameters.total_count--;
    }
    /*Reset line count*/
    g_current_parameters.current_count = 0;
    /*Issue write end command*/
    *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;
    /*if in BGO mode, exit here; remaining processing if any will be done in ISR*/
    if ((g_current_parameters.current_operation == FLASH_CUR_CF_BGO_WRITE)
        ||
        (g_current_parameters.current_operation == FLASH_CUR_DF_BGO_WRITE))
    {
      return err;
    }
    /* Read FRDY bit until it has been set to 1 indicating that the current
     * operation is complete.*/
    if (*src_start_address < FLASH_DF_BLOCK_INVALID)
    {
        g_current_parameters.wait_cnt = WAIT_MAX_DF_WRITE;
    }
    else
    {
        g_current_parameters.wait_cnt = WAIT_MAX_ROM_WRITE;
    }

    while (1 != FLASH.FSTATR.BIT.FRDY)
    {
      /* Wait until FRDY is 1 unless timeout occurs. */
      if (g_current_parameters.wait_cnt-- <= 0)
      {
        /* if FRDY is not set to 1 after max timeout, issue the stop command*/
        flash_stop();
        return FLASH_ERR_TIMEOUT;
      }
    }

    /*Check if there were any errors
     * Check if Command Lock bit is set*/
    if (0 != FLASH.FASTAT.BIT.CMDLK)
    {
      /*Check if there is a lockbit error*/
      if ((0x0001 & FLASH.FPESTAT.WORD)
          && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
      {
        err = FLASH_ERR_LOCKBIT_SET;
      }
      /*Check if there is an error caused by something other than lockbit*/
      else if ((0x0002 & FLASH.FPESTAT.WORD)
          && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
      {
        err = FLASH_ERR_FAILURE;
      }
      else
      {
        err = FLASH_ERR_CMD_LOCKED;
      }
      return err;
    }
  }

  return err;
}


/***********************************************************************************************************************
 * Function Name: flash_lockbit_read
 * Description  : Function to read the lockbit state for any block.
 * Arguments    : flash_block_address_t block_address
 *                flash_res_t *lock_state
 *                 - This will be set to FLASH_RES_LOCKBIT_STATE_NON_PROTECTED if the block is in the non-protected state
 *                 - This will be set to FLASH_RES_LOCKBIT_STATE_PROTECTED if the block is in the protected state
 *                 This field will have a valid result only if the return value from this function is FLASH_SUCCESS
 *
 * Return Value : FLASH_SUCCESS
 *                  Operation completed successfully
 *                FLASH_ERR_LOCKED
 *                  Peripheral in locked state. A reset was issued to recover from this state
 *                FLASH_ERR_TIMEOUT
 *                  Operation timed out. A reset was issued to recover from this state
 *                FLASH_ERR_ADDRESS
 *                  Invalid CF address
 *                FLASH_ERR_BOUNDARY
 *                  Address not on a block boundary
 *                FLASH_ERR_FAILURE
*                   LockBit operation attempted in BGO mode. This is temporarily not supported
 * Note     :     This function must run from RAM
 ***********************************************************************************************************************/
flash_err_t flash_lockbit_read(flash_block_address_t block_address, flash_res_t *lock_state)
{
  flash_err_t err = FLASH_SUCCESS;
  /* Timeout counter. */
  volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;

#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
  if (((block_address > FLASH_CF_BLOCK_0) || (block_address <= FLASH_CF_BLOCK_INVALID )))
  {
      return FLASH_ERR_ADDRESS;
  }

  if ((block_address >= FLASH_CF_BLOCK_7)
   && ((block_address & (FLASH_CF_SMALL_BLOCK_SIZE-1)) != 0))
  {
      return FLASH_ERR_BOUNDARY;
  }
  else if ((block_address < FLASH_CF_BLOCK_7)
   && ((block_address & (FLASH_CF_MEDIUM_BLOCK_SIZE-1)) != 0))
  {
      return FLASH_ERR_BOUNDARY;
  }
#endif

  /*Transition to CF P/E mode to issue LOCKBIT READ command*/
  if (FLASH_SUCCESS != flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH))
  {
    return FLASH_ERR_FAILURE;
  }

  if (g_current_parameters.bgo_enabled_cf == true)
  {
    g_current_parameters.current_operation = FLASH_CUR_CF_BGO_READ_LOCKBIT;
  }

  FLASH.FSADDR.LONG = block_address;
  /*Issue two part Lockbit Read commands*/
  *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_LOCK_BIT_READ;
  *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

  if (g_current_parameters.bgo_enabled_cf == true)
  {
    return err;
  }
  /* Read FRDY bit until it has been set to 1 indicating that the current
   * operation is complete.*/
  while (1 != FLASH.FSTATR.BIT.FRDY)
  {
    /* Wait until FRDY is 1 unless timeout occurs. */
    if (wait_cnt-- <= 0)
    {
      /* if FRDY is not set to 1 after max timeout, issue the stop command and reset*/
      err = FLASH_ERR_TIMEOUT;
      flash_reset();
      return err;
    }
  }
  if (0 != FLASH.FASTAT.BIT.CMDLK)
  {
    flash_reset();
    err = FLASH_ERR_CMD_LOCKED;
    return err;
  } else
  {
    if (0x01 == FLASH.FLKSTAT.BYTE)
    {
      *lock_state = FLASH_RES_LOCKBIT_STATE_NON_PROTECTED;
    } else
    {
      *lock_state = FLASH_RES_LOCKBIT_STATE_PROTECTED;
    }

    /*Transition to read mode*/
    err = flash_pe_mode_exit();
  }

  return err;
}



/***********************************************************************************************************************
* Function Name: flash_api_lockbit_set
* Description  : Function will set the lockbit for the specified number of code flash blocks.
* Arguments    : flash_block_address_t block_address -
*                 Starting address of code flash block to set the lockbit for.
*                 Element from "flash_block_address_t" enum must be used
*                uint32_t num_blocks -
*                 Number of bytes to set the lockbit for.
*                flash_res_t *result
*                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
*                 operation
* Return Value : FLASH_ERR_BLANK -
*                    Specified Data Flash area is blank
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range (1-65535) or is not a multiple of 4
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Code Flash Address
*                FLASH_ERR_BOUNDARY -
*                    Start address is not on block boundary
*                FLASH_ERR_LOCKED -
*                    The FCU is in a command locked state and cannot process the operation.The function performed a
*                    RESET on the peripheral to recover from this state.
*                FLASH_ERR_FAILURE
*                    LockBit operation attempted in BGO mode. This is temporarily not supported
***********************************************************************************************************************/
flash_err_t flash_api_lockbit_set(flash_block_address_t block_address, uint32_t num_blocks)
{
    flash_err_t err;

#if (FLASH_CFG_PARAM_CHECKING_ENABLE == 1)
    if (((block_address > FLASH_CF_BLOCK_0) || (block_address <= FLASH_CF_BLOCK_INVALID )))
    {
        return FLASH_ERR_ADDRESS;
    }

    if ((num_blocks > FLASH_NUM_BLOCKS_CF) || (num_blocks <= 0))
    {
        return FLASH_ERR_BLOCKS;
    }

    err = check_cf_block_total(block_address, num_blocks);
    if (err != FLASH_SUCCESS)
    {
        return err;     // block_address + num_blocks out of range
    }
#endif

    /* Lock flash driver and set state to LOCK_BIT */
    if (FLASH_SUCCESS != flash_lock_state(FLASH_LOCK_BIT))
    {
        return FLASH_ERR_BUSY;
    }

    /* Transition to CF P/E mode to issue LOCKBIT READ command */
    err = flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
    if (FLASH_SUCCESS != err)
    {
        return(err);
    }

    /* Set the current operation */
    g_current_parameters.current_operation = FLASH_CUR_LOCKBIT_SET;

    /* Start the LockBit Set operation */
    err = flash_lockbit_write(block_address, num_blocks);
    if (FLASH_SUCCESS != err)
    {
        flash_reset();
    }

    /* Current operation is completed. Exit from PE mode and return status */
    flash_pe_mode_exit();
    flash_release_state();

    return err;
}



/***********************************************************************************************************************
 * Function Name: flash_lockbit_write
 * Description  : Function to write(set) the lockbit for any block.
 * Arguments    : flash_block_address_t block_address
 *
 * Return Value : FLASH_SUCCESS
 *                Lockbit is set for the specified block
 *                FLASH_ERR_LOCKED
 *                Peripheral in locked state. A reset was issued to recover from this state
 *                FLASH_ERR_TIMEOUT
 *                Operation timed out. A reset was issued to recover from this state
 *                FLASH_ERR_ADRRESS
 *                Invalid address
 *                FLASH_ERR_LOCKBIT_SET
 *                Lockbit is set for the block
 * Note     :     This function must run from RAM
 ***********************************************************************************************************************/
flash_err_t flash_lockbit_write(flash_block_address_t block_address, uint32_t num_blocks)
{
    flash_err_t err = FLASH_SUCCESS;
    volatile uint32_t wait_cnt = FLASH_FRDY_CMD_TIMEOUT;


    if (g_current_parameters.bgo_enabled_cf == true)
    {
        g_current_parameters.current_operation = FLASH_CUR_CF_BGO_WRITE_LOCKBIT;
    }

    g_current_parameters.dest_addr = block_address;
    g_current_parameters.total_count = num_blocks;

    /* Loop through each block address and set lockbit */
    for (g_current_parameters.current_count = 0;
         g_current_parameters.current_count < g_current_parameters.total_count;
         g_current_parameters.current_count++)
    {
        /* Init flash register and write fcu command */
        FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_LOCK_BIT_PGM;
        *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

        if (g_current_parameters.bgo_enabled_cf == true)
        {
            return err;
        }
        /* Read FRDY bit until it has been set to 1 indicating that the current
         * operation is complete.*/
        while (1 != FLASH.FSTATR.BIT.FRDY)
        {
            /* Wait until FRDY is 1 unless timeout occurs. */
            if (wait_cnt-- <= 0)
            {
                /* if FRDY is not set to 1 after max timeout, return error code*/
                flash_stop();
                return FLASH_ERR_TIMEOUT;
            }
        }
        /*Check if there were any errors
         * Check if Command Lock bit is set*/
        if (0 != FLASH.FASTAT.BIT.CMDLK)
        {
            /* FPESTAT only valid if FRDY=1 and PRGERR or ERSERR is set */
            if ((0x0001 & FLASH.FPESTAT.WORD)       // error due to lockbit on write or erase
             && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
            {
                err = FLASH_ERR_LOCKBIT_SET;
            }
            else if ((0x0002 & FLASH.FPESTAT.WORD)  // error due to non-lockbit error
             && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
            {
                err = FLASH_ERR_FAILURE;
            }
            else
            {
                err = FLASH_ERR_CMD_LOCKED;
            }
            return err;
        }

        /* Decrement to start address of next CF block */
        if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7)
        {
            g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
        }
        else
        {
            g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
        }
    }
#if 0
  /*Transition to read mode*/
  err = flash_pe_mode_exit();
  if (err != FLASH_SUCCESS)
  {
    return err;
  }
#endif
    return err;
}
/***********************************************************************************************************************
 * Function Name: flash_reset
 * Description  : Function resets the Flash peripheral
 ** Arguments   : None
 * Return Value : FLASH_SUCCESS -
 *                Flash Peripheral successfully reset.
 * Notes     :   -This function will reset the peripheral by stopping any ongoing operations,
 *                clearing the DFAE and CFAE flags and changing the PE mode to Read mode.
 ***********************************************************************************************************************/
flash_err_t flash_reset()
{

    /* Cannot release sequencer from the command-locked state with status clear
     * or forced-stop commands if CFAE or DFAE is set. Must read those bits
     * before can set to 0.
     */
    if (FLASH.FASTAT.BIT.CFAE == 1)
    {
        FLASH.FASTAT.BIT.CFAE = 0;
    }
#ifndef FLASH_NO_DATA_FLASH
    if (FLASH.FASTAT.BIT.DFAE == 1)
    {
        FLASH.FASTAT.BIT.DFAE = 0;
    }
#endif

    /* Possible FLASH_CMD_RESET is called when no outstanding command is in progress.
     * In that case, enter pe mode so flash_stop() can write to the sequencer.
     */
    if (g_flash_state == FLASH_READY)
    {
        flash_pe_mode_enter(FLASH_TYPE_CODE_FLASH);
    }

    /*Issue a forced stop */
    flash_stop();

    /*Transition to Read mode*/
    FLASH.FENTRYR.WORD = 0xAA00;
    while (FLASH.FENTRYR.WORD != 0x0000)
        ;

    return FLASH_SUCCESS;
}


#if (FLASH_CFG_CODE_FLASH_BGO == 1)

/***********************************************************************************************************************
 * Function Name: Excep_FCU_FRDYI
 * Description  : ISR for Flash Ready Interrupt
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
#pragma interrupt Excep_FCU_FRDYI(vect=VECT(FCU,FRDYI))
static void Excep_FCU_FRDYI(void)
{
  /*Wait counter used for DBFULL flag*/
  uint32_t wait_cnt = FLASH_DBFULL_TIMEOUT;
  if ((FLASH_CUR_DF_BGO_WRITE == g_current_parameters.current_operation)
      || (FLASH_CUR_CF_BGO_WRITE == g_current_parameters.current_operation))
  {
    /*If there are still bytes to write*/
    if (g_current_parameters.total_count > 0)
    {
      /*Set block start address*/
      FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
      /*Issue two part Write commands*/
      *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_PROGRAM;
      *g_pfcu_cmd_area = (uint8_t) g_current_parameters.min_pgm_size;
      /* Write one line (256 for CF, 4 for DF) */
      while (g_current_parameters.current_count++   < g_current_parameters.min_pgm_size)
      {
        /* Copy data from source address to destination area */
        *(FCU_WORD_PTR) g_pfcu_cmd_area =   *(uint16_t *) g_current_parameters.src_addr;
        while (FLASH.FSTATR.BIT.DBFULL == 1)
        {
          /* Wait until DBFULL is 0 unless timeout occurs. */
          if (wait_cnt-- <= 0)
          {
            /* if DBFULL is not set to 0 after max timeout, reset thr FCU*/
            flash_reset();
            g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_FAILURE;
            return;
          }
        }
        g_current_parameters.src_addr += 2;
        g_current_parameters.dest_addr += 2;
        g_current_parameters.total_count--;
      }
      /*Reset line count*/
      g_current_parameters.current_count = 0;
      /*Issue write end command*/
      *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;
      /*Exit ISR until next FRDY interrupt to continue operation*/
      return;
    }
    /*Done writing all bytes*/
    else
    {
      g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_WRITE_COMPLETE;
    }
  }
  else if ((FLASH_CUR_DF_BGO_ERASE == g_current_parameters.current_operation)
      || (FLASH_CUR_CF_BGO_ERASE    == g_current_parameters.current_operation))
  {
    g_current_parameters.current_count++;
    if (g_current_parameters.current_count
        < g_current_parameters.total_count)
    {
      /*If current mode is Data Flash PE, increment to the next block starting address
       * by adding 64 (DF Block Size) else decrement to the next flash block start address*/
      if (FLASH.FENTRYR.WORD == 0x0080)
      {
        g_current_parameters.dest_addr += FLASH_DF_BLOCK_SIZE;
      }
      else if (FLASH.FENTRYR.WORD == 0x0001)
      {
        if (g_current_parameters.dest_addr
            <= (uint32_t) FLASH_CF_BLOCK_7)
        {
          g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
        }
        else
        {
          g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
        }

      }
      /*Set block start address*/
      FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
      /*Issue two part Block Erase commands*/
      *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_BLOCK_ERASE;
      *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;
      /*Exit ISR until next FRDY interrupt to continue operation*/
      return;
    }
    /*If all blocks are erased*/
    else
    {
      g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_ERASE_COMPLETE;
    }
  }
  else if (FLASH_CUR_DF_BGO_BLANKCHECK == g_current_parameters.current_operation)
  {
    if (FLASH.FBCSTAT.BYTE == 0x01)
    {
      g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_NOT_BLANK;
    }
    else
    {
      g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_BLANK;
    }

  }
  else if (FLASH_CUR_CF_BGO_READ_LOCKBIT == g_current_parameters.current_operation)
  {
      if (FLASH.FLKSTAT.BIT.FLOCKST == 1)
      {
          g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_LOCKBIT_NON_PROTECTED;
      }
      else
      {
          g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_LOCKBIT_PROTECTED;
      }
  }
  else if (FLASH_CUR_CF_BGO_WRITE_LOCKBIT == g_current_parameters.current_operation)
  {
      if (0 == FLASH.FASTAT.BIT.CMDLK)    // last block lock successful
      {
          while (++g_current_parameters.current_count < g_current_parameters.total_count)
          {
              /* Decrement to start address of next CF block */
              if (g_current_parameters.dest_addr <= (uint32_t) FLASH_CF_BLOCK_7)
              {
                  g_current_parameters.dest_addr -= FLASH_CF_MEDIUM_BLOCK_SIZE;
              }
              else
              {
                  g_current_parameters.dest_addr -= FLASH_CF_SMALL_BLOCK_SIZE;
              }

              /* Init flash registers and write fcu command */
              FLASH.FSADDR.LONG = g_current_parameters.dest_addr;
              *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_LOCK_BIT_PGM;
              *g_pfcu_cmd_area = (uint8_t) FLASH_FACI_CMD_FINAL;

              /* Exit ISR until next FRDY interrupt to continue operation (lock next block) */
              return;
          }

          g_flash_int_ready_cb_args.event = FLASH_INT_EVENT_LOCKBIT_WRITTEN;
      }
      else /* writing lockbit failed */
      {
          flash_reset();
          g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_FAILURE;
      }
  }
  else
  {
    //un-handled FRDY case
  }

  if (g_current_parameters.current_operation != FLASH_CUR_STOP)
  {
      /*finished current operation. Exit P/E mode*/
      flash_pe_mode_exit();
      /*Release lock and Set current state to Idle*/
      flash_release_state();
      if ((FIT_NO_FUNC != flash_ready_isr_handler)
       && (NULL != flash_ready_isr_handler))
      {
          flash_ready_isr_handler((void *) &g_flash_int_ready_cb_args);
      }
  }
}

/***********************************************************************************************************************
 * Function Name: flash_error_isr
 * Description  : ISR for Flash Error Interrupt
 * Arguments    : none
 * Return Value : none
 ***********************************************************************************************************************/
#pragma interrupt flash_error_isr(vect=VECT(FCU,FIFERR))
static void flash_error_isr(void)
{

  /*Check if Command Lock bit is set*/
  if (1 == FLASH.FASTAT.BIT.CMDLK)
  {
    if (1 == FLASH.FASTAT.BIT.DFAE)
    {
      g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_DF_ACCESS;
    }
    else if (1 == FLASH.FASTAT.BIT.CFAE)
    {
      g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_CF_ACCESS;
    }
    else if ((0x0001 & FLASH.FPESTAT.WORD)
        && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
    {
        g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_LOCKBIT_SET;
    }
    else if ((0x0002 & FLASH.FPESTAT.WORD)
        && ((FLASH.FSTATR.BIT.PRGERR) || (FLASH.FSTATR.BIT.ERSERR)))
    {
      g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_FAILURE;
    }
    else
    {
      g_flash_int_error_cb_args.event = FLASH_INT_EVENT_ERR_CMD_LOCKED;
    }

  }

  /*Reset the FCU: This will stop any existing processes and exit PE mode*/
  flash_reset();
  IR(FCU,FRDYI)= 0;  //Clear any pending Flash Ready interrupt request
  flash_release_state();
  if ((FIT_NO_FUNC != flash_error_isr_handler)
      && (NULL != flash_error_isr_handler))
  {
    flash_error_isr_handler((void *) &g_flash_int_error_cb_args);
  }

}
#endif // FLASH_CFG_CODE_FLASH_BGO

#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#pragma section //end section FRAM
#endif
#endif  // FLASH_TYPE_3

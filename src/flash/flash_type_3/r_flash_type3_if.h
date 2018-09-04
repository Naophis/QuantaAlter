#ifndef FLASH_API_IF_FCU_64M_HEADER_FILE
#define FLASH_API_IF_FCU_64M_HEADER_FILE

#include <stdint.h>
#include <stdbool.h>

#define FLASH_FREQ_LO           (4000000)
#define FLASH_FREQ_HI           (60000000)

#define FLASH_FCU_INT_ENABLE    FLASH.FAEINT.BYTE = 0x90;   \
                                FLASH.FRDYIE.BYTE = 0x01;
#define FLASH_FCU_INT_DISABLE   FLASH.FAEINT.BYTE = 0x00;   \
                                FLASH.FRDYIE.BYTE = 0x00;
#include "r_flash_rx.h"          // Include this here or flash_err_t doesn't get resolved
flash_err_t flash_init();
flash_err_t flash_clock_config(uint32_t);
flash_err_t flash_fcuram_codecopy();
flash_err_t flash_reset();
flash_err_t flash_stop();
flash_err_t flash_suspend();
flash_err_t flash_resume();
flash_err_t flash_interrupt_config(bool state, void *pCallback);
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
void flash_codecopy(void);
extern void (*flash_ready_isr_handler)(void *); // Function pointer for Flash Ready ISR
extern void (*flash_error_isr_handler)(void *); // Function pointer for Flash Error ISR

flash_err_t flash_api_open(void);
flash_err_t flash_api_write(uint32_t flash_addr, uint32_t buffer_addr,
		uint32_t bytes);
flash_err_t flash_api_erase(flash_block_address_t block_start_address,
		uint32_t num_blocks);
flash_err_t flash_api_blankcheck(uint32_t address, uint32_t num_bytes,
		flash_res_t *result);
flash_err_t flash_api_control(flash_cmd_t cmd, void *pcfg);
uint32_t flash_get_romBlock_size(uint32_t addr, rom_block_info_t *pblock_info);
bool flash_get_romBlock_info(uint32_t block_number,
		rom_block_info_t *pblock_info);
uint8_t flash_getStatus(void);

#endif /* FLASH_API_IF_FCU_64M_HEADER_FILE */


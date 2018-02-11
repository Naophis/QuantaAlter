/**********************************************************************************************************************
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
**********************************************************************************************************************/
/**********************************************************************************************************************
* File Name    : r_flash_type3_if.h
* Description  : This file defines the flash API functions for FCU enabled MCU's.
*
**********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version Description           
*         : 02.18.2014 1.10    Support for RX64M
*         : 12.08.2016 2.00    Modified for BSPless operation.
*         : 17.11.2016 2.10    Added FLASH_FREQ_xx and FLASH_FCU_INT_xxx #defines
**********************************************************************************************************************/

#ifndef FLASH_API_IF_FCU_64M_HEADER_FILE
#define FLASH_API_IF_FCU_64M_HEADER_FILE

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* Fixed width integer support. */
#include <stdint.h>
/* bool support */
#include <stdbool.h>


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define FLASH_FREQ_LO           (4000000)
#define FLASH_FREQ_HI           (60000000)

#define FLASH_FCU_INT_ENABLE    FLASH.FAEINT.BYTE = 0x90;   \
                                FLASH.FRDYIE.BYTE = 0x01;
#define FLASH_FCU_INT_DISABLE   FLASH.FAEINT.BYTE = 0x00;   \
                                FLASH.FRDYIE.BYTE = 0x00;

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

#include "r_flash_rx.h"          // Include this here or flash_err_t doesn't get resolved

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
flash_err_t flash_init();
flash_err_t flash_clock_config(uint32_t);
flash_err_t flash_fcuram_codecopy();
flash_err_t flash_reset();
flash_err_t flash_stop();
flash_err_t flash_suspend();
flash_err_t flash_resume();
flash_err_t flash_interrupt_config(bool state, void *pCallback);
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
void flash_codecopy (void);
extern void (*flash_ready_isr_handler)(void *);          // Function pointer for Flash Ready ISR
extern void (*flash_error_isr_handler)(void *);          // Function pointer for Flash Error ISR



flash_err_t flash_api_open(void);
flash_err_t flash_api_write(uint32_t flash_addr, uint32_t buffer_addr, uint32_t bytes);
flash_err_t flash_api_erase(flash_block_address_t block_start_address, uint32_t num_blocks);
flash_err_t flash_api_blankcheck(uint32_t address, uint32_t num_bytes, flash_res_t *result);
flash_err_t flash_api_control(flash_cmd_t cmd,  void  *pcfg);
uint32_t flash_get_romBlock_size (uint32_t addr, rom_block_info_t* pblock_info);
bool flash_get_romBlock_info (uint32_t block_number, rom_block_info_t* pblock_info);
uint8_t flash_getStatus (void);



#endif /* FLASH_API_IF_FCU_64M_HEADER_FILE */



/***********************************************************************************************************************
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
* Copyright (C) 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : r_flash_rx.c
* Description  : This module implements the FLASH API
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : DD.MM.YYYY Version Description
*              : 12.07.2014 1.00    First Release
*              : 13.01.2015 1.10    Updated for RX231
*              : 21.07.2016 1.20    Fixed initialization of g_current_parameters for Flash Type 3.
*              : 12.08.2016 2.00    Modified for BSPless operation (softwareLock()/Unlock()).
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
#include "r_flash_rx_if.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
External functions
***********************************************************************************************************************/

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* State variable for the Flash API. */
flash_states_t g_flash_state = FLASH_UNINITIALIZED;
static int32_t g_flash_lock;

/* Internal functions. */
void (*flash_ready_isr_handler)(void *);          /* Function pointer for Flash Ready ISR */
void (*flash_error_isr_handler)(void *);          /* Function pointer for Flash Error ISR */

#if (FLASH_TYPE == FLASH_TYPE_3)
    /*Structure that holds the parameters for current operations*/
    current_param_t g_current_parameters = {
                                             0,     /* Source Address */
                                             0,     /* Destination Address */
                                             0,     /* Total Count */
                                             0,     /* Current Count */
                                             FLASH_CUR_INVALID, /* Current Operation */
                                             0,     /* Minimum Program Size */
                                             0,     /* Wait Count for current operation */
                                             false, /* DF BGO Disabled */
                                             false, /* CF BGO Disabled */
                                            };
#else
    /*Structure that holds the parameters for current operations*/
    current_param_t g_current_parameters = {
                                             0,     /* Source Address */
                                             0,     /* Destination Address */
                                             0,     /* Total Count */
                                             0,     /* Current Count */
                                             FLASH_CUR_INVALID, /* Current Operation */
                                             0,     /* Minimum Program Size */
                                             0      /* Wait Count for current operation */
                                            };
#endif

/***********************************************************************************************************************
* Function Name: R_FLASH_Open
* Description  : Function will initialize the flash peripheral.
* Arguments    : void
* Return Value : FLASH_SUCCESS -
*                    API initialized successfully.
*                FLASH_ERR_BUSY
*                    API has already been initialized and another operation is ongoing.
*                FLASH_ERR_FAILURE
*                    Initialization failed.
*                    A RESET was performed on the Flash circuit to rectify any internal errors
***********************************************************************************************************************/
flash_err_t R_FLASH_Open(void)
{
    flash_err_t err;

    /* After a reset parts of the Flash API must be copied to RAM before the API
       can be used. This originally was done by editing the dbsct.c file to
       copy the code over when other RAM sections are initialized. There is now
       the R_FlashCodeCopy() function which does the same thing.
       If we are going to be writing to Code Flash then we want the API in RAM
       (exception: flash type 3 limited capability). The Flash control circuit
       cannot program or erase ROM while executing or reading from ROM */
#if (FLASH_CFG_CODE_FLASH_RUN_FROM_ROM == 0) || (FLASH_TYPE != FLASH_TYPE_3)
    R_FlashCodeCopy();
#endif


    /* Call the MCU specific control function which handles control commands for the target MCU */
    err = flash_api_open();     /* Call supported handler */
    if (err == FLASH_SUCCESS)
    {
        /* Flash is ready */
        g_flash_state = FLASH_READY;
    }

    return(err);
}

/******************************************************************************
* Function Name: R_FlashCodeCopy
* Description  : Copies Flash API code from ROM to RAM. This function needs to
*                be called before any program/erase functions. This function
*                does not need to be used when
*                NOTE: This function does not have to execute from in RAM.
* Arguments    : none
* Return Value : none
******************************************************************************/
void R_FlashCodeCopy (void)
{
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)

    /* Pointer to beginning of RAM section where API code will be copied to. */
    uint8_t * p_ram_section;
    /* Pointer to beginning of ROM section with API code. */
    uint8_t * p_rom_section;
    /* Number of bytes copied. */
    uint32_t  bytes_copied;

    /* Initialize RAM section pointer. */
    p_ram_section = (uint8_t *)__sectop("RPFRAM");

    /* Initialize ROM section pointer. */
    p_rom_section = (uint8_t *)__sectop("PFRAM");

    /* Copy over code from ROM to RAM. */
    for (bytes_copied = 0; bytes_copied < __secsize("PFRAM"); bytes_copied++)
    {
        /* Copy over data 1 byte at a time. */
        p_ram_section[bytes_copied] = p_rom_section[bytes_copied];
    }
#endif
}

/******************************************************************************
End of function  R_FlashCodeCopy
******************************************************************************/
/* If FLASH_CFG_CODE_FLASH_BGO is enabled then the following functions (before
   the next #pragma section) also need to be in RAM in the case that the user
   calls them during a ROM operation. */
#if (FLASH_CFG_CODE_FLASH_ENABLE == 1)
#pragma section FRAM
#endif

/***********************************************************************************************************************
* Function Name: flash_softwareLock
* Description  : Attempt to acquire the lock that has been sent in.
* Arguments    : plock -
*                    Pointer to lock structure with lock to try and acquire.
* Return Value : true -
*                    Lock was acquired.
*                false -
*                    Lock was not acquired.
***********************************************************************************************************************/
bool flash_softwareLock (int32_t * const plock)
{
    bool ret = false;

    /* Variable used in trying to acquire lock. Using the xchg instruction makes this atomic */
    int32_t is_locked = true;

    /* Try to acquire semaphore to obtain lock */
    xchg(&is_locked, plock);

    /* Check to see if semaphore was successfully taken */
    if (is_locked == false)
    {
        /* Lock obtained, return success. */
        ret = true;
    }
    else
    {
        /* Lock was not obtained, another task already has it. */
    }

    return ret;
} /* End of function flash_softwareLock() */

/***********************************************************************************************************************
* Function Name: flash_softwareUnlock
* Description  : Release hold on lock.
* Arguments    : plock -
*                    Pointer to lock structure with lock to release.
* Return Value : true -
*                    Lock was released.
*                false -
*                    Lock was not released.
***********************************************************************************************************************/
bool flash_softwareUnlock (int32_t * const plock)
{
    /* Set lock back to unlocked. */
    *plock = false;

    return true;
} /* End of function flash_softwareUnlock() */


/***********************************************************************************************************************
* Function Name: R_FLASH_Write
* Description  : Function will write to the specified Code or Data Flash memory area.
*                Note that this function does not insure that the block(s) being written are blank.
*                If that information is required, R_FLASH_BlankCheck() should be used.
* Arguments    : uint32_t src_address -
*                 Source buffer address (data being written to Flash)
*                uint32_t dest_address -
*                 Destination address.
*                uint32_t num_bytes
*                 Number of bytes to be written
* Return Value : FLASH_SUCCESS -
*                    Write completed successfully; successfully initialized in case of BGO mode.
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
*                FLASH_ERR_FAILURE
*                    Flash Write operation failed for some other reason. This can be a result of trying to write to an area
*                    that has been protected via access control.
***********************************************************************************************************************/
flash_err_t R_FLASH_Write(uint32_t src_address, uint32_t dest_address, uint32_t num_bytes)
{

    /* Call the MCU specific write function which handles control commands for the target MCU */
    return(flash_api_write(src_address, dest_address,  num_bytes));

}

/***********************************************************************************************************************
* Function Name: R_FLASH_Erase
* Description  : Function will erase the specified Code or Data Flash blocks.
* Arguments    : uint32_t block_start_address -
*                 Start address of the first block. Actual address or entry from "flash_block_address_t" enum can be used
*                uint32_t num_blocks -
*                 Number of blocks to erase.
* Return Value : FLASH_SUCCESS -
*                    Erase completed successfully; successfully initialized in case of BGO mode.
*                FLASH_ERR_BLOCKS -
*                    Number of blocks exceeds max range or is 0
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Code/Data Flash block start address
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation
*                FLASH_ERR_FAILURE
*                    Flash Write operation failed for some other reason. This can be a result of trying to erase an area
*                    that has been protected via access control.
***********************************************************************************************************************/
flash_err_t R_FLASH_Erase(flash_block_address_t block_start_address, uint32_t num_blocks)
{
    return(flash_api_erase(block_start_address, num_blocks));       /* Call FCU supported handler */
}

#ifndef MCU_RX65_ALL
/***********************************************************************************************************************
* Function Name: R_FLASH_BlankCheck
* Description  : Function will perform a blank check on the specified Flash area.
*                This function operates differently for the RX100 (non FCU) series MCU which does
*                support blank checking of the Code flash area.
* RX100 series:
*                If Blank checking Code Flash then this function must execute from RAM.
*                The function will incrementally check the area from the start address onward.
*                The minimum number of bytes is 256 for CF and 4 for DF.
*                The max is 256K for CF, 8192 for DF.
*                For parts that may support > 256K CF, then the address range provided may not span a 256K boundary.
*                For example: with a 512K part one could not specify a range of 255K - 257K even though that is
*                a 2K range. That would require two seperate BlankCheck calls. One for 255-256, one for 256-257
*
* Arguments:     uint32_t address -
*                 Start address to perform blank check. Actual address or entry from "flash_block_address_t" enum can be used
*                uint32_t num_blocks -
*                 Number of bytes to perform blank check operation for.
*                flash_res_t *result
*                 Returns the result of the blank check operation. This field is valid only in non-BGO mode
*                 operation
*
* RX600 and RX200 Series: Only Data Flash may be blank checked.
*                 This function does not have to execute from in RAM. It must be in RAM though if BGO Polling mode is active is
*                 enabled and this function is called during a ROM P/E operation.
*                 RX610 & RX62x support block and 8 byte checks
*                 RX630/631/63N support block and 2 byte checks
*
* Arguments:      address -
*                  The address to check if is blank.
*                  If the parameter 'size'=='BLANK_CHECK_8_BYTE',
*                  this should be set to an 8-byte address boundary.
*                  If the parameter 'size'=='BLANK_CHECK_ENTIRE_BLOCK',
*                  this should be set to a defined Data Block Number
*                  ('BLOCK_DB0', 'BLOCK_DB1', etc...) or an address
*                  in the data flash block.  Either option will work.
*                  If the parameter 'size'=='BLANK_CHECK_2_BYTE',
*                  this should be set to a 2 byte address boundary.
*                 size -
*                  This specifies if you are checking an 8-byte location,
*                  2-byte location, or an entire block. You must set this
*                  to either 'BLANK_CHECK_8_BYTE', 'BLANK_CHECK_2_BYTE',
*                  or 'BLANK_CHECK_ENTIRE_BLOCK'.
*
*                 result
*                  Returns the result of the blank check operation. This field is valid only in non-BGO mode (blocking mode)
*
* Return Value : FLASH_SUCCESS
*                 Operation was completed successfully
*                FLASH_ERR_BYTES -
*                    Number of bytes exceeds max range (1-65535) or is not a multiple of 4
*                FLASH_ERR_ADRRESS -
*                    Start address is an invalid Data Flash Address
*                FLASH_ERR_BUSY
*                    Flash peripheral is busy with another operation or not initialized
*                FLASH_ERR_FAILURE -
*                    Operation failed for some other reason.*
***********************************************************************************************************************/
flash_err_t R_FLASH_BlankCheck(uint32_t address, uint32_t num_bytes, flash_res_t *result)
{

    return(flash_api_blankcheck(address, num_bytes, result));

}
#endif

/***********************************************************************************************************************
* Function Name: R_FLASH_Control
* Description  : This function supports additional configuration operations.
*      The supported commands are listed in the flash_cmd_t enum.
* Arguments    : flash_cmd_t cmd -
*                 command.
*                void *pcfg -
*                 Pointer to configuration. This argument can be NULL for
*                 commands that do not require a configuration.
*
*                Command                                | Argument
*                FLASH_CMD_RESET------------------------| NULL
*                FLASH_CMD_STATUS_GET-------------------| NULL
* Type 1 only:
*
*                FLASH_CMD_ACCESSWINDOW_SET-------------| void (*pAccessInfo)(void *)
*                FLASH_CMD_ACCESSWINDOW_GET-------------| void (*pAccessInfo)(void *)
*                FLASH_CMD_SWAPFLAG_TOGGLE--------------| NULL
*                FLASH_CMD_SWAPFLAG_GET-----------------| void (uint32_t *)
*                FLASH_CMD_SWAPSTATE_SET----------------| void (uint8_t *)
*                FLASH_CMD_SWAPSTATE_GET----------------| void (uint32_t *)
*
* Type 2 only:
*                FLASH_CMD_LOCKBIT_WRITE----------------| flash_lockbit_config_t
*                FLASH_CMD_LOCKBIT_READ-----------------| flash_lockbit_config_t
*                FLASH_CMD_LOCKBIT_ENABLE---------------| NULL
*                FLASH_CMD_LOCKBIT_DISABLE--------------| NULL
*
* Return Value : FLASH_SUCCESS -
*                    Operation completed successfully.
*                FLASH_ERR_FAILURE -
*                    Operation not available for this MCU
*                FLASH_ERR_ADRRESS -
*                    Address is an invalid Code/Data Flash block start address
*                FLASH_ERR_NULL_PTR -
*                    Pointer was NULL for a command that expects a configuration structure
*                FLASH_ERR_BUSY -
*                    Flash peripheral is busy with another operation or not initialized
*
***********************************************************************************************************************/
flash_err_t R_FLASH_Control(flash_cmd_t cmd, void *pcfg)
{
    /* Call the MCU specific control function which handles control commands for the target MCU */
    return(flash_api_control(cmd, pcfg));

}

/***********************************************************************************************************************
* Function Name: R_FLASH_GetVersion
* Description  : Returns the current version of this module. The version number is encoded where the top 2 bytes are the
*                major version number and the bottom 2 bytes are the minor version number. For example, Version 4.25
*                would be returned as 0x00040019.
* Arguments    : none
* Return Value : Version of this module.
***********************************************************************************************************************/
#pragma inline(R_FLASH_GetVersion)
uint32_t R_FLASH_GetVersion (void)
{
    /* These version macros are defined in r_flash_if.h. */
    return ((((uint32_t)FLASH_RX_VERSION_MAJOR) << 16) | (uint32_t)FLASH_RX_VERSION_MINOR);
}

/******************************************************************************
* Function Name: flash_lock_state
* Description  : Attempt to grab the flash state to perform an operation
*                NOTE1: This function does not have to execute from in RAM. It
*                       must be in RAM though if FLASH_CFG_CODE_FLASH_BGO is
*                       enabled and this function is called during a ROM P/E
*                       operation.
* Arguments    : new_state -
*                    Which state to attempt to transition to
* Return Value : FLASH_SUCCESS -
*                    State was grabbed
*                FLASH_ERR_BUSY -
*                    Flash is busy with another operation
******************************************************************************/
flash_err_t flash_lock_state (flash_states_t new_state)
{
    /* Check to see if lock was successfully taken */

    /* NOTE: Code normally should not access internals of another driver,
     * however, we cannot use the BSP lock/unlock routines unless they are
     * located in RAM so code flash operations will work. This, however,
     * would break existing software in the field. Hence, this solution.
     */
    if (flash_softwareLock(&g_flash_lock) == true)
    {
        /* Lock taken, we can change state */
        g_flash_state = new_state;

        /* Return success */
        return FLASH_SUCCESS;
    }
    else
    {
        /* Another operation is on-going */
        return FLASH_ERR_BUSY;
    }
}


/******************************************************************************
* Function Name: flash_release_state
* Description  : Release state so another flash operation can take place
*                NOTE1: This function does not have to execute from in RAM. It
*                       must be in RAM though if FLASH_CFG_CODE_FLASH_BGO is
*                       enabled and this function is called during a ROM P/E
*                       operation.
* Arguments    : none
* Return Value : none
******************************************************************************/
void flash_release_state (void)
{

    /* Done with current operation */
    g_flash_state = FLASH_READY;

    /* Release hold on lock */
    flash_softwareUnlock(&g_flash_lock);
}


#if (FLASH_TYPE != FLASH_TYPE_1)
/***********************************************************************************************************
* Function Name: flash_get_status
* Description  : Returns the current state of the flash
*                NOTE1: This function does not have to execute from in RAM. It must be in RAM though if
*                CF BGO is enabled and this function is called during a ROM P/E operation.
* Arguments    : none
* Return Value : FLASH_SUCCESS -
*                    Flash is ready to use
*                FLASH_ERR_BUSY -
*                    Flash is busy with another operation or is uninitialized
***********************************************************************************************************/
flash_err_t flash_get_status (void)
{
    /* Return flash status */
    if( g_flash_state == FLASH_READY )
    {
        return FLASH_SUCCESS;
    }
    else
    {
        return FLASH_ERR_BUSY;
    }
}
#endif

#pragma section /* end FLASH SECTION FRAM */

/* end of file */

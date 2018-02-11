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
* File Name    : r_flash_rx.h
* Description  : This is a private header file used internally by the FLASH module. It should not be modified or
*                included by the user in their application.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version Description
*           12.07.2014 1.00    First Release
*           13.01.2015 1.10    Updated for RX231
*           11.02.2016 1.20    Updated for Flash Type 4
*           25.05.2016 1.30    Added FLASH_CUR_CF_BGO_READ/WRITE_LOCKBIT for flash type 3.
*           08.08.2016 2.00    Modified for BSPless operation.
*                              Added prototypes for flash_softwareLock()/Unlock().
*                              Added support for RX230.
*           18.11.2016 2.10    Added support for RX24U.
*                              Added equates FLASH_HAS_ERR_ISR and FLASH_HAS_FCU.
***********************************************************************************************************************/

#ifndef RX_FLASH_API_PRIVATE_HEADER_FILE
#define RX_FLASH_API_PRIVATE_HEADER_FILE

#include <stdbool.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#if (FLASH_TYPE != 1)
#define FLASH_HAS_ERR_ISR           1
#endif

#if ((FLASH_TYPE == 3) || (FLASH_TYPE == 4))
#define FLASH_HAS_FCU               1
#endif


/* 'size' parameter for Flash Type 2 flash_api_fcu_blankcheck.
 * The number of bytes checked by the smallest blank check is always the
 * smallest data flash programming size. */
#define BLANK_CHECK_SMALLEST         0
/* 'size' parameter for R_FlashDataAreaBlankCheck */
#define BLANK_CHECK_ENTIRE_BLOCK     1


/* Memory specifics for the each MCU group */
#if   defined(MCU_RX111)
    #include "./src/targets/rx111/r_flash_rx111.h"
#elif   defined(MCU_RX110)
    #include "./src/targets/rx110/r_flash_rx110.h"
#elif   defined(MCU_RX113)
    #include "./src/targets/rx113/r_flash_rx113.h"
#elif   defined(MCU_RX130)
    #include "./src/targets/rx130/r_flash_rx130.h"
#elif   defined(MCU_RX610)
    #include "./src/targets/rx610/r_flash_rx610.h"
#elif defined(MCU_RX621) || defined(MCU_RX62N)
    #include "./src/targets/rx62n/r_flash_rx62n.h"
#elif defined(MCU_RX62T)
    #include "./src/targets/rx62t/r_flash_rx62t.h"
#elif defined(MCU_RX62G)
    #include "./src/targets/rx62g/r_flash_rx62g.h"
#elif defined(MCU_RX630)
    #include "./src/targets/rx630/r_flash_rx630.h"
#elif defined(MCU_RX631) || defined(MCU_RX63N)
    #include "./src/targets/rx63n/r_flash_rx63n.h"
#elif defined(MCU_RX63T)
    #include "./src/targets/rx63t/r_flash_rx63t.h"
#elif defined(MCU_RX210)
    #include "./src/targets/rx210/r_flash_rx210.h"
#elif defined(MCU_RX21A)
    #include "./src/targets/rx21a/r_flash_rx21a.h"
#elif defined(MCU_RX220)
    #include "./src/targets/rx220/r_flash_rx220.h"
#elif defined(MCU_RX231) || defined(MCU_RX230)
    #include "./src/targets/rx231/r_flash_rx231.h"
#elif defined(MCU_RX23T)
    #include "./src/targets/rx23t/r_flash_rx23t.h"
#elif defined(MCU_RX24T)
    #include "./src/targets/rx24t/r_flash_rx24t.h"
#elif defined(MCU_RX24U)
    #include "./src/targets/rx24u/r_flash_rx24u.h"
#elif defined(MCU_RX64M)
    #include <targets/rx64m/r_flash_rx64m.h>
#elif defined(MCU_RX651)
    #include "./src/targets/rx651/r_flash_rx651.h"
#elif defined(MCU_RX65N)
    #include "./src/targets/rx65n/r_flash_rx65n.h"
#elif defined(MCU_RX71M)
    #include "r_flash_rx71m.h"
#else
    #error "!!! No 'targets' folder for this MCU Group !!!"
#endif

/* These functions are only used when BGO (non-blocking) mode is enabled */
#if ((FLASH_CFG_DATA_FLASH_BGO == 1) || (FLASH_CFG_CODE_FLASH_BGO == 1))
/* Callback function to call when flash erase is finished */
void FlashEraseDone(void);
/* Callback function to call when flash write is finished */
void FlashWriteDone(void);
/* Function to take care of flash errors */
void FlashError(void);
/* Callback function to call when flash blank check is finished. 'result'
   argument is 0 if block was blank and 1 if it was not */
void FlashBlankCheckDone(uint8_t result);
#endif


/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef enum
{
    FLASH_UNINITIALIZED = 0,
    FLASH_INITIALIZATION,
    FLASH_READY,
    FLASH_WRITING,
    FLASH_ERASING,
    FLASH_BLANKCHECK,
    FLASH_GETSTATUS,
    FLASH_LOCK_BIT
} flash_states_t;


typedef enum _current
{
    FLASH_CUR_INVALID,
    FLASH_CUR_IDLE,
    FLASH_CUR_CF_ERASE,
    FLASH_CUR_CF_WRITE,
    FLASH_CUR_CF_BGO_WRITE,
    FLASH_CUR_CF_BGO_ERASE,
    FLASH_CUR_DF_ERASE,
    FLASH_CUR_DF_BGO_ERASE,
    FLASH_CUR_DF_WRITE,
    FLASH_CUR_DF_BLANKCHECK,
    FLASH_CUR_DF_BGO_BLANKCHECK,
    FLASH_CUR_CF_BLANKCHECK,
    FLASH_CUR_CF_TOGGLE_STARTUPAREA,
    FLASH_CUR_CF_ACCESSWINDOW,
    FLASH_CUR_DF_BGO_WRITE,
    FLASH_CUR_CF_BGO_READ_LOCKBIT,
    FLASH_CUR_CF_BGO_WRITE_LOCKBIT,
    FLASH_CUR_FCU_INIT,
    FLASH_CUR_LOCKBIT_SET,
    FLASH_CUR_STOP
} flash_cur_t;


typedef struct _current_parameters
{
    uint32_t    src_addr;               /* Source address for operation in progress */
    uint32_t    dest_addr;              /* Destination address for operation in progress */
    uint32_t    total_count;            /* Total number of bytes to write/erase */
    uint32_t    current_count;          /* Bytes of total completed */
    flash_cur_t current_operation;      /* Operation in progress, ie. FLASH_CUR_CF_ERASE */
    uint16_t    min_pgm_size;           /* As defined for the part, usually differs for CF and DF */
    uint32_t    wait_cnt;               /* Worst case wait time for operation completion */
#if ((FLASH_TYPE == FLASH_TYPE_3) || (FLASH_TYPE == FLASH_TYPE_4))
    bool        bgo_enabled_df;
    bool        bgo_enabled_cf;
#endif
} current_param_t;


/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/
extern current_param_t g_current_parameters;            /* Current operation parameters */

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
bool flash_softwareLock (int32_t * const plock);
bool flash_softwareUnlock (int32_t * const plock);

#endif /* RX_FLASH_API_PRIVATE_HEADER_FILE */

/* end of file */

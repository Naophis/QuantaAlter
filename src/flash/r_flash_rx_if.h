#ifndef FLASH_INTERFACE_HEADER_FILE
#define FLASH_INTERFACE_HEADER_FILE

#include "r_flash_rx_config.h"
#include "r_mcu_config.h"

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/
/* Driver Version Number. */
#define FLASH_RX_VERSION_MAJOR           (2)
#define FLASH_RX_VERSION_MINOR           (10)

/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/* DRIVER INTERNAL PROGRAMMING GROUPINGS */

#define FLASH_TYPE_1    1
#define FLASH_TYPE_2    2
#define FLASH_TYPE_3    3
#define FLASH_TYPE_4    4

#define FLASH_TYPE      FLASH_TYPE_3
#define FLASH_HAS_ISR_CALLBACK  1
#define FLASH_ERASE_ASCENDING_BLOCK_NUMS    1
#define FLASH_HAS_DIFF_CF_BLOCK_SIZES   1
#define FLASH_HAS_SEQUENTIAL_CF_BLOCKS_LOCK     1

/* Return error codes */
typedef enum _flash_err {
	FLASH_SUCCESS = 0, FLASH_ERR_BUSY,         // Peripheral Busy
	FLASH_ERR_ACCESSW,      // Access window error
	FLASH_ERR_FAILURE, // Operation failure, programming or erasing error due to something other than lock bit
	FLASH_ERR_CMD_LOCKED,   // Peripheral in command locked state
	FLASH_ERR_LOCKBIT_SET,  // Pgm/Erase error due to lock bit.
	FLASH_ERR_FREQUENCY,    // Illegal frequency value attempted
	FLASH_ERR_ALIGNED,      // The address not aligned correctly for CF or DF
	FLASH_ERR_BOUNDARY,    // Writes cannot cross the 1MB boundary on some parts
	FLASH_ERR_OVERFLOW, // 'Address + number of bytes' for this operation went past the end of memory area.
	FLASH_ERR_BYTES,        // Invalid number of bytes passed
	FLASH_ERR_ADDRESS, // Invalid address or address not on a programming boundary
	FLASH_ERR_BLOCKS,       // The 'number of blocks' argument is invalid
	FLASH_ERR_PARAM,        // Illegal parameter
	FLASH_ERR_NULL_PTR,     // Received null ptr; missing required argument
	FLASH_ERR_UNSUPPORTED,  // Command not supported for this flash type
	FLASH_ERR_SECURITY,     // Pgm/Erase error due to part locked (FAW.FSPR)
	FLASH_ERR_TIMEOUT,      // Timeout Condition
} flash_err_t;

/* R_FLASH_Control() commands */
typedef enum _flash_cmd {
	FLASH_CMD_RESET, // Kill any ongoing operation and reset the flash controller
	FLASH_CMD_STATUS_GET, // Get flash status; returns FLASH_ERR_BUSY or FLASH_SUCCESS (idle)
	FLASH_CMD_SET_BGO_CALLBACK,     // Specify callback function for Flash ISR
									// Arg: flash_interrupt_config_t*
	FLASH_CMD_SWAPFLAG_GET, // Get current selection for the start-up area used at reset
							// Arg: uint8_t* (FLASH_STARTUP_SETTING_xxx)
	FLASH_CMD_SWAPFLAG_TOGGLE,      // Swap the start-up area used at reset

	FLASH_CMD_SWAPSTATE_GET, // Get the temporarily active start-up area (FLASH_SAS_xxx)
							 // Arg: uint8_t*
	FLASH_CMD_SWAPSTATE_SET, // Set the start-up area for temporary use (FLASH_SAS_xxx)
							 // Arg: uint8_t*
	FLASH_CMD_ACCESSWINDOW_SET,     // Set the Access Window boundaries for CF
									// Arg: flash_access_window_config_t*
	FLASH_CMD_ACCESSWINDOW_GET,     // Get the Access Window boundaries for CF
									// Arg: flash_access_window_config_t*
	FLASH_CMD_LOCKBIT_PROTECTION,   // Enable or disable CF lock bit protection
									// Arg: flash_lockbit_enable_t*
	FLASH_CMD_LOCKBIT_PROGRAM,  // Program the lock bit for a specific CF block.
								// Arg: flash_program_lockbit_config_t*
	FLASH_CMD_LOCKBIT_READ, // Arg: flash_read_lockbit_config_t* OR flash_lockbit_config_t*
	FLASH_CMD_LOCKBIT_WRITE,        // Arg: flash_lockbit_config_t*
	FLASH_CMD_LOCKBIT_ENABLE,       // (Flash Type 3) Enabled by default
	FLASH_CMD_LOCKBIT_DISABLE, // (Flash Type 3) Override lockbits; erase block to clear lockbit

	FLASH_CMD_CONFIG_CLOCK,     // (Flash Types 3,4) Arg: uint32_t* (FCLK speed)

	FLASH_CMD_ROM_CACHE_ENABLE,     // Enable caching of ROM
	FLASH_CMD_ROM_CACHE_DISABLE,    // Disable caching (before rewriting ROM)
	FLASH_CMD_ROM_CACHE_STATUS, // Arg: uint8_t*  (1 if cache is enabled; 0 otherwise)
	FLASH_CMD_END_ENUM
} flash_cmd_t;

/*Result type for certain operations*/
typedef enum _flash_res {
	FLASH_RES_INVALID,                      // Invalid condition
	FLASH_RES_LOCKBIT_STATE_PROTECTED, // (Flash Type 3) Result for FLASH_CMD_LOCKBIT_READ
	FLASH_RES_LOCKBIT_STATE_NON_PROTECTED, // (Flash Type 3) Result for FLASH_CMD_LOCKBIT_READ
	FLASH_RES_BLANK,                        // Result for Blank Check Function
	FLASH_RES_NOT_BLANK                     // Result for Blank Check Function
} flash_res_t;

typedef enum _flash_type {
	FLASH_TYPE_CODE_FLASH = 0, FLASH_TYPE_DATA_FLASH, FLASH_TYPE_INVALID
} flash_type_t;

/* Event type for the flash interrupt callback function (where available) */
typedef enum _flash_interrupt_event {
	FLASH_INT_EVENT_INITIALIZED,
	FLASH_INT_EVENT_ERASE_COMPLETE,
	FLASH_INT_EVENT_WRITE_COMPLETE,
	FLASH_INT_EVENT_BLANK,
	FLASH_INT_EVENT_NOT_BLANK,
	FLASH_INT_EVENT_TOGGLE_STARTUPAREA,
	FLASH_INT_EVENT_SET_ACCESSWINDOW,
	FLASH_INT_EVENT_LOCKBIT_WRITTEN,
	FLASH_INT_EVENT_LOCKBIT_PROTECTED,
	FLASH_INT_EVENT_LOCKBIT_NON_PROTECTED,
	FLASH_INT_EVENT_ERR_DF_ACCESS,
	FLASH_INT_EVENT_ERR_CF_ACCESS,
	FLASH_INT_EVENT_ERR_SECURITY,
	FLASH_INT_EVENT_ERR_CMD_LOCKED,
	FLASH_INT_EVENT_ERR_LOCKBIT_SET,
	FLASH_INT_EVENT_ERR_FAILURE,
	FLASH_INT_EVENT_END_ENUM
} flash_interrupt_event_t;

/* Control() FLASH_CMD_SET_BGO_CALLBACK */
typedef struct _flash_interrupt_config {
	void (*pcallback)(void *);
	uint8_t int_priority;
} flash_interrupt_config_t;

/*Event type for ISR callback*/
typedef struct {
	flash_interrupt_event_t event; /* Which Flash event caused this interrupt */
} flash_int_cb_args_t;


#include "flash_type_3/r_flash_type3_if.h"
/* Control() FLASH_CMD_LOCKBIT_READ, FLASH_CMD_LOCKBIT_WRITE */
typedef struct _flash_lockbit_config {
	flash_block_address_t block_start_address;
	flash_res_t result; /* Returned by API when using FLASH_CMD_LOCKBIT_READ */
	uint32_t num_blocks; /* Set by user for FLASH_CMD_LOCKBIT_WRITE */
} flash_lockbit_config_t;

#include "flash_type_3/r_flash_type3_if.h"

typedef union _flash_control_arg {
	flash_lockbit_config_t lockbit_cmd;
	flash_interrupt_config_t bgo_cmd;
} flash_control_arg_t;

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/
flash_err_t R_FLASH_Open(void);
flash_err_t R_FLASH_Write(uint32_t src_address, uint32_t dest_address,
		uint32_t num_bytes);
flash_err_t R_FLASH_Erase(flash_block_address_t block_start_address,
		uint32_t num_blocks);
flash_err_t R_FLASH_BlankCheck(uint32_t address, uint32_t num_bytes,
		flash_res_t *blank_check_result);
flash_err_t R_FLASH_Control(flash_cmd_t cmd, void *pcfg);
uint32_t R_FLASH_GetVersion(void);
void R_FlashCodeCopy(void);

#endif /* FLASH_INTERFACE_HEADER_FILE */

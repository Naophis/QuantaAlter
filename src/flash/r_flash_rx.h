#ifndef RX_FLASH_API_PRIVATE_HEADER_FILE
#define RX_FLASH_API_PRIVATE_HEADER_FILE

#include <stdbool.h>

#define FLASH_HAS_ERR_ISR           1
#define FLASH_HAS_FCU               1
#define BLANK_CHECK_SMALLEST         0
#define BLANK_CHECK_ENTIRE_BLOCK     1

#include "r_flash_rx71m.h"

typedef enum {
	FLASH_UNINITIALIZED = 0,
	FLASH_INITIALIZATION,
	FLASH_READY,
	FLASH_WRITING,
	FLASH_ERASING,
	FLASH_BLANKCHECK,
	FLASH_GETSTATUS,
	FLASH_LOCK_BIT
} flash_states_t;

typedef enum _current {
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

typedef struct _current_parameters {
	uint32_t src_addr; /* Source address for operation in progress */
	uint32_t dest_addr; /* Destination address for operation in progress */
	uint32_t total_count; /* Total number of bytes to write/erase */
	uint32_t current_count; /* Bytes of total completed */
	flash_cur_t current_operation; /* Operation in progress, ie. FLASH_CUR_CF_ERASE */
	uint16_t min_pgm_size; /* As defined for the part, usually differs for CF and DF */
	uint32_t wait_cnt; /* Worst case wait time for operation completion */
#if ((FLASH_TYPE == FLASH_TYPE_3) || (FLASH_TYPE == FLASH_TYPE_4))
	bool bgo_enabled_df;
	bool bgo_enabled_cf;
#endif
} current_param_t;

extern current_param_t g_current_parameters; /* Current operation parameters */

bool flash_softwareLock(int32_t * const plock);
bool flash_softwareUnlock(int32_t * const plock);

#endif /* RX_FLASH_API_PRIVATE_HEADER_FILE */

/* end of file */

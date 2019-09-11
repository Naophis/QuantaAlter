#ifndef FLASH_CONFIG_HEADER_FILE
#define FLASH_CONFIG_HEADER_FILE

#define FLASH_CFG_USE_FIT_BSP       (0)
#define FLASH_CFG_PARAM_CHECKING_ENABLE     (1)
#define FLASH_CFG_CODE_FLASH_ENABLE (0)
#define FLASH_CFG_DATA_FLASH_BGO   (0)      // Not supported on MCUs with no data flash
#define FLASH_CFG_CODE_FLASH_BGO   (0)
#define FLASH_CFG_CODE_FLASH_RUN_FROM_ROM   (0) // Flash type 3 only
#define FLASH_CFG_FLASH_READY_IPL   (5)     // Flash type 2 only
#define FLASH_CFG_IGNORE_LOCK_BITS  (1)     // Flash type 2 only

#endif /* FLASH_CONFIG_HEADER_FILE */

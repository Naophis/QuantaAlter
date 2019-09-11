#ifndef R_MCU_CONFIG_HEADER_FILE
#define R_MCU_CONFIG_HEADER_FILE

#include "r_flash_rx_config.h"
#define MCU_RX71M
#define MCU_RX71_ALL

#include <stdint.h>     // typedefs
#include <stdbool.h>
#include <stddef.h>     // NULL
#include <machine.h>    // nop(), xchg()
#include "../iodefine.h"

#define MCU_CFG_ICLK_HZ             (240000000)
#define MCU_CFG_FCLK_HZ             (60000000)

#define MCU_CFG_PART_MEMORY_SIZE    (0x15)

#define MCU_ROM_SIZE_BYTES              (4194304)
#define MCU_RAM_SIZE_BYTES              (524288)
#define MCU_DATA_FLASH_SIZE_BYTES       (65536)

#define FIT_NO_PTR      ((void *)0x10000000)    // Reserved space on RX
#define FIT_NO_FUNC     ((void *)0x10000000)    // Reserved space on RX

#endif /* R_MCU_CONFIG_HEADER_FILE */

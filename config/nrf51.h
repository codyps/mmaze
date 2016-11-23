#pragma once

#include <units.h>
#define ARCH armv6m
#define CORE cortex-m0
#define INCLUDE_VECTOR() <config/nrf51-vector.def>

#define CONFIG_FLASH_FILL 0xFFFFFFFF
#define CONFIG_FLASH_OFFS 0
#define CONFIG_FLASH_SIZE  KIBI(128)

#define CONFIG_RAM_OFFS 0x20000000
/* FIXME: varies with SoC variant, but can be detected at runtime */
/* FIXME: also consider supporting RAM blocks */
/* NOTE: for redbear lab ble nano 1.5, 32KiB */
/* NOTE: for redbear lab ble nano 1.0, 16KiB */
#define CONFIG_RAM_SIZE KIBI(32)

/* FIXME: technically app specific. In nrf51 case, this might be guarunteed,
 * investigate. */
#define CONFIG_SYSCLOCK MEGA(16)

#pragma once

#include <units.h>

#define CONFIG_SYSCLOCK MEGA(24)

#define CONFIG_FLASH_FILL 0xFFFFFFFF
#define INCLUDE_VECTOR()  <config/k66-vector.def>

#define CONFIG_FLASH_OFFS 0
#define CONFIG_FLASH_SIZE  KIBI(128)

/* K66P144M180SF5RMV2.pdf pg 97 */
#define SRAM_U_BASE   0x20000000
#define CONFIG_SRAM_L_SIZE KIBI(64)
#define CONFIG_SRAM_U_SIZE KIBI(192)
#define CONFIG_RAM_SIZE  (CONFIG_SRAM_L_SIZE + CONFIG_SRAM_U_SIZE)
#define CONFIG_RAM_OFFS  (SRAM_U_BASE - CONFIG_SRAM_L_SIZE)

/* Note:
 *  - LLS2 & VLLS2:
 *  	- 32KB from 0x2000_0000 is powered (RAM1)
 *  	- 32KB ending at 0x1FFF_FFFF is optionally powered (STOPCTRL[RAM2PO]) (RAM2)
 *
 * [RAM3 is remaining ram]
 *
 * Consider allowing seperate treatment of those ram regions.
 *
 * VLLS1 & VLLS0 only retain 32-byte register file.
 *
 * SRAM_L is accessed via core code bus & backdoor
 * SRAM_U is accessed via core system bus & backdoor
 *
 * Backdoor is crossbar switch to other non-core masters.
 */

#define CONFIG_FLEXNVM_OFFS 0x10000000
#define CONFIG_FLEXNVM_SIZE MEBI(64)
#define CONFIG_FLEXRAM_OFFS 0x14000000
#define CONFIG_FLEXRAM_SIZE MEBI(64)

#define CONFIG_BITBAND_AIPS0_OFFS 0x40000000
#define CONFIG_BITBAND_AIPS0_SIZE 0x00080000
#define CONFIG_BITBAND_AIPS1_OFFS 0x40080000
#define CONFIG_BITBAND_AIPS1_SIZE 0x0007f000

#define CONFIG_BITBAND_GPIO_OFFS  0x400ff000
#define CONFIG_BITBAND_GPIO_SIZE  0x00001000

/* 0x3FC is "Alternate Non-Volatile IRC User Trim"?? */
#define CONFIG_FLASH_CONFIG_FIELD_BASE 0x3FC
#define CONFIG_FLASH_CONFIG_FIELD_SIZE 16 /* 0x40C */

/*
 * External OSC = MEGA(16)
 * Internal OSC = MEGA(4)
 */

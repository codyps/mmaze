#pragma once
/* flutter wireless "Early Backer Special Edition" */

#include <units.h>

/*
 * XXX: verify
 * XXX: this is really APP + board specific, not process specific
 */
#define CONFIG_SYSCLOCK MEGA(24)

/* XXX: verify */
#define CONFIG_FLASH_FILL 0xFFFFFFFF
#define INCLUDE_VECTOR()  <config/armv7m-vector.def>

#define CONFIG_FLASH_OFFS 0x00400000
#define CONFIG_FLASH_SIZE KIBI(64)

#define CONFIG_RAM_OFFS 0x20000000
#define CONFIG_RAM_SIZE KIBI(16)

#if 0
/* Basic address space */
#define CONFIG_BOOT_MEMORY	0
#define CONFIG_INTERNAL_ROM	0x00800000
#define CONFIG_BIT_BAND_32MB	0x24000000
#define CONFIG_BIT_BAND_1MB	0x22000000
#endif

/* http://www.atmel.com/Images/Atmel-6500-32-bit-Cortex-M3-Microcontroller-SAM3S4-SAM3S2-SAM3S1_Datasheet.pdf
 *
 * sam3s1a:
 * 64KB flash
 * 16KB sram
 * 6 timers
 * 34 gpio
 * 2/1 uart
 * 8 ch adc
 * 0 12 bit dac
 * no external bus
 * no hsmci
 */

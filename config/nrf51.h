#pragma once

#include <units.h>
#define ARCH armv7m
#define CORE cortex-m0
#define INCLUDE_VECTOR() <config/nrf51-vector.def>

#define CONFIG_FLASH_FILL 0xFFFFFFFF
#define CONFIG_FLASH_OFFS 0
#define CONFIG_FLASH_SIZE  KIBI(128)

#define CONFIG_RAM_OFFS 0x20000000
/* FIXME: varies with SoC variant, but can be detected at runtime */
/* FIXME: also consider supporting RAM blocks */
#define CONFIG_RAM_SIZE KIBI(16)

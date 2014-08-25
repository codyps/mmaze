#ifndef CONFIG_LM3S_H_
#define CONFIG_LM3S_H_

#define CONFIG_FLASH_FILL 0xFFFFFFFF
#define INCLUDE_VECTOR()  <config/armv7m-vector.def>

#define CONFIG_FLASH_OFFS 0
#define CONFIG_FLASH_SIZE 0x20000

#define CONFIG_RAM_OFFS 0x20000000
#define CONFIG_RAM_SIZE 0x10000

/* For the lm3s:
 * 0x0000.0000 to 0x0001.FFFF : Flash
 * 0x2000.0000 to 0x2000.FFFF : SRAM
 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
 */
#endif

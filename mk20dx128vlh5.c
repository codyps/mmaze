/* MK20DX128VLH5
 * M = main
 * K20 = k20 family
 * D = cortex-m3 + dsp, no fpu
 * X = flash + flex
 * 128 = 128KB flash
 * () = main revision
 * V = -40 to 105 deg C
 * LH = 64LQFP
 * 5 = 50MHz max clock freq
 */

/* from http://cache.freescale.com/files/32bit/doc/ref_manual/K20P64M50SF0RM.pdf */

#define KIBI(x) ((x) * 1024)

#define GPIO_CT 40
#define EEPROM_BYTES KIBI(2)
#define SRAM_BYTES   KIBI(16)
#define FLASH_BYTES  KIBI(128)
#define TOTAL_FLASH_BYTES KIBI(160) /* ??? something with Flex? */

#define FLEX_NVM_BYTES KIBI(32)
#define FLEX_RAM_BYTES KIBI(2)

#define FLASH_BASE    0
#define FLEX_NVM_BASE 0x10000000
#define FLEX_RAM_BASE 0x14000000
#define SRAM_U_BASE   0x20000000
#define SRAM_BASE     (SRAM_U_BASE - SRAM_BYTES / 2)

#define SRAM_U_BITBAND_ALIAS_BASE 0x22000000
#define GPIO_BITBAND_ALIAS_BASE   0x400FF000
#define AIPS_AND_GPIO_BITBAND_ALIAS_BASE 0x42000000

/* "32 Byte Register file", "VBAT Register File" */
#define BACKUP_REG_BYTES 32


/* clock init */
/* SIM module's CLKDIVn registers */
/* FTLFL_FOPT[LPBOOT] sets reset value of core clock, system clock, bus clock, and flash clock */

/*
 *
 * "Erase to 1"
 *
 * FTFL_FOPT[LPBOOT]	core/system	bus		flash		desc
 * 0			0x7 (div by 8)	0x7 (div by 8)	0xf (div by 16)	low power boot
 * 1			0x0 (div by 1)  0x0 (div by 1)  0x1 (div by 2)  fast clock boot
 */

/* Flash Configuration field */

#define CONFIG_FLASH_CONFIG_FIELD_BASE 0x400
#define CONFIG_FLASH_CONFIG_FIELD_SIZE 16

#define FCF_BACKDOOR_OFFS 0x400
#define FCF_BACKDOOR_SZ   8

#define FCF_FPROT0_OFFS 0x408
#define FCF_FPROT0_SZ 4

#define FCF_FDPROT_OFFS 0x40F
#define FCF_FDPROT_SZ 1

#define FCF_FEPROT_OFFS 0x40E
#define FCF_FEPROT_SZ 1

#define FCF_FOPT_OFFS 0x40D
#define FCF_FOPT_SZ 1

#define FCF_FSEC_OFFS 0x40C
#define FCF_FSEC_SZ 1

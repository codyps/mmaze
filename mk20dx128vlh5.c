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


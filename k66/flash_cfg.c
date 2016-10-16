#include <stdint.h>

/* Dealing with the FCF:
 *  - define another memory region
 *  - always define this mess
 */
struct k66_flash_config_field {
	/* "Alternate Non-volatile IRC user trim" */
	uint8_t res[2];
	uint8_t trim_1;
	/*
	 * [0] SCFTRIM
	 * [4:1] FCTRIM
	 * [6] FCFTRIM
	 */
	uint8_t sctrim;

	uint8_t backdoor_key[8];
	uint8_t flash_prot[4];
	uint8_t flash_data_prot;
	uint8_t flash_eeprom_prot;
	uint8_t flash_option;
	uint8_t flash_security;
} fcf __attribute__((section(".flash_config_field"),__externally_visible__)) = {
};

_Static_assert(sizeof(fcf) == (4 + 8 + 4 + 1 + 1 + 1 + 1), "flash configuration field miss-sized");

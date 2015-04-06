#include "armv7m.h"
#include "sam3/pio.h"
#include "sam3/wdt.h"

void init_early(void);
void init_early(void)
{
	/*
	 * sam3s1a boots with watchdog enabled & configurable once.
	 * We disable it for now.
	 */
	SAM3_WDT.mode = (1 << SAM3_WDT_MR_WDDIS);
}

/* G = PA16
 * R = PA20
 * B = PA0
 */
__attribute__((noreturn))
void main(void)
{
	/* TODO: set up clocks */

	/* Give PIO control over the RGB pins */
	SAM3_PIOA.enable = (1 << 20) | (1 << 16) | (1 << 0);
	SAM3_PIOA.output_enable = (1 << 20) | (1 << 16) | (1 << 0);

	/* Drive them */
	for (;;) {
		SAM3_PIOA.set_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
		SAM3_PIOA.clear_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
	}
}

#include "armv7m.h"
#include "sam3/pio.h"

/* G = PA16
 * R = PA20
 * B = PA0
 */

__attribute__((noreturn))
void main(void)
{
	/* TODO: set up clocks */
	/* TODO: disable watchdog */
	/* TODO: blink led */

	/* Give PIO control over the RGB pins */
	SAM3_PIOA.enable = (1 << 20) | (1 << 16) | (1 << 0);

	/* Drive them */
	for (;;) {
		SAM3_PIOA.set_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
		SAM3_PIOA.clear_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
	}
}

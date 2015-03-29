#include "armv7m.h"
#include "sam3/pio.h"

__attribute__((__always_inline__))
static inline void nop()
{
	asm volatile ("nop");
}

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
	for (;;)
		;
}

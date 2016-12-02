#include <e1/init.h>
#include <e1/debug-led.h>

#include "k20/gpio.h"
#include "k20/port.h"
#include "k20/sim.h"

void board_init_early(void)
{
	/* enable clocks */
	SIM_SCGC5 = SIM_SCGC5_PORTC;

	/* Ensure PORT PCR is configured as GPIO */
	K20_PORT.c.pcr[5] = K20_PORT_MUX_GPIO | K20_PORT_DSE;

	/* Configure GPIO */
	K20_GPIO.c.pddr = 1 << 5;

}

void debug_led_toggle(void)
{
	K20_GPIO.c.ptor = 1 << 5;
}

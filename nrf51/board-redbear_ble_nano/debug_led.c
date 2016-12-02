#include <nrf51/gpio.h>
#include <e1/debug-led.h>
#include <e1/init.h>

/* P0_19 has our debug led */

void board_init_early(void)
{
	NRF51_GPIO.dir_set = (1 << 19);
	NRF51_GPIO.out_set = (1 << 19);
}

void debug_led_set(bool on)
{
	if (on)
		NRF51_GPIO.out_set = (1<<19);
	else
		NRF51_GPIO.out_clear = (1<<19);
}

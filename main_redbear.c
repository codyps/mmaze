#include "armv7m.h"
#include <e1/watchdog.h>
#include <e1/debug-led.h>
#include <stdbool.h>

__attribute__((noreturn))
void main(void)
{
	for (;;) {
		delay_us(1000);
		debug_led_set(false);
		delay_us(1000);
		debug_led_set(true);
	}
}

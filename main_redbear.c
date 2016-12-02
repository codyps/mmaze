#include <e1/delay.h>
#include <e1/watchdog.h>
#include <e1/debug-led.h>
#include <stdbool.h>

__attribute__((noreturn))
void main(void)
{
	for (;;) {
		delay_ms(100);
		debug_led_set(false);
		delay_ms(100);
		debug_led_set(true);
	}
}

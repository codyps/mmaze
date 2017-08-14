#include <e1/delay.h>
#include <e1/watchdog.h>
#include <e1/debug-led.h>
#include <e1/serial.h>
#include "isr.h"
#include <stdbool.h>

__attribute__((noreturn))
void main(void)
{
	for (;;) {
		delay_ms(100);
		debug_led_set(false);
		delay_ms(100);
		debug_led_set(true);
		print_char('+');
	}
}

__attribute__((__interrupt__,__noreturn__))
void isr_hard_fault(void)
{
	for (;;)
		;
}


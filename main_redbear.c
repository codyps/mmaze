#include <e1/delay.h>
#include <e1/watchdog.h>
#include <e1/debug-led.h>
#include <e1/serial.h>
#include "isr.h"
#include <stdbool.h>


#include "circ.h"
#include <assert.h>
__attribute__((noreturn))
void main(void)
{
#if 0
	size_t sz = CIRC_SPACE_SZ_FROM_HEAD_(7u, 1u, 8u);
	assert(sz == 1);

	static struct print_buf {
		/* size these to an appropriate atomic size */
		uint32_t head;
		uint32_t tail;
		uint8_t data[8];
	} print_buf;

	print_buf.head = 7;
	print_buf.tail = 1;

	sz = CIRC_SPACE_SZ_FROM_HEAD(print_buf);
	assert(sz == 1);
#endif
	__builtin_abort();

	for (;;) {
		delay_ms(100);
		debug_led_set(false);
		delay_ms(100);
		debug_led_set(true);
		print_str("012345678910\r\n");
	}
}

__attribute__((__interrupt__,__noreturn__))
void isr_hard_fault(void)
{
	// double fault to lockup
	__builtin_abort();
}


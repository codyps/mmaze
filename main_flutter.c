#include "armv7m.h"

__attribute__((__always_inline__))
static inline void nop()
{
	asm volatile ("nop");
}

__attribute__((noreturn))
void main(void)
{
	/* TODO: set up clocks */
	/* TODO: disable watchdog */
	/* TODO: blink led */
	for (;;)
		;
}

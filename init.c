
/* 0x0000.0000 to 0x0001.FFFF : Flash
 * 0x2000.0000 to 0x2000.FFFF : SRAM
 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
 */

#include <stdint.h>
__attribute__((noreturn))
extern void main (void);

extern uint32_t __bss_start__, __bss_end__, __data_start__, __data_end__, __data_load_start__;

__attribute__((externally_visible,noreturn,interrupt,section(".init0")))
void __init(void)
{
	uint32_t *s, *d;

	if (&__data_start__ != &__data_load_start__) {
		s = &__data_load_start__;
		d = &__data_start__;
		while (d < &__data_end__)
			*d++ = *s++;
	}

	d = &__bss_start__;
	while (d < &__bss_end__)
		*d++ = 0;

	main();
}

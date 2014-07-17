
/* 0x0000.0000 to 0x0001.FFFF : Flash
 * 0x2000.0000 to 0x2000.FFFF : SRAM
 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
 */

#include <stdint.h>
__attribute__((noreturn))
extern void main (void);

extern uint32_t __bss_start[], __bss_end[], __data_start[], __data_end[], __data_load_start[];

typedef void (*init_fn)(void);
extern init_fn __preinit_array_start[], __preinit_array_end[], __init_array_start[], __init_array_end[];

__attribute__((noreturn,interrupt))
void __init(void)
{
	uint32_t *s, *d;
	init_fn *f;

	s = __data_load_start;
	d = __data_start;
	while (d < __data_end)
		*d++ = *s++;

	d = __bss_start;
	while (d < __bss_end)
		*d++ = 0;

	f = __preinit_array_start;
	while (f < __preinit_array_end) {
		(*f)();
		f++;
	}

	f = __init_array_start;
	while (f < __init_array_end) {
		(*f)();
		f++;
	}

	main();
}

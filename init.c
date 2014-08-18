
#include <stdint.h>
__attribute__((noreturn))
extern void main (void);
extern void __libc_init_array(void);
extern void _init(void);

/* make __libc_init_array() happy */
__attribute__((weak))
void _init(void)
{}

#if 0
static void __libc_init_array(void)
{
	typedef void (*init_fn)(void);
	extern init_fn __preinit_array_start[], __preinit_array_end[],
	       __init_array_start[], __init_array_end[];

	init_fn *f;
	f = __preinit_array_start;
	while (f < __preinit_array_end) {
		(*f)();
		f++;
	}

	_init();

	f = __init_array_start;
	while (f < __init_array_end) {
		(*f)();
		f++;
	}
}
#endif

void __init(void);

__attribute__((noreturn,interrupt,naked))
void isr_reset(void)
{
	extern uint32_t __bss_start[], __bss_end[], __data_start[],
	       __data_end[], __data_load_start[];
	uint32_t *s, *d;

	s = __data_load_start;
	d = __data_start;
	while (d < __data_end)
		*d++ = *s++;

	d = __bss_start;
	while (d < __bss_end)
		*d++ = 0;

	__libc_init_array();
	main();
}

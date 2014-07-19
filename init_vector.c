#include <stddef.h>

__attribute__((weak,interrupt,noreturn))
void bad_interrupt(void)
{
	__builtin_trap();
}

#define IS_reset_EQ_reset 1
#define VECTOR(n) __attribute__((weak,interrupt,alias("bad_interrupt"))) void _isr_##n(void);
#define VECTOR_NULL
#include "vectors.def"
#undef VECTOR
#undef VECTOR_NULL

extern char __stack_high[];

typedef void (isr_fn)(void);
__attribute__ ((section(".vector"),externally_visible))
// void (* const vectors[])(void) = {
isr_fn *const vectors[] = {
	(isr_fn *)&__stack_high,
#define VECTOR(n) _isr_##n,
#define VECTOR_NULL (isr_fn *)NULL,
#include "vectors.def"
#undef VECTOR
#undef VECTOR_NULL
};


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

extern void __stack_high;

// Interrupt vectors table
__attribute__ ((section(".vector")))
void (* const __vectors[])(void) = {
	&__stack_high,
#define VECTOR(n) _isr_##n,
#define VECTOR_NULL NULL
#include "vectors.def"
#undef VECTOR
#undef VECTOR_NULL
};

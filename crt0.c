
__attribute__((weak,interrupt,noreturn))
void __bad_interrupt(void)
{
	__builtin_trap();
}

#define VECTOR(n) \
	__attribute__((weak,interrupt,alias("__bad_interrupt"))) void _isr_##n(void);
#define VECTOR_NULL
#include "vectors.def"
#undef VECTOR
#undef VECTOR_NULL

extern void __stack_high__;

// Interrupt vectors table
__attribute__ ((section(".isr_vector")))
void (* const __vectors[])(void) = {
	&__stack_high__,

#define VECTOR(n) _isr_##n,
#define VECTOR_NULL NULL
#include "vectors.def"
#undef VECTOR
#undef VECTOR_NULL
};


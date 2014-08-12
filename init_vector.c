#include <stddef.h>
#include <stdint.h>

__attribute__((interrupt,noreturn))
static void bad_interrupt(void)
{
	__builtin_trap();
}
/*
 * VECTOR(addres, name)
 * VECTOR_NULL
 * IRQ(address, name)
 * IRQ_START_ADDR(addr)
 * VECTOR_END(addr, vect_ct, irq_ct)
 */
 
#define VECTOR(addr, name) __attribute__((weak,interrupt,alias("bad_interrupt"))) void isr_##name(void);
#define VECTOR_NULL(addr)
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END

extern uint32_t __stack_high[];

typedef void (isr_fn)(void);
struct isr_vectors_s {
	void *stack_high;
#define VECTOR(addr, name) isr_fn *isr_##name;
#define VECTOR_NULL(addr) uint32_t null_at_##addr;
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
} isr_vectors;

__attribute__ ((section(".isr_vector"),externally_visible))
const struct isr_vectors_s vectors = {
	&__stack_high,
#define VECTOR(addr, name) &isr_##name,
#define VECTOR_NULL(addr) 0,
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
};


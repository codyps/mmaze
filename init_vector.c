#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include "init_vector.h"

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
 
/*
 * Generate a weak alias to bad_interrupt() for each VECTOR
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

/*
 * Define struct irq_vectors_s containing all vectors
 */
extern uint32_t __stack_high[];
typedef void (isr_fn)(void);
struct isr_vectors_s {
	void *stack_high;
#define IRQ(addr, name) VECTOR(addr, name)
#define VECTOR(addr, name) isr_fn *isr_##name;
#define VECTOR_NULL(addr) uint32_t null_at_##addr;
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
};

/*
 * Verify vector offsets using the above struct
 */
#define ASSERT_OFFS(addr, field) static_assert(offsetof(struct isr_vectors_s, field) == addr, "address offset incorrect");
#define VECTOR(addr, name) ASSERT_OFFS(addr, isr_##name)
#define VECTOR_NULL(addr) ASSERT_OFFS(addr, null_at_##addr)
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
#undef ASSERT_OFFS

/*
 * TODO: Verify VECTOR_END()
 * TODO: Verify IRQ_START_ADDR()
 * TODO: calculate vector & irq numbers
 * TODO: calculate NVIC regs
 */

/*
 * Populate an instance of that structure with the appropriate symbols
 */
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


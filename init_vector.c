#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include "isr.h"

void bad_interrupt(void);
__attribute__((__interrupt__,__noreturn__))
void bad_interrupt(void)
{
	for (;;)
		;
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
#define VECTOR_IRQ(addr, name) VECTOR(addr, name)
#define VECTOR_NULL(addr)
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define IRQN(num, sname, name) VECTOR(0, name)
#define IRQN_RESERVED(num)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_IRQ
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef IRQN
#undef IRQN_RESERVED
#undef VECTOR_END

/*
 * Verify vector offsets using the isr_vector struct
 */
#define ASSERT_OFFS(addr, field) static_assert(offsetof(struct isr_vector, field) == (addr), "address offset incorrect: " #field " != " #addr);
#define VECTOR(addr, name) ASSERT_OFFS(addr, isr_##name)
#define VECTOR_IRQ(addr, name) VECTOR(addr, name)
#define VECTOR_NULL(addr) ASSERT_OFFS(addr, null_at_##addr)
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQN(num, sname, name) /* TODO: check */
#define IRQN_RESERVED(num) /* TODO: check */
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_IRQ
#undef VECTOR_NULL
#undef IRQ
#undef IRQN
#undef IRQN_RESERVED
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
extern uint32_t __stack_high[];
__attribute__ ((section(".isr_vector"),externally_visible,used))
const struct isr_vector isr_vector = {
	&__stack_high,
#define VECTOR(addr, name) &isr_##name,
#define VECTOR_IRQ(addr, name) VECTOR(addr, name)
#define VECTOR_NULL(addr) 0,
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQ_START_ADDR(addr)
#define IRQN_RESERVED(num) 0,
#define IRQN(num, sname, name) VECTOR(0, name)
#define VECTOR_END(addr, vect_ct, irq_ct)
#include INCLUDE_VECTOR()
#undef VECTOR
#undef VECTOR_IRQ
#undef VECTOR_NULL
#undef IRQ
#undef IRQ_START_ADDR
#undef IRQN
#undef IRQN_RESERVED
#undef VECTOR_END
};


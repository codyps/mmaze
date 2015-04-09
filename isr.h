#pragma once

#define VECTOR(addr, name) void isr_##name(void);
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
 * Define struct irq_vectors_s containing all vectors
 */
typedef void (isr_fn)(void);
struct isr_vector {
	void *stack_high;
#define IRQ(addr, name) VECTOR(addr, name)
#define IRQN(num, sname, name)  VECTOR(0, name)
#define IRQN_RESERVED(num) uint32_t reserved_irq_##num;
#define VECTOR_IRQ(addr, name) VECTOR(addr, name)
#define VECTOR(addr, name) isr_fn *isr_##name;
#define VECTOR_NULL(addr) uint32_t null_at_##addr;
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
};

extern const struct isr_vector isr_vector;

#pragma once

/*
 * VECTOR(addres, name)
 * VECTOR_NULL
 * IRQ(address, name)
 * IRQ_START_ADDR(addr)
 * VECTOR_END(addr, vect_ct, irq_ct)
 */

/*
 * Generate a enum of IRQn numbers
 */
#define VECTOR(addr, name) IRQN__INVALID_##name,
#define VECTOR_IRQ(addr, name) IRQN_##name,
#define VECTOR_NULL(addr)  IRQN__INVALID_NULL_AT_##addr,
#define IRQN(num, sname, name) IRQN_##name,
#define IRQN_RESERVED(num) IRQN__RESERVED_##num,
#define IRQ(addr, name) IRQN_##name,
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#define IRQ_START_ADDR(addr)

enum vector_irq_num {
	IRQN__FIRST = -16, /* so "reset" == -15 */
#include INCLUDE_VECTOR()
	IRQN__LAST
};

#undef VECTOR
#undef VECTOR_IRQ
#undef VECTOR_NULL
#undef IRQN
#undef IRQN_RESERVED
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
#undef IRQ_START_ADDR

/*
 * Generate a enum of EXCPTION numbers
 */
#define VECTOR(addr, name) EXCEPTION_##name,
#define VECTOR_IRQ(addr, name) EXCEPTION_##name,
#define VECTOR_NULL(addr)  EXCEPTION__INVALID_NULL_AT_##addr,
#define IRQN_RESERVED(num) EXCPETION__RESERVED_##num,
#define IRQN(num, sname, name)  VECTOR(0, name)
#define IRQ(addr, name) EXCEPTION_##name,
#define IRQ_START_ADDR(addr)
#define VECTOR_END(addr, vect_ct, irq_ct)
#define IRQ_START_ADDR(addr)

enum vector_exception_num {
	EXCEPTION__FIRST = 0, /* so "reset" == 1 */
#include INCLUDE_VECTOR()
	EXCEPTION__LAST
};

#undef VECTOR
#undef VECTOR_IRQ
#undef VECTOR_NULL
#undef IRQN
#undef IRQN_RESERVED
#undef IRQ
#undef IRQ_START_ADDR
#undef VECTOR_END
#undef IRQ_START_ADDR

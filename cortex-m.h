/*
 * Processor support for multiple arm cortex-m variants:
 *
 *  - armv7m (cortex-m3)
 *  - armv6m (cortex-m0)
 */

#pragma once
#include <stdint.h>

__attribute__((__always_inline__))
static inline void wfi(void)
{
	__asm__ __volatile__("wfi");
}


__attribute__((__always_inline__))
static inline void nop(void)
{
	__asm__ __volatile__("nop");
}

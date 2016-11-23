#pragma once

#include "units.h"
#include "mmio-def.h"
#include "armvXm.h"

/* XXX: should names have armv7m prefixes? */
#define SYST_CSR	MMIO_32(0xE000E010)
#define SYST_CSR_ENABLE    (1 << 0)
#define SYST_CSR_TICKINT   (1 << 1)
#define SYST_CSR_CLKSOURCE (1 << 2)
#define SYST_CSR_COUNTFLAG (1 << 16)

#define SYST_RVR	MMIO_32(0xE000E014)
#define SYST_CVR	MMIO_32(0xE000E018)
#define SYST_CALIB	MMIO_32(0xE000E01C)

#define ICTR		MMIO_32(0xE000E004)

/*
 * From the armv7-m arch ref manual:
 * SHPR1 0xE000ED18 4-7
 * SHPR2 0xE000ED1C 8-11
 * SHPR3 0xE000ED20 12-15
 */
#if 0
static void syshandler_priority_set(uint8_t prio, uint8_t expn)
{

}
#endif

#define SHPR3 MMIO_32(0xE000ED20)

__attribute__((__always_inline__)) static inline void irq_enable(void)
{
	__asm__ __volatile__("cpsie i");
}

__attribute__((__always_inline__)) static inline void irq_disable(void)
{
	__asm__ __volatile__("cpsid i");
}

__attribute__((__always_inline__)) static inline void fault_enable(void)
{
	__asm__ __volatile__("cpsie f");
}

__attribute__((__always_inline__)) static inline void fault_disable(void)
{
	__asm__ __volatile__("cpsid f");
}

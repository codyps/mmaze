#ifndef ARMV7M_H_
#define ARMV7M_H_

/* XXX: should names have armv7m prefixes? */
#define SYST_CSR   (*(volatile uint32_t *)0xE000E010)
#define SYST_CSR_ENABLE    (1 << 0)
#define SYST_CSR_TICKINT   (1 << 1)
#define SYST_CSR_CLKSOURCE (1 << 2)
#define SYST_CSR_COUNTFLAG (1 << 16)

#define SYST_RVR   (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018)
#define SYST_CALIB (*(volatile uint32_t *)0xE000E01C)

#define ICTR (*(volatile uint32_t *)0xE000E004)

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

#define SHPR3 (*(volatile uint32_t *)0xE000ED20)


__attribute__((__always_inline__)) static inline void irq_enable(void)
{
	asm volatile("cpsie i");
}

__attribute__((__always_inline__)) static inline void irq_disable(void)
{
	asm volatile("cpsid i");
}

__attribute__((__always_inline__)) static inline void fault_enable(void)
{
	asm volatile("cpsie f");
}

__attribute__((__always_inline__)) static inline void fault_disable(void)
{
	asm volatile("cpsid f");
}

__attribute__((__always_inline__)) static inline void wfi(void)
{
	asm volatile("wfi");
}


static inline delay_cycles_x4(unsigned count)
{
	asm (
		"\n\t"
		"\n\t"
	:::
	);
}

#endif

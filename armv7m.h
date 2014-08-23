#ifndef ARMV7M_H_
#define ARMV7M_H_

#include "mmio-def.h"

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

__attribute__((__always_inline__)) static inline void wfi(void)
{
	__asm__ __volatile__("wfi");
}


/*
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0432c/CHDCICDF.html
 *
 * 0: 5 cycles
 * 1: 9 cycles
 * n: (n + 1) * 4 + 1 cycles
 *
 * Max delay: 0x400000001 cycles (17179869185)
 */
static inline void delay_cycles_x4p1(uint32_t ct)
{
	__asm__ __volatile__ (
		"1:	subs %0, %0, #1 \n\t" /* 1 cycle */
		"	bcs 1b"	/* 3 for all but last (1) */
	: "=r" (ct)	/* outputs */
	: "0" (ct)	/* inputs */
	: "cc"		/* clobbers */
	);
}

/*
 * At 24Mhz:
 *  24 cycles per us, max delay = 
 */
static inline void delay_us_at_freq(uint32_t us, uint32_t freq_hz)
{
	/* XXX: what are our maximum amounts here? */
	delay_cycles_x4p1(freq_hz / US_PER_SEC * us);
}

#ifdef CONFIG_SYSCLOCK
static inline void delay_us(uint32_t us)
{
	delay_us_at_freq(us, CONFIG_SYSCLOCK);
}
static inline void delay_ms(uint32_t ms)
{
	delay_us_at_freq(ms * 1000, CONFIG_SYSCLOCK);
}
#endif

#endif

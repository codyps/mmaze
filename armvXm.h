/*
 * Processor support for multiple arm variants:
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
		".syntax unified\n\t"
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
	delay_cycles_x4p1(freq_hz / US_PER_SEC * us / 4);
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

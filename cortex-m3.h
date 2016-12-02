/**
 * FIXME: timings here are cortex-m0 ones, check cortex-m3 docs!
 */

#pragma once

#include <stdint.h>
#include <armv7m.h>
/*
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0432c/CHDCICDF.html
 *
 * 0: 5 cycles
 * 1: 9 cycles
 * n: (n + 1) * 4 + 1 cycles
 *
 * Max delay: 0x400000001 cycles (17179869185)
 */
__attribute__((__always_inline__))
static inline void delay_cycles_x4p1(uint32_t ct)
{
	__asm__ __volatile__ (
		"1:	subs %0, %0, #1 \n\t" /* 1 cycle */
		/* 1 + P [some cost of prediction failure, not sure we can be
		 * certain of timing cost ] */
		"	bcc 1b \n\t"
	: "=r" (ct)	/* outputs */
	: "0" (ct)	/* inputs */
	: "cc"		/* clobbers */
	);
}

/*
 *  (x + 1) * 4 = cycles
 *  cycles / 4 = x + 1
 *  cycles / 4 - 1 = x
 */
__attribute__((__always_inline__))
static inline void delay_cycles(uint32_t cycles)
{
#if 0
	/* Use the DWT_CYCCNT register */
	__asm__ __volatile__ (
	/* load 32bit address into register */
	"ldr %0, %1 \n\t"
	"1: \n\t"
	/* load contents of *%0 */
	"   \n\t"
	/* check if loaded value is far enough along */
	: "=r" (cycles)
	);
#endif
	(void)cycles;
}

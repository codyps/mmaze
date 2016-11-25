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
static inline void delay_cycles_x4p1(uint32_t ct)
{
	__asm__ __volatile__ (
		"1:	subs %0, %0, #1 \n\t" /* 1 cycle */
		"	bcc 1b"	/* 3 for all but last (1) */
	: "=r" (ct)	/* outputs */
	: "0" (ct)	/* inputs */
	: "cc"		/* clobbers */
	);
}

#include "delay_x4p1.h"

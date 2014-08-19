#include "k20-gpio.h"

#define SYST_CSR   (*(volatile uint32_t *)0xE000E010)
#define SYST_CSR_ENABLE    (1 << 0)
#define SYST_CSR_TICKINT   (1 << 1)
#define SYST_CSR_CLKSOURCE (1 << 2)
#define SYST_CSR_COUNTFLAG (1 << 16)

#define SYST_RVR   (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018)
#define SYST_CALIB (*(volatile uint32_t *)0xE000E01C)

#define ICTR (*(volatile uint32_t *)0xE000E004)

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

__attribute__((__interrupt__))
void isr_systick(void)
{
}

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

/* NVIC_IPR_BASE 0xE000E400 */
/* */
//#define NVIC_SYS_PRI3   (*((volatile U32 *)0xE000ED20))
//NVIC_SYS_PRI3 |=  0x00FF0000

__attribute__((noreturn))
void main(void)
{
	/* On boot, PRIMASK and FAULTMASK are 0, faults and interrupts are
	 * enabled */

	/* PIN13 = LED = PTC5 */
	/* Ensure PORT PCR is configured as GPIO (probably default) */
	/* Configure GPIO */
	GPIO.c.pddr = 1 << 5;
	GPIO.c.psor = 1 << 5;
	//GPIO.c.ptor = 1 << 5;

	for (;;)
		;

	/* INIT systick for a 1ms tick */
	/* 50000000 / 1000 = 50000 ticks per second */
	/* 'ticks per second' = X
	 * 1 / X = seconds per tick
	 * 1 / 1000 = seconds / milliseconds
	 */
	SYST_RVR = CONFIG_SYSCLOCK / 1000;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_TICKINT | SYST_CSR_CLKSOURCE;

	for (;;)
		;
}

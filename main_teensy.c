#include "armv7m.h"
#include "isr.h"
#include <e1/debug-led.h>

static uint32_t count;
__attribute__((__interrupt__))
void isr_systick(void)
{
	count ++;
	if ((count % 1000) == 0)
		debug_led_toggle();
}

#define SCB_VTOR MMIO_32(0xE000ED08)

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

	/* INIT systick for a 1ms tick */
	/* 50000000 / 1000 = 50000 ticks per second */
	/* 'ticks per second' = X
	 * 1 / X = seconds per tick
	 * 1 / 1000 = seconds / milliseconds
	 */
	SYST_RVR = CONFIG_SYSCLOCK / 1000 - 1;
	SYST_CVR = 0;
	SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_TICKINT | SYST_CSR_CLKSOURCE;

	/* TODO: low power mode? */
	for (;;)
		wfi();
}

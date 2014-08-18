#include "k20-gpio.h"

#define SYST_CSR   (*(volatile uint32_t *)0xE000E010)
#define SYST_CSR_ENABLE    (1 << 0)
#define SYST_CSR_TICKINT   (1 << 1)
#define SYST_CSR_CLKSOURCE (1 << 2)
#define SYST_CSR_COUNTFLAG (1 << 16)

#define SYST_RVR   (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018)
#define SYST_CALIB (*(volatile uint32_t *)0xE000E01C)

__attribute__((__interrupt__))
void isr_systick(void)
{
	GPIO.c.ptor = 1 << 5;
}

void main(void)
{
	/* PIN13 = LED = PTC5 */
	/* Ensure PORT PCR is configured as GPIO (probably default) */
	/* Configure GPIO */
	GPIO.c.pddr =  1 << 5;

	/* INIT systick for a 1ms tick */
	SYST_RVR = CONFIG_SYSCLOCK / 1000;
	SYST_CSR = SYST_CSR_ENABLE | SYST_CSR_TICKINT | SYST_CSR_CLKSOURCE;

	for (;;)
		;
}

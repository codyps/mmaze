#include "k20-gpio.h"
#include "k20-port.h"
#include "k20-sim.h"
#include "k20-wdog.h"
#include "armv7m.h"

static uint32_t count;
__attribute__((__interrupt__))
void isr_systick(void)
{
	count ++;
	if ((count % 1000) == 0)
		K20_GPIO.c.ptor = 1 << 5;
}

#define SCB_VTOR MMIO_32(0xE000ED08)

/* NVIC_IPR_BASE 0xE000E400 */
/* */
//#define NVIC_SYS_PRI3   (*((volatile U32 *)0xE000ED20))
//NVIC_SYS_PRI3 |=  0x00FF0000

/* Dealing with the FCF:
 *  - define another memory region
 *  - always define this mess
 */
struct k20_flash_config_field {
} fcf __attribute__((section(".flash_config_field"),externally_visible)) = {
};

struct k20_usb_bdt {
} btdt __attribute__((aligned(512))) = {
};

/*
 * Flash config field "LPBOOT"
 *
 * 0 Low-power boot: OUTDIVx values in SIM_CLKDIV1 register are auto-configured
 *   at reset exit for higher divide values that produce lower power consumption at
 *   reset exit.
 * • Core and system clock divider (OUTDIV1) and bus clock divider (OUTDIV2)
 *   are 0x7 (divide by 8)
 * • Flash clock divider (OUTDIV4)is 0xF (divide by 16)
 *
 * 1 Normal boot: OUTDIVx values in SIM_CLKDIV1 register are auto-configured at
 *   reset exit for higher frequency values that produce faster operating frequencies at
 *   reset exit.
 * • Core and system clock divider (OUTDIV1) and bus clock divider (OUTDIV2)
 *   are 0x0 (divide by 1)
 * • Flash clock divider (OUTDIV4)is 0x1 (divide by 2)
 */

__attribute__((__always_inline__))
static inline void nop()
{
	asm volatile ("nop");
}

/*
 * This is called before BSS is zeroed and before constructors are called.
 */
void init_early(void);
void init_early(void)
{
	/*
	 * The teensy bootloader enables the watchdog at somepoint before it
	 * passes control to us. We need to either disable it or feed it.
	 *
	 * For now we disable it.
	 */
	K20_WDOG.unlock = K20_WDOG_UNLOCK_SEQ1;
	K20_WDOG.unlock = K20_WDOG_UNLOCK_SEQ2;
	nop();
	nop();
	K20_WDOG.stctrlh = K20_WDOG_STCTRLH_ALLOWUPDATE;
}

__attribute__((noreturn))
void main(void)
{
	/* On boot, PRIMASK and FAULTMASK are 0, faults and interrupts are
	 * enabled */
	/* PIN13 = LED = PTC5 */

	/* enable clocks */
	SIM_SCGC5 = SIM_SCGC5_PORTC;

	/* Ensure PORT PCR is configured as GPIO */
	K20_PORT.c.pcr[5] = K20_PORT_MUX_GPIO | K20_PORT_DSE;

	/* Configure GPIO */
	K20_GPIO.c.pddr = 1 << 5;

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

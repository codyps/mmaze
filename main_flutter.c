#include "armv7m.h"
#include "sam3/pio.h"
#include "sam3/wdt.h"
#include "sam3/usart.h"
#include "sam3/pmc.h"
#include "sam3/periph.h"
#include <e1/init.h>

#define TRUST_RESET 1

void init_early(void)
{
	/*
	 * sam3s1a boots with watchdog enabled & configurable once.
	 * We disable it for now.
	 */
	SAM3_WDT.mode = (1 << SAM3_WDT_MR_WDDIS);
}

/*
 * R = PA20 (PWML1 = B)
 * G = PA16 (PWML2 = C)
 * B = PA0 (PWMH0 = A)
 */

/*
 * URXD0 = PA9  = S7 = radio slave select
 * UTXD0 = PA10 = S6 = radio gpio 2
 */

static void usart0_putc(char b)
{
	/* spin while we have data ready full */
	while (!(SAM3_USART0.channel_status & SAM3_US_CSR_TXRDY))
		;
	SAM3_USART0.transmitter_holding = b;
}

/*
 * RXD0 = PA5 = D2 = free = Periph A
 * TXD0 = PA6 = D3 = free = Periph A
 */
static void usart0_init(void)
{
	/* Configure PIO */
# if !TRUST_RESET
	SAM3_PIOA.peripheral_select_1 = 0;
	SAM3_PIOA.peripheral_select_2 = 0;
# endif

	/* Enable Module Clock */

	/* Configure NVIC */

	/* Enable USART reg access */
	/* XXX: might be enabled at reset anyhow, verify */
#if !TRUST_RESET
	SAM3_USART0.write_protect_mode = SAM3_US_WPMR_WPKEY;
#endif

	/* Configure USART mode */
	SAM3_USART0.mode
		= SAM3_US_MR_CHRL(3) /* 8 bit */
		| SAM3_US_MR_PAR(1)  /* odd parity */
		| 0 << SAM3_US_MR_SYNC /* async */
		| 1 << SAM3_US_MR_FILTER
		;
	/* Configure USART interrupts */
#if 0
	/* don't need any for now, will enable DMA */
	SAM3_USART0.interrupt_enable
		= 1 << SAM3_US_IR_TXEMPTY
		;
#endif

	SAM3_USART0.reciver_timeout = 0;
	SAM3_USART0.transmitter_timeguard = 0;

	/* Configure Baud Rate */
	SAM3_USART0.baud_rate_generator = sam3s_usart_to_cd(64000000, 0, 0, 115200);

	/* Enable tx */

	/* [Re-]protect USART registers */
	SAM3_USART0.write_protect_mode = SAM3_US_WPMR_WPKEY | 1 << SAM3_US_WPMR_WPEN;
}

/*
 * flutter has a 12MHz external OSC attached to XIN & XOUT (PB9 & PB10)
 *
 * sam3s1a has 2 internal oscs: 32kHz (slow) & 4/8/12MHz (fast).
 */
static void
clock_init(void)
{
	/* NOTE: Unlock PMC if it was previously locked */

	/* 1. enable main oscillator */

	/* At reset, the 4/8/12 MHz Fast RC Oscillator (internal) is enabled
	 * with 4MHz selected and is used as MAIN CLOCK.
	 */

	/*
	 * Enable external crystal (MOSCXTEN) & set it as MAINCLK (main clock)
	 *
	 * We enable & switch at the same time as changing the source of
	 * MAINCLK is forbidden while the PLL is enabled. In other words:
	 * because we want the main crystal (external) to be the source for the
	 * PLL, we must select it as the MAINCLK before enabling the PLL.
	 *
	 * FIXME: determine if enabling & switching MAINCLK at once is alowed
	 */
	SAM3_PMC.main_oscillator
		= SAM3_PMC_CKGR_MOR_KEY
		/* enable main crystal (external) */
		| SAM3_PMC_CKGR_MOR_MOSCXTEN
		/* wait 8 * 8 slow clocks for main crystal startup
		 * XXX taken from arduino */
		| SAM3_PMC_CKGR_MOR_MOSCXTST(0x8)
		/* select the main crystal (external) */
		| SAM3_PMC_CKGR_MOR_MOSCSEL
		/* enable main crystal failure detector */
		| SAM3_PMC_CKGR_MOR_CFDEN
		;

	/* wait for main crystal to startup */
	while (!(SAM3_PMC.status & SAM3_PMC_SR_MOSCXTS))
		;

	/* start up time = 8 * MOSCXTST / SLCK = 56 slow clock cycles */

	/* 2. check main osc freq: CKGR_MCFR, once MAINFRDY is set */

	/* 3. Set PLL & Divider */
#if !TRUST_RESET
	/* XXX: pmc might be write protected */
#endif
	/* settings taken from arduino init */
	/*
	 * XXX: figure out how this is actually calculated
	 * 12 MHz (MAIN) * 32 / 3 = 128 MHz (divided below by 2 to 64 MHz)
	 */
	SAM3_PMC.plla
		= SAM3_PMC_CKGR_PLLAR_ONE
		/* multiplyer = 32 */
		| SAM3_PMC_CKGR_PLLAR_MUL(0x1f)
		/* XXX: taken from arduino */
		/* lock after 0x3f * 8 slow clock cycles */
		| SAM3_PMC_CKGR_PLLAR_COUNT(0x3f)
		/* divider = 3 */
		| SAM3_PMC_CKGR_PLLAR_DIV(0x3)
		;

	while (!(SAM3_PMC.status & SAM3_PMC_SR_LOCKA))
		;

	/* 4. select master clock & processor clock */

	/*
	 * The manual advises that updating this register must be done in 2
	 * stages. The following is the order for switching to PLL. Reverse
	 * (CSS then PRES) if switching to MAIN or SLOW clocks
	 */
	SAM3_PMC.master_clock
		= (SAM3_PMC.master_clock & ~SAM3_PMC_MCKR_PRES_MASK)
		| SAM3_PMC_MCKR_PRES(1) /* set PRES = 2 */
		;

	while (!(SAM3_PMC.status & SAM3_PMC_SR_MCKRDY))
		;

	SAM3_PMC.master_clock
		= (SAM3_PMC.master_clock & ~SAM3_PMC_MCKR_CSS_MASK)
		| SAM3_PMC_MCKR_CSS_PLLA /* set CSS = PLLA */
		;

	while (!(SAM3_PMC.status & SAM3_PMC_SR_MCKRDY))
		;

	/* 5. select programmable clocks (SCER, SCDR, SCSR & PMC_PCKx) */

	/* 6. enable peripheral clocks (PCER.) */

	/* Note: only values > 8 have any effect. See Table 10-1 "Peripheral
	 * Identifiers" PMC Clock Control column. */
	SAM3_PMC.peripheral_clock_enable_0
		= SAM3_PERIPH_ID_USART0
		| SAM3_PERIPH_ID_PIOA
		;

	/* lock acess to (some) PMC registers */
	SAM3_PMC.write_protect_mode = 0x504D43 << 8 | 1;
}

__attribute__((noreturn))
void main(void)
{
	clock_init();
	usart0_init();

	/* Give PIO control over the RGB pins */
	SAM3_PIOA.enable = (1 << 20) | (1 << 16) | (1 << 0);
	SAM3_PIOA.output_enable = (1 << 20) | (1 << 16) | (1 << 0);

	/* Drive them */
	for (;;) {
		SAM3_PIOA.set_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
		SAM3_PIOA.clear_output_data = (1 << 20) | (1 << 16) | (1 << 0);
		delay_ms(100);
		usart0_putc('X');
	}
}

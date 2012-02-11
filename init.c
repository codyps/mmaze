
/* 0x0000.0000 to 0x0001.FFFF : Flash
 * 0x2000.0000 to 0x2000.FFFF : SRAM
 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
 */

__attribute__((noreturn))
void main(void)
{
	for(;;)
		;
}

static __attribute__((interrupt, noreturn)) void hard_fault_isr(void)
{
	for(;;)
		;
}

static __attribute__((interrupt, noreturn)) void nmi_isr(void)
{
	for(;;)
		;
}

static __attribute__((interrupt, noreturn)) void reset_isr(void)
{
	/* TODO: copy data into memory */
	/* TODO: clear bss */

	main();
}

#include <stdint.h>

extern const uint32_t _estack;

__attribute__((section(".isr_vector"))) void *vec[64] = {
	_estack,   /* 0 top of stack */

	/* Processor Exceptions */

	reset_isr,      /* 1 reset, -3 */
	nmi_isr,        /* 2 nmi, -2 */
	hard_fault_isr, /* 3 hard fault, -1 */
	0,/* 4 memory managment */
	0,/* 5 bus fault */
	0,/* 6 usage fault */
	0, 0, 0, 0, /* 7-10 - */
	0,/* 11 SVCall */
	0,/* 12 Debug Monitor */
	0,/* 13 - */
	0,/* 14 PendSV */
	0,/* 15 SysTick */

	/* Interrupts */

	0,/* 16 GPIO A */
	0,/* 17 GPIO B */
	0,/* 18 GPIO C */
	0,/* 19 GPIO D */
	0,/* 20 GPIO E */
	0,/* 21 UART0 */
	0,/* 22 UART1 */
	0,/* 23 SSI0 */
	0,/* 24 I2C0 */
	0,/* 25 PWM Fault */
	0,/* 26 PWM Generator 0 */
	0,/* 27 PWM Generator 1 */
	0,/* 28 PWM Generator 2 */
	0,/* 29 QEI0 */
	0,/* 30 ADC0 Sequence 0 */
	0,/* 31 ADC0 Sequence 1 */
	0,/* 32 ADC0 Sequence 2 */
	0,/* 33 ADC0 Sequence 3 */
	0,/* 34 Watchdog Tmr 0 */
	0,/* 35 Timer 0A */
	0,/* 36 Timer 0B */
	0,/* 37 Timer 1A */
	0,/* 38 Timer 1B */
	0,/* 39 Timer 2A */
	0,/* 40 Timer 2B */
	0,/* 41 Analog Comparator 0 */
	0,/* 42 Analog Comparator 1 */
	0,/* 43 - */
	0,/* 44 System Control */
	0,/* 45 Flash memory control */
	0,/* 46 GPIO F */
	0,/* 47 GPIO G */
	0,/* 48 GPIO H */
	0,/* 49 - */
	0,/* 50 SSI1 */
	0,/* 51 Timer 3A */
	0,/* 52 Timer 3B */
	0,/* 53 I2C1 */
	0,0,0,0,0,/* 54-58 */
	0,/* 59 Hibernation Module */
	0,/* 60 USB */
	0,/* 61 PWM Generator 3 */
	0,/* 62 uDMA Software */
	0/* 63 uDMA error */
};

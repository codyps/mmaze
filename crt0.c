#include "lm3s.h"

// Dummy handler.
__attribute__((weak,interrupt,noreturn))
void __bad_interrupt(void)
{
	for(;;)
		;
}

// Weakly bind all interrupt vectors to the dummy handler.
#define _ISR(n) \
	_Pragma(weak _isr_##n = __bad_interrupt)		\
	void __attribute__((weak,interrupt)) _isr_##n(void)
_ISR(reset);
_ISR(nmi);
_ISR(hard_fault);
_ISR(mm);
_ISR(bus_fault);
_ISR(usage_fault);
_ISR(svcall);
_ISR(debug_monitor);
_ISR(pendsv);
_ISR(systick);

extern void __stack_high__;

// Interrupt vectors table
__attribute__ ((section(".isr_vector")))
void (* const __vectors[])(void) = {
	&__stack_high__,
	_isr_reset,
	_isr_nmi,
	_isr_hard_fault,
	_isr_mm,
	_isr_bus_fault,
	_isr_usage_fault,
	0,
	0,
	0,
	0,
	_isr_svcall,
	_isr_debug_monitor,
	0,
	_isr_pendsv,
	_isr_systick

	/* TODO: Others */
};


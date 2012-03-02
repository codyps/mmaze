#include "lm3s.h"

// Dummy handler.
void Default_Handler (void) { while (1); }

// Weakly bind all interrupt vectors to the dummy handler.
void __attribute__((weak)) _isr_reset(void);
void __attribute__((weak)) _isr_nmi(void);
void __attribute__((weak)) _isr_hardfault(void);
void __attribute__((weak)) MemManage_Handler(void);
void __attribute__((weak)) BusFault_Handler(void);
void __attribute__((weak)) UsageFault_Handler(void);
void __attribute__((weak)) SVC_Handler(void);
void __attribute__((weak)) DebugMon_Handler(void);
void __attribute__((weak)) PendSV_Handler(void);
void __attribute__((weak)) SysTick_Handler(void);
#pragma weak NMI_Handler        = Default_Handler
#pragma weak HardFault_Handler  = Default_Handler
#pragma weak MemManage_Handler  = Default_Handler
#pragma weak BusFault_Handler   = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler        = Default_Handler
#pragma weak DebugMon_Handler   = Default_Handler
#pragma weak PendSV_Handler     = Default_Handler
#pragma weak SysTick_Handler    = Default_Handler

extern void __stack_high__;
#define VECTOR(vname)					\
	_Pragma(weak _vector_##vname = defualt_handler)	\
	_vector_##vnmae

// Interrupt vectors table
__attribute__ ((section(".isr_vector")))
void (* const __vectors[])(void) = {
	&__stack_high__,
	_vector_reset,
	_vector_nmi,
	_vector_hardfault,
	_vector_mmu,
	_vector_busfault,
	_vector_usagefault,
	0,
	0,
	0,
	0,
	_vector_svc,
	_vector_debugmon,
	0,
	_vector_pend_svc,
	_vector_systic,
	// Vendor specific interrupts for LPC1768:
};

extern void main (void);

extern uint32_t __bss_start__, __bss_end__, __data_start__, __data_end__, __data_load_start__;

__attribute__((noreturn,interrupt))
void __init(void)
{
	uint32_t *s, *d;

	if (&__data_start__ != &__data_load_start__) {
		s = &__data_load_start__;
		d = &__data_start__;
		while (d < &__data_end__)
			*d++ = *s++;
	}

	d = &__bss_start__;
	while (d < &__bss_end__)
		*d++ = 0;

	main();
}


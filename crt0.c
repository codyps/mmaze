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

extern void __sstack__;
typedef void (* const Interrupt_Handler_P)(void);

#define VECTOR(vname)					\
	_Pragma(weak _vector_##vname = defualt_handler)	\
	_vector_##vnmae

// Interrupt vectors table
__attribute__ ((section(".isr_vector")))
Interrupt_Handler_P interrupt_vectors[] = {
	&__sstack__,
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

extern int main (void);

extern uint32_t __bss_start__, __bss_end__, __data_start__, __data_end__;

void _init0(void)
{
	uint32_t *s, *d;
	if (__data_start__ != 
	// Copy initialization data to RAM (.data section)
	s = &_etext;
	d = &_sdata;
	while (d < &_edata) *d++ = *s++;
	// Zero the remaining allocated RAM (.bss section)
	d = &_sbss;
	while (d < &_ebss)  *d++ = 0;

	// Everything is ready. Run the user program.
	main();
	while (1);
}


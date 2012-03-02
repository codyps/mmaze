
/* 0x0000.0000 to 0x0001.FFFF : Flash
 * 0x2000.0000 to 0x2000.FFFF : SRAM
 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
 */

#include "interrupt.h"

__attribute__((noreturn))
void main(void)
{
	for(;;)
		;
}

ISR(HARD_FAULT_vect)
{
	for(;;)
		;
}

ISR(NMI_vect)
{
	for(;;)
		;
}

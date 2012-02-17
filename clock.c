#include "lm3s.h"

void pllinit(void)
{

	/*5.2 Initialization and Configuration

	  The PLL is configured using direct register writes to the RCC/RCC2
	  register. If the RCC2 register is being used, the USERCC2 bit must be
	  set and the appropriate RCC2 bit/field is used. The steps required to
	  successfully change the PLL-based system clock are:

	  1. Bypass the PLL and system clock divider by setting the BYPASS bit
	  and clearing the USESYS bit in the RCC register. This configures the
	  system to run off a “raw” clock source and allows for the new
	  PLL configuration to be validated before switching the system clock
	  to the PLL.
	  */

#define SYSCTL_BYPASS_mask (1<<11)
#define SYSCTL_USESYS_mask (1<<
	uint32_t rcc = SYSCTL->rcc;
	rcc = rcc | SYSCTL_BYPASS_mask;
	rcc &= ~(1 << USESYS);
	SYSCTL->rcc = rcc;

	/*
	   2. Select the crystal value (XTAL) and oscillator source (OSCSRC),
	   and clear the PWRDN bit in RCC/RCC2. Setting the XTAL field
	   automatically pulls valid PLL configuration data for the appropriate
	   crystal, and clearing the PWRDN bit powers and enables the PLL and
	   its output.

	   3. Select the desired system divider (SYSDIV)  in RCC/RCC2 and set
	   the USESYS bit in RCC. The SYSDIV field determines the system
	   frequency for the microcontroller.

	NOTE: SYSDIV = 0x3 for 50Mhz

	   4. Wait for the PLL to lock by polling the PLLLRIS bit in the Raw
	   Interrupt Status (RIS) register.

	   5. Enable use of the PLL by clearing the BYPASS bit in RCC/RCC2.
	 */
}

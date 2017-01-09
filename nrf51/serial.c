#include <e1/init.h>
#include "uart.h"
#include "isr.h"
/*
 * UART aka serial port handling
 *
 * - UART hw has it's own ID (2), so it has it's own interrupt & register
 *   space, not shared with anything else.
 *
 * - no data buffer on transmit
 * - 6 byte buffer on recieve, overwritten on full
 */

__attribute__((__interrupt__))
void isr_uart0(void)
{
	/* determine the event which occured
	 *
	 * if TXDRDY -> previous byte was sent, load new byte if needed
	 * if RXDRDY -> read byte (unfortunately, we can only read 1 byte at a time)
	 * if ERROR -> rx break? idk
	 */
}

void arch_init(void)
{
	/* configure gpio? ("to ensure correct signal levels on the pins when
	 * the system is in OFF mode, the pins must be configured in the GPIO")
	 */


	/* configure PSELRXD, PSELRTS,
	 * PSELTRTS and PSELTXD */

	NRF51_UART.inten = 0
		| NRF51_UART_INT_RXDRDY
		| NRF51_UART_INT_TXDRDY
		| NRF51_UART_INT_ERROR
		;
}

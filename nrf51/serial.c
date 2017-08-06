#include <e1/init.h>
#include "uart.h"
#include "gpio.h"
#include "isr.h"
#include "circ_buf.h"
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

#define TXD_PIN 0
#define RXD_PIN 1

void arch_init(void)
{
	/* configure gpio ("to ensure correct signal levels on the pins when
	 * the system is in OFF mode, the pins must be configured in the GPIO")
	 */

	/* rxd: input */
	/* FIXME: input buffer? pullups? */
	NRF51_GPIO.pin_config[RXD_PIN] = 0;
	/* txd: output, value = 1 */
	NRF51_GPIO.pin_config[TXD_PIN] = 1;
	NRF51_GPIO.out_set = (1 << TXD_PIN);

	/* configure PSELRXD, PSELRTS, PSELTRTS and PSELTXD before enabling
	 * uart */
	NRF51_UART.psel_rxd = RXD_PIN;
	NRF51_UART.psel_txd = TXD_PIN;

	NRF51_UART.inten = 0
		| NRF51_UART_INT_RXDRDY
		| NRF51_UART_INT_TXDRDY
		| NRF51_UART_INT_ERROR
		;

	NRF51_UART.baudrate = NRF51_UART_BAUD_115200;

	/* FIXME: what does "ENABLE" imply? */
	NRF51_UART.enable = 4;

}

struct print_buf {
	/* size these to an appropriate atomic size */
	uint32_t head;
	uint32_t tail;
	uint8_t data[256];
} print_buf;

void print_str(const char *s)
{

}

void print_char(char c)
{
	/* add to buffer or block */
	/* trigger TX task?? (consider if it always needs triggering) */
}

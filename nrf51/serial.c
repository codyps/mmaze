#include <e1/init.h>
#include <e1/serial.h>
#include <e1/compiler.h>
#include <e1/assert.h>

#include <cortex-m.h>
#include <armv6m.h>

#include "uart.h"
#include "gpio.h"
#include "isr.h"
#include "nvic.h"
#include "circ.h"

#include <stdbool.h>

static struct print_buf {
	/* size these to an appropriate atomic size */
	uint32_t head;
	uint32_t tail;
	uint8_t data[8];
} print_buf;

/*
 * UART aka serial port handling
 *
 * - UART hw has it's own ID (2), so it has it's own interrupt & register
 *   space, not shared with anything else.
 *
 * - no data buffer on transmit
 * - 6 byte buffer on recieve, overwritten on full
 */

static void uart0_push(void)
{
	uint8_t b = *CIRC_CONTENTS(print_buf);
	ACCESS_ONCE(print_buf.tail) = CIRC_NEXT(print_buf, tail, 1);
	// order important
	NRF51_UART.txd = b;
}

__attribute__((__interrupt__))
void isr_uart0(void)
{
	/* determine the event which occured
	 *
	 * if TXDRDY -> previous byte was sent, load new byte if needed
	 * if RXDRDY -> read byte (unfortunately, we can only read 1 byte at a time)
	 * if ERROR -> rx break? idk
	 */

	if (NRF51_UART.data_sent_from_txd) {
		if (CIRC_IS_EMPTY(print_buf)) {
			NRF51_UART.stop_tx = 1;
		} else {
			uart0_push();
		}
		NRF51_UART.data_sent_from_txd = 0;
	} else {
		__builtin_abort();
	}
}

#define TXD_PIN 9
#define RXD_PIN 11

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

	// ENABLE the interrupt in the NVIC
	// Low priority
	

	/* FIXME: what does "ENABLE" imply? */
	NRF51_UART.enable = 4;
	nvic_enable(IRQN_uart0);
}

void serial_write(const void *data, size_t len)
{
	/* append to the buffer in chunks we can handle */
	for (;;) {
		if (!len)
			return;

		while (CIRC_IS_FULL(print_buf)) {
			wfi();
			barrier();
		}

		bool was_empty = CIRC_IS_EMPTY(print_buf);

		// TODO: copy array at once.
		while (!CIRC_IS_FULL(print_buf)) {
			print_buf.data[print_buf.head] = *(const uint8_t *)data;
			print_buf.head = (print_buf.head + 1) % sizeof(print_buf.data);
			data ++;
			len --;
		}

		if (was_empty) {
			uart0_push();
			NRF51_UART.start_tx = 1;
		}
	}
}

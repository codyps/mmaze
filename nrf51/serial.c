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

#include <stdbool.h>

static struct print_buf {
	/* size these to an appropriate atomic size */
	uint32_t head;
	uint32_t tail;
	uint8_t data[256];
} print_buf;

// insert at head, remove at tail. In otherwords, head moves and tail follows behind.
#define CIRC_IS_FULL(n) CIRC_IS_FULL_((n).head, (n).tail, sizeof((n).data))
#define CIRC_IS_FULL_(head, tail, sz) \
	((((head) + 1) % (sz)) == (tail))

#define CIRC_SPACE_SZ(n) CIRC_SPACE_SZ_((n).head, (n).tail, sizeof((n).data))
#define CIRC_SPACE_SZ_(head, tail, sz) \
	(((head) - (tail)) % (sz))

#define CIRC_IS_EMPTY(n) CIRC_IS_EMPTY_((n).head, (n).tail)
#define CIRC_IS_EMPTY_(head, tail) \
	((head) == (tail))

#define CIRC_SPACE_FROM_HEAD(n) CIRC_SPACE_FROM_HEAD_((n).head, &((n).data[0]))
#define CIRC_SPACE_FROM_HEAD_(head, data) \
	((data) + head)

#define CIRC_SPACE_SZ_FROM_HEAD(n) CIRC_SPACE_SZ_FROM_HEAD_((n).head, (n).tail, sizeof((n).data))
#define CIRC_SPACE_SZ_FROM_HEAD_(head, tail, size) \
	(((head) >= (tail)) \
		? ((size) - (head)) \
		: ((tail) - (head)))

#define CIRC_CONTENTS(n) CIRC_CONTENTS_((n).tail, ((n).data))
#define CIRC_CONTENTS_(tail, data) (&((data)[(tail)]))

#define CIRC_NEXT(buf, field, ct) CIRC_NEXT_((buf).field, (ct), sizeof((buf).data))
#define CIRC_NEXT_(orig, add, sz) (((orig) + (add)) % (sz))

#define CIRC_ADVANCE(buf, field, ct) CIRC_ADVANCE_((buf).field, (ct), sizeof((buf).data))
#define CIRC_ADVANCE_(orig, add, sz) ((orig) = CIRC_NEXT_((orig), (add), (sz)))

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
	NRF51_UART.txd = b;
	CIRC_ADVANCE(print_buf, tail, 1);
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

		size_t run_len = CIRC_SPACE_SZ_FROM_HEAD(print_buf);
		e1_assert(run_len);
		if (run_len > len)
			run_len = len;
		void *run = CIRC_SPACE_FROM_HEAD(print_buf);
		memcpy(run, data, run_len);
		/* MEMCPY MUST OCCUR BEFORE */
		barrier();
		CIRC_ADVANCE(print_buf, head, run_len);

		if (was_empty) {
			NRF51_UART.start_tx = 1;
			uart0_push();
		}

		data += run_len;
		len -= run_len;
	}
}

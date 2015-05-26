#include <stdint.h>

/* TODO: track BK1 vs BK0 for ping-pong endpoints */
/* Each bit is used for 1 endpoint (sam3s has 8 endpoints) */
static uint8_t bk0_next;

static void
udp_fill_ep0_for_setup(void)
{
	/* TODO: */
}

static void
udp_cancel_data(void)
{
	/* if ! EP has dual banks { */

	/* if !TXPKTRDY */
	/*	reset ep */
	/* else */
	/*	clear TXPKTRDY */
	/*	reset ep */

	/* } else { */

	/* if !TXPKTRDY */
	/*	reset ep */
	/* else */
	/*	clear TXPKTRDY, read until read back as 0 */
	/*	set TXPKTRDY, read until read back as 1 */
	/*	clear TXPKTRDY, read until read back as 0 */
	/*	reset ep */

	/* } */
}

static void
udp_state_attach(void)
{
	/* enable pull-up (PUON bit in UDP_TXVC) */
	/* transcever can remain disabled */
}

__attribute__((__interrupt__))
void
isr_udp(void)
{
	/* Causes of interrupt: */

	/* - RXSETUP: we have automatically ack-ed a setup transfer */
	/* {
	 *	- read setup packet from FIFO
	 *	- clear RXSETUP
	 * }
	 */

	/*
	 * - RX_DATA_BK0 or RX_DATA_BK1: we have recieved a Data OUT packet
	 * {
	 *	- read packet from FIFO
	 *	- clear RX_DATA_BK0 or RX_DATA_BK1
	 * }
	 */

	/*
	 * - STALLSENT: we have sent a stall packet to the host
	 * {
	 *	- clear STALLSENT
	 * }
	 */


}

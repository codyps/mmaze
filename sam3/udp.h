/* USB device port */
#pragma once

#define IF_INC() "udp.def"
#define IF_NAME udp
#define IF_PREFIX sam3
#include "gen-if.h"

static void
udp_init(void)
{
	/* TODO: program the interrupt controller */

	/* TODO: enable UDP peripheral clock in PMC */


}

static void
udp_on_disconnect()
{
	/* TODO: Avoid a floating DDP and DDM by:
	 * - disablinging the transceiver TXVDIS=1
	 * - then disabling the pull-up PUON=0
	 */
}

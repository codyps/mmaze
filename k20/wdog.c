#include <armv7m.h>
#include "wdog.h"
#include <e1/watchdog.h>

void watchdog_disable(void)
{
	/*
	 * The teensy bootloader enables the watchdog at somepoint before it
	 * passes control to us. We need to either disable it or feed it.
	 *
	 * For now we disable it.
	 */
	K20_WDOG.unlock = K20_WDOG_UNLOCK_SEQ1;
	K20_WDOG.unlock = K20_WDOG_UNLOCK_SEQ2;
	nop();
	nop();
	K20_WDOG.stctrlh = K20_WDOG_STCTRLH_ALLOWUPDATE;
}

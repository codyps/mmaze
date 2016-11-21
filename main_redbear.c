#include "armv7m.h"
#include "isr.h"
#include <e1/watchdog.h>

__attribute__((noreturn))
void main(void)
{
	/* TODO: low power mode? */
	for (;;)
		wfi();
}

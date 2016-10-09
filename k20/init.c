#include <e1/watchdog.h>
#include <e1/init.h>
void arch_init_early(void)
{
	watchdog_disable();
}


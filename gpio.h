#include "lm3s.h"

__attribute__((ctors))
void gpio_ahb_init(void)
{
	/* Use AHB for all gpio ports */
	SYSCTL->gpiohbctl = 0xff;
}

#ifndef _GPIO_H
#define _GPIO_H

#include "lm3s.h"

static inline void gpio_ahb_init(void)
{
	/* Use AHB for all gpio ports */
	SYSCTL.gpiohbctl = 0xff;
}


#endif

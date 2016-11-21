#pragma once

#define NRF51_GPIOTE_BASE 0x40006000
#define NRF51_GPIO_BASE   0x50000000


#define IF_INC() "nrf51/gpio.def"
#define IF_PREFIX nrf51
#define IF_NAME   gpio
#include "gen-if.h"

#define NRF51_GPIO (*(volatile struct nrf51_gpio *)(NRF51_GPIO_BASE))

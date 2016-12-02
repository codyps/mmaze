#pragma once
#define NRF51_UICR_BASE 0x10001000

#define IF_INC() "nrf51/uicr.def"
#define IF_PREFIX nrf51
#define IF_NAME   uicr
#include "gen-if.h"

#pragma once
#include <stdint.h>
#include <stddef.h>

#define IF_INC() "pio.def"
#define IF_PREFIX sam3
#define IF_NAME pio

#include "gen-if.h"

#define SAM3_PIOA_BASE 0x0400E0E00
#define SAM3_PIOB_BASE 0x0400E1000
#define SAM3_PIOC_BASE 0x0400E1200

#define SAM3_PIO(a) (*(volatile struct sam3_pio *)(a))
#define SAM3_PIOX(n) SAM3_PIO(SAM3_PIO##n##_BASE)
#define SAM3_PIOA SAM3_PIOX(A)
#define SAM3_PIOB SAM3_PIOX(B)
#define SAM3_PIOC SAM3_PIOX(C)

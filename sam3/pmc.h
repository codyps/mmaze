#pragma once

#define IF_INC() "pmc.def"
#define IF_NAME pmc
#define IF_PREFIX sam3
#include "gen-if.h"

#define SAM3_PMC_BASE 0x400E0400
#define SAM3_PMC (*(volatile struct sam3_pmc *)(SAM3_PMC_BASE))

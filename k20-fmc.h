#ifndef K20_FMC_H_
#define K20_FMC_H_

#include <stdint.h>

#define MMIO_32(a) (*(volatile uint32_t *)(a))

#define FMC_PFAPR	MMIO_32(0x4001F000)
#define FMC_PFB0CR	MMIO_32(0x4001F004)
#define FMC_TAGVDW0S0	MMIO_32(0x4001F100)


#endif

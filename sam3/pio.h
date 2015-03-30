#pragma once
#include <stdint.h>
#include <stddef.h>

/*
 * generate structure
 */

#define R32(addr, sn, m, ln) uint32_t ln;
#define RES_1(addr) uint32_t res_##addr;
#define RES(a1, a2) uint32_t res_##a1##_to_##a2[(a2 - a1) / 4 + 1];

struct sam3_pio {
# include "pio.def"
};

#undef R32
#undef RES_1
#undef RES

/*
 * check offsets
 */

#define R32(addr, sn, m, ln) _Static_assert(offsetof(struct sam3_pio, ln) == addr, \
		"Offset wrong: " #ln "  " #addr);
#define RES_1(addr) _Static_assert(offsetof(struct sam3_pio, res_##addr) == addr, \
		"Offset wrong for reserved: " #addr);
#define RES(a1, a2) _Static_assert(offsetof(struct sam3_pio, res_##a1##_to_##a2) == a1, \
		"Offset wrong for reserved: " #a1 " to " #a2);

#include "pio.def"

#undef R32
#undef RES_1
#undef RES

#define SAM3_PIOA_addr 0x0400E0E00
#define SAM3_PIOB_addr 0x0400E1000
#define SAM3_PIOC_addr 0x0400E1200

#define SAM3_PIO(a) (*(volatile struct sam3_pio *)(a))
#define SAM3_PIOA SAM3_PIO(SAM3_PIOA_addr)
#define SAM3_PIOB SAM3_PIO(SAM3_PIOB_addr)
#define SAM3_PIOC SAM3_PIO(SAM3_PIOC_addr)

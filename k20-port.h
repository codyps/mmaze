#ifndef K20_PORT_H_
#define K20_PORT_H_

#include <stdint.h>
#include <assert.h>

struct k20_port_regs {
	uint32_t pcr[32];
	uint32_t gpclr,
		 gpchr,
		 isfr;
	uint32_t pad[0x1000 / 4 - 32 - 3];
};

static_assert(sizeof(struct k20_port_regs) == 0x1000, "");

struct k20_port {
	struct k20_port_regs a, b, c, d, e;
};

#define K20_PORT_BASE 0x40049000
#define K20_PORT (*(volatile struct k20_port *)K20_PORT_BASE)

static_assert((uintptr_t)&K20_PORT.a == 0x40049000, "");
static_assert((uintptr_t)&K20_PORT.b == 0x4004A000, "");
static_assert((uintptr_t)&K20_PORT.c == 0x4004B000, "");

#define K20_PORT_MUX_SHIFT 8
#define K20_PORT_MUX_MASK (7 << K20_PORT_MUX_SHIFT)
#define K20_PORT_MUX_GPIO (1 << K20_PORT_MUX_SHIFT)

#define K20_PORT_DSE (1 << 6)
#define K20_PORT_ODE (1 << 5)
#define K20_PORT_PFE (1 << 4)

#endif

#ifndef K20_GPIO_H_
#define K20_GPIO_H_

#include <stdint.h>
#include <assert.h>

struct k20_gpio_regs {
	uint32_t pdor;
	uint32_t psor;
	uint32_t pcor;
	uint32_t ptor;
	uint32_t pdir;
	uint32_t pddr;
	/* pad to 64 bytes (16 u32s) */
	uint32_t res[10];
};

static_assert(sizeof(struct k20_gpio_regs) == 64);

struct k20_gpio_mod {
	struct k20_gpio_regs a, b, c, d, e;
};

static_assert(sizeof(struct k20_gpio_mod) == 0x114);

#define GPIO_BASE 0x400FF000
#define GPIO (*(volatile struct k20_gpio_mod)GPIO_BASE)

#endif

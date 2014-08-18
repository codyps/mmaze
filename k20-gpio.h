#ifndef K20_GPIO_H_
#define K20_GPIO_H_

#include <stdint.h>
#include <assert.h>

struct k20_gpio_regs {
	uint32_t pdor; /* data output */
	uint32_t psor; /* data set */
	uint32_t pcor; /* data clear */
	uint32_t ptor; /* data toggle */
	uint32_t pdir; /* data input */
	uint32_t pddr; /* data direction */
	/* pad to 64 bytes (16 u32s) */
	uint32_t res[10];
};

static_assert(sizeof(struct k20_gpio_regs) == 64, "");

struct k20_gpio_mod {
	struct k20_gpio_regs a, b, c, d, e;
};

#define GPIO_BASE 0x400FF000
#define GPIO (*(volatile struct k20_gpio_mod *)GPIO_BASE)

#endif

#ifndef K20_WDOG_H_
#define K20_WDOG_H_

#include <assert.h>

#define WDOG_STCTRLH (*(volatile uint16_t *)0x40052000)

#define K20_WDOG_BASE 0x40052000

struct k20_wdog {
	uint16_t stctrlh;
	uint16_t stctrll;
	uint16_t tovalh;
	uint16_t tovall;
	uint16_t winh;
	uint16_t winl;
	uint16_t refresh;
	uint16_t unlock;
	uint16_t tmrouth;
	uint16_t tmroutl;
	uint16_t rstcnt;
	uint16_t presc;
};

#define K20_WDOG (*(volatile struct k20_wdog *)K20_WDOG_BASE)

static_assert((uintptr_t)&K20_WDOG.presc == 0x40052016, "");


#define K20_WDOG_UNLOCK_SEQ1 0xC520
#define K20_WDOG_UNLOCK_SEQ2 0xD928

#define K20_WDOG_STCTRLH_ALLOWUPDATE (1 << 4)

#endif

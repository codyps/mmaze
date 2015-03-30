#pragma once
#include <mmio-def.h>
#include <stdint.h>

struct sam3_wdt {
	uint32_t control,
		 mode,
		 status;
};

#define SAM3_WDT_BASE (0x400E1400 + 0x50)
_Static_assert(SAM3_WDT_BASE == 0x400E1450, "SAM3 WDT BASE address mismatch");
#define SAM3_WDT (*(volatile struct sam3_wdt *)SAM3_WDT_BASE)

#define SAM3_WDT_CR MMIO_32(SAM3_WDT_BASE)
#define SAM3_WDT_CR_KEY (0xA5 << 24)
#define SAM3_WDT_CR_WDRSTT 1

#define SAM3_WDT_MR MMIO_32(SAM3_WDT_BASE + 4)
#define SAM3_WDT_MR_WDIDLEHLT 29
#define SAM3_WDT_MR_WDDBGHLT 28
#define SAM3_WDT_MR_WDD 16
#define SAM3_WDT_MR_WDDIS 15
#define SAM3_WDT_MR_WDRPROC 14
#define SAM3_WDT_MR_WDRSTEN 13
#define SAM3_WDT_MR_WDFIEN 12
#define SAM3_WDT_MR_WDV 0

#define SAM3_WDT_SR MMIO_32(SAM3_WDT_BASE + 8)
#define SAM3_WDT_SR_WDERR 1
#define SAM3_WDT_SR_WDUNF 0

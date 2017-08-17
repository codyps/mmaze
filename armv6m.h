#pragma once

#include "mmio-def.h"

#define SYSCTL_BASE 0xE000E000
#define NVIC_BASE 0xE000E100
#define DEBUG_BASE 0xE000EDF0
#define MPU_BASE 0xE000ED90

/* ARMv6-m / ARM DDI 0419D - B3.2.2 */
#define ACTLR MMIO_32(0xE000E008) // rw, reset=impl-def
#define CPUID MMIO_32(0xE000ED00) // ro, reset=impl-def
#define ICSR  MMIO_32(0xE000ED04) // rw, reset=0
#define VTOR  MMIO_32(0xE000ED08) // rw, reset=0
#define AIRCR MMIO_32(0xE000ED0C) // rw, reset bits[10:8]=0
#define SCR   MMIO_32(0xE000ED10) // rw, reset bits[4,2,1]=0
#define CCR   MMIO_32(0xE000ED14) // ro, reset bits[9:3]=-1
#define SHPR2 MMIO_32(0xE000ED1C) // rw
#define SHPR3 MMIO_32(0xE000ED20) // rw
#define SHCSR MMIO_32(0xE000ED24) // rw, reset=0
#define DFSR  MMIO_32(0xE000ED30) // rw, reset=0

// 'A', 0x41 = ARM Limited.
static inline
uint8_t cpuid_implimentor(uint32_t cpuid)
{
	return cpuid >> 24;
}

// impl-defined
static inline
uint8_t cpuid_variant(uint32_t cpuid)
{
	return (cpuid >> 20) & 0x7;
}

// 0xC = ARMv6-M
static inline
uint8_t cpuid_architecture(uint32_t cpuid)
{
	return (cpuid >> 16) & 0xf;
}

// impl-defined
static inline
uint16_t cpuid_partno(uint32_t cpuid)
{
	return (cpuid >> 4) & ((1<<(15-4))-1);
}

// impl-defined
static inline
uint8_t cpuid_revision(uint32_t cpuid)
{
	return cpuid & 0xf;
}

// set-enable
#define NVIC_ISER MMIO_32(0xE000E100) // rw, reset=0

// clear-enable
#define NVIC_ICER MMIO_32(0xE000E180) // rw, reset=0

// set-pending
#define NVIC_ISPR MMIO_32(0xE000E200) // rw, reset = 0

// clear-pending
#define NVIC_ICPR MMIO_32(0xE000E280) // rw, reset = 0

// interrupt priority
#define NVIC_IPR MMIO_32_ARRAY(0xE000E400, 0xE000E41C)

static inline
void nvic_enable(uint32_t int_num)
{
	NVIC_ISER = 1 << int_num;
}

static inline
void nvic_disable(uint32_t int_num)
{
	NVIC_ICER = 1 << int_num;
}

static inline
uint8_t nvic_priority(uint32_t int_num)
{
	uint8_t rn = int_num % 4; 
	return NVIC_IPR[int_num / 4] >> (rn * 8) >> 6;
}

static inline
void nvic_clear_pending(uint32_t int_num)
{
	NVIC_ICPR = 1 << int_num;
}

static inline
void nvic_set_priority(uint32_t int_num, uint8_t prio)
{
	prio = prio & 0x3;
	uint8_t rn = int_num % 4; 
	uint8_t n = int_num / 4;
	uint8_t rb = rn * 8;
	uint32_t o = NVIC_IPR[n];
	o &= ~((uint32_t)0xff << rb);
	o |= (prio << 6) << rb;
	NVIC_IPR[n] = o;
}

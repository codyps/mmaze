#pragma once
#include <stdint.h>

/* delay_cycles() */
#include <e1/arch-cpu.h>

__attribute__((__always_inline__))
static inline void delay_cycles(uint32_t cycles);

/*
 * freq_hz = (cycles / second)
 *
 * delay_cycles = (cycles / second) * (time)
 * delay_cycles = (cycles / second) * (time_us / us_per_sec)
 *
 * FIXME: this gets us exact numbers _if_ `freq_hz` is evenly divisible by
 * (1000 * 1000), (ie: if we're running at an even MHz). Otherwise, we lose
 * some accuracy in the division + multiply here. Consider testing for
 * constants and switching to a more accurate computation when we can do it at
 * compile time.
 * 
 * FIXME: document limits
 */
__attribute__((__always_inline__))
static inline void delay_us_at_freq(uint32_t us, uint32_t freq_hz)
{
	delay_cycles(freq_hz / US_PER_SEC * us);
}

#ifdef CONFIG_SYSCLOCK
__attribute__((__always_inline__))
static inline void delay_us(uint32_t us)
{
	delay_us_at_freq(us, CONFIG_SYSCLOCK);
}

__attribute__((__always_inline__))
static inline void delay_ms(uint32_t ms)
{
	delay_us_at_freq(ms * 1000, CONFIG_SYSCLOCK);
}
#endif


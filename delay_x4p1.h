#pragma once
#include <units.h>
#include <stdint.h>

__attribute__((__always_inline__))
static inline void delay_cycles_x4p1(uint32_t cycles);

/*
 *  (x + 1) * 4 = cycles
 *  cycles / 4 = x + 1
 *  cycles / 4 - 1 = x
 */
__attribute__((__always_inline__))
static inline void delay_cycles(uint32_t cycles)
{
	delay_cycles_x4p1(cycles / 4 - 1);
}

/*
 * At 24Mhz:
 *  24 cycles per us, max delay = 
 *  
 * freq_hz = (cycles / second)
 * 
 * delay_cycles = (cycles / second) * (time)
 * delay_cycles = (cycles / second) * (time_us / us_per_sec)
 * 
 */
__attribute__((__always_inline__))
static inline void delay_us_at_freq(uint32_t us, uint32_t freq_hz)
{
	/* XXX: what are our maximum amounts here? */
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

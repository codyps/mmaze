
/*
 * baud = selected_clock / (8 * (2 - over) * CD)
 *
 * or
 *
 * baud = selected_clock / (8 * (2 - over) * (CD + FP / 8))
 *
 *
 * FP = 0-7 (3 bits)
 * CD = 16 bits
 * selected_clock = one_of(MCK, MCK/DIV, SCK)
 * DIV = some product dependent fixed value
 *
 *
 * baud * 8 * (2 - over) * (CD + FP / 8) = selected_clock
 * baud * (2 - over) * (8 * CD + FP) = selected_clock
 *
 *
 */

#include <stdint.h>
#include <stdbool.h>

static uint32_t
to_baud(uint32_t clock_hz, bool over, uint8_t fp, uint16_t cd)
{
	/* Only works with double math, need to convert to int math */
	return clock_hz / (8 * (2 - over) * (cd + (double)fp / 8));
}


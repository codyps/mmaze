/*
 * SAM3s USART baud rate calculation test
 */


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
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

typedef unsigned long long ull;

static uint32_t
to_baud(uint32_t clock_hz, bool over, uint8_t fp, uint16_t cd)
{
	/* Only works with double math, need to convert to int math */
	return clock_hz / (8 * (2 - over) * (cd + (double)fp / 8));
}

/*
 *
(%i1) solve(baud = clock_hz / (8 * (2 - over) * (cd + fp / 8)), cd);
                         baud fp over - 2 baud fp + clock_hz
(%o1)            [cd = - -----------------------------------]
                                8 baud over - 16 baud
 */


/*
 * Divide positive or negative dividend by positive divisor and round
 * to closest integer. Result is undefined for negative divisors and
 * for negative dividends if the divisor variable type is unsigned.
 */
#define DIV_ROUND_CLOSEST(x, divisor)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisor) __d = divisor;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisor))-1) > 0 || (__x) > 0) ?	\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)

#define SAM3S_USART_TO_CD_(clock_hz, over, fp, baud) \
	((
#define SAM3S_USART_TO_CD(clock_hz, baud)


static uint32_t
to_cd(uint32_t clock_hz, bool over, uint8_t fp, uint32_t baud)
{
	return DIV_ROUND_CLOSEST(
		2 * baud * fp + clock_hz - baud * fp * over,
		16 * baud - 8 * baud * over
	);
}

static void
usage(char *pn, int e)
{
	printf(
"usage: %s <action> [action-args]\n"
"actions:\n"
"  baud <clock_hz> <over> <fp> <cd>\n"
"  cd   <clock_hz> <over> <fp> <baud>\n"
	, pn);
	exit(e);
}

static int
kstrtoull(const char *s, unsigned int base, unsigned long long *res)
{
	char *rc;
	unsigned long long r = strtoull(s, &rc, base);
	if (*s != '\0' && *rc == '\0') {
		if (r == ULLONG_MAX)
			return -errno;
		*res = r;
		return 0;
	}
	return -errno;
}

static unsigned long long
xkstrtoull(const char *s, unsigned int base) {
	unsigned long long r;
	int v = kstrtoull(s, base, &r);
	if (v) {
		fprintf(stderr, "Expected number, found '%s' (%d)\n",
				s, v);
		exit(EXIT_FAILURE);
	}
	return r;
}


int
main(int argc, char **argv)
{
	if (argc < 2) {
		usage(argv[0], 0);
	}
	unsigned long long baud, clock_hz, fp, over, cd, real_baud;

	switch (*argv[1]) {
	case 'c':
		if (argc != 6)
			usage(argv[0], 1);

		clock_hz = xkstrtoull(argv[2], 0);
		over = xkstrtoull(argv[3], 0);
		fp = xkstrtoull(argv[4], 0);
		baud = xkstrtoull(argv[5], 0);

		cd = to_cd(clock_hz, over, fp, baud);
		real_baud = to_baud(clock_hz, over, fp, cd);
		printf("cd=%#llx\n", cd);
		printf("real_baud=%lld\n", real_baud);
		printf("baud_error=%f\n", 1 - ((double)baud/ real_baud));
		break;
	case 'b':
		if (argc != 6)
			usage(argv[0], 1);

		clock_hz = xkstrtoull(argv[2], 0);
		over = xkstrtoull(argv[3], 0);
		fp = xkstrtoull(argv[4], 0);
		cd = xkstrtoull(argv[5], 0);

		baud = to_baud(clock_hz, over, fp, cd);
		printf("baud=%llu\n", baud);
		break;
	}

	return 0;
}

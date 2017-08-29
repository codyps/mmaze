#include "circ.h"
#include "test.h"

int main(void)
{
	plan_tests(512);

	// when indexes are equal, circ is empty
	// max space is (sizeof buf - 1)
	ok1(!CIRC_IS_FULL_(0u, 0u, 2u));
	ok1(CIRC_IS_FULL_(0u, 1u, 2u));

	ok_eq_fmt(CIRC_SPACE_SZ_(0u, 0u, 2u), 1, "%u");
	ok_eq_fmt(CIRC_SPACE_SZ_(0u, 1u, 2u), 0, "%u");
	unsigned i;
	unsigned s = 16;
	for (i = 0; i < s; i ++) {
		ok_eq_fmt(CIRC_SPACE_SZ_(i, i, s), s - 1, "%u");
	}

	// if tail is > head, we've wrapped head around
	// if there is no space from head to tail (ie: head + 1 = tail), we
	// don't have any space left in buf.
	for (i = 0; i < (s - 1); i ++) {
		unsigned t = (i + 1) % s;
		printf("# i=%u, t=%u, s=%u\n", i, t, s);
		ok_eq_fmt(CIRC_SPACE_SZ_(i, t, s), 0, "%u");
		ok1(CIRC_IS_FULL_(i, t, s));
		ok1(!CIRC_IS_EMPTY_(i, t));
	}
	
	unsigned j;
	for (j = 2; j < (s - 1); j++) {
		for (i = 0; i < j; i ++) {
			unsigned t = (i + j) % s;
			printf("# i=%u, t=%u, s=%u, j=%u\n", i, t, s, j);
			ok_eq_fmt(CIRC_SPACE_SZ_(i, t, s), j - 1, "%u");
			ok1(!CIRC_IS_FULL_(i, t, s));
			ok1(!CIRC_IS_EMPTY_(i, t));
		}
	}

	for (i = 0; i < (s - 2); i ++) {
		unsigned t = (i + 2) % s;
		ok_eq_fmt(CIRC_SPACE_SZ_(i, t, s), 1, "%u");
		ok1(!CIRC_IS_FULL_(i, t, s));
	}

	for (i = 0; i < (s - 3); i ++) {
		unsigned t = (i + 3) % s;
		ok_eq_fmt(CIRC_SPACE_SZ_(i, t, s), 2, "%u");
		ok1(!CIRC_IS_FULL_(i, t, s));
	}

	for (i = 0; i < (s - 4); i ++) {
		unsigned t = (i + 4) % s;
		ok_eq_fmt(CIRC_SPACE_SZ_(i, t, s), 3, "%u");
		ok1(!CIRC_IS_FULL_(i, t, s));
		ok1(!CIRC_IS_EMPTY_(i, t));
	}

	for (i = 0; i < (s - 1); i++) {
		unsigned h = (i + 1) % s;
		ok_eq_fmt(CIRC_SPACE_SZ_(h, i, s), s - 2, "%u");
		ok1(!CIRC_IS_FULL_(h, i, s));
		ok1(!CIRC_IS_EMPTY_(h, i));
	}

	unsigned h = 0;
	ok_eq_fmt(CIRC_SPACE_SZ_FROM_HEAD_(h, 1, s), 0, "%u");
	ok_eq_fmt(CIRC_SPACE_SZ_FROM_HEAD_(h, 2, s), 1, "%u");
	ok_eq_fmt(CIRC_SPACE_SZ_FROM_HEAD_(h, 3, s), 2, "%u");
	ok_eq_fmt(CIRC_SPACE_SZ_FROM_HEAD_(s-1, h, s), 0, "%u");


	ok1(!CIRC_IS_FULL_(7u, 1u, 8u));
	ok1(CIRC_IS_FULL_(7u, 0u, 8u));
	ok1(CIRC_IS_FULL_(0u, 1u, 8u));
	ok_eq_fmt(CIRC_SPACE_SZ_FROM_HEAD_(7u, 1u, 8u), 1u, "%u");

	return exit_status();
}

#pragma once

#define e1_assert(x) do { \
	if (!(x)) { \
		__builtin_abort(); \
	} \
} while (0)

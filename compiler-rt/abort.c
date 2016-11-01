#include <stdlib.h>
void abort(void)
{
	__builtin_trap();
}

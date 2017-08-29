#include <assert.h>

void __assert_func(const char *file, int line, const char *func, const char *value)
{
	(void)file;
	(void)line;
	(void)func;
	(void)value;
	__builtin_abort();
}

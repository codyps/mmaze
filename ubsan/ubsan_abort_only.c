#include "ubsan_abort.h"

void ubsan_abort(const struct ubsan_source_location* location,
                        const char *fmt, ...)
{
	(void)location;
	(void)fmt;
	__builtin_abort();
}

void ubsan_abort_1v(const struct ubsan_source_location* location,
			const struct ubsan_value_handle *v, const struct ubsan_type_descriptor *td,
                        const char *fmt, ...)
{
	(void)location;
	(void)fmt;
	(void)v;
	(void)td;
	__builtin_abort();
}


void ubsan_abort_2v(const struct ubsan_source_location* location,
			const struct ubsan_value_handle *v, const struct ubsan_type_descriptor *td,
			const struct ubsan_value_handle *v2, const struct ubsan_type_descriptor *td2,
                        const char *fmt, ...)
{
	(void)location;
	(void)fmt;
	(void)v;
	(void)td;
	(void)v2;
	(void)td2;
	__builtin_abort();
}

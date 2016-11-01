#include "ubsan.h"

__attribute__((__format__(__printf__, 2, 3)))
void ubsan_abort(const struct ubsan_source_location* location,
                        const char *fmt, ...);

__attribute__((__format__(__printf__, 4, 5)))
void ubsan_abort_1v(const struct ubsan_source_location* location,
			const struct ubsan_value_handle *v, const struct ubsan_type_descriptor *td,
                        const char *fmt, ...);

__attribute__((__format__(__printf__, 6, 7)))
void ubsan_abort_2v(const struct ubsan_source_location* location,
			const struct ubsan_value_handle *v, const struct ubsan_type_descriptor *td,
			const struct ubsan_value_handle *v2, const struct ubsan_type_descriptor *td2,
                        const char *fmt, ...);

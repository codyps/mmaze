#include <assert.h>
#include <inttypes.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ubsan.h"
#include "ubsan_abort.h"

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifndef NORETURN
#define NORETURN __attribute__((__noreturn__))
#endif

#define DEBUG
#ifndef DEBUG
#define debug(...) printf_check(__VA_ARGS__)
static inline void
__attribute__((__format__(printf, 1, 2)))
printf_check(const char *fmt, ...)
{
	(void)fmt;
}
#else
#define debug(...) fprintf(stderr, __VA_ARGS__)
#endif

enum ubsan_type_kind {
	/*
	 * struct utk_int_type_info {
	 *	u16 base_two_size: 15;
	 *	u16 is_signed: 1;
	 * }
	 *
	 * if (sizeof(value) =< sizeof(value_handle))
	 *  value_handle = value;
	 * else
	 *  value_handle = &value;
	 */
	utk_int = 0,

	/*
	 * struct utk_float_type_info {
	 *	u16 bit_width;
	 * }
	 *
	 * value_handle is set the same way as integer type, after casting the
	 * float to an int.
	 */
	utk_float = 1,

	/*
	 */
	utk_unknown = 0xffff
};

static const struct ubsan_source_location unknown_location = {
	"<unknown location>",
	0,
	0,
};

struct ubsan_type_mismatch_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *type;
	uintptr_t alignment;
	unsigned char type_check_kind;
};

EXTERN_C
void __ubsan_handle_type_mismatch(void *data_raw,
                                  void *pointer_raw)
{
	struct ubsan_type_mismatch_data *data = data_raw;
	struct ubsan_value_handle *pointer = pointer_raw;

	ubsan_abort(&data->location, "type mismatch: alignment=%" PRIuPTR " type_check_kind=%d " UTD_FMT " pointer=%p",
			data->alignment, data->type_check_kind, UTD_EXP(data->type), pointer);
}

struct ubsan_overflow_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *type;
};

static void
ubsan_report_overflow(struct ubsan_overflow_data *data,
		struct ubsan_value_handle *lhs, struct ubsan_value_handle *rhs,
		const char *kind, const char *op)
{
	ubsan_abort_2v(&data->location, lhs, data->type, rhs, data->type, "%s overflow: {} %s {}", kind, op);
}

EXTERN_C
void __ubsan_handle_add_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw)
{
	ubsan_report_overflow(data_raw, lhs_raw, rhs_raw, "add", "+");
}

EXTERN_C
void __ubsan_handle_sub_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw)
{
	ubsan_report_overflow(data_raw, lhs_raw, rhs_raw, "sub", "-");
}

EXTERN_C
void __ubsan_handle_mul_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw)
{
	ubsan_report_overflow(data_raw, lhs_raw, rhs_raw, "mul", "*");
}

EXTERN_C
void __ubsan_handle_negate_overflow(void* data_raw,
                                    void* old_value_raw)
{
	struct ubsan_overflow_data *data = data_raw;
	struct ubsan_overflow_data *old_value = old_value_raw;
	(void) old_value;
	ubsan_abort(&data->location, "negation overflow");
}

EXTERN_C
void __ubsan_handle_divrem_overflow(void* data_raw,
                                    void* lhs_raw,
                                    void* rhs_raw)
{
	ubsan_report_overflow(data_raw, lhs_raw, rhs_raw, "divrem", "/ or %");
}

struct ubsan_shift_out_of_bounds_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *lhs_type;
	const struct ubsan_type_descriptor *rhs_type;
};

EXTERN_C
void __ubsan_handle_shift_out_of_bounds(void* data_raw,
                                        void* lhs_raw,
                                        void* rhs_raw)
{
	struct ubsan_shift_out_of_bounds_data *data = data_raw;
	struct ubsan_value_handle *lhs = lhs_raw;
	struct ubsan_value_handle *rhs = rhs_raw;

	ubsan_abort_2v(&data->location,
			lhs, data->lhs_type,
			rhs, data->rhs_type,
			"shift out of bounds: {} << {}");
}

struct ubsan_out_of_bounds_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *array_type;
	const struct ubsan_type_descriptor *index_type;
};

EXTERN_C
void __ubsan_handle_out_of_bounds(void* data_raw,
                                  void* index_raw)
{
	struct ubsan_out_of_bounds_data *data = data_raw;
	struct ubsan_value_handle *index = index_raw;
	/* FIXME: show data->array_type */
	ubsan_abort_1v(&data->location, index, data->index_type, "out of bounds");
}

struct ubsan_unreachable_data
{
	struct ubsan_source_location location;
};

EXTERN_C
void __ubsan_handle_builtin_unreachable(void *data_raw)
{
	struct ubsan_unreachable_data *data = data_raw;
	ubsan_abort(&data->location, "reached unreachable");
}

EXTERN_C
void __ubsan_handle_missing_return(void *data_raw)
{
	struct ubsan_unreachable_data *data = data_raw;
	ubsan_abort(&data->location, "missing return");
}

struct ubsan_vla_bound_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *type;
};

EXTERN_C
void __ubsan_handle_vla_bound_not_positive(void* data_raw,
                                           void* bound_raw)
{
	struct ubsan_vla_bound_data *data = data_raw;
	struct ubsan_value_handle *bound = bound_raw;
	(void) bound;
	ubsan_abort(&data->location, "negative variable array length");
}

struct ubsan_float_cast_overflow_data {
	const struct ubsan_type_descriptor *from_type;
	const struct ubsan_type_descriptor *to_type;
};

struct ubsan_float_cast_overflow_data_v2 {
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *from_type;
	const struct ubsan_type_descriptor *to_type;
};

/*
 * we have to guess, no extra info is given (thanks developers!)
 *
 * First element is either: a pointer to a string, or a pointer to a type_desc.
 *
 * We have to assume we're allowed to dereference a pointer without knowing the underlying type.
 * This is all types of nasty, and probably is UB itself :)
 *
 * If the first 2 bytes look like a type_desc, then it is probably the old data
 * If they don't, it's probably v2.
 *
 * If more type_desc values are added, this will need to be updated.
 */
static bool data_looks_like_v1(void *data)
{
	uint8_t *v = *((void **)data);
	return (v[0] + v[1]) < 2 || v[0] == 0xff || v[1] == 0xff;
}

EXTERN_C
void __ubsan_handle_float_cast_overflow(void* data_raw,
                                        void* from_raw)
{
	struct ubsan_float_cast_overflow_data_v2 data;
	if (data_looks_like_v1(data_raw)) {
		struct ubsan_float_cast_overflow_data *d_v1 = data_raw;
		data.location = unknown_location;
		data.from_type = d_v1->from_type;
		data.to_type = d_v1->to_type;
	} else {
		data = *((struct ubsan_float_cast_overflow_data_v2 *)data_raw);
	}

	struct ubsan_value_handle *from = from_raw;
	ubsan_abort_1v(&data.location, from, data.from_type, "float cast overflow from {}");
}

struct ubsan_invalid_value_data
{
	struct ubsan_source_location location;
	struct ubsan_type_descriptor *type;
};

EXTERN_C
void __ubsan_handle_load_invalid_value(void* data_raw,
                                       void* value_raw)
{
	struct ubsan_invalid_value_data *data = data_raw;
	struct ubsan_value_handle *value = value_raw;
	ubsan_abort_1v(&data->location, value, data->type, "invalid value load: {}");
}

struct ubsan_function_type_mismatch_data
{
	struct ubsan_source_location location;
	const struct ubsan_type_descriptor *type;
};

EXTERN_C
void __ubsan_handle_function_type_mismatch(void* data_raw,
                                           void* value_raw)
{
	struct ubsan_function_type_mismatch_data *data = data_raw;
	struct ubsan_value_handle *value = value_raw;
	ubsan_abort_1v(&data->location, value, data->type, "function type mismatch: {}");
}

#if 0
struct ubsan_nonnull_return_data {
	struct ubsan_source_location loc;
	struct ubsan_source_location attr_loc;
};

void __ubsan_handle_nonnull_return(struct ubsan_nonnull_return_data *data)
{
	ubsan_abort(&data->loc, "nonnull return, attribute at " USL_FMT,
			USL_EXP(&data->attr_loc));
}

struct ubsan_cfi_bad_icall_data {
	struct ubsan_source_location loc;
	const struct ubsan_type_descriptor *type;
};

void __ubsan_handle_cfi_bad_icall(struct ubsan_cfi_bad_icall_data *data, struct ubsan_value_handle *function)
{
	VR(data->type, function, b);
	ubsan_abort(&data->loc, "cfi bad icall: %s", b);
}
#endif

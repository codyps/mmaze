/*
 * Generic ubsan interface definitions
 */
#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#include <stdint.h>

#define USL_EXP(x) (x)->filename, (x)->line, (x)->column
#define USL_FMT "%s:%" PRIu32 ":%" PRIu32
struct ubsan_source_location {
	const char *filename;
	uint32_t line;
	uint32_t column;
};

struct ubsan_value_handle;

#define UTD_EXP(x) (x)->type_name, (x)->type_kind, (x)->type_info
#define UTD_FMT "%s (kind:%04" PRIx16 " , info:%04" PRIx16 ")"
struct ubsan_type_descriptor {
	/* one of enum ubsan_type_kind */
	uint16_t type_kind;

	/* interp varies based on type_kind, see individual decoding notes above */
	uint16_t type_info;

	/*
	 * used as a vla, with a minimum size of 1
	 * null terminated string
	 */
	char type_name[1];
};

EXTERN_C
void __ubsan_handle_type_mismatch(void *data_raw,
                                  void *pointer_raw);
EXTERN_C
void __ubsan_handle_add_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw);

EXTERN_C
void __ubsan_handle_sub_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw);

EXTERN_C
void __ubsan_handle_mul_overflow(void* data_raw,
                                 void* lhs_raw,
                                 void* rhs_raw);

EXTERN_C
void __ubsan_handle_negate_overflow(void* data_raw,
                                    void* old_value_raw);

EXTERN_C
void __ubsan_handle_divrem_overflow(void* data_raw,
                                    void* lhs_raw,
                                    void* rhs_raw);

EXTERN_C
void __ubsan_handle_shift_out_of_bounds(void* data_raw,
                                        void* lhs_raw,
                                        void* rhs_raw);

EXTERN_C
void __ubsan_handle_out_of_bounds(void* data_raw,
                                  void* index_raw);
EXTERN_C
void __ubsan_handle_builtin_unreachable(void *data_raw);

EXTERN_C
void __ubsan_handle_missing_return(void *data_raw);

EXTERN_C
void __ubsan_handle_float_cast_overflow(void* data_raw,
                                        void* from_raw);
EXTERN_C
void __ubsan_handle_vla_bound_not_positive(void* data_raw,
                                           void* bound_raw);

EXTERN_C
void __ubsan_handle_load_invalid_value(void* data_raw,
                                       void* value_raw);
EXTERN_C
void __ubsan_handle_function_type_mismatch(void* data_raw,
                                           void* value_raw);

EXTERN_C
void __ubsan_handle_nonnull_arg(void *data_raw);

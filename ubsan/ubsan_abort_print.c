#include "ubsan_abort.h"

static uint_fast16_t
value_int_size(const struct ubsan_type_descriptor *desc)
{
	assert(desc->type_kind == utk_int);
	return 1 << (desc->type_info >> 1);
}

static uint_fast16_t
value_float_size(const struct ubsan_type_descriptor *desc)
{
	assert(desc->type_kind == utk_float);
	return desc->type_info;
}

static uint_fast16_t
value_size(const struct ubsan_type_descriptor *desc)
{
	switch (desc->type_kind) {
	case utk_int:
		return value_int_size(desc);
	case utk_float:
		return value_float_size(desc);
	default:
		return 0;
	}
}

static bool
value_is_inline(const struct ubsan_type_descriptor *desc)
{
	uint_fast16_t v = value_size(desc);
	return v && (v <= (sizeof(void *) * CHAR_BIT));
}

static bool
value_is_signed(const struct ubsan_type_descriptor *desc)
{
	assert(desc->type_kind == utk_int);
	return desc->type_info & 1;
}

static uintmax_t
load_int(const struct ubsan_type_descriptor *desc, const struct ubsan_value_handle *vh)
{
	assert(desc->type_kind == utk_int);
	uintmax_t v = 0;
	uint_fast16_t bytes;
	uint_fast16_t byte_count = value_size(desc);
	unsigned char *h = (unsigned char *)vh;
	for (bytes = 0; bytes < byte_count; bytes++) {

static int
type_render(const struct ubsan_type_descriptor *desc, char *out, size_t out_len)
{
	switch (desc->type_kind) {
	case utk_int:
		return snprintf(out, out_len, "%s (aka int%" PRIuFAST16 "_t)",
				desc->type_name,
				value_int_size(desc));
	case utk_float:
		return snprintf(out, out_len, "%s (aka float%" PRIuFAST16 "_t)",
				desc->type_name,
				value_float_size(desc));
	case utk_unknown:
		return snprintf(out, out_len, "unk{name=%s,info=%04" PRIx16 "}",
				desc->type_name,
				desc->type_info);
	default:
		return snprintf(out, out_len, "<%#04" PRIx16 ">{name=%s,info=%04" PRIx16 "}",
				desc->type_kind,
				desc->type_name,
				desc->type_info);
	}
}

#define VR(desc_, vh_, name) \
	char name[value_render((desc_), (vh_), NULL, 0) + 1]; \
	value_render((desc_), (vh_), name, sizeof(name));

static int
value_render(const struct ubsan_type_descriptor *desc, const struct ubsan_value_handle *vh,
		char *out, size_t out_len)
{
	switch (desc->type_kind) {
	case utk_int:
		if (value_is_signed(desc)) {
			return snprintf(out, out_len, "%s (aka int%" PRIuFAST16 "_t) = %jd",
					desc->type_name,
					value_int_size(desc),
					value_int(desc, vh));
		} else {
			return snprintf(out, out_len, "%s (aka uint%" PRIuFAST16 "_t) = %ju",
					desc->type_name,
					value_int_size(desc),
					value_uint(desc, vh));
		}
	case utk_float:
		return snprintf(out, out_len, "%s (aka float%" PRIdFAST16 "_t) = %Lf",
				desc->type_name,
				value_float_size(desc),
				value_float(desc, vh));
	default:
		return type_render(desc, out, out_len);
	}
}

void ubsan_abort(const struct ubsan_source_location* location,
                        const char *fmt, ...)
{
	if (!location || !location->filename)
		location = &unknown_location;
	fprintf(stderr, "Undefined behavior at " USL_FMT  ": ",
			USL_EXP(location));
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
	putc('\n', stderr);
}



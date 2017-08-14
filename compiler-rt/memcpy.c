#include <stddef.h>
#include <string.h>

void *memcpy(void *dst_v, const void *src_v, size_t len)
{
	char *dst = dst_v;
	const char *src = src_v;
	while (len) {
		*dst = *src;
		dst++;
		src++;
		len --;
	}

	return dst_v;
}

#pragma once

#include <stddef.h>
void serial_write(const void *data, size_t len);


#include <string.h>

static inline void print_str(const char *s)
{
	serial_write(s, strlen(s));
}

static inline void print_char(char c)
{
	serial_write(&c, 1);
}

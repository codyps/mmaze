#ifndef MMIO_DEF_H_
#define MMIO_DEF_H_

#include <stdint.h>
#define MMIO_32(a) (*(volatile uint32_t *)(a))

#define MMIO_32_ARRAY(start, end) (*((volatile uint32_t(*)[((end) - (start)) / 4])start))

#endif

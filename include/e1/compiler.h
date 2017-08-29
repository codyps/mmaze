#pragma once

#define barrier() __asm__ __volatile__("": : :"memory")
#define ACCESS_ONCE(v) (*((volatile __typeof__(&v))&(v)))

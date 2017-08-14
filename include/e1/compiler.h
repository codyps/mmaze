#pragma once

#define barrier() __asm__ __volatile__("": : :"memory")

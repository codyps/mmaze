#ifndef LM3S_H_
#define LM3S_H_

#ifndef __ASSEMBLER__
#include <stdint.h>
#endif

#define _VECTOR(N) __vector_ ## N
#define __packed __attribute__((packed))

#ifdef LM3S3748
# include "lm3s3748.h"
#else
# error "Unknown Processor"
#endif


#endif

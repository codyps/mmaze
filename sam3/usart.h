#pragma once

/*
 * Baudrate = selected_clock / (8 * (2 - Over) * (CD + FP / 8) )
 *
 */

#define IF_INC() "usart.def"
#define IF_NAME usart
#define IF_PREFIX sam3

#include "gen-if.h"

#define SAM3_USART0_BASE 0
#define SAM3_USART1_BASE 0

#define SAM3_USART(a) (*(volatile struct sam3_usart *)(a))
#define SAM3_USARTN(n) SAM3_USART(SAM3_USART##n##_BASE)
#define SAM3_USART0 SAM3_USARTN(0)
#define SAM3_USART1 SAM3_USARTN(1)

#define SAM3_US_CR_RTSDIS 19 /* RCS */
#define SAM3_US_CR_RTSEN  18 /* FCS */
#define SAM3_US_CR_DTRDIS 17
#define SAM3_US_CR_DTREN  16
#define SAM3_US_CR_RETTO  15
#define SAM3_US_CR_RSTNAC 14
#define SAM3_US_CR_SENDA  12
#define SAM3_US_CR_STTTO  11
#define SAM3_US_CR_STPBRK 10
#define SAM3_US_CR_STTBRK 9
#define SAM3_US_CR_RSTSTA 8
#define SAM3_US_CR_TXDIS  7
#define SAM3_US_CR_TXEN   6
#define SAM3_US_CR_RXDIS  5
#define SAM3_US_CR_RXEN   4
#define SAM3_US_CR_RSTTX  3
#define SAM3_US_CR_RSTRX  2

#define SAM3_US_MR_ONEBIT  31
#define SAM3_US_MR_MODSYNC 30
#define SAM3_US_MR_MAN     29
#define SAM3_US_MR_FILTER  28
#define SAM3_US_MR_MAX_ITERATION_SHIFT 24
#define SAM3_US_MR_MAX_ITERATION_MASK  7
#define SAM3_US_MR_MAX_ITERATION(x) (((x) & 7) << 24)
#define SAM3_US_MR_INVDATA 32
#define SAM3_US_MR_VAR_SYNC 22
#define SAM3_US_MR_DSNACK 21
#define SAM3_US_MR_INACK 20
#define SAM3_US_MR_OVER 19
#define SAM3_US_MR_CLKO 18
#define SAM3_US_MR_MODE9 17
#define SAM3_US_MR_MSBF 16
#define SAM3_US_MR_CHMODE(x) (((x) & 3) << 14)
#define SAM3_US_MR_NBSTOP(x) (((x) & 3) << 12)
#define SAM3_US_MR_PAR(x) (((x) & 7) << 9)
#define SAM3_US_MR_SYNC 8
#define SAM3_US_MR_CHRL(x) (((x) & 3) << 6)
#define SAM3_US_MR_USCLKS(x) (((x) & 3) << 4)
#define SAM3_US_MR_USART_MODE(x) (((x) & 0xf) << 0)

/* IER, IDR, IMR */
#define SAM3_US_IR_TXRDY 1
#define SAM3_US_IR_TXEMPTY 9
#define SAM3_US_IR_TXBUFE 11

#define SAM3_US_CSR_TXRDY 1
#define SAM3_US_CSR_TXEMPTY 9
#define SAM3_US_CSR_TXBFE 11

#define SAM3_US_BRGR_CD(x) (((x) & 0xffff) << 0)
#define SAM3_US_BRGR_FP(x) (((x) & 0x7) << 16)

#define SAM3_US_WPMR_WPEN 0
#define SAM3_US_WPMR_WPKEY (0x555341 << 8)

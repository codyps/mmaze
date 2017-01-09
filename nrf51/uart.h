#pragma once

#define NRF51_UART_BASE 0x40002000

#define IF_INC() "nrf51/uart.def"
#define IF_PREFIX nrf51
#define IF_NAME   uart
#include "gen-if.h"

#define NRF51_UART (*(volatile struct nrf51_uart *)(NRF51_UART_BASE))

#define NRF51_UART_INT_CTS (1<<0)
#define NRF51_UART_INT_NCTS (1<<1)
#define NRF51_UART_INT_RXDRDY (1<<2)
#define NRF51_UART_INT_TXDRDY (1<<7)
#define NRF51_UART_INT_ERROR (1<<9)
#define NRF51_UART_INT_RXTO (1<<17)

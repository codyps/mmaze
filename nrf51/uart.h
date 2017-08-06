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

/* TODO: determine format of these values so we can calculate them */
#define NRF51_UART_BAUD_115200  0x01D7E000
#define NRF51_UART_BAUD_230400  0x03AFB000
#define NRF51_UART_BAUD_250000  0x04000000
#define NRF51_UART_BAUD_460800  0x075F7000
#define NRF51_UART_BAUD_921600  0x0EBEDFA4
#define NRF51_UART_BAUD_1M      0x10000000
#define NRF51_UART_BAUD_DEFAULT NRF51_UART_BAUD_250000

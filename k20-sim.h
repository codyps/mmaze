#ifndef K20_SIM_H_
#define K20_SIM_H_

#define SIM_SOPT1    (*(volatile uint32_t *)0x40047000)
#define SIM_SOPT1_USBREGEN (1 << 31)
#define SIM_SOPT1_USBSSTBY (1 << 30)
#define SIM_SOPT1_USBVSTBY (1 << 29)
#define SIM_SOPT1_OSC32KSEL_SHIFT 18
#define SIM_SOPT1_OSC32KSEL_MASK  (3 << 18)
#define SIM_SOPT1_OSC32KSEL_SYS 0
#define SIM_SOPT1_OSC32KSEL_RTC (2 << 18)
#define SIM_SOPT1_OSC32KSEL_LPO (3 << 18)
#define SIM_SOPT1_RAMSIZE_SHIFT 12
#define SIM_SOPT1_RAMSIZE_MASK  (0xf << 12)

#define SIM_SOPT1CFG (*(volatile uint32_t *)0x40047004)
#define SIM_SOPT1CFG_USSWE (1 << 26)
#define SIM_SOPT1CFG_UVSWE (1 << 25)
#define SIM_SOPT1CFG_URWE  (1 << 24)

#define SIM_SOPT2    (*(volatile uint32_t *)0x40048004)
#define SIM_SOPT2_USBSRC	(1 << 18)
#define SIM_SOPT2_PLLFLLSEL	(1 << 16)
#define SIM_SOPT2_TRACECLKSEL	(1 << 12)
#define SIM_SOPT2_PTD7PAD	(1 << 11)
#define SIM_SOPT2_CLKOUTSEL_SHIFT 5
#define SIM_SOPT2_CLKOUTSEL_MASK (7 << 5)
#define SIM_SOPT2_RTCCLKOUTSEL	(1 << 4)

#define SIM_SOPT4    (*(volatile uint32_t *)0x4004800C)
#define SIM_SOPT4_FTM0TRG0SRC	(1 << 28)
#define SIM_SOPT4_FTM1CLKSEL	(1 << 25)
#define SIM_SOPT4_FTM0CLKSEL	(1 << 24)
#define SIM_SOPT4_FTM1CH0SRC_SHIFT 18
#define SIM_SOPT4_FTM1CH0SRC_MASK  (3 << 18)
#define SIM_SOPT4_FTM1FLT0	(1 << 4)
#define SIM_SOPT4_FTM0FLT1	(1 << 1)
#define SIM_SOPT4_FTM0FLT0	(1 << 0)

#define SIM_SOPT5    (*(volatile uint32_t *)0x40048010)
#define SIM_SOPT5_UART1RXSRC_MASK (3 << 6)
#define SIM_SOPT5_UART1RXSRC_RX 0
#define SIM_SOPT5_UART1RXSRC_CMP0 (1 << 6)
#define SIM_SOPT5_UART1RXSRC_CMP1 (2 << 6)
#define SIM_SOPT5_UART1TXSRC (1 << 4)
#define SIM_SOPT5_UART0RXSRC_MASK (3 << 2)
#define SIM_SOPT5_UART0RXSRC_RX 0
#define SIM_SOPT5_UART0RXSRC_CMP0 (1 << 2)
#define SIM_SOPT5_UART0RXSRC_CMP1 (2 << 2)
#define SIM_SOPT5_UART0TXSRC (1 << 0)

#define SIM_SOPT7    (*(volatile uint32_t *)0x40048018)
#define SIM_SOPT7_ADC0ALTTRGEN	(1 << 7)
#define SIM_SOPT7_ADC0PRETRGSEL	(1 << 4)
#define SIM_SOPT7_ADC0TRGSEL_MASK (0xf)
#define SIM_SOPT7_ADC0TRGSEL_PDB0_EXTRG 0
#define SIM_SOPT7_ADC0TRGSEL_HS_CMP0 1
#define SIM_SOPT7_ADC0TRGSEL_HS_CMP1 2
#define SIM_SOPT7_ADC0TRGSEL_PIT_TRG0 4
#define SIM_SOPT7_ADC0TRGSEL_PIT_TRG1 5

#define SIM_SDID	(*(volatile uint32_t *)0x40048024)

#define SIM_SCGC4	(*(volatile uint32_t *)0x40048034)
#define SIM_SCGC4_VREF	(1 << 20)
#define SIM_SCGC4_CMP	(1 << 19)
#define SIM_SCGC4_USBOTG (1 << 18)
#define SIM_SCGC4_UART2 (1 << 12)
#define SIM_SCGC4_UART1 (1 << 11)
#define SIM_SCGC4_UART0 (1 << 10)
#define SIM_SCGC4_I2C0  (1 << 6)
#define SIM_SCGC4_CMT	(1 << 2)
#define SIM_SCGC4_EWM	(1 << 1)

#define SIM_SCGC5	(*(volatile uint32_t *)0x40048038)
#define SIM_SCGC5_PORTE (1 << 13)
#define SIM_SCGC5_PORTD (1 << 12)
#define SIM_SCGC5_PORTC (1 << 11)
#define SIM_SCGC5_PORTB (1 << 10)
#define SIM_SCGC5_PORTA (1 << 9)
#define SIM_SCGC5_TSI	(1 << 5)
#define SIM_SCGC5_LPTIMER (1 << 0)

#define SIM_SCGC6	(*(volatile uint32_t *)0x4004803C)
#define SIM_SCGC6_RTC	(1 << 29)
#define SIM_SCGC6_ADC0	(1 << 27)

#define SIM_SCGC7	(*(volatile uint32_t *)0x40048040)

#define SIM_CLKDIV1	(*(volatile uint32_t *)0x40048044)
#define SIM_CLKDIV2	(*(volatile uint32_t *)0x40048048)

#define SIM_FCFG1	(*(volatile uint32_t *)0x4004804C)
#define SIM_FCFG2	(*(volatile uint32_t *)0x40048050)

#define SIM_UIDH	(*(volatile uint32_t *)0x40048054)
#define SIM_UIDMH	(*(volatile uint32_t *)0x40048058)

#define SIM_UIDML	(*(volatile uint32_t *)0x4004805C)
#define SIM_UIDL	(*(volatile uint32_t *)0x40048060)


#endif

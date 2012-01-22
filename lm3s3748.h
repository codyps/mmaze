/* Licence: GPLv3 with LE */

#ifndef LM3S3748_H_
#define LM3S3748_H_

#include <stdint.h>
#define __packed __attribute__((packed))

/***  System Control - SYSCTL ***/
/* base = 0x400F.E000 */
#define SYSCTL_base 0x400FE000
#define SYSCTL_size 0x1000 /* assumed */
#define SYSCTL_regct (SYSCTL_size / sizeof(uint32_t))

typedef union SYSCTL_regs_u {
	struct {
#define DID0_offs 0
#define DID1_offs 0x004
		uint32_t did[2];
#define DC0_offs 0x008
#define DC1_offs 0x010
#define DC2_offs 0x014
#define DC3_offs 0x018
#define DC4_offs 0x01C
#define DC5_offs 0x020
#define DC6_offs 0x024
#define DC7_offs 0x028
		uint32_t dc[8];

		/* XXX: JUMP */
		uint32_t res1[1];

#define PBORCTL_offs 0x030
#define PBORCTL_reset 0x00007FFD
		uint32_t pborctl;
#define LDOPCTL_offs 0x034
		uint32_t ldopctl;

		/* XXX: JUMP */
		uint32_t res2[2];

#define SRCR0_offs 0x040
#define SRCR1_offs 0x044
#define SRCR2_offs 0x048
		uint32_t srcr[3];

		/* XXX: JUMP */
		uint32_t res3[1];

#define RIS_offs 0x050
		uint32_t ris;
#define IMC_offs 0x054
		uint32_t imc;
#define MISC_offs 0x058
		uint32_t misc;
#define RESC_offs 0x05C
		uint32_t resc;
#define RCC_offs 0x060
#define RCC_reset 0x078E3AD1
		uint32_t rcc;
#define PLLCFG_offs 0x064
		uint32_t pllcfg;

		/* XXX: JUMP */
		uint32_t res4[1];

#define GPIOHBCTL_offs 0x06C
		uint32_t gpiohbctl;
#define RCC2_offs 0x070
		uint32_t rcc2;

		/* XXX: JUMP */
		uint32_t res5[2];

#define MOSCCTL_offs 0x07C
		uint32_t moscctl;

		/* XXX: JUMP */
		uint32_t res6[32];

#define RCGC0_offs 0x100
#define RCGC1_offs 0x104
#define RCGC2_offs 0x108
		uint32_t rcgc[3];

		/* XXX: JUMP */
		uint32_t res7[1];

#define SCGC0_offs 0x110
#define SCGC1_offs 0x114
#define SCGC2_offs 0x118
		uint32_t scgc[3];

		/* XXX: JUMP */
		uint32_t res8[1];

#define DCGC0_offs 0x120
#define DCGC1_offs 0x124
#define DCGC2_offs 0x128
		uint32_t dcgc[3];

		/* XXX: JUMP */
		uint32_t res9[6];

#define DSLPCLKCFG_offs 0x144
		uint32_t dslpclkcfg;
	};
	uint32_t raw[SYSCTL_regct];
} SYSCTL_t;
#define SYSCTL ((volatile SYSCTL_t *) SYSCTL_base)

/*** GPIO ***/
#define GPIO_step 0x1000
#define GPIO_regct (GPIO_step / sizeof(uint32_t))
#define GPIO_ct   8

/* 0x1000 / sizeof(uint32_t) = 1024 = 0x400 */
typedef union GPIO_regs_u {
	struct {
/* GPIODATA
 * Uses a special address masking scheme */
#define GPIODATA_offs 0
#define GPIODATA_reset 0
#define GPIODATA_mask 0xff
		uint32_t data[256]; /* size = 0x400 */

#define GPIODIR_offs  0x400
#define GPIODIR_reset 0
#define GPIODIR_mask  0xff
		uint32_t dir;

#define GPIOIS_offs  0x404
#define GPIOIS_reset 0
#define GPIOIS_mask  0xff
		uint32_t is;

#define GPIOIBE_offs  0x408
#define GPIOIBE_reset 0
		uint32_t ibe;

#define GPIOIEV_offs  0x40C
#define GPIOIEV_reset 0
		uint32_t iev;

#define GPIOIM_offs  0x410
#define GPIOIM_reset 0
		uint32_t im;

#define GPIORIS_offs  0x414
#define GPIORIS_reset 0
		uint32_t ris;

#define GPIOMIS_offs  0x418
#define GPIOMIS_reset 0
		uint32_t mis;

#define GPIOICR_offs  0x41C
#define GPIOICR_reset 0
		uint32_t icr;

#define GPIOAFSEL_offs 0x420
// #define GPIOAFSEL_reset -
		uint32_t afsel;

		/* XXX: JUMP */
		uint32_t res1[136];

#define GPIODR2R_offs  0x500
#define GPIODR2R_reset 0x000000FF
		uint32_t dr2r;

#define GPIODR4R_offs  0x504
#define GPIODR4R_reset 0
		uint32_t dr4r;

#define GPIODR8R_offs  0x508
#define GPIODR8R_reset 0
		uint32_t dr8r;

#define GPIOODR_offs   0x50C
#define GPIOODR_reset  0
		uint32_t odr;

#define GPIOPUR_offs  0x510
//#define GPIOPUR_reset -
		uint32_t pur;

#define GPIOPDR_offs  0x514
#define GPIOPDR_reset 0
		uint32_t pdr;

#define GPIOSLR_offs  0x518
#define GPIOSLR_reset 0
		uint32_t slr;

#define GPIODEN_offs  0x51C
//#define GPIODEN_reset -
		uint32_t den;

#define GPIOLOCK_offs  0x520
#define GPIOLOCK_reset 0x00000001
		uint32_t lock;

#define GPIOCR_offs  0x524
//#define GPIOCR_reset -
		uint32_t cr;

		/* GPIO Analog Mode Select - GPIOAMSEL
		 * Only valid for ports D and E */
#define GPIOAMSEL_offs  0x528
#define GPIOAMSEL_reset 0
		uint32_t amsel;

		/* XXX: jump */
		uint32_t res2[681];

#define GPIOPeriphID4_offs 0xFD0
		uint32_t periph_id4;
#define GPIOPeriphID5_offs 0xFD4
		uint32_t periph_id5;
#define GPIOPeriphID6_offs 0xFD8
		uint32_t periph_id6;
#define GPIOPeriphID7_offs 0xFDC
		uint32_t periph_id7;
#define GPIOPeriphID0_offs 0xFE0
		uint32_t periph_id0;
#define GPIOPeriphID1_offs 0xFE4
		uint32_t periph_id1;
#define GPIOPeriphID2_offs 0xFE8
		uint32_t periph_id2;
#define GPIOPeriphID3_offs 0xFEC
		uint32_t periph_id3;

#define GPIOPCellID0_offs 0xFF0
		uint32_t pcell_id0;
#define GPIOPCellID1_offs 0xFF4
		uint32_t pcell_id1;
#define GPIOPCellID2_offs 0xFF8
		uint32_t pcell_id2;
#define GPIOPCellID3_offs 0xFFC
		uint32_t pcell_id3;
	};
	uint32_t raw[GPIO_regct];
} GPIO_regs_t;

/* GPIO AHB bases
 * A 0x4005.8000
 * B 0x4005.9000
 * C 0x4005.A000
 * D 0x4005.B000
 * E 0x4005.C000
 * F 0x4005.D000
 * G 0x4005.E000
 * H 0x4005.F000
 */

typedef union GPIO_AHB_u {
	struct {
		GPIO_regs A;
		GPIO_regs B;
		GPIO_regs C;
		GPIO_regs D;
		GPIO_regs E;
		GPIO_regs F;
		GPIO_regs G;
		GPIO_regs H;
	};
	GPIO_regs raw[GPIO_ct];
} GPIO_AHB_t;

#define GPIO_AHB_base 0x40058000
#define GPIO_AHB ((volatile GPIO_AHB_t *) GPIO_AHB_base)

/* GPIO APB
 * A 0x4000.4000
 * B 0x4000.5000
 * C 0x4000.6000
 * D 0x4000.7000
 * E 0x4002.4000
 * F 0x4002.5000
 * G 0x4002.6000
 * H 0x4002.7000
 */

typedef struct GPIO_APB_s {
	GPIO_regs A;
	GPIO_regs B;
	GPIO_regs C;
	GPIO_regs D;

	uint32_t res1[0x7000];

	GPIO_regs E;
	GPIO_regs F;
	GPIO_regs G;
	GPIO_regs H;
} GPIO_APB_t;

#define GPIO_APB_base1 0x40004000
#define GPIO_APB_base2 0x40024000
#define GPIO_APB ((volatile GPIO_APB_t *) GPIO_APB_base1)

/*** ADC ***/

typedef struct ADC_s {
#define ADC_ACTSS_offs 0
	uint32_t actss;
#define ADC_CRIS_offs  0x004
	uint32_t cris;
#define ADC_IM_offs    0x008
	uint32_t im;
#define ADC_ISC_offs   0x00C
	uint32_t isc;
#define ADC_OSTAT_offs 0x010
	uint32_t ostat;
#define ADC_EMUX_offs  0x014
	uint32_t emux;
#define ADC_USTAT_offs 0x018
	uint32_t ustat;

	/* XXX: JUMP */
	uint32_t res_1[1];

#define ADC_SSPRI_offs 0x020
	uint32_t sspri;

	/* XXX: JUMP */
	uint32_t res_2[1];

#define ADC_PSSI_offs  0x028
	uint32_t pssi;

	/* XXX: JUMP */
	uint32_t res_3[1];

#define ADC_SAC_offs   0x030
	uint32_t sac;

	/* XXX: JUMP */
	uint32_t res_4[3];

#define ADC_SSMUX0_offs   0x040
#define ADC_SSCTL0_offs   0x044
#define ADC_SSFIFO0_offs  0x048
#define ADC_SSFSTAT0_offs 0x04C

#define ADC_SSMUX1_offs   0x060
#define ADC_SSCTL1_offs   0x064
#define ADC_SSFIFO1_offs  0x068
#define ADC_SSFSTAT1_offs 0x06C

#define ADC_SSMUX2_offs   0x080
#define ADC_SSCTL2_offs   0x084
#define ADC_SSFIFO2_offs  0x088
#define ADC_SSFSTAT2_offs 0x08C

#define ADC_SSMUX3_offs   0x0A0
#define ADC_SSCTL3_offs   0x0A4
#define ADC_SSFIFO3_offs  0x0A8
#define ADC_SSFSTAT3_offs 0x0AC

	union {
		struct {
			uint32_t mux;
			uint32_t ctl;
			uint32_t fifo;
			uint32_t fstat;

			uint32_t res1;
		} ss[4];
		struct {
			uint32_t ssmux0;
			uint32_t ssctl0;
			uint32_t ssfifo0;
			uint32_t ssfstat0;
			uint32_t ss_res0;

			uint32_t ssmux1;
			uint32_t ssctl1;
			uint32_t ssfifo1;
			uint32_t ssfstat1;
			uint32_t ss_res1;

			uint32_t ssmux2;
			uint32_t ssctl2;
			uint32_t ssfifo2;
			uint32_t ssfstat2;
			uint32_t ss_res2;

			uint32_t ssmux3;
			uint32_t ssctl3;
			uint32_t ssfifo3;
			uint32_t ssfstat3;
			uint32_t ss_res3;
		};
	};
} ADC_t;

#define ADC_base 0x40038000
#define ADC ((volatile ADC_t *)ADC_base)

#endif


/* Licence: GPLv3 with Linking Exception */

#ifndef LM3S3748_H_
#define LM3S3748_H_

#define FLASH_start 0
#define FLASH_end   0x0001FFFF

#include <stdint.h>
#define __packed __attribute__((packed))

/*** Watchdog timer 0 - WDT ***/

/* Example:
 *	WDT->load = 10;
 */
typedef struct WDT_regs_s {
#define WDT_LOAD_offs 0
	uint32_t load;
#define WDT_VALUE_offs 0x004
	uint32_t value;
#define WDT_CTL_offs   0x008
	uint32_t ctl;
#define WDT_ICR_offs   0x00C
	uint32_t icr;
#define WDT_RIS_offs   0x010
	uint32_t ris;
#define WDT_MIS_offs   0x014
	uint32_t mis;

	/* XXX: JUMP */
	uint32_t res1[256];

#define WDT_TEST_offs  0x418
	uint32_t test;

	/* XXX: JUMP */
	uint32_t res2[505];

#define WDT_LOCK_offs  0xC00
	uint32_t lock;

	/* XXX: JUMP */
	uint32_t res3[243];

#define WDT_PeriphID4 0xFD0
#define WDT_PeriphID5 0xFD4
#define WDT_PeriphID6 0xFD8
#define WDT_PeriphID7 0xFDC
#define WDT_PeriphID0 0xFE0
#define WDT_PeriphID1 0xFE4
#define WDT_PeriphID2 0xFE8
#define WDT_PeriphID3 0xFEC
	union {
		struct {
			uint32_t periph_id4;
			uint32_t periph_id5;
			uint32_t periph_id6;
			uint32_t periph_id7;
			uint32_t periph_id0;
			uint32_t periph_id1;
			uint32_t periph_id2;
			uint32_t periph_id3;
			uint32_t periph_id4;
		};
		uint32_t periph_id[8];
	};

#define WDT_PCellD0 0xFF0
#define WDT_PCellD1 0xFF4
#define WDT_PCellD2 0xFF8
#define WDT_PCellD3 0xFFC
	uint32_t pcell_id[4];
} WDT_regs_t;

#define WDT_base 0x40000000
#define WDT ((volatile WDT_regs_t *)WDT_base)

/*** uDMA - DMA ***/

/* uDMA Channel Control Structure */
typedef struct DMA_cc_s {
#define DMA_SRCENDP_offs 0
	uint32_t srcendp;
#define DMA_DSTENDP_offs 0x004
	uint32_t dstendp;
#define DMA_CHCTL_offs   0x008
	uint32_t chctl;
} DMA_cc_t;

/* uDMA Registers */
typedef struct DMA_regs_s {
#define DMA_STAT_offs     0
	uint32_t stat;
#define DMA_CFG_offs      0x004
	uint32_t cfg;
#define DMA_CTLBASE_offs  0x008
	uint32_t ctlbase;
#define DMA_ALTBASE_offs  0x00C
	uint32_t altbase;
#define DMA_WAITSTAT_offs 0x010
	uint32_t waitstat;
#define DMA_SWREQ_offs    0x014
	uint32_t swreq;
#define DMA_USEBURSTSET_offs 0x018
	uint32_t useburstset;
#define DMA_USEBURSTCLR_offs 0x01C
	uint32_t useburstclr;
#define DMA_REQMASKSET_offs  0x020
	uint32_t reqmaskset;
#define DMA_REQMASKCLR_offs  0x024
	uint32_t reqmaskclr;
#define DMA_ENASET_offs      0x028
	uint32_t enaset;
#define DMA_ENACLR_offs      0x02C
	uint32_t enaclr;
#define DMA_ALTSET_offs      0x030
	uint32_t altset;
#define DMA_ALTCLR_offs      0x034
	uint32_t altclr;
#define DMA_PRIOSET_offs     0x038
	uint32_t prioset;
#define DMA_PRIOCLR_offs     0x03C
	uint32_t prioclr;

	/* XXX: JUMP */
	uint32_t res1[3];

#define DMA_ERRCLR_offs      0x04C
	uint32_t errclr;

	/* XXX: JUMP */
	uint32_t res2[996];

	union {
		struct {
#define DMA_PeriphID4_offs    0xFD0
			uint32_t periph_id4;

			/* XXX: JUMP */
			uint32_t res3[3];

#define DMA_PeriphID0_offs    0xFE4
			uint32_t periph_id0;
#define DMA_PeriphID1_offs    0xFE8
			uint32_t periph_id1;
#define DMA_PeriphID2_offs    0xFEC
			uint32_t periph_id2;
#define DMA_PeriphID2_offs    0xFEC
			uint32_t periph_id3;
		};
		uint32_t periph_id[8];
	};

#define DMA_PCellID0_offs 0xFF0
#define DMA_PCellID1_offs 0xFF4
#define DMA_PCellID2_offs 0xFF8
#define DMA_PCellID3_offs 0xFFC
	uint32_t pcell_id[4];
} DMA_regs_t;

#define DMA_base 0x400FF000
#define DMA ((volatile DMA_regs_t *)DMA_base)

/*** Flash Memory ***/

/* See SYSCTL for RMCTL */

/* Flash Memory Control Registers (Flash Control Offset */
typedef struct FLASH_regs_s {
#define FMA_offs    0
	uint32_t fma;
#define FMD_offs    0x004
	uint32_t fmd;
#define FMC_offs    0x008
	uint32_t fmc;
#define FCRIS_offs  0x00C
	uint32_t fcris;
#define FCIM_offs   0x010
	uint32_t fcim;
#define FCMISC_offs 0x014
	uint32_t fcmisc;
} FLASH_regs_t;

#define FLASH_base  0x400FD000
#define FLASH ((volatile FLASH_regs_t *)FLASH_base)

/* See SYSCTL for Flash Memory Protection Regs */

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
		uint32_t res6a[28];

	/* FLASH - Rom Registers (System Control Offset) */
#define RMCTL_offs  0x0F0
		uint32_t rmctl;

		/* XXX: JUMP */
		uint32_t res6b[3];

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
		uint32_t res9[1];

		/* FLASH */
#define FMPRE0_dep_offs 0x130 /* 0x200 */
		uint32_t fmpre0_dep;
#define FMPPE0_dep_offs 0x134 /* 0x400 */
		uint32_t fmppe0_dep;

		/* XXX: JUMP */
		uint32_t resA[2];

		/* FLASH */
#define USECRL_offs    0x140
		uint32_t usecrl;

		/* SYSCTL */
#define DSLPCLKCFG_offs 0x144
		uint32_t dslpclkcfg;

		/* XXX: JUMP */
		uint32_t resB[34];

		/* FLASH */
#define USER_DBG_offs  0x1D0
		uint32_t user_dbg;

		/* XXX: JUMP */
		uint32_t resC[3];

#define USER_REG0_offs 0x1E0
#define USER_REG1_offs 0x1E4
#define USER_REG2_offs 0x1E8
#define USER_REG3_offs 0x1EC
		uint32_t user_reg[4];

		/* XXX: JUMP */
		uint32_t resD[4]

#define FMPRE0_offs    0x200
#define FMPRE1_offs    0x204
#define FMPRE2_offs    0x208
#define FMPRE3_offs    0x20C
		uint32_t fmpre[4];

		/* JUMP */
		uint32_t resE[124];

#define FMPPE0_offs    0x400
#define FMPPE1_offs    0x404
#define FMPPE2_offs    0x408
#define FMPPE3_offs    0x40C
		uint32_t fmppe[4];
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

		union {
			struct {
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
			};
			uint32_t perph_id[8];
		};

#define GPIOPCellID0_offs 0xFF0
#define GPIOPCellID1_offs 0xFF4
#define GPIOPCellID2_offs 0xFF8
#define GPIOPCellID3_offs 0xFFC
		uint32_t pcell_id[4];
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

/*** Hibernation - HIB */

typedef struct HIB_s {
#define HIB_RTCC_offs 0
	uint32_t rtcc;
#define HIB_RTCM0_offs 0x004
	uint32_t rtcm0;
#define HIB_RTCM1_offs 0x008
	uint32_t rtcm1;
#define HIB_RTCLD_offs 0x00C
	uint32_t rtcld;
#define HIB_CTL_offs   0x010
	uint32_t ctl;
#define HIB_IM_offs    0x014
	uint32_t im;
#define HIB_RIS_offs   0x018
	uint32_t ris;
#define HIB_MIS_offs   0x01C
	uint32_t mis;
#define HIB_IC_offs    0x020
	uint32_t ic;
#define HIB_RTCT_offs  0x024
	uint32_t rtct;

	/* XXX: JUMP */
	uint32_t res[2];

#define HIB_DATA_offs 0x030
#define HIB_DATA_2_offs 0x12C
	uint32_t data[64];
} HIB_t;

#define HIB_base 0x400FC000
#define HIB ((volatile HIB_t) HIB_base)


/*** UART ***/

#define UART0_base 0x4000C000
#define UART1_base 0x4000D000

typedef struct UART_regs_s {
#define UART_DR_offs 0
	uint32_t dr;
#define UART_RSR_offs 0x004
	uint32_t ecr;
#define UART_ECR_offs 0x004

	/* JUMP */
	uint32_t res1[4];

#define UART_FR_offs 0x018
	uint32_t fr;

	/* JUMP */
	uint32_t res2[1];

#define UART_ILPR_offs 0x020
	uint32_t ilpr;
#define UART_IBRD_offs 0x024
	uint32_t ibrd;
#define UART_FBRD_offs 0x028
	uint32_t lcrh;
#define UART_LCRH_offs 0x02C
	uint32_t ctl;
#define UART_CTL_offs  0x030
	uint32_t ctl;
#define UART_IFLS_offs 0x034
	uint32_t ifls;
#define UART_IM_offs   0x038
	uint32_t im;
#define UART_RIS_offs  0x03C
	uint32_t ris;
#define UART_MIS_offs  0x040
	uint32_t mis;
#define UART_ICR_offs  0x044
	uint32_t icr;
#define UART_DMACTL_offs    0x048
	uint32_t dmactl;

	/* JUMP */
	uint32_t res3[993];

#define UART_PeriphID4_offs 0xFD0
#define UART_PeriphID5_offs 0xFD4
#define UART_PeriphID6_offs 0xFD8
#define UART_PeriphID7_offs 0xFDC
#define UART_PeriphID0_offs 0xFE0
#define UART_PeriphID1_offs 0xFE4
#define UART_PeriphID2_offs 0xFE8
#define UART_PeriphID3_offs 0xFEC
	uint32_t periph_id[8];

#define UART_PCellID0_offs  0xFF0
#define UART_PCellID1_offs  0xFF4
#define UART_PCellID2_offs  0xFF8
#define UART_PCellID3_offs  0xFFC
	uint32_t pcell_id[4];
} UART_regs_t;

#define UART0 ((volatile UART_regs_t *)UART0_base)
#define UART1 ((volatile UART_regs_t *)UART1_base)

/*** I2C ***/

#define I2C0_base 0x40020000
#define I2C1_base 0x40021000

typedef struct I2C_regs_s {
#define I2C_MSA_offs 0
	uint32_t msa;
#define I2C_MCS_offs  0x004
	uint32_t mcs;
#define I2C_MDR_offs  0x008
	uint32_t mdr;
#define I2C_MTPR_offs 0x00C
	uint32_t mtpr;
#define I2C_MIMR_offs 0x010
	uint32_t mimr;
#define I2C_MRIS_offs 0x014
	uint32_t mris;
#define I2C_MMIS_offs 0x018
	uint32_t mmis;
#define I2C_MICR_offs 0x01C
	uint32_t micr;
#define I2C_MCR_offs  0x020
	uint32_t mcr;

	/* JUMP */
	uint32_t res1[503];

#define I2C_SOAR_offs 0x800
	uint32_t soar;
#define I2C_SCSR_offs 0x804
	uint32_t scsr;
#define I2C_SDR_offs  0x808
	uint32_t sdr;
#define I2C_SIMR_offs 0x80C
	uint32_t simr;
#define I2C_SRIS_offs 0x810
	uint32_t sris;
#define I2C_SMIS_offs 0x814
	uint32_t smis;
#define I2C_SICR_offs 0x818
	uint32_t sicr;
} I2C_regs_t;

#define I2C0 ((volatile I2C_regs_t *)I2C0_base)
#define I2C1 ((volatile I2C_regs_t *)I2C1_base)

/*** Spi - SSI ***/
typedef struct SSI_regs_s {
#define SSI_CR0_offs 0
	uint32_t cr0;
#define SSI_CR1_offs 0x004
	uint32_t cr1;
#define SSI_DR_offs  0x008
	uint32_t dr;
#define SSI_SR_offs  0x00C
	uint32_t sr;
#define SSI_CPSR_offs 0x0010
	uint32_t cpsr;
#define SSI_IM_offs  0x014
	uint32_t im;
#define SSI_RIS_offs 0x018
	uint32_t ris;
#define SSI_MIS_offs 0x01C
	uint32_t mis;
#define SSI_ICR_offs 0x020
	uint32_t icr;
#define SSI_DMACTL_offs 0x024
	uint32_t dmactl;

	uint32_t res_1[1002];

#define SSI_PeriphID4_offs 0xFD0
#define SSI_PeriphID5_offs 0xFD4
#define SSI_PeriphID6_offs 0xFD8
#define SSI_PeriphID7_offs 0xFDC
#define SSI_PeriphID0_offs 0xFE0
#define SSI_PeriphID1_offs 0xFE4
#define SSI_PeriphID2_offs 0xFE8
#define SSI_PeriphID3_offs 0xFEC
	uint32_t periph_id[8];

#define SSI_PCellID0_offs 0xFF0
#define SSI_PCellID1_offs 0xFF4
#define SSI_PCellID2_offs 0xFF8
#define SSI_PCellID3_offs 0xFFC
	uint32_t pcell_id[4];
} SSI_regs_t;

/*** Cortex-m3 Core Peripherals - CORE ***/

typedef struct CORE_regs_s {
	uint32_t res_1[4];

	/* System Timer (SysTick) */
#define STCTRL    0x010
	uint32_t stctrl;
#define STRELOAD  0x014
	uint32_t streload;
#define STCURRENT 0x018
	uint32_t stcurrent;

	uint32_t res_2[57];

	/* Nested Vectored Interrupt Controller (NVIC) */
#define EN0     0x100
#define EN1     0x104
	uint32_t en[2];

	uint32_t res_3[30];

#define DIS0    0x180
	uint32_t dis0;

	uint32_t res_4[31];

#define PEND0   0x200
#define PEND1   0x204
	uint32_t pend[2];

	uint32_t res_5[30];

#define UNPEND0 0x280
#define UNPEND1 0x284
	uint32_t unpend[2];

	uint32_t res_6[30];

#define ACTIVE0 0x300
#define ACTIVE1 0x304
	uint32_t active[2];

	uint32_t res_7[62];

#define PRI0    0x400
#define PRI1    0x404
#define PRI2    0x408
#define PRI3    0x40C
#define PRI4    0x410
#define PRI5    0x414
#define PRI6    0x418
#define PRI7    0x41C
#define PRI8    0x420
#define PRI9    0x424
#define PRI10   0x428
#define PRI11   0x42C
	uint32_t pri[12];

	uint32_t res_8[692];

	/* System Control Block (SCB) */
#define CPUID   0xD00
	uint32_t cpuid;
#define INTCTRL 0xD04
	uint32_t intctrl;
#define VTABLE  0xD08
	uint32_t vtable;
#define APINT   0xD0C
	uint32_t apint;
#define SYSCTRL 0xD10
	uint32_t sysctrl;
#define CFGCTRL 0xD14
	uint32_t cfgctrl;
#define SYSPRI1 0xD18
	uint32_t syspri1;
#define SYSPRI2 0xD1C
	uint32_t syspri2;
#define SYSPRI3 0xD20
	uint32_t syspri3;
#define SYSHNDCTRL 0xD24
	uint32_t sysshndctrl;
#define FAULTSTAT  0xD28
	uint32_t faultstat;
#define HFAULTSTAT 0xD2C
	uint32_t hfaultstat;
#define MMADDR     0xD34
	uint32_t mmaddr;
#define FAULTADDR  0xD38
	uint32_t faultaddr;

	uint32_t res_9[21];

	/* Memory Protection Unit (MPU) */
#define MPUTYPE    0xD90
	uint32_t mputype;
#define MPUCTRL    0xD94
	uint32_t mpuctrl;
#define MPUNUMBER  0xD98
	uint32_t mpunumber;
#define MPUBASE    0xD9C
	uint32_t mpubase;
#define MPUATTR    0xDA0
	uint32_t mpuattr;
#define MPUBASE1   0xDA4
	uint32_t mpubase1;
#define MPUATTR1   0xDA8
	uint32_t mpuattr1;
#define MPUBASE2   0xDAC
	uint32_t mpubase2;
#define MPUATTR2   0xDB0
	uint32_t mpuattr2;
#define MPUBASE3   0xDB4
	uint32_t mpubase3;
#define MPUATTR3   0xDB8
	uint32_t mpuattr3;

	uint32_t res_A[81];

	/* NVIC */
#define SWTRIG  0xF00
	uint32_t swtrig;
} CORE_regs_t;

#define CORE_base 0xE000E000
#define CORE ((volatile CORE_regs_t *)CORE_base)

/*** General Purpose Timers - GPTM ***/
#define GPTM0_base 0x4003000
#define GPTM1_base 0x4003100
#define GPTM2_base 0x4003200
#define GPTM3_base 0x4003300
#define GPTM_reg_ct 0x1000

typedef union GPTM_regs_u {
	struct {
#define GPTM_CFG_offs    0
	uint32_t cfg;
#define GPTM_TAMR_offs   0x004
	uint32_t tamr;
#define GPTM_TBMR_offs   0x008
	uint32_t tbmr;
#define GPTM_MCTL_offs   0x00C
	uint32_t mctl;
#define GPTM_MIMR_offs   0x018
	uint32_t mimr;
#define GPTM_MRIS_offs   0x01C
	uint32_t mris;
#define GPTM_MMIS_offs   0x020
	uint32_t mmis;
#define GPTM_MICR_offs   0x024
	uint32_t micr;
#define GPTM_MTAILR_offs 0x028
	uint32_t mtailr;
#define GPTM_MTBILR_offs 0x02C
	uint32_t mtbilr;
#define GPTM_MTAMATCHR_offs 0x030
	uint32_t mtamatchr;
#define GPTM_MTBMATCHR_offs 0x034
	uint32_t mtbmatchr;
#define GPTM_MTAPR_offs 0x038
	uint32_t mtapr;
#define GPTM_MTBPR_offs 0x03C
	uint32_t mtbpr;
#define GPTM_MTAR_offs  0x048
	uint32_t mtar;
#define GPTM_MTBR_offs  0x04C
	uint32_t mtbr;
	};
	uint32_t raw[GPTM_reg_ct];
} GPTM_regs_t;

typedef struct GPTM_s {
	GPTM_regs_t raw[4];
} GPTM_t;

#define GPTM (((volatile GPTM_t *)GPTM0_base)->raw)

#endif

#ifndef CM3_H_
#define CM3_H_

/* XXX: should names have cm3 prefixes? */

/*** Cortex-m3 Core Peripherals - CORE ***/
#define CORE_BASE 0xE000E000
struct cm3_core_regs {
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
};
#define CORE (*(volatile struct cm3_core_regs *)CORE_BASE)

/***  System Control - SYSCTL ***/
#define SYSCTL_BASE 0x400FE000

typedef struct cm3_sysctl_regs {
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
# define RCC_ACG_mask     (1<<27)
# define RCC_SYSDIV           23
# define RCC_USESYS_mask  (1<<22)
# define RCC_PWMDIV           17
# define RCC_PWRDN            13
# define RCC_BYPASS_mask  (1<<11)
# define RCC_XTAL             6
# define RCC_OSCSRC      `    4
# define RCC_IOSCDIS_mask (1<<1)
# define RCC_MOSCDIS_mask (1<<0)
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
	uint32_t resD[4];

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
#define SYSCTL (*(volatile struct cm3_sysctl_regs *)SYSCTL_BASE)

/* WDT */

/* CORE_DEBUG */
#endif

/*
 * Use a Hardware Timer to control the frequency of the STEP output to the
 * stepper motors
 *
 * Also handle tweaking the control lines
 */

enum mode {
	MODE_FULL   = 0x0,
	MODE_1_2    = 0x1,
	MODE_1_4    = 0x2,
	MODE_1_8    = 0x3,
	MODE_1_16   = 0x4,
	MODE_1_32   = 0x5,
	MODE_1_32a  = 0x6,
	MODE_1_32b  = 0x7
};

static void set_mode(enum mode mode)
{
	GPIO_regs_t *b = &(GPIO_AHB->B);
	b->data = mode & 0x3;
}

void stepper_init(void)
{
	GPIO_regs_t *b = &(GPIO_AHB->B);
	GPIO_regs_t *h = &(GPIO_AHB->H);

	/* lowest 5 bits */
	b->dir |= 0x1f;

	/* 0b01110 */
	h->dir |= 0x0e;

	/* 0b10001 */
	h->dir &= ~(0x11);

	GPIO_AHB->F.dir 
}

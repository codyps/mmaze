MEMORY
{
	/* For the lm3s:
	 * 0x0000.0000 to 0x0001.FFFF : Flash
	 * 0x2000.0000 to 0x2000.FFFF : SRAM
	 * 0x2200.0000 to 0x221F.FFFF : Bitband of SRAM
	 */
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x0001FFFF
	ram (wx) : ORIGIN = 0x20000000, LENGTH = 0x0000FFFF
}

INCLUDE "armv7m.lds"

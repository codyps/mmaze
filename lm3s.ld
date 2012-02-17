
ENTRY(__init)
STARTUP(crt0.S.o)

MEMORY
{
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x0001FFFF
	ram (wx) : ORIGIN = 0x20000000, LENGTH = 0x2000FFFF
}

SECTIONS
{
	. = 0;
	.text :
	{
		*(.isr_vector)
		*(.text*)
		*(.rodata)
	} > rom

	. = 0x20000000;

	.data :
	{
		__data_start__ = . ;
		*(.data)
		__data_end__ = . ;
	} > ram AT > rom

	__data_size__ = __data_end__ - __data_start__;

	.bss :
	{
		__bss_start__ = . ;
		*(.bss)
		*(COMMON)
		__bss_end__ = . ;
	} > ram AT > rom

	_estack = 0x2000FFFF;
}

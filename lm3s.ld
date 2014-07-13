
ENTRY(__init)

MEMORY
{
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x0001FFFF
	ram (wx) : ORIGIN = 0x20000000, LENGTH = 0x0000FFFF
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.init*)
		*(.text*)
		*(.rodata)
	} >rom =0xFFFFFFFF

	.data : ALIGN(4)
	{
		__data_start__ = . ;
		*(.data)
		__data_end__   = . ;
	} >ram AT>rom =0xFFFFFFFF
	__data_load_start__ = LOADADDR(.data);
	__data_size__       = SIZEOF(.data);
	__data_load_end__   = __data_load_start__ + __data_size__;

	.bss (NOLOAD) : ALIGN(4)
	{
		__bss_start__ = . ;
		*(.bss)
		*(COMMON)
		__bss_end__   = . ;
	} >ram

	.noinit (NOLOAD) : ALIGN(4)
	{
		*(.noinit*)
	} > ram
}

__stack_high__ = ORIGIN(ram) + LENGTH(ram) - 4;
__stack_low__   = __bss_end__;

__ram_start__ = ORIGIN(ram);
__rom_start__ = ORIGIN(rom);

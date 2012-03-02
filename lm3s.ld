
ENTRY(__init)

MEMORY
{
	rom (rx) : ORIGIN = 0x00000000, LENGTH = 0x0001FFFF
	ram (wx) : ORIGIN = 0x20000000, LENGTH = 0x0000FFFF
}

SECTIONS
{
	.isr 0 :
	{
		KEEP(*(.isr_vector))
	} > rom

	.text : ALIGN(4)
	{
		*(.init*)
		*(.text*)
		= 0xFFFFFFFF
	} >rom

	.rodata : ALIGN(4)
	{
		*(.rodata)
		= 0xFFFFFFFF
	} >rom

	.data : ALIGN(4)
	{
		__data_start__ = . ;
		*(.data)
		__data_end__ = . ;
		= 0xFFFFFFFF
	} >ram AT>rom
	__data_size__ = __data_end__ - __data_start__;

	.bss : ALIGN(4)
	{
		__bss_start__ = . ;
		*(.bss)
		*(COMMON)
		__bss_end__ = . ;
		= 0xFFFFFFFF
	} >ram AT>rom
	__bss_size__ = __bss_end__ - __bss_start__;

}

__estack__    = ORIGIN(ram) + LENGTH(ram) - 4;
__ram_start__ = ORIGIN(ram);
__rom_start__ = ORIGIN(rom);

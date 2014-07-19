
ENTRY(__init)

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

SECTIONS
{
	.vector : {
		ASSERT(. == 0, "Something before vector");
		__vector_start = .;
		KEEP(*(.vector))
		ASSERT(__vector_start != ., "Vector not included");
	} >rom =0xFFFFFFFF

	.text : ALIGN(4) {
		*(.init*)
		*(.text*)
	} >rom =0xFFFFFFFF

	.rodata : {
		*(.rodata*)
	} >rom =0xFFFFFFFF

	.preinit_array : ALIGN(4) {
		__preinit_array_start = .;
		KEEP (*(.preinit_array))
		__preinit_array_end = .;
	} >rom =0xFFFFFFFF
	.init_array : ALIGN(4) {
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;
	} >rom =0xFFFFFFFF
	.fini_array : ALIGN(4) {
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;
	} >rom =0xFFFFFFFF

	.data : ALIGN(4) {
		__data_start = . ;
		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
		__data_end   = . ;
	} >ram AT>rom =0xFFFFFFFF
	__data_load_start = LOADADDR(.data);
	__data_load_end   = __data_load_start + SIZEOF(.data);
	. = .;
	.bss (NOLOAD) : ALIGN(4) {
		__bss_start = . ;
		*(.bss* .gnu.linkonce.b.*)
		*(COMMON)
		__bss_end   = . ;
	} >ram

	.noinit (NOLOAD) : ALIGN(4) {
		*(.noinit*)
		__noinit_end = .;
	} >ram

	end = __noinit_end;
}

__stack_high = ORIGIN(ram) + LENGTH(ram) - 4;

__ram_start = ORIGIN(ram);
__rom_start = ORIGIN(rom);

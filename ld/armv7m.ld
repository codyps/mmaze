
ENTRY(isr_reset)

SECTIONS
{
	.isr_vector : {
		ASSERT(. == 0, "Something before isr_vector");
		__vector_start = .;
		KEEP(*(.isr_vector))
		ASSERT(__vector_start != ., "isr_vector not included");
		/* TODO: check that we end up 4 byte aligned */
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

LD_FEATURE ("SANE_EXPR")

MEMORY
{
	flash (rx)  : ORIGIN = CONFIG_FLASH_OFFS, LENGTH = CONFIG_FLASH_SIZE
#ifdef CONFIG_FLASH_SPECIAL_OFFS
	flash_special (r): ORIGIN = CONFIG_FLASH_SPECIAL_OFFS, LENGTH = CONFIG_FLASH_SPECIAL_SIZE
#endif
	ram   (!rx) : ORIGIN = CONFIG_RAM_OFFS,   LENGTH = CONFIG_RAM_SIZE
}

ENTRY(isr_reset)

SECTIONS
{
	.isr_vector : {
		ASSERT(. == 0, "Something before isr_vector");
		__vector_start = .;
		KEEP(*(.isr_vector))
		ASSERT(__vector_start != ., "isr_vector not included");
		/* TODO: check that we end up 4 byte aligned */
	} >flash =CONFIG_FLASH_FILL

/* This is before .text for Freescale k20 & k66 family (and likely others)
 * support (base = 0x400).
 *
 * For other chips, it may need to be later.
 * As a result of placing this here, there is some spare space before it, and
 * the `.low_flash` section is used to populate it.
 */
#ifdef CONFIG_FLASH_CONFIG_FIELD_BASE
	.low_flash : {
		*(.low_flash)
		KEEP(*(.low_flash_keep))
	} >flash =CONFIG_FLASH_FILL

	.flash_config_field CONFIG_FLASH_CONFIG_FIELD_BASE : {
		ASSERT(. != CONFIG_FLASH_CONFIG_FIELD_BASE, "flash config field misplaced");
		KEEP(*(.flash_config_field*))
		ASSERT(. != CONFIG_FLASH_CONFIG_FIELD_SIZE, "flash config field was not provided or too small");
	} >flash =CONFIG_FLASH_FILL
#endif

	.text : ALIGN(4) {
		*(.text*)
		*(.gnu.linkonce.t.*)
	} >flash =CONFIG_FLASH_FILL

	.rodata : {
		*(.rodata*)
		*(.gnu.linkonce.r.*)
	} >flash =CONFIG_FLASH_FILL

	.preinit_array : ALIGN(4) {
		__preinit_array_start = .;
		KEEP (*(.preinit_array))
		__preinit_array_end = .;
	} >flash =CONFIG_FLASH_FILL
	.init_array : ALIGN(4) {
		__init_array_start = .;
		KEEP (*(SORT(.init_array.*)))
		KEEP (*(.init_array))
		__init_array_end = .;
	} >flash =CONFIG_FLASH_FILL
	.fini_array : ALIGN(4) {
		__fini_array_start = .;
		KEEP (*(.fini_array))
		KEEP (*(SORT(.fini_array.*)))
		__fini_array_end = .;
	} >flash =CONFIG_FLASH_FILL

	.data : ALIGN(4) {
		__data_start = . ;
		*(.data .data.* .gnu.linkonce.d.*)
		SORT(CONSTRUCTORS)
		__data_end   = . ;
	} >ram AT>flash =CONFIG_FLASH_FILL
	__data_load_start = LOADADDR(.data);
	__data_load_end   = __data_load_start + SIZEOF(.data);

	.bss (NOLOAD) : ALIGN(4) {
		__bss_start = . ;
		*(.bss* .gnu.linkonce.b.*)
		*(COMMON)
		__bss_end   = . ;
	} >ram

	.noinit (NOLOAD) : ALIGN(4) {
		__noinit_start = .;
		*(.noinit*)
		__noinit_end = .;
	} >ram

	.note.gnu.build-id : {
		__build_id_start = .;
		KEEP(*(.note.gnu.build-id))
		__build_id_end = .;
	} >flash =CONFIG_FLASH_FILL

#ifdef CONFIG_FLASH_SPECIAL_OFFS
	.flash_special : {
		KEEP(*(.flash_special*))
	} >flash_special =CONFIG_FLASH_FILL
#endif

}

__stack_high = ORIGIN(ram) + LENGTH(ram);

__ram_start = ORIGIN(ram);
__flash_start = ORIGIN(flash);

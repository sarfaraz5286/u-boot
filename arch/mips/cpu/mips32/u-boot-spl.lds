#if defined(CONFIG_64BIT)
#define PTR_COUNT_SHIFT	3
#else
#define PTR_COUNT_SHIFT	2
#endif

#define GD_SIZE 0xa0

MEMORY { .sram : ORIGIN = CONFIG_SPL_TEXT_BASE,\
		LENGTH = CONFIG_SPL_MAX_SIZE }
MEMORY { .bss : ORIGIN = CONFIG_SPL_BSS_START_ADDR, \
		LENGTH = CONFIG_SPL_BSS_MAX_SIZE }


OUTPUT_ARCH(mips)
ENTRY(_start)
SECTIONS
{
	. = ALIGN(4);
	.text : {
		arch/mips/cpu/mips32/start.o	(.text)
		*(.text*)
	} > .sram

	. = ALIGN(4);
	.rodata : {
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
	} > .sram

	. = ALIGN(4);
	.data : {
		*(.data*)
		. = ALIGN(16);
		_gp = . + 0x7ff0;
	} > .sram

	.got : {
		*(.got)
	} > .sram

	num_got_entries = SIZEOF(.got) >> PTR_COUNT_SHIFT;

	. = ALIGN(4);
	.sdata : {
		*(.sdata*)
	} > .sram

	. = ALIGN(4);
	.u_boot_list : {
		KEEP(*(SORT(.u_boot_list*)));
	} > .sram

	. = ALIGN(4);
	__image_copy_end = .;
	__init_end = .;

	.bss : {
		. = ALIGN(4);
		__bss_start = .;
		*(.bss*)
		. += GD_SIZE;
		. = ALIGN(4);
		__bss_end = .;
	} > .bss

	_end = .;
}

OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS {
    . = 0x20000000;

    .text : AT(ADDR(.text)) {
        *(.text*)
		. = ALIGN(0x1000);
    }

    .data : AT(ADDR(.data)) {
        *(.data*)
		. = ALIGN(0x1000);
    }

    .rodata : AT(ADDR(.rodata)) {
        *(.rodata*)
		. = ALIGN(0x1000);
    }

    .bss : AT(ADDR(.bss)) {
        *(COMMON)
        *(.bss)
        *(.bootstrap_stack)
        . = ALIGN(0x1000);
    }
}

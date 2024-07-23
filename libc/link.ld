OUTPUT_FORMAT(elf32-i386)
ENTRY(__init_everything)

SECTIONS {
    . = 0x20000000;

    .text : {
        *(.text*)
        *(.text.*)

	. = ALIGN(0x1000);
    }

    .data : {
        *(.data*)
        *(.data.*)

	. = ALIGN(0x1000);
    }

    .rodata : {
        *(.rodata*)
        *(.rodata.*)

	. = ALIGN(0x1000);
    }

    .bss : AT(ADDR(.bss)) {
        *(COMMON)
        *(.bss*)
        *(.bootstrap_stack)
        . = ALIGN(0x1000);
    }

	/DISCARD/ : {
        *(.eh_frame_hdr)
        *(.eh_frame)
    }
}

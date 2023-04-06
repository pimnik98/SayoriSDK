# Флаги компилятора языка C
CFLAGS  = -nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding
# Флаги компоновщика
LDFLAGS = -T ../link.ld -m elf_i386
# Флаги ассемблера
ASFLAGS = --32

TARGETS = main.o draw.o memtest.o
SOURCES = base/base.o base/display.o base/draw.o base/kbd.o
LIBBASE = libbase.a

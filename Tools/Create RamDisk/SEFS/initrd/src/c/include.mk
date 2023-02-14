# Флаги компилятора языка C
CFLAGS  = -nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding -w
# Флаги компоновщика
LDFLAGS = -T ../link.ld -m elf_i386
# Флаги ассемблера
ASFLAGS = --32

TARGETS = main.o draw.o bsstest.o memtest.o
SOURCES = base/base.o base/display.o base/draw.o
LIBBASE = libbase.a

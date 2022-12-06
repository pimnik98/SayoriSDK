# Флаги компилятора языка C
CFLAGS=-nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -Wimplicit-function-declaration -O0 -ffreestanding -w
# Флаги компоновщика
LDFLAGS=-Tlink.ld -m elf_i386
# Флаги ассемблера
ASFLAGS=--32
SOURCES= main.o
all:$(SOURCES) link
build:
	$(SOURCES) link
link:
	ld $(LDFLAGS) -o env $(SOURCES)

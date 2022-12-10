# Флаги компилятора языка C
CFLAGS=-nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding -w
# Флаги компоновщика
LDFLAGS=-Tlink.ld -m elf_i386
# Флаги ассемблера
ASFLAGS=--32

SOURCES= main.o base/base.o base/display.o

all: link

$(SOURCES): %.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

link: $(SOURCES)
	touch "$(shell pwd)/../env"
	rm "$(shell pwd)/../env"
	ld $(LDFLAGS) -o  "$(shell pwd)/../env" $(SOURCES)


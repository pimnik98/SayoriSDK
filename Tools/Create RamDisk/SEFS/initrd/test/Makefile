# Флаги компилятора языка C
CFLAGS  = -nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding -w
# Флаги компоновщика
LDFLAGS=-T ../link.ld -m elf_i386
# Флаги ассемблера
ASFLAGS = --32

TARGETS = main.o draw.o
SOURCES = base/base.o base/display.o base/draw.o

all: link

$(SOURCES): %.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

$(TARGETS): %.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

link: $(SOURCES) $(TARGETS)
	touch "$(shell pwd)/../env"
	rm "$(shell pwd)/../env"
	touch "$(shell pwd)/../draw"
	rm "$(shell pwd)/../draw"
	ld $(LDFLAGS) -o  "$(shell pwd)/../env" main.o $(SOURCES)
	ld $(LDFLAGS) -o  "$(shell pwd)/../draw" draw.o $(SOURCES)

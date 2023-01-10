# Флаги компилятора языка C
CFLAGS  = -nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding -w
# Флаги компоновщика
LDFLAGS = -T ../link.ld -m elf_i386
# Флаги ассемблера
ASFLAGS = --32

TARGETS = main.o draw.o bsstest.o memtest.o
SOURCES = base/base.o base/display.o base/draw.o
LIBBASE = libbase.a

all: link

$(SOURCES): %.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

$(TARGETS): %.o : %.c
	$(CC) $< $(CFLAGS) -c -o $@

link: $(SOURCES) $(TARGETS)
	ar crs $(LIBBASE) $(SOURCES)
	ld $(LDFLAGS) -o  "$(shell pwd)/../../env" main.o libbase.a
	ld $(LDFLAGS) -o  "$(shell pwd)/../../draw" draw.o libbase.a
	ld $(LDFLAGS) -o  "$(shell pwd)/../../bsstest" bsstest.o libbase.a
	ld $(LDFLAGS) -o  "$(shell pwd)/../../mem" memtest.o libbase.a

clean:
	rm $(LIBBASE) $(SOURCES) || true

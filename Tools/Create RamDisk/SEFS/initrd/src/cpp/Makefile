# Флаги компилятора языка C
CFLAGS  = -nostdinc -nostdlib -fno-builtin -fno-stack-protector -m32 -g -Iinclude/ -O0 -ffreestanding -Wall -fno-use-cxa-atexit -fno-use-init-array -fno-exceptions 
# Флаги компоновщика
LDFLAGS = -T ../link.ld -m elf_i386
# Флаги ассемблера
ASFLAGS = --32

TARGETS = cpphello.o
SOURCES = sayori_std.o

all: link

$(SOURCES): %.o : %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

$(TARGETS): %.o : %.cpp
	$(CC) $< $(CFLAGS) -c -o $@

link: $(SOURCES) $(TARGETS)
	ld $(LDFLAGS) -o  "$(shell pwd)/../../cpphello" cpphello.o $(SOURCES)

clean:
	rm $(TARGETS) $(SOURCES)

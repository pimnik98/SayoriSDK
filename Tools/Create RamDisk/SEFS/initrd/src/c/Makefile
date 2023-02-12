include include.mk

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

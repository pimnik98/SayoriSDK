CFLAGS= -m32 -ffreestanding -msse2 -Iinclude -nostdlib -fno-builtin -fno-stack-protector -O0
C_COMPILE_FILES=$(shell find base/ -name *.c)
OBJS=$(C_COMPILE_FILES:%.c=%.o)

OUT=libsayori_c.a

all: $(OUT)

clean:
	-rm $(OBJS)
	-rm $(OUT)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(AR) rs $(OUT) $(OBJS)

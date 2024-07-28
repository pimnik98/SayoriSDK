CFLAGS= -m32 -ffreestanding -fno-pic -msse2 -Iinclude -nostdlib -fno-builtin -fno-stack-protector -O0
C_COMPILE_FILES=$(shell find base/ -name *.c)
ASM_COMPILE_FILES=$(shell find base/ -name *.S)
ASM_OBJS=$(ASM_COMPILE_FILES:%.S=%.o)
OBJS=$(C_COMPILE_FILES:%.c=%.o)

OUT=libsayori_c.a

all: $(OUT)

clean:
	-rm $(OBJS)
	-rm $(OUT) $(ASM_OBJS)

$(ASM_OBJS): %.o: %.S
	$(AS) --32 $< -o $@

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT): $(ASM_OBJS) $(OBJS)
	$(AR) rs $(OUT) $(ASM_OBJS) $(OBJS)

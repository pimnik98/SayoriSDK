CPPFLAGS= -m32 -ffreestanding -msse2 -Iinclude -nostdlib -fno-builtin -fno-stack-protector -O0 -fno-exceptions -Wall -fno-pic -fno-pie -Wextra
CPP_COMPILE_FILES=$(shell find src/ -name '*.cpp')
OBJS=$(CPP_COMPILE_FILES:%.cpp=%.o)

OUT=libsayori_cpp.a

all: $(OUT)
	$(CXX) $(CPPFLAGS) testvec.cpp -c -o vec.o
	ld.lld -T../libc/link.ld vec.o $(OUT) ../libc/libsayori_c.a -o vec

clean:
	-rm $(OBJS)
	-rm $(OUT)

$(OBJS): %.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(AR) rs $(OUT) $(OBJS)

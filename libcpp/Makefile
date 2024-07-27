CPPFLAGS= -m32 -ffreestanding -msse2 -Iinclude -nostdlib -fno-builtin -fno-stack-protector -O0 -fno-exceptions -Wall -fno-pic -fno-pie -Wextra
CPP_COMPILE_FILES=$(shell find src/ -name '*.cpp')
OBJS=$(CPP_COMPILE_FILES:%.cpp=%.o)

OUT=libsayori_cpp.a

all: $(OUT)
	$(CXX) $(CPPFLAGS) testfile.cpp -c -o testfile.o
	ld.lld -T../libc/link.ld testfile.o $(OUT) ../libc/libsayori_c.a -o filetest

clean:
	-rm $(OBJS)
	-rm $(OUT)

$(OBJS): %.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(AR) rs $(OUT) $(OBJS)

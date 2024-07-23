CPPFLAGS= -m32 -ffreestanding -msse2 -Iinclude -nostdlib -fno-builtin -fno-stack-protector -O0 -fno-exceptions
CPP_COMPILE_FILES=$(shell find src/ -name *.cpp)
OBJS=$(CPP_COMPILE_FILES:%.cpp=%.o)

OUT=libsayori_cpp.a

all: $(OUT)

clean:
	-rm $(OBJS)
	-rm $(OUT)

$(OBJS): %.o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(OUT): $(OBJS)
	$(AR) rs $(OUT) $(OBJS)

extern "C" {
#include "../../libc/include/stdint.h"
#include "../../libc/include/memory.h"
}

void* operator new(size_t size) {
    return malloc(size);
}

void* operator new[](size_t size) {
    return malloc(size);
}

void operator delete(void* ptr) { free(ptr); }
void operator delete(void* ptr, [[maybe_unused]] size_t size) { free(ptr); }
void operator delete[](void* ptr) { free(ptr); }
void operator delete[](void* ptr, [[maybe_unused]] size_t size) { free(ptr); }

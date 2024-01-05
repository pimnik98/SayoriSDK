#include "syscall.h"
#include "memory.h"

void* malloc(size_t size) {
    void* memory = 0;

    _syscall(MEMORY_ALLOC_SYSCALL, size, (size_t)&memory, 0);

    return memory;
}

void free(void* memory) {
    _syscall(MEMORY_FREE_SYSCALL, (size_t)memory, 0, 0);
}

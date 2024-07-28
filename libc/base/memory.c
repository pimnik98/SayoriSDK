#include "syscall.h"
#include "string.h"
#include "memory.h"

void* malloc(size_t size) {
    void* memory = 0;

    _syscall(MEMORY_ALLOC_SYSCALL, size, 1, (size_t)&memory);

    return memory;
}

void* malloc_aligned(size_t size, size_t align) {
    void* memory = 0;

    _syscall(MEMORY_ALLOC_SYSCALL, size, align, (size_t)&memory);

    return memory;
}

void* calloc(size_t size, size_t count) {
	void* memory = 0;

	_syscall(MEMORY_ALLOC_SYSCALL, size * count, 1, (size_t)&memory);

	memset(memory, 0, size * count);

	return memory;
}

void* realloc(void* memory, size_t size) {
	void* new_memory = 0;

	_syscall(MEMORY_REALLOC_SYSCALL, (size_t)memory, size, (size_t)&memory);

	return memory;
}

void free(void* memory) {
    _syscall(MEMORY_FREE_SYSCALL, (size_t)memory, 0, 0);
}

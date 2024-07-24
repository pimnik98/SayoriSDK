#pragma once

#define MEMORY_ALLOC_SYSCALL 1
#define MEMORY_FREE_SYSCALL 2
#define MEMORY_REALLOC_SYSCALL 18

void* realloc(void* memory, size_t size);
void* calloc(size_t size, size_t count);
void* malloc(size_t size);
void free(void* ptr);

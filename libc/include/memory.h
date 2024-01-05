#pragma once

#define MEMORY_ALLOC_SYSCALL 1
#define MEMORY_FREE_SYSCALL 2

void* malloc(size_t size);
void free(void* ptr);
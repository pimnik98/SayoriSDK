#pragma once

#include "../../libc/include/stdint.h"

void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* ptr);
void operator delete(void* ptr, size_t size);
void operator delete[](void* ptr);
void operator delete[](void* ptr, size_t size);

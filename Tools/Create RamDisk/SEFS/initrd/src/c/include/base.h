#pragma once

#include "stdint.h"

void* _syscall(size_t num, size_t p1, size_t p2, size_t p3);
struct env* env_io(size_t Data1, size_t Data2);
void debug_puts(const char str[]);
void debug_io(size_t Data1, size_t Data2);

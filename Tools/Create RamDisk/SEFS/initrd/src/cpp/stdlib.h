#pragma once

#include "string.h"

void strver(char *str);
int itoa(int n, char *buffer);
void* malloc(int value);
void* calloc(size_t number, size_t size);
void* realloc(void* mem, size_t size);
void free(void* memory);

#pragma once

#include "stdint.h"

#define FILE_DESCR_OPEN 4
#define FILE_DESCR_READ 5
#define FILE_DESCR_CLOSE 6

int fd_open(const char* filename, const char* mode);
void fd_read(int fd, size_t size, size_t count, void* buffer);
void fd_close(int fd);
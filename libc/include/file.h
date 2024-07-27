#pragma once

#include "stdint.h"
#include "stddef.h"

#define SYSCALL_FILE_DESCR_OPEN 4
#define SYSCALL_FILE_DESCR_READ 5
#define SYSCALL_FILE_DESCR_CLOSE 6
#define SYSCALL_FILE_DESCR_WRITE 19

#define O_READ 1
#define O_WRITE 2
#define O_CREATE 4
#define O_APPEND 8
#define O_TRUNC 16

int fd_open(const char* filename, size_t mode);
void fd_read(int fd, size_t size, size_t count, void* buffer);
void fd_write(int fd, size_t size, size_t count, const void* buffer);
void fd_close(int fd);

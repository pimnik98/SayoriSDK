#include "syscall.h"
#include "file.h"

int fd_open(const char* filename, size_t mode) {
    int fd = 0;
    _syscall(
            SYSCALL_FILE_DESCR_OPEN,
            (size_t) filename,
            mode,
            (size_t) &fd
    );

    return fd;
}

void fd_read(int fd, size_t size, size_t count, void* buffer) {
    _syscall(
            SYSCALL_FILE_DESCR_READ,
            (size_t) fd,
            size * count,
            (size_t) buffer
            );
}

void fd_write(int fd, size_t size, size_t count, const void* buffer) {
    _syscall(
            SYSCALL_FILE_DESCR_WRITE,
            (size_t) fd,
            size * count,
            (size_t) buffer
            );
}

void fd_close(int fd) {
    _syscall(
            SYSCALL_FILE_DESCR_CLOSE,
            (size_t) fd,
            0,
            0
            );
}

#include "syscall.h"
#include "exit.h"

__attribute__((noreturn)) void exit(int status) {
	_syscall(
            EXIT_SYSCALL,
            status,
            0,
            0
            );

	while(1)
		;
}

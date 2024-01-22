//
// Created by ndraey on 22.01.24.
//

#include "timer.h"
#include "syscall.h"

size_t ticks() {
    return _syscall(
            TIMER_GET_TICKS_SYSCALL,
            0,
            0,
            0
            );
}
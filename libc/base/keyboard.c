//
// Created by ndraey on 22.01.24.
//

#include "../include/keyboard.h"
#include "syscall.h"

size_t getkey() {
    return _syscall(
            KEYBOARD_GETKEY_SYSCALL,
            0,
            0,
            0
            );
}
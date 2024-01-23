//
// Created by ndraey on 22.01.24.
//

#pragma once

#include "stdint.h"

#define TIMER_GET_TICKS_SYSCALL 14
#define TIMER_SLEEP_SYSCALL 15

size_t ticks();
void sleep(uint32_t millis);

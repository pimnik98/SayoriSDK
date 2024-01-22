//
// Created by ndraey on 22.01.24.
//

#pragma once

#include "stdint.h"

#define TIMER_GET_TICKS_SYSCALL 14

size_t ticks();
void wait_ticks(size_t ticks_num);
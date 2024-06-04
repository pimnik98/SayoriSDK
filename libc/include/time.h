#pragma once

#include "stdint.h"

#define DATETIME_SYSCALL 16

typedef struct sayori_time {
	uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t century;
} sayori_time_t;

sayori_time_t get_time();

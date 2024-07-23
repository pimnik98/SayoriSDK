//
// Created by ndraey on 22.01.24.
//

#include "../include/time.h"
#include "syscall.h"

sayori_time_t get_time() {
	sayori_time_t time;
	
    _syscall(
            DATETIME_SYSCALL,
            (size_t)&time,
            0,
            0
            );

   	return time;
}

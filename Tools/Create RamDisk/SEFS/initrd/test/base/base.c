/**
 * @file base.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - Soul Base Module for ELF
 * @version 0.1.0
 * @date 2022-08-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <stdint.h>
#include <env.h>

struct env* e;


void* env_io(void* Data1, void* Data2){
    void* Data;
    asm volatile("int $0x50"
                : "=a"(Data)
                : "a"(0x03),
                  "b"(Data1),
                  "c"(Data2)
                );
    return Data;
}

void* setEnv(){
    e = (struct env*) env_io(0,0);
}

void* getEnv(){
    return e->Display_W;
}

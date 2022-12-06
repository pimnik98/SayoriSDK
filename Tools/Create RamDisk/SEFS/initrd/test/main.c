/**
 * @file main.c
 * @author Пиминов Никита (nikita.piminoff@yandex,ru)
 * @brief SayoriOS SDK - ENV TEST APP
 * @version 0.1.0
 * @date 2022-06-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <stdint.h>


int main(){
  asm volatile("int $0x50"
                :
                : "a"(0x02),
                  "b"(0),
                  "c"(1)
                );
    return 1;
}

/**
 * @file main.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - ENV TEST APP
 * @version 0.1.0
 * @date 2022-06-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <stdint.h>

char* hello = "Hyvaa huomenta, Nikita Piminov!!!\n";

int main(){
  asm volatile("int $0x50"
                :
                : "a"(0x02), // TTYCTL
                  "b"(1),    // FUNCTION 1 - PUTS
                  "c"(hello) // ADDRESS OF DATA
                );
    return 1;
}

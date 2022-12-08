/**
 * @file main.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - ENV TEST APP
 * @version 0.1.0
 * @date 2022-06-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <stdint.h>
#include <env.h>


char* hello = "Huomenta myös sinulle, Drew Pavlenko, KIITOS TODELLA!!!\n";

int main(){
    // Делаем настройку окружения
    setEnv();
    env_io(2,getEnv());
    return 1;
}

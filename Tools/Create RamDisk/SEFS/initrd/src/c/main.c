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
#include <draw.h>

//char* hello = "Huomenta myös sinulle, Drew Pavlenko, KIITOS TODELLA!!!\n";

int main(int argc, char* argv[]){
    // Делаем настройку окружения
    __BaseInit(argc, argv);    

    return 1;
}

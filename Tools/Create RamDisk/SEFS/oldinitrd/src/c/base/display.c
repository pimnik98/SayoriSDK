/**
 * @file display.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - Display Driver - Soul Base Module for ELF
 * @version 0.1.0
 * @date 2022-08-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <stdint.h>
#include <base.h>

/**
 * @brief Вызов драйвера экрана
 *
 * @warning Рекомендуется вызывать только для базового модуля управления
 */
void __DisplayInit(){
    debug_puts("Display Init...");
    int DisplayAddr = (int)env_io(0x01,0x00);
    debug_io(0x00 ,DisplayAddr);
    debug_io(0x02, DisplayAddr);
}

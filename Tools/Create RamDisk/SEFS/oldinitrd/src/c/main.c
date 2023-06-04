/**
 * @file main.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - ENV TEST APP
 * @version 0.1.0
 * @date 2022-06-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include <base.h>
#include <stdint.h>
#include <env.h>
#include <draw.h>
#include <kbd.h>

// char* hello = "Huomenta myös sinulle, Drew Pavlenko, KIITOS TODELLA!!!\n";
// char* hello2 = "God morgon, Nikita Pimenov! Jag önskar att du gör detta projekt populärt!\n";

int main(int argc, char* argv[]){
    // Делаем настройку окружения
	_syscall(0x02, 1, "Press any key...", 0);

    debug_puts("Got key:");
    debug_putint(kbd_getc());

    return 1;
}

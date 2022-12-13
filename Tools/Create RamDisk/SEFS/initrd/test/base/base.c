/**
 * @file base.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - Base - Soul Base Module for ELF
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

void debug_io(void* Data1, void* Data2){
    asm volatile("int $0x50"
                :
                : "a"(0x04),
                  "b"(Data1),
                  "c"(Data2)
                );
}


void* getEnv(){
    return e->Display_W;
}


void __BaseInit(int argc, char* argv[]){
    debug_io(0x01,"App ARGC:");
    debug_io(0x00,argc);
    for(int i=0;i<argc;i++){
      debug_io(0x01,argv[i]);
    }
    e = (struct env*) env_io(0x00,0x00);
    debug_io(0x01,"Base Init...");
    __DisplayInit();
}

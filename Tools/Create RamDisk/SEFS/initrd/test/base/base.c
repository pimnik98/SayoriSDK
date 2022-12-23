/**
 * @file base.c
 * @author Пиминов Никита (nikita.piminoff@yandex.ru)
 * @brief SayoriOS SDK - Base - Soul Base Module for ELF
 * @version 0.1.0
 * @date 2022-08-12
 * @copyright Copyright SayoriOS Team (c) 2022
 */

#include "base.h"
#include <env.h>

void* _syscall(size_t num, size_t p1, size_t p2) {
  void *result;
  asm volatile("int $0x50"
               : "=a"(result)
               : "a"(num),
                 "b"(p1),
                 "c"(p2));
  return result;
}

struct env* env_io(size_t Data1, size_t Data2) {
  /*
  void *Data;
  asm volatile("int $0x50"
               : "=a"(Data)
               : "a"(0x03),
                 "b"(Data1),
                 "c"(Data2));
  return Data;
  */
  debug_io(1, "================");
  debug_io(1, "Data1: ");
  debug_io(2, Data1);
  debug_io(1, "Data2: ");
  debug_io(2, Data2);
  debug_io(1, "================");
  debug_io(2, _syscall(0x03, Data1, Data2));
  return _syscall(0x03, Data1, Data2);
}

void debug_io(size_t Data1, size_t Data2) {
  /*
    asm volatile("int $0x50"
               :
               : "a"(0x04),
                 "b"(Data1),
                 "c"(Data2));
  */
  _syscall(0x04, Data1, Data2);
}

void __BaseInit(int argc, char *argv[])
{
  debug_io(0x01, "App ARGC:");
  debug_io(0x00, argc);
  for (int i = 0; i < argc; i++) {
    debug_io(0x01, argv[i]);
  }
  
  struct env *e = env_io(0x00, 0x00);
  
  debug_io(0x01, "Base Init...");
  __DisplayInit();
}

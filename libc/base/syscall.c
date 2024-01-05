/**
 * @file syscall.c
 * @author NDRAEY >_ (piakchu.andrey@vk.com)
 * @brief Syscall management
 * @version 0.3.4
 * @date 2023-12-10
 * @copyright Copyright SayoriOS Team (c) 2023
 */

#include "syscall.h"

int _syscall(size_t num, size_t p1, size_t p2, size_t p3) {
  int result = 0;
  __asm__ volatile("int $0x50"
               : "=a"(result)
               : "a"(num),
                 "b"(p1),
                 "c"(p2),
                 "d"(p3));
  return result;
}

#ifndef SAYORISDK_PRINTF_H
#define SAYORISDK_PRINTF_H

#include <stdarg.h>
#include "stdint.h"

size_t measure_vsprintf(const char *format, va_list args);
size_t measure_sprintf(const char* format, ...);

int vsprintf(char* buffer, const char *format, va_list args);
int sprintf(char* buffer, const char* format, ...);

int vasprintf(char** buffer, const char* format, va_list args);
int asprintf(char** buffer, const char* format, ...);

int vsnprintf(char* buffer, size_t n, const char* format, va_list args);
int snprintf(char* buffer, size_t n, const char* format, ...);

void printf(const char *text, ...);

#endif //SAYORISDK_PRINTF_H

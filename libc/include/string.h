#ifndef SAYORISDK_STRING_H
#define SAYORISDK_STRING_H

#pragma once

#include "stddef.h"
#include "stdbool.h"

SAYORI_INLINE bool isdigit(char a) {
    return a >= '0' && a <= '9';
}

bool isalnum(char c);
bool isUTF(char c);
bool isSymbol(char c);
uint32_t SymConvert(char c, char c1, char c2);
uint32_t UTFConvert(char c, char c1);
size_t strlen(const char *str);
size_t mb_strlen(const char *str);
size_t struntil(const char* str, const char find);
void* memcpy(void* /*restrict*/ destination, const void* /*restrict*/ source, size_t n);
void* memset(void* ptr, char value, size_t num);
void* memmove(void *dest, void *src, size_t count);
int strcmp(const char *s1, const char *s2);
bool strcmpn(const char *str1, const char *str2);
int strcpy(char* dest, const char* src);
int32_t memcmp(const char *s1, const char *s2, size_t n);
size_t strspn(const char *s, const char *accept);
int32_t strncmp(const char *s1, const char *s2, size_t num);
char *strtok(char *s, const char *delim);
char *strncpy(char *dest, const char *src, size_t n);
char* strcat(char* destination, const char* source);
void substr(char* /*restrict*/ dest, const char* /*restrict*/ source, int from, int length);
char *strchr(const char *_s, char _c);
void strtolower(char* as);
void strtoupper(char* as);
bool isNumber(const char* c);
uint32_t atoi(const char s[]);
void strver(char *str);
size_t itoa(int32_t n, char *buffer);
size_t itou(size_t n, char *buffer);
size_t itoh(size_t i, char *buffer);
int dcmpstr( const char *s1, const char *s2 );
char digit_count(size_t num);
char hex_count(size_t num);
bool isnumberstr(char* a);
size_t strcount(const char* string, char character);
char* strstr(const char* haystack, const char* needle);
unsigned long strtoul(const char* str, char** endptr, int base);
#endif //SAYORISDK_STRING_H

#ifdef SAYORISDK_MATH_H
double strtod(const char* str, char** endptr);
#endif //SAYORISDK_MATH_H

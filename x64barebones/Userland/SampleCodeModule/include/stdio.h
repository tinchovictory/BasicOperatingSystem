#ifndef STDIO
#define STDIO

#include <stdint.h>

int putchar(char c);

int getchar();

int printf(const char* format, ...);

int puts(char * str);

void putNum(int num);

#endif
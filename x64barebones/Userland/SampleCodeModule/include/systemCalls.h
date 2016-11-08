#ifndef _SYSTEM_CALLS_USER_
#define _SYSTEM_CALLS_USER_

#include <stdint.h>

uint64_t systemCall(uint64_t systemCallNumber, uint64_t fileDescriptor, uint64_t * buf, uint64_t nBytes); // asm function


/* Returns the number of bytes that were read. If value is negative, then the system call returned an error. */
int read(int fildes, void *buf, unsigned int nbytes);


/* Returns the number of bytes that were written. If value is negative, then the system call returned an error. */
int write(int fildes, const void *buf, unsigned int nbytes);


void clearScreen();

#endif
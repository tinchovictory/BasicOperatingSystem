#ifndef _SYSTEM_CALLS_
#define _SYSTEM_CALLS_

#include <stdint.h>

uint64_t systemCall(uint64_t systemCallNumber, uint64_t fileDescriptor, uint64_t * buf, uint64_t nBytes); // asm function

#endif
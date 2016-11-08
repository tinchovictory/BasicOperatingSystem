#ifndef _SYSTEM_CALLS_
#define _SYSTEM_CALLS_

#include <stdint.h>

void systemCall(uint64_t fd, uint64_t * buf);

#endif
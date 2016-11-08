#include "systemCalls.h"
#include <videoDriver.h>
#include <stdint.h>

void systemCall(uint64_t fd, uint64_t * buf){
	unsigned char c = fd/10 + '0';
	printCharacters(&c, 1);
	newLine();
	printCharacters(buf, 2);
	newLine();
	print(buf);
	//printCharacters(buf+1,1);
}
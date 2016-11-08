#include "systemCalls.h"
#include <videoDriver.h>

void systemCall(int fd){
	unsigned char c = fd + '0';
	printCharacters(&c, 1);
}
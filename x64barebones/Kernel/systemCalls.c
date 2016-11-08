#include "systemCalls.h"
#include <videoDriver.h>
#include <keyBoardDriver.h>

#define SYS_CALL_READ 1
#define SYS_CALL_WRITE 2
#define SYS_CALL_CLEAR_SCREEN 3


uint64_t clearScreenSys(){
	clearScreen();
	return 0;
}
uint64_t write(uint64_t fileDescriptor, char * buf, uint64_t nBytes);

uint64_t read(uint64_t fileDescriptor, char * buf, uint64_t nBytes){

	if(fileDescriptor == 1){
		int i,cont = 1;
		for (i = 0; i < nBytes && cont; i++){
			*(buf + i) = getKey();
			if(*(buf + i) == 0){
				cont = 0;
			}
		}
		return i;
	}
	return -1;
}

uint64_t write(uint64_t fileDescriptor, char * buf, uint64_t nBytes){

	if(fileDescriptor == 1){
		int i;
		for(i = 0; i < nBytes && buf[i] != 0; i++){
			printCharacters(buf[i]);
		}
		return i;
	}
	return -1;
}


uint64_t systemCall(uint64_t systemCallNumber, uint64_t fileDescriptor, void * buf, uint64_t nBytes){
	if(systemCallNumber == SYS_CALL_READ){
		return read(fileDescriptor, (char *) buf, nBytes);
	}else if(systemCallNumber == SYS_CALL_WRITE){
		return write(fileDescriptor, (char *) buf, nBytes);
	}else if(systemCallNumber == SYS_CALL_CLEAR_SCREEN){
		return clearScreenSys();
	}
	return 0;
}
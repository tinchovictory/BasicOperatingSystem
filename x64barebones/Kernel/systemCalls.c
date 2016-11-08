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

uint64_t read(uint64_t fileDescriptor, uint64_t * buf, uint64_t nBytes){
	return getKey();
}

uint64_t write(uint64_t fileDescriptor, uint64_t * buf, uint64_t nBytes){
	// int i;
	// for(i=0;i<nBytes;i++){
	// 	printCharacters(buf+i,1);
	// }
	printCharacters(buf,nBytes);//si le paso un nBytes mayor va a fallar. Lo de arriba no anda
	return nBytes;
}


uint64_t systemCall(uint64_t systemCallNumber, uint64_t fileDescriptor, uint64_t * buf, uint64_t nBytes){
	if(systemCallNumber == SYS_CALL_READ){
		return read(fileDescriptor, buf, nBytes);
	}else if(systemCallNumber == SYS_CALL_WRITE){
		return write(fileDescriptor, buf, nBytes);
	}else if(systemCallNumber == SYS_CALL_CLEAR_SCREEN){
		return clearScreenSys();
	}
	return 0;
}
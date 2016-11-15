#include "systemCalls.h"
#include <videoDriver.h>
#include <keyBoardDriver.h>

#define SYS_CALL_READ 1
#define SYS_CALL_WRITE 2
#define SYS_CALL_CLEAR_SCREEN 3
#define SYS_CALL_MEMORY 4

#define MEMORY_ASIGN_CODE 0
#define MEMORY_FREE_CODE 1

#define STANDARD_IO_FD 1
#define ETHERNET_FD 2

static void * memory = (void *)0x900000;

uint64_t clearScreenSys(){
	clearScreen();
	return 0;
}
uint64_t write(uint64_t fileDescriptor, char * buf, uint64_t nBytes);

uint64_t read(uint64_t fileDescriptor, char * buf, uint64_t nBytes){

	if(fileDescriptor == STANDARD_IO_FD){
		int cont = 1, readBytes=0;
		for (int i = 0; i < nBytes && cont; i++){
			*(buf + i) = (char) getKey();
			if(*(buf + i) == 0){
				cont = 0;
			}else{
				readBytes++;
			}
		}
		return readBytes;
	}
	return -1;
}

uint64_t write(uint64_t fileDescriptor, char * buf, uint64_t nBytes){

	if(fileDescriptor == STANDARD_IO_FD){
		int i;
		for(i = 0; i < nBytes && buf[i] != 0; i++){
			printCharacters(buf[i]);
		}
		return i;
	}
	return -1;
}

uint64_t memoryManagement(uint64_t fnCode, uint64_t nBytes){
	if(fnCode == MEMORY_ASIGN_CODE){//asigno memoria
		void * ptr = memory;
		memory += nBytes;
		return (uint64_t) ptr;
	}else if(fnCode == MEMORY_FREE_CODE){//libero memoria
		return 0;
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
	}else if(systemCallNumber == SYS_CALL_MEMORY){
		return memoryManagement(fileDescriptor, nBytes);
	}
	return 0;
}


#include <stdint.h>
#include <sysIO.h>

#include <naiveConsole.h>

#define IO_ADDRESS 0xC000
#define TURN_ON 0x52

void turnOnRTL(){
	sysOutByte(IO_ADDRESS + TURN_ON, 0x0);

	sysOutByte(IO_ADDRESS + 0x37, 0x10);
	while( (sysInLong(IO_ADDRESS + 0x37) & 0x10) != 0 );
}

void initBufferRTL(char* buffer){
	sysOutLong(IO_ADDRESS + 0x30, (uintptr_t)buffer);
}

void setImrIsr(){
	sysOutWord(IO_ADDRESS + 0x3C, 0x0005);
}

void configRCR(){
	sysOutLong( IO_ADDRESS + + 0x44, 0xf | (1 << 7) );
}

void enableRTL(){
	sysOutByte( IO_ADDRESS + 0x37, 0x0C);
}

void initRTL(){
	char buffer[100] = {0};

	turnOnRTL();
	initBufferRTL(buffer);
	setImrIsr();
	configRCR();
	enableRTL();

	ncPrint(buffer);
}
#include <stdint.h>
#include <sysIO.h>

#include <naiveConsole.h>

#define IO_ADDRESS 0xC000
#define TURN_ON 0x52
#define ISR 0x3E

#define RECIEVE_DESC 0x30
#define TSAD0 0x20
#define TSAD1 0x24
#define TSAD2 0x28
#define TSAD3 0x2C

#define TOK (1<<2) //packet transmision completed succesfully
#define ROK 1		//succesfull completition of packet reception


#define BUFFER_SIZE 100 

static char buffer[4][BUFFER_SIZE] = {0};

void turnOnRTL(){
	sysOutByte(IO_ADDRESS + TURN_ON, 0x0);

	sysOutByte(IO_ADDRESS + 0x37, 0x10);
	while( (sysInLong(IO_ADDRESS + 0x37) & 0x10) != 0 );
}

void initBufferRTL(){
	sysOutLong(IO_ADDRESS + 0x30, (uintptr_t)buffer[0]);
	sysOutLong(IO_ADDRESS + TSAD0, (uintptr_t)buffer[1]);
	sysOutLong(IO_ADDRESS + TSAD1, (uintptr_t)buffer[2]);
	sysOutLong(IO_ADDRESS + TSAD2, (uintptr_t)buffer[3]);
	sysOutLong(IO_ADDRESS + TSAD3, (uintptr_t)buffer[4]);
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

void sendmessage(){
	buffer[1][0]='h';
	buffer[1][1]='o';
	buffer[1][2]=0;
	sysOutLong( IO_ADDRESS + 0x10, 3); /* bits 0 to 12 set with message size, bit 13 (OWN) with 0, bits 16 to 21 with 0*/

}

void rtlHandler(){
	uint16_t status = sysInWord( IO_ADDRESS + ISR);

	if(status & TOK){
		ncPrint("Message sent");
	}
	else{
		ncPrint("Message recieved");
	}
	initRTL();
}

void initRTL(){
	turnOnRTL();
	initBufferRTL();
	setImrIsr();
	configRCR();
	enableRTL();
	//sendmessage();
}
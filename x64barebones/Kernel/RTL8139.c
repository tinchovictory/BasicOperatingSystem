#include "RTL8139.h"
#include <stdint.h>
#include <sysIO.h>

#include <naiveConsole.h>

#define IO_ADDRESS 0xC000 //Get from pci search

#define CONFIG_1 0x52	//Configuration Register 1 Address
#define ISR 0x3E 	//Interrupt Status Register Start Address
#define CR 0x37		//Command Register Address

#define RBSTART 0x30 	//Receive Buffer Start Address 
#define TSAD0 0x20		//Transmit Start Address of Descriptor0
#define TSAD1 0x24		//Transmit Start Address of Descriptor1
#define TSAD2 0x28		//Transmit Start Address of Descriptor2
#define TSAD3 0x2C		//Transmit Start Address of Descriptor3

#define CHECK_TOK 0x4		//packet transmision completed succesfully
#define CHECK_ROK 0x1		//succesfull completition of packet reception

#define CLEAR_TOK 0xFB
#define CLEAR_ROK 0xFE

#define TR_BUFFER_SIZE 10000 
#define RE_BUFFER_SIZE 10000

#define MAC_SIZE 6

static char trBuffer[3][TR_BUFFER_SIZE] = {{0}};
static char reBuffer[RE_BUFFER_SIZE] = {0};

typedef struct {
	uint8_t macDest[MAC_SIZE];
	uint8_t macSrc[MAC_SIZE];
	uint16_t lenght;
	uint8_t payload[1000];
	uint32_t frameCheck;
} ethFrame;


void mymemcpy( void * dest, void * src, int lenght){
	char * d = dest;
	char * s = src;
	//char * srcT = (char *) src;
	for(int i = 0; i < lenght; i++){
		d[i] = s[i];
	}
}

void transmit(ethFrame * frame){
	if(frame == NULL){
		return;
	}

	int lenght = 0;

	/* Copy ethernet frame to transmit buffer */
	mymemcpy(trBuffer[0]+lenght,frame->macDest,MAC_SIZE);
	lenght += MAC_SIZE;
	mymemcpy(trBuffer[0]+lenght,frame->macSrc,MAC_SIZE);
	lenght += MAC_SIZE;
	trBuffer[0][lenght] = frame->lenght;
	lenght += 2;
	mymemcpy(trBuffer[0]+lenght,frame->payload,frame->lenght);
	lenght += frame->lenght;
	trBuffer[0][lenght] = frame->frameCheck;
	lenght += 2;

	for(int i=0; i<200; i++){
		ncPrintChar(trBuffer[0][i]);	
	}

	sysOutLong( IO_ADDRESS + 0x10, lenght & 0xFFF);//clear own bit

}

void sendMsg(){
	/*buffer[1][0]='h';
	buffer[1][1]='o';
	buffer[1][2]=0;*/
	//sysOutLong( IO_ADDRESS + 0x10, 3); /* bits 0 to 12 set with message size, bit 13 (OWN) with 0, bits 16 to 21 with 0*/
	ethFrame frame = {{0xDE,0x00,0x40,0xAA,0x21,0x2E},{0xDE,0x00,0x40,0xAA,0x21,0x2E},100,{'h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l','h','o','l',0},'b'};
	frame.payload[1] = 'c';
	
	/*frame.macDest[0] = 
	frame.macDest = {0xDE,0x00,0x40,0xAA,0x21,0x2E};
	frame.macSrc = {0xDE,0x00,0x40,0xAA,0x21,0x2E};
	frame.lenght = 3;
	frame.payload = {'h','o''l',0};
	frame.frameCheck = 0;*/
	transmit(&frame);
}

void rtlHandler(){
	uint16_t status = sysInWord( IO_ADDRESS + ISR);

	if( (status & CHECK_ROK) != 0 ){ // ISR bit 0 enabled indicates Recive OK

		ncPrint("Message recieved");
		ncNewline();
		for(int i=0; i<200; i++){
			ncPrintChar(reBuffer[i]);
		}
		ncPrint("done");

		//pongo el ROK en 0
		sysOutWord( IO_ADDRESS + ISR, CLEAR_ROK);


	}else if( (status & CHECK_TOK) != 0 ){ // ISR bit 2 enabled indicates Transmit OK

ncPrint("Message sent");

		//pongo el TOK en 0
		sysOutWord( IO_ADDRESS + ISR, status | CLEAR_TOK);

	}

	/*if(status & TOK){
		ncPrint("Message sent");
	}
	else{
		ncPrint("Message recieved");
	}
	initRTL();*/
}

void initRTL(){
	
	/* Send 0x00 to the CONFIG_1 register. This should essentially "power on" the device. */
	sysOutByte(IO_ADDRESS + CONFIG_1, 0x0);

	/* Software reset to clear the RX and TX buffers and set everything back to defaults. */
	sysOutByte(IO_ADDRESS + CR, 0x10);
	/* Checking the RST bit to make sure that the chip has finished the reset. */
	while( (sysInLong(IO_ADDRESS + CR) & 0x10) != 0 );

	/* Setting the Read and Write buffers memory location to the RTL */
	sysOutLong(IO_ADDRESS + RBSTART, (uintptr_t)reBuffer);
	sysOutLong(IO_ADDRESS + TSAD0, (uintptr_t)trBuffer[0]);
	sysOutLong(IO_ADDRESS + TSAD1, (uintptr_t)trBuffer[1]);
	sysOutLong(IO_ADDRESS + TSAD2, (uintptr_t)trBuffer[2]);
	sysOutLong(IO_ADDRESS + TSAD3, (uintptr_t)trBuffer[3]);

	/* Set the RTL8139 to accept only the Transmit OK (TOK) and Receive OK (ROK) interrupts
	** we would have the TOK and ROK bits of the IMR high and leave the rest low. */
	sysOutWord(IO_ADDRESS + 0x3C, 0x0005);

	/* Telling the RTL8139 to accept AB+AM+APM+AAP packets (0xf).
	** Setting WRAP bit, so the packet will be written contiguously in memory. */
	sysOutLong( IO_ADDRESS + 0x44, 0xf | (1 << 7) );

	/* Start up the RX and TX functions.
	** Once this is completed, then the card will start allowing packets in and/or out. */
	sysOutByte( IO_ADDRESS + CR, 0x0C);

}
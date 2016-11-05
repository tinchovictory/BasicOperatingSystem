#include <interruptions.h>

void sti();
unsigned char getKeyboard();
void printCharacter();
void irq0Handler();
void irq1Handler();
void setPicMaster(uint16_t);

#pragma pack(push)
#pragma pack(1)


typedef struct { 
	uint16_t offset_l; //bit 0..15
	uint16_t selector;
	uint8_t zero_l;
	uint8_t attrs;
	uint16_t offset_m; //16..31
	uint32_t offset_h; //32..63
	uint32_t zero_h;
} IDTEntry_t;

#pragma pack(pop)



static IDTEntry_t* IDT = (IDTEntry_t*) 0x0;
static char *video = (char *) 0xB8000;
static int i=0;
static int cursor=80;

void tickHandler() {
	//video[i++] = i;	
}

void keyBoardDriver(){
	video[cursor]=getKeyboard();
	cursor+=2;
}



typedef void (*handler_t)(void);

handler_t handlers[] = {tickHandler,printCharacter};

void irqDispatcher(int irq) {
	handlers[irq]();
}


void iSetHandler(int index, uint64_t handler) {
	IDT[index].offset_l = (uint16_t) handler & 0xFFFF;
	IDT[index].offset_m = (uint16_t) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (uint32_t) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
	
}

void initializeInterruptions(){
	iSetHandler(0x20, (uint64_t) irq0Handler);
	iSetHandler(0x21, (uint64_t) irq1Handler);
	setPicMaster(0xFC); // activo las irq0 y irq1 en el pic
	
	sti();
}


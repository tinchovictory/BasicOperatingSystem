#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>

#include <videoDriver.h>
#include <keyBoardDriver.h>
#include <pci.h>
#include <RTL8139.h>

#include <systemCalls.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	ncPrint("[x64BareBones]");
	ncNewline();

	ncPrint("CPU Vendor:");
	ncPrint(cpuVendor(buffer));
	ncNewline();

	ncPrint("[Loading modules]");
	ncNewline();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	ncPrint("[Done]");
	ncNewline();
	ncNewline();

	ncPrint("[Initializing kernel's binary]");
	ncNewline();

	clearBSS(&bss, &endOfKernel - &bss);

	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
	ncNewline();
	return getStackBase();
}


void printEthMsg(ethMsg msg1){
	ncNewline();ncPrint("Mac destination: ");
		for(int i=0; i<MAC_SIZE; i++){
			ncPrintHex(msg1.mac[i]);
		}
		ncNewline();ncPrint("length: ");
		ncPrintDec(msg1.length);ncNewline();
		ncPrint("Message: ");ncNewline();
		for(int i=0; i<msg1.length; i++){
			ncPrintChar(msg1.msg[i]);
		}
		ncNewline();
		ncPrint("---------End of message----");ncNewline();ncNewline();
}
int main()
{	
	ncClear();
	initializeInterruptions();
	
	//searchRTL();
	activeRTLdma();
	//activeDMA();
	initRTL();
	ncPrint("RTL initalized");ncNewline();
	

	/*int i;
	ethMsg msg1={{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{'h','o','l','a',0},5};//DE:00:40:AA:21:2E
	ethMsg gMsg ;

	for(i=0;i<800000000;i++);
	//sendMsg(msg1);
	systemCall(2, 2, &msg1, 100);
//for(i=0;i<800000000;i++);
systemCall(2, 2, &msg1, 100);
for(i=0;i<800000000;i++);
	if(systemCall(1,2,&gMsg,100)){
		printEthMsg(gMsg);
	}else{
		ncPrint("No Msg");
	}
	if(systemCall(1,2,&gMsg,100)){
		printEthMsg(gMsg);
	}else{
		ncPrint("No Msg");
	}
	if(systemCall(1,2,&gMsg,100)){
		printEthMsg(gMsg);
	}else{
		ncPrint("No Msg");
	}
	//printEthMsg(gMsg);
	//getMsg(&gMsg);
	//printEthMsg(gMsg);
	//for(i=0;i<800000000;i++);
	//sendMsg("ANDA?",6);
//sendMsg("ANDA?",6);
	//ncNewline();
	//ncPrint("Finished");
*/
	
	ncClear();
	((EntryPoint)sampleCodeModuleAddress)();
	return 0;
}

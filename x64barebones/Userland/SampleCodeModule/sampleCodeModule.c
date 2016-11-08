#include <systemCalls.h>

/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;

int main() {
	
	char c[5] = {'h',0,'o','l','a'}; 
/*
	write(1,c,4);
	//clearScreen();
	c[0] = '1';
	write(1,"\n",1);
	write(1,c,10);
*/
	read(1,c,1);
	write(1,c,10);
	while(*c != '1'){
		read(1,c,1);
		write(1,c,10);
	}

	/*for(int i=0;i<100;i++){
		unsigned char ch =read(1,0,0);
		write(1, &ch, 1);
	}*/

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
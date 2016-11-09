#include <systemCalls.h>
#include <stdio.h>

/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;

int main() {
	
	char c[5] = {'h',0,'o','l','a'}; 
	char buffer[100];
	char character;
	/*int i=0;
	while((character=getchar())!= '\n'){
		buffer[i++]=character;
	}
	buffer[i]=0;
	printf(buffer);*/

	/*buffer[0]=getchar();
	buffer[1]=getchar();
	buffer[2]=getchar();
	buffer[3]=0;*/
	putchar('>');
	putchar(' ');
	printf("HOLA %s que se yo %d","Segundo",40432);
	

	while(1){
		char c= getchar();
		if (c=='\n'){
			putchar(c);
			putchar('>');
			putchar(' ');
		}else{
		putchar(c);
		}
	}
	//printf("HOLA");


	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
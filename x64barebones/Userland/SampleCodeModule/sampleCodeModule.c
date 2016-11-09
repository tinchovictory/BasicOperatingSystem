#include <systemCalls.h>
#include <stdio.h>
#include <string.h>
void shell();

/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;

int main() {
	shell();
/*	putchar('>');
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
*/

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
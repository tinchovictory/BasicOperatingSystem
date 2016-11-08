#include <stdint.h>
/* sampleCodeModule.c */

static int var1 = 0;
static int var2 = 0;

void systemCall(uint64_t systemCallNumber,uint64_t * buf);

int main() {
	
	char c[5] = {'h','o','l','a'}; 

	systemCall(1,c);

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
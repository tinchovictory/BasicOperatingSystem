#include <systemCalls.h>

int strlen(const char* str);


int printf(const char* format){

	return write(1,format,strlen(format));
}
int getchar(){
	char c;
	while((read(1,&c,1)==1));
	return c;
}

int strlen(const char* str){
	int count=0; 
	while(*str){
		count++;
		str++;
	}
	return count;
}
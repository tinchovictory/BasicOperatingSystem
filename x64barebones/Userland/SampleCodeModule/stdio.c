#include <systemCalls.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


int printf(const char* format,...){
	va_list valist;
	va_start(valist,format);
	int i;
	
	for(i=0;format[i]!=0;i++){
		while(format[i]!=0 && format[i]!='%'){
			putchar(format[i++]);
		}
		if(format[i]!=0 && format[i]=='%'){
			i++;
			if(format[i]=='s'){
				puts(va_arg(valist, char *));
			}else if(format[i]=='c') {
				putchar(va_arg(valist, int));
			}else if (format[i]=='d'){
				putNum(va_arg(valist,int));
			}
		}
	}


	return 1;
}

void putNum(int num){
	char buffer[100]={0};
	int i;
	for (i=0;num!=0;i++){
		buffer[i]=num%10;
		num=num/10;
	}
	while(i){
		putchar(buffer[--i]+'0');
	}

}

int puts(char * str){
	return write(1,str,strlen(str));
}

int getchar(){
	char c;
	while((read(1,&c,1)==0));
	return c;
}

int putchar(char c){
	return write(1,&c,1);
}

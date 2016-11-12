#include <systemCalls.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>




void putNum(int num){
	char buffer[100]={0};
	int i;
	if(num==0){
		putchar('0');
		return;
	}else if(num<0){
		putchar('-');
		num=num*-1;
	}
	for (i=0;num!=0;i++){
		buffer[i]=num%10;
		num=num/10;
	}
	while(i){
		putchar(buffer[--i]+'0');
	}

}

int printString(char * str){
	return write(1,str,strlen(str));
}

int puts(char * str){
	int ans = printString(str);
	ans += putchar('\n');
	return ans;
}

int getchar(){
	char c;
	while((read(1,&c,1)==0));
	return c;
}

int putchar(char c){
	return write(1,&c,1);
}


void printf(const char* format,...){
	va_list parameters;
	va_start(parameters,format);
	int i;
	for(i=0;format[i]!=0;i++){
		while(format[i]!=0 && format[i]!='%'){
			putchar(format[i++]);
		}
		if (format[i]==0){
			break;
		}else if(format[i]=='%'){
			i++;
			if(format[i]=='s'){
				printString(va_arg(parameters, char *));
			}else if(format[i]=='c') {
				putchar(va_arg(parameters, int));
			}else if (format[i]=='d'){
				putNum(va_arg(parameters,int));
			}
		}
	}
	va_end(parameters);


	return;
}

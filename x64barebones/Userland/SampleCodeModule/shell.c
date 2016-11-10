#include <stdio.h>
#include <string.h>

int startsWith(const char * str1, const char * str2){
	while(*str1){
		if(*str1!=*str2){
			return 0;
		}
		str1++;
		str2++;
	}
	return 1;
}

void processComand(char * buffer){
	if (!strcmp(buffer,"help")){
		puts("  echo : print on screen\n");
		puts("  hola : saludo de la consola\n");
	}
	else if(startsWith("echo",buffer)){
		puts("  ");
		puts(buffer+4);
		putchar('\n');
	}
	else if(!strcmp(buffer,"hola")){
		puts("  Hola! Mi nombre es NetSky\n");
	}
	else{
		printf("  Command not found - help for instructions\n");
	}
}


void shell(){
	
	char buffer[100];
	int i=0;
	while(1){
		char c;
		puts("$> ");
		while ((c=getchar())!= '\n'){
			if(c != '\b'){
				buffer[i++]=c;
			}else{
				if(i==0){
					continue;
				}
				i--;
			}
			putchar(c);
		}
		putchar(c);
		buffer[i]=0;
		c='0';
		processComand(buffer);
		//putchar(c);
		i=0;
	}

}
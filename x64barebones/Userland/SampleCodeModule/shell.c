#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myGame.h"
#include <myChat.h>
//#include <systemCalls.h>

void clearScreen();
/*
typedef struct {
	uint8_t mac[6];
	uint8_t msg[1000];
	uint16_t length;
} ethMsg;
void mymemcpy( void * dest, void * src, int length){
	char * d = dest;
	char * s = src;

	for(int i = 0; i < length; i++){
		d[i] = s[i];
	}
}
*/
void processComand(char * buffer){
	if (!strcmp(buffer,"help")){
		printf("  echo : print on screen\n");
		printf("  hola : saludo de la consola\n");
		printf("  2048game : Juego 2048\n");
		printf("  chat: enter to chat\n");
		printf("  clear:  clear screen\n");
	}
	else if(startsWith("echo ",buffer)){
		puts(buffer+5);
	}
	else if(!strcmp(buffer,"hola")){
		puts("  Hola! Mi nombre es NetSky");
	}else if(!strcmp(buffer,"2048game")){
		game2048();
	}
	else if(!strcmp("clear",buffer)){
		clearScreen();
	}else if(startsWith("chat",buffer)){
		myChat();
		//ethMsg msg1={{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},0,0};
		//mymemcpy(msg1.msg,buffer+5,strlen(buffer+5));
		//msg1.length=strlen(buffer+5);
		//write(2,&msg1,100);


	}/*else if(!strcmp("read",buffer)){
		ethMsg msg1;
		if(!read(2,&msg1,100)){
			puts("No messages!");
			return;
		}

		puts("Mac source: ");
		for(int i=0; i<6; i++){
			putNum(msg1.mac[i]);
		}
		puts("length: ");
		putNum(msg1.length);
		puts("Message: ");
		for(int i=0; i<msg1.length; i++){
			putchar(msg1.msg[i]);
		}
		puts("");
		puts("---------End of message----");
	}*/
	else{
		puts("  Command not found - help for instructions");
	}
}


void shell(){

	char buffer[100];
	int i=0;
	while(1){
		char c;
		printf("$> ");
		while ((c=getchar())!= '\n'){
			if(c != '\b'){
				buffer[i++]=c;
				putchar(c);
			}else if (i>0){
				i--;
				putchar(c);
			}	
		}
		putchar(c);
		buffer[i]=0;
		processComand(buffer);
		i=0;
	}
	

}
#include <myChat.h>
#include <stdio.h>
#include <string.h>
#include <systemCalls.h>

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

void command(char * str){
	if(startsWith("send ",str)){
		ethMsg msg={{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0},0};
		mymemcpy(msg.msg,str+5,strlen(str+5));
		msg.length=strlen(str+5);
		write(2,&msg,msg.length);
	}else{
		puts("WRONG COMMAND!");
	}
}

void getMsg(){
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
}

void myChat(){
	printf("Este es el chat!\n" );
	char buffer[200];
	int i=0;
	char c;
	//while((c=getchar())!= 'q'){
	while(1){
		printf("Chat -> ");

		//verifico si recibi algo
		getMsg();
		

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
		command(buffer);
		i=0;
	}
}
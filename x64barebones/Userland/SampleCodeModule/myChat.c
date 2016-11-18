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

int command(char * str){
	if(startsWith("send ",str)){
		return 1;
	}else{
		ethMsg msg={{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},{0},0};
		mymemcpy(msg.msg,str,strlen(str));
		msg.length=strlen(str);
		write(2,&msg,msg.length);
	}
	return 0;
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



void deleteLine(int amount){
	while(amount){
		putchar('\b');
		amount--;
	}
}


void myChat(){
	printf("Este es el chat!\n" );
	char buffer[200];
	int i=0;
	int exit=0;
	char c;
	int deleteFlag=0;
	ethMsg msg;
	
	while(!exit){
		//printf("You: ");
		if(i==0 && !deleteFlag){
			printf("You: ");
		}
		//verifico si recibi algo
		int cFlag;
		int mFlag;


		while ((cFlag=read(1,&c,1))==0 && (mFlag=read(2,&msg,100))==0);
			if(cFlag){
				if(c == '\n'){
					buffer[i]=0;
					exit=command(buffer);//mandar mensaje
					i=0;
					putchar(c);
				}else if(c == '\b'){
					if(i>0){
						putchar(c);
						i--;
					}else{
						deleteFlag=1;
					}
				}else{
					buffer[i++]=c;
					putchar(c);
					deleteFlag=0;
				}	

				
				cFlag=0;
			}
			if(mFlag){
				buffer[i]=0;
				deleteLine(i + 5);//borrarlinea
				printf("%s\n", msg.msg);				//imprimir mensaje
				if(i!=0){
					printf("You: %s",buffer);				//volver a imprimir linea
				}						
				mFlag=0;
			}
	}

}
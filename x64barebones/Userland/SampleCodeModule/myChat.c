#include <myChat.h>
#include <stdio.h>
#include <string.h>
#include <systemCalls.h>

#define USERNAME_LENGTH 50
#define MAC_SIZE 6
#define ONLINE 0
#define OFFLINE 1
#define MESSAGE 2


#define PUBLIC 3
#define PRIVATE 4





typedef struct {
	uint8_t mac[MAC_SIZE];
	uint8_t msg[1000];
	uint16_t length;
	uint8_t type;
} ethMsg;

void mymemcpy( void * dest, void * src, int length){
	char * d = dest;
	char * s = src;

	for(int i = 0; i < length; i++){
		d[i] = s[i];
	}
}

int command(char * str){
	if(!strcmp("exit",str)){
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

void welcome(char * user){
	printf("        **************Welcome to SkyChat!**************\n" );
	printf("This are the available commands:\n");
	printf("     exit: exit chat room\n");
	printf("\n" );

	char c;
	int j = 0;
	printf("%s", "What's your name?: ");


	while((c=getchar())!='\n' && j<USERNAME_LENGTH){
		if(c == '\b'){
			if(j!=0 ){			
				putchar(c);
				j--;
			}
		}else{
		putchar(c);
		user[j++] = c;
		}
	}
	user[j] = 0;
	putchar('\n');
	
}
void send(int type, char dest[MAC_SIZE] , char * message){
	
	ethMsg msg={{0},{0},0};
	mymemcpy(msg.mac,dest,MAC_SIZE);
	mymemcpy(msg.msg,message,strlen(message));
	msg.length=strlen(message);
	msg.type=type;
	write(2,&msg,msg.length);
}

void online(char * user){
	send(ONLINE,PUBLIC,user);
}

void myChat(){
	char buffer[200];
	int i=0;
	int exit=0;
	char c;
	int deleteFlag=0;
	char user[USERNAME_LENGTH];

	welcome(user);
	online(user);
	
	while(!exit){
		if(!i && !deleteFlag){
			printf("%s: ",user);
		}
		//verifico si recibi algo
		int cFlag;
		int mFlag;
		ethMsg msg;

		while ( (cFlag=read(1,&c,1))==0 && (mFlag=read(2,&msg,100))==0 );
			
		if(cFlag){
			if(c == '\n'){
				buffer[i]=0;
				exit=command(buffer);//mandar mensaje
				i=0;
				putchar(c);
			}else if(c == '\b'){
				if(i!=0 ){			
					putchar(c);
					i--;
				}if(i ==0){
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
			deleteLine(i+2+strlen(user));

			msg.msg[msg.length]=0;//convierto el ensja a string
			printf("Your Friend: %s\n", msg.msg);				//imprimir mensaje
			
			if(i){
				printf("%s: %s",user,buffer);	
				//printf("You: %s",buffer);				//volver a imprimir linea
			}						
			mFlag=0;
		}
	}

}

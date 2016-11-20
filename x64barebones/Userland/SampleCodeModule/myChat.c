#include <myChat.h>
#include <stdio.h>
#include <string.h>
#include <systemCalls.h>

#define MAX_USERS 50
#define USERNAME_MAXLENGTH 50
#define MAC_SIZE 6
#define ONLINE 0
#define OFFLINE 1
#define MESSAGE 2





static uint8_t public[MAC_SIZE] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
static uint8_t user[USERNAME_MAXLENGTH];
static uint8_t userList[USERNAME_MAXLENGTH][MAX_USERS];
static uint8_t macList[MAC_SIZE][MAX_USERS];
static int usersCount=0;
static uint8_t generic[]="Your friend";

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
		send(OFFLINE,public,user);
		printf("\n        Thanks for using our chat room! Bye bye!\n");
		return 1;
	}else if(str[0]==0){
		return 0;
	}
	else{
		send(MESSAGE,public,str);
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

void welcome(){
	printf("        ***********************************************\n");
	printf("        **                                           **\n");
	printf("        **            Welcome to SkyChat!            **\n");
	printf("        **                                           **\n");
	printf("        ***********************************************\n");
	printf("This are the available commands:\n");
	printf("     exit: exit chat room\n");
	printf("\n" );

	char c;
	int j = 0;
	printf("%s", "What's your name?: ");


	while((c=getchar())!='\n' && j<USERNAME_MAXLENGTH){
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
	putchar('\n');
	putchar('\n');
	
}
void send(int type, uint8_t dest[MAC_SIZE] , char * message){

	ethMsg msg={{0},{0},0};
	mymemcpy(msg.mac,dest,MAC_SIZE);
	mymemcpy(msg.msg,message,strlen(message));
	msg.length=strlen(message);
	msg.type=type;
	write(2,&msg,msg.length);
}

void save(char * user, uint8_t mac[MAC_SIZE]){
	mymemcpy(userList[usersCount],user,strlen(user));
	mymemcpy(macList[usersCount],mac,MAC_SIZE);
	usersCount++;
}

void delete(char * user, uint8_t mac[MAC_SIZE]){
	
}

int cmpMac(uint8_t mac1[MAC_SIZE],uint8_t mac2[MAC_SIZE]){
	for(int i = 0; i < MAC_SIZE; i++){
		if(mac1[i] != mac2[i]){
			return 0;
		}
	}
	return 1;
}

char * getName(uint8_t mac[MAC_SIZE]){
	int i;
	for(i=0; i<usersCount ;i++){
		if(cmpMac(mac,macList[i])){
			return userList[i];
		}
	}
	return generic;
}

void recieve(ethMsg msg){
	if(msg.type==ONLINE){
		printf("           %s is now online!\n",msg.msg );
		save(msg.msg,msg.mac);//gauradar MAC y nombre de usario
	}else if(msg.type== OFFLINE){
		printf("           %s is now offline\n",msg.msg );
	}else if(msg.type == MESSAGE){
		msg.msg[msg.length]=0;//convierto el mensja a string
		printf("%s: %s\n",getName(msg.mac), msg.msg);				//imprimir mensaje
	}else{
		printf("ALGO SALIO MAL\n");
	}
}

void myChat(){
	char buffer[200];
	int i=0;
	int exit=0;
	char c;
	int deleteFlag=0;
	

	welcome();
	send(ONLINE,public,user);
	
	while(!exit){
		if(!i && !deleteFlag){
			printf("%s: ",user);
		}
		//verifico si recibi algo
		int cFlag;
		int mFlag;
		ethMsg msg;
		/*Aprovecho que el read me devuelve la cantidad de bits que copio
		 si no hay nada para leer read devuelve cero.
		 Este while queda loopeando hasta que halla algo para leer*/
		while ( (cFlag=read(1,&c,1))==0 && (mFlag=read(2,&msg,100))==0 );
			
		if(cFlag){
			if(c == '\n'){
				if(i!=0){
					buffer[i]=0;
					exit=command(buffer);//mandar mensaje
					i=0;
					putchar(c);
				}else{
					deleteFlag=1;
				}
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
			recieve(msg);
			
			if(i){
				printf("%s: %s",user,buffer);	
				//printf("You: %s",buffer);				//volver a imprimir linea
			}						
			mFlag=0;
		}
	}

}

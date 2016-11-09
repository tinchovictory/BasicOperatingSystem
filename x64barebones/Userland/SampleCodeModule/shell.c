#include <stdio.h>
#include <string.h>

int startsWithEcho(char * str){
	if(str[0]='e' && str[1]=='c' && str[2]=='h' && str[3]=='o'){
		return 1;
	}
	return 0;
}

void processComand(char * buffer){
	if (!strcmp(buffer,"help")){
		puts("echo : print on screen\n");
	}else if(startsWithEcho(buffer)){
		puts(buffer+4);
		putchar('\n');
	}else{
	puts("  Command not found - help for instructions\n");
}
}


void shell(){
	
	char buffer[100];
	int i=0;
	while(1){
		char c;
		puts("> ");
		while ((c=getchar())!= '\n'){
			buffer[i++]=c;
			putchar(c);
		}
		putchar(c);
		buffer[i]=0;
		processComand(buffer);
		i=0;
	}

}
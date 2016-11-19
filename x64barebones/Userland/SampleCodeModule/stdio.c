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

int isDigit(char c){
	if (c>='0' && c<='9'){
		return 1;
	}else {
		return 0;
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

static int i = 0;
static char buffer[100];

int getchar(){
	if(i){
		return buffer[--i];
	}
	char c;
	while((read(1,&c,1)==0));
	return c;
}

int ungetc(int c){
	buffer[i++] = c;
	return 0;//QUE DEVUELVE?
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
			}else if (format[i]=='d' || format[i]=='i'){
				putNum(va_arg(parameters,int));
			}else if(isDigit(format[i])){
				int margen = 0;
				int j = 0;
				while(isDigit(format[i])){
					margen = margen*10 + format[i] - '0';
					j++;
					i++;
				}
				if(format[i]=='s'){
					char * word = va_arg(parameters, char *);
					int length = strlen(word);
					if(length < margen){
						margen -= length;
						while(margen){
							putchar(' ');
							margen--;
						}
					}
					printString(word);
				}else if(format[i]=='d' || format[i]=='i'){
					int length;
					int number = va_arg(parameters, int);
					int aux = number;
					while(aux){
						aux /= 10;
						length++;
					}
					if(length < margen){
						margen -= length;
						while(margen){
							putchar(' ');
							margen--;
						}
					}
					putNum(number);
				}else if(format[i]=='c'){
					margen--;
					while(margen){
						putchar(' ');
						margen--;
					}
					putchar(va_arg(parameters, int ));
				}
				else{
					i-=j;
				}
			}else{
				putchar('%');
				putchar(format[i]);
			}
		}
	}
	va_end(parameters);


	return;
}

void scanf(const char *format, ...){

	va_list parameters;
	va_start(parameters,format);
	int i;
	char c = 0;
	
	for(i=0; format[i] != 0; i++){
	
		while(format[i] != 0 && format[i] != '%' && (c = getchar()) != '\n'){
			i++;
		}
	
		if (format[i] == 0 || c == '\n'){
			break;
		}else if(format[i] == '%'){
	
			i++;
	
			if(format[i] == 'd' || format[i] == 'i'){
	
				int * number_ptr;
				number_ptr = va_arg(parameters,int *);
				*number_ptr = 0;
	
				while((c = getchar()) == ' '){

				}

				ungetc(c);
				
				while((c = getchar()) != '\n' && c != ' ' && isDigit(c)){
					*number_ptr = (*number_ptr)*10 + c -'0';
				}
				if(!isDigit(c)){
				
					ungetc(c);
				
				}else if(c == '\n'){
					break;
				}
			
			}else if(format[i] == 's'){
			
				char * string_ptr;
				string_ptr = va_arg(parameters,char *);
			
				while((c=getchar()) == ' '){

				}

				ungetc(c);
				
				while((c=getchar()) != '\n' && c != ' '){
				
					*string_ptr = c;
					string_ptr++;
				
				}
				
				*string_ptr = 0;
				
				if(c == '\n'){
					break;
				}else if(c == ' '){
				
					ungetc(c);
				
				}
			
			}else if(format[i] == 'c'){
			
				char * char_ptr;
				char_ptr = va_arg(parameters,char *);
			
				while((c = getchar()) == ' '){

				}
				
				*char_ptr = c;
			}
		}	
	}
	va_end(parameters);
	return;

}


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

void getline(char* buffer){
/*	int i=0;
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
	return;
*/}


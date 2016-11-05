
unsigned int checkKeyboard();
unsigned char getKeyboard();

static char keyboard[128]={0,0,'1','2','3','4','5','6','7','8','9','0','-','=','\b'/*borrar*/,
						0/*tab*/,'q','w','e','r','t','y','u','i','o','p','[',']','\n',
						0/*MAYUS*/,'a','s','d','f','g','h','j','k','l',';','\'','\\',
						0/*shift*/,0,'z','x','c','v','b','n','m',',','.','/',0/*shift*/};
	


void printCharacter(){
	char * video= (char *) 0xB8000;
	
	if(checkKeyboard()){
		unsigned char character=getKeyboard();
		if(character<128){
		character=keyboard[character];
		write(1,&character,1);
		}
	}
}
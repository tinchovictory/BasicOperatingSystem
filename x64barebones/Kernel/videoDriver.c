#include <stdint.h>
#define WINDOW_WIDTH 80
#define WINDOW_HEIGHT 25
#define DEFAULT_COLOR 0x0F
#define END_OF_SCREEN WINDOW_WIDTH*2 * WINDOW_HEIGHT

/*static char * video = (char *) 0xB8000;
static int cursor=0;


int write(int fd, const void *buf, int nbytes){
	if( fd == 1){
		int i;
		for (i=0; i<nbytes; i++){
			video[cursor]=((char *) buf)[i];
			cursor+=2;
		}
	}
	return 0;
}

void clearScreen(){
	int i,j;
	for (i=0; i<ROWS ; i++ ){
		for (j=0; j<COLS ; j+=2){
			video[i+j*80*2]=' ';
		}
	}
}*/

static char * screen = (char *)0xB8000;
static char * currentPosition = (char*)0xB8000;

void clearScreen(){
	for(int i = 0; i < WINDOW_WIDTH*2 * WINDOW_HEIGHT; i++){
		if(i%2 == 1){
			screen[i] = DEFAULT_COLOR;
		}else{
			screen[i] = ' ';
		}
	}
	currentPosition = screen;
}

void moveScreenUp(){
	for(int i = 0; i< WINDOW_WIDTH*2 * (WINDOW_HEIGHT-1); i++){
		screen[i] = screen[i+WINDOW_WIDTH*2];
	}
	for(int i = 0; i < WINDOW_WIDTH*2; i+=2){
		*(screen + END_OF_SCREEN - WINDOW_WIDTH*2 + i) = ' ';
		*(screen + END_OF_SCREEN - WINDOW_WIDTH*2 + i + 1) = DEFAULT_COLOR;
	}
	currentPosition = screen + END_OF_SCREEN - WINDOW_WIDTH*2;
}

void checkEndOfScreen(){
	if(currentPosition >= screen + END_OF_SCREEN){
		moveScreenUp();
	}
}

void print(const char * string){
	while(*string){
		*(currentPosition++) = *(string++);
		*(currentPosition++) = DEFAULT_COLOR;
		checkEndOfScreen();
	}
}

void printCharacters(const char * character, int length){
	while(length != 0){
		*(currentPosition++) = *(character++);
		*(currentPosition++) = DEFAULT_COLOR;
		checkEndOfScreen();
		length--;
	}
}

void newLine(){
	currentPosition +=  (screen - currentPosition) % (WINDOW_WIDTH*2) + WINDOW_WIDTH*2;
	checkEndOfScreen();
}

void backSpace(){
	if(currentPosition == screen){
		return;
	}
	currentPosition-=2;
	*currentPosition = ' ';
}


/*
void clearScreenWithColor(int color){
	for(int i = 0; i < WINDOW_WIDTH*2 * WINDOW_HEIGHT; i++){
		if(i%2 == 1){
			screen[i] = color;
		}else{
			screen[i] = ' ';
		}
	}
	currentPosition = screen;
}

void clearScreen(){
	clearScreenWithColor(0x0F);
}

void printStringWithColor(const char * string, int color){
	while(*string){
		*(currentPosition++) = *(string++);//pongo el caracter
		if(color != -1){
			*(currentPosition++) = color;//pongo el color
		}else{
			currentPosition++;
		}
	}
}

void printString(char * string){
	printStringWithColor(string, -1);
}



void printPositionedString(char * string, int row, int column){
	char * cPos = currentPosition;

	currentPosition = screen + row * WINDOW_WIDTH * 2 + column * 2;
	printString(string);

	currentPosition = cPos;
}


void colorRow(int row, int color){
	char * pos = screen + row * 80 * 2;
	for(int i = 1; i < 80 * 2; i+=2){
		pos[i] = color;
	}
}
*/




#include <stdint.h>
#define COLS 80
#define ROWS 25

static char * video = (char *) 0xB8000;
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
}
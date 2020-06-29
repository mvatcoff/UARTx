#include "khbit_loop.h"

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void khbit_loop(int *fd, FILE *fd_log){
	
	char letrain=0, letraout=0;   /* caracteres de lectura escritura */
  	int cuenta;			              /* caracteres leidos en el puerto */

	init_keyboard();
	while( (letrain != 4) && (letraout != 4) ) {  // <CTRL-D>
	    if(kbhit()) {
	    	letraout = readch();
        	if (fd_log != NULL)
            	fwrite(&letraout,sizeof(char),sizeof(letraout),fd_log);
       		write( *fd, &letraout, 1 ); //ESCRIBIR EL PUERTO
          	if(letraout == 10) { 
	    		letraout = 13; 
	    		write( *fd, &letraout, 1 ); 
	    	}
	    	fflush( NULL );
	    }
	    cuenta=read(*fd, &letrain, 1);
        if( cuenta > 0 ) {
        	if (fd_log != NULL) 
            	fwrite(&letrain, sizeof(char),sizeof(letrain),fd_log);
          	write( 0, &letrain, 1 ); 
	    	fflush( NULL );
 	    }
    }
}

void init_keyboard() {
	tcgetattr(0,&initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard() {
	tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit() {
	char ch;
	int nread;
	if(peek_character != -1)
		return 1;
	new_settings.c_cc[VMIN]=0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0,&ch,1);
	new_settings.c_cc[VMIN]=1;
	tcsetattr(0, TCSANOW, &new_settings);
	if(nread == 1) {
		peek_character = ch;
		return 1;
	}
	return 0;
}

int readch() {
	char ch;
	if(peek_character != -1) {
		ch = peek_character;
		peek_character = -1;
		return ch;
	}
	read(0,&ch,1);
	return ch;
}

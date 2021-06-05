/*
This is a software to write and read data from USB-UART port in Linux systems

Copyright (C) 2021  Mariano Vatcoff <marianovatcoff@gmail.com>

    This file is part of UARTx

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
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
        	if (fd_log != NULL) fwrite(&letraout,sizeof(char),sizeof(letraout),fd_log);
          	if(letraout == 10) {
	    		letraout = 13;
	    	}
	    	write( *fd, &letraout, 1 ); //ESCRIBIR EL PUERTO
	    	fflush( NULL );
	    	//tcflush(*fd,TCIOFLUSH);
	    	//tcdrain(*fd);
	    }

	    cuenta=read(*fd, &letrain, 1);
        if( cuenta > 0 ) {
        	if (fd_log != NULL) fwrite(&letrain, sizeof(char),sizeof(letrain),fd_log);
          	write( 1, &letrain, 1 );
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

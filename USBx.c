#include <fcntl.h> 	/* Definiciones de control de archivos */
#include <errno.h> 	/* Definiciones de control de errores */
#include <termios.h> /* Estructura de control termios */
#include <sys/ioctl.h> 	/* Constantes para ioctl */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
<<<<<<< HEAD
#include "./lib/ctrl_argv.c"
#include "./lib/setup_port.c"
#include "./lib/khbit_loop.c"
=======
#include "./include/ctrl_argv.c"
#include "./include/setup_port.c"
#include "./include/khbit_loop.c"
>>>>>>> 52c0a2722982bcb996d9c23a7b353a226bc3e445


int main( int argc, char *argv[] ) {
  int fd;                       /* descriptor archivo del puerto */
  FILE *fd_log=NULL;                 /* descriptor archivo log */
  char puerto[20]="";
  char path_log[20]=""; 
   			            

  /* CONTROL DE CONSISTENCIA DE LA LINEA DE COMANDOS */
    ctrl_argv(argc,argv,puerto,path_log);
  
  //Apertura del puerto
    fd = open(puerto, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
    if (fd == -1) {
      perror("open_port");
      exit( 1 );
    }
    else 
      //fcntl(fd, F_SETFL, 0); // funciona en forma síncrona
      fcntl(fd, F_SETFL, O_NDELAY); // funciona en forma asíncrona
  
  //Apertura del archivo log
    fd_log=fopen(path_log,"w+");
    if (fd_log == NULL){
      printf("No se pudo crear el archivo en %s \n",path_log);
    }

  //Lazo de lectura escritura
    khbit_loop(&fd,fd_log);


  close_keyboard();
  close( fd );
  if (fd_log != NULL)
    fclose(fd_log);
  exit(0);
}   



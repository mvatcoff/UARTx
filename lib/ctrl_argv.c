#include "ctrl_argv.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void ctrl_argv(int argc, char *argv[],char *puerto, char *path_log){

  if( argc < 4 ) {
    printf( "\nUso: %s puerto[/dev/ttyUSB0] disciplina[ej. 8N1] velocidad[bps] [OPCIONES]\n\n [OPCIONES]\n  -t       PATH del .txt para el historial de comunicación\n\n",
            argv[0] );
    exit(1);
  }
   
  strcpy(puerto, argv[1] );
  printf("Puerto: %s\n", puerto);
  
  
  if( (atoi(&argv[2][0]) < 5) || (atoi(&argv[2][0]) > 8) ) {
    printf( "Chars por palabra debe estar entre 5 y 8\n" );
    exit( 1 );
  }

  if( (toupper(argv[2][1]) != 'N') && (toupper(argv[2][1]) != 'E') &&
      (toupper(argv[2][1]) != 'O') ) {
    printf( "Paridad debe ser N, E, O\n" );
    exit( 1 );
  }

  if( (atoi(&argv[2][2]) < 1) || (atoi(&argv[2][2]) > 2) ) {
    printf( "Bits de stop debe ser 1 ó 2\n" );
    exit( 1 );
  }
 
 if (argc > 4)
  if (argv[4][1] == 't'){
    strcpy(path_log,argv[5]);
    printf("Log File: %s\n",path_log);
    
  }
   
  /* FIN CONTROL DE CONSISTENCIA DE LA LINEA DE COMANDOS */
  }

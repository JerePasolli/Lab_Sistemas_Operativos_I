#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "executeCommands.h"


int main(int argc, char *argv[]){
    
    char hostname[MAX_LENGHT];
    char username[MAX_LENGHT];
    int result;

    result = gethostname(hostname, MAX_LENGHT); //se obtiene hostname
    if (result){
      perror("gethostname() error");
      return EXIT_FAILURE;
    }
    result = getlogin_r(username, MAX_LENGHT); //se obtiene username
    if (result){
      perror("getlogin_r() error");
      return EXIT_FAILURE;
    }

    if(argc == 1){
      readCommand(username, hostname,1,argv); //no se debe leer de archivo
    }
    else if (argc == 2){ //se debe abrir archivo y leer instrucciones desde ahi
      readCommand(username, hostname,2,argv);
    }

    else{
      fprintf(stderr,"Error, more than two arguments\n");
    }
    

    return 0;
}

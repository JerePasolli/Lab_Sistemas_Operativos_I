#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "executeBinarys.h"
#include "utils.h"

int jobid = 1;
pid_t child_pid = 0;

void spawn (char* path, char* args[], char* redirectin, char* redirectout){ //crea el hijo y redirecciona stdin y/o stdout de ser necesario
    int pid = fork();
	if (pid > 0) { //hijo creado correctamente
        child_pid = pid;
	}
    else if (pid < 0){
        fprintf(stderr, "Error creating the child\n");
        exit(1);
    }
	else { //tarea que ejecuta el hijo
        if(redirectin != NULL && redirectout != NULL){//redireccionar stdin y stdout
            if(freopen(redirectin, "r",stdin) == NULL){
                fprintf(stderr, "Error redirecting stdin\n");
            }
            if(freopen(redirectout, "w",stdout) == NULL){
                fprintf(stderr, "Error redirecting stdout\n");
            }
        }
        else if(redirectin != NULL){ //redireccionar stdin
            if(freopen(redirectin, "r",stdin) == NULL){
                fprintf(stderr, "Error redirecting stdin, the file -%s- doesnt exist\n",redirectin);
            }
        }
        else if(redirectout != NULL){ //redireccionar stdout
            if(freopen(redirectout, "w",stdout) == NULL){
                fprintf(stderr, "Error redirecting stdout\n");
            }
        }
        execl (path, path, args[0], args[1], args[2], args[3], args[4], (char  *) NULL);
		// solo se ejecutara si hay un error
		fprintf (stderr, "An error occurred in execution,the path is incorrect or some argument is invalid\n");
		exit(1);
	}
}

void handler(int signum){ //maneja las señales ctrl-c, ctrl-z, ctrl-|
    switch(signum){
        case SIGCHLD: //señal SIGCHLD, indica que el hijo termino su ejecucion
            waitpid(-1,0,WNOHANG);
            jobid++;
            break;
        case SIGINT: //señal SIGINT, corresponde a interrupcion por teclado
            if(child_pid > 0){
                signal(SIGINT,SIG_IGN);
                printf("\n");
                kill(child_pid,SIGINT);
            }
            break;
        case SIGTSTP: //señal SIGTSTP
            if(child_pid > 0){
                signal(SIGTSTP,SIG_IGN);
                printf("\nSTOP[%d]\n",child_pid);
                kill(child_pid,SIGTSTP); //no funciona del todo bien
                
            }
            break;
        case SIGQUIT:
            if(child_pid > 0){
                signal(SIGQUIT,SIG_IGN);
                printf("\n");
                kill(child_pid, SIGQUIT);
            }
            break;
    }
}

void executeNormal(char *path, char* args[], char* redirectin, char* redirectout){ //maneja ejecucion en primer plano
    signal(SIGCHLD, handler);
    signal(SIGTSTP, handler);
    signal(SIGQUIT, handler);
    signal(SIGINT,handler);
    spawn(path, args, redirectin, redirectout);
    pause();
    
}

void executeBackground(char *path, char* args[], char* redirectin, char* redirectout){ //maneja ejecucion en segundo plano
    signal(SIGCHLD, handler);
    signal(SIGTSTP, handler);
    signal(SIGQUIT, handler);
    signal(SIGINT,handler);
    spawn(path, args, redirectin, redirectout);
    printf("[%d]%d\n",jobid,child_pid);
}

void executeBinary(char input[MAX_LENGHT], char* redirectin, char* redirectout){ //recibe programa a ejecutar y decide si se ejecuta en back o no
    char *token = strtok(input, " ");
    int counter = 0;
    int background = 0;
    char *path;
    char *args[5] = {NULL, NULL, NULL, NULL, NULL};


    while (token != NULL) {
        
        if(strchr(token,'&') != NULL){
            background = 1;
            if(strcmp(token,"&") != 0){
                removeChar(token,'&');
            }
        }
            
        if(counter == 6){
            fprintf(stderr, "Error, demasiados argumentos, se soporta un maximo de 5 argumentos\n");
            exit(1);
        }
        if(counter == 0){
            if(strcmp(token,"&") != 0){
                if(strchr(token,'/') == NULL){ //si no se ingresa el path del programa, lo buscara en /bin
                    path = (char*)malloc(sizeof(token)+(6*sizeof(char)));
                    strcpy(path,"/bin/");
                    strcat(path,token);
                }
                else{
                    path = (char*)malloc(sizeof(token));
                    strcpy(path,token); //copio path relativo o absoluto
                }
            }
        }
        else{ 
            if(strcmp(token,"&") != 0){
                free(args[counter-1]);
                args[counter-1] = malloc(strlen(token));
                strcpy(args[counter-1],token); //se arma arreglo con argumentos
            }
                
        }
        counter++;
        token = strtok(NULL, " ");
    }
    free(token);

    if(background == 1){
        executeBackground(path, args, NULL, NULL);
        free(path);
    }
    else{
        executeNormal(path, args, redirectin, redirectout);
        free(path);
    }

    free(args[0]);
    free(args[1]);
    free(args[2]);
    free(args[3]);
    free(args[4]);
}

void executePipes(char input[MAX_LENGHT],char* redirectin, char* redirectout){ //se encarga de ejecucion con pipes
    char *token = strtok(input, "|");
    char *tokens[5] = {NULL, NULL, NULL, NULL, NULL};
    int counter = 0; //guarda la cantidad de procesos a unir

    while (token != NULL && counter <5){ //se soporta un encadenado de 5 procesos como maximo, es decir cuatro pipes
        removeBeginning(token);
        tokens[counter] = (char *)malloc(sizeof(token));
        strcpy(tokens[counter],token);
       
        token = strtok(NULL, "|");
        counter ++;
    }

    free(token);
    processPipe(counter,tokens,redirectin,redirectout);
    free(tokens[0]);
    free(tokens[1]);
    free(tokens[2]);
    free(tokens[3]);
    free(tokens[4]);
    
}

void processPipe(int argc, char *tokens[],char* redirectin, char* redirectout) //procesa y redirecciona pipes entre procesos involucrados
{
  int processes = argc;
  int apipe[argc][2];
  int pid;

  int result = -1;
  for (int i = 0; i < processes; i++) {
    result = pipe(apipe[i]);
    if (result == -1) {
      exit(1);
    }

  }

  for (int i = 0; i < processes; i++) {

    pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error in fork()\n");
        exit(1);
    }

    // Hijo
    else if (pid == 0) {

      // Para procesos que no son el primero
      if (i > 0) { // Se usa la salida del proceso previo como entrada de este
        
        // Se chequea que el read del pipe es distinto del STDIN
        if (apipe[i - 1][0] != STDIN_FILENO) {
          // Read del pipe se envia al STDIN
          if (dup2(apipe[i - 1][0], STDIN_FILENO) == -1) {
            exit(1);
          }
        }
      }

      // Se envia el WRITE del pipe al STDOUT
      if (i < processes - 1) { //esto evita que se realice en el ultimo proceso, ya que este si tiene que usar el STDOUT
        // Se chequea que el WRITE del pipe es distinto del STDOUT
        if (apipe[i][1] != STDOUT_FILENO) {

          // WRITE del pipe se envia a STDOUT
          if (dup2(apipe[i][1], STDOUT_FILENO) == -1) {
            exit(1);
          }
        }
      }

      for (int j = 0; j < processes; j++) {
         if(close(apipe[j][0]) == -1)
         exit(1);
         if(close(apipe[j][1]) == -1)
         exit(1);
      }

      // Cada hijo ejecuta el proceso luego de haber configurado los pipes
      if(i == processes-1)
        executeBinary(tokens[i],NULL, redirectout);
      else if (i==0)
        executeBinary(tokens[i],redirectin, NULL);
      else
        executeBinary(tokens[i],NULL, NULL);
    }
  }
   
  // Se cierran los extremos de los pipes del padre ya que no son necesarios
  for (int i = 0; i < processes; i++) {
         if(close(apipe[i][0]) == -1)
         exit(1);
         if(close(apipe[i][1]) == -1)
         exit(1);
  }

    //padre espera a que los hijos terminen
  for (int i = 0; i < processes; i++) {
      wait(NULL);
  }
}

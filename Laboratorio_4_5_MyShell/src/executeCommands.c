#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "executeCommands.h"
#include "executeBinarys.h"
#include "utils.h"

void executeCommand(char input[MAX_LENGHT]){

    char aux[MAX_LENGHT];
    char aux2[MAX_LENGHT];

    if(strcmp("\n",input) == 0){
        return;
    }

    else if(strncmp("cd",input,2)==0){ //comando cd
        char *oldpwd;
        char *pwd;

        strncpy(aux,input+3,MAX_LENGHT); //copio en aux el directorio al que se necesita mover el usuario
        removeSpaces(aux);
        if(strcmp("",aux) == 0){
            if((chdir(getenv("HOME"))) != 0)  //cambio de directorio
                perror("Error");
        }
        else if(strcmp(aux,"-") != 0){ //se detecta instruccion cd <directorio>
            oldpwd = getcwd(NULL,0);
            if(setenv("OLDPWD",oldpwd,1) != 0){ //antes de cambiar de directorio seteo OLDPWD
                perror("Error");
            } 
            if(chdir(aux) != 0)  //cambio de directorio
                perror("Error");
            free(oldpwd);
        }
     
        else{ // se detecta instruccion cd -
            char *temp = getenv("OLDPWD");
            if(temp == NULL){
                fprintf(stderr,("Error on getenv OLDPWD"));
                exit(1);
            }
            oldpwd = getenv("PWD");
            if(oldpwd == NULL){
                fprintf(stderr,("Error on getenv PWD"));
                exit(1);
            }
            if(setenv("OLDPWD",oldpwd,1) != 0){
                perror("Error");
            }
            if(chdir(temp) != 0) //cambio de directorio a OLDPWD, luego de haber actualizado variables de entorno correspondientes  
                perror("Error");
        }

        pwd = getcwd(NULL,0);
            if (pwd == NULL) {
                fprintf(stderr,"getcwd() error");
                exit(1);
            } 
        if(setenv("PWD",pwd,1) != 0){ //luego de haber ejecutado el comando, actualizo valor de la variable de entorno PWD
            perror("Error");
        }  
        free(pwd);
    }    
    else if(strncmp("clr",input,3)==0){ //comando clr
        printf("\033[2J");
        printf("\033[H");
    }
    else if(strncmp("echo",input,4)==0){ //comando echo
        strncpy(aux,input+5,MAX_LENGHT); //copio en aux lo que se desea imprimir en consola
        if(strncmp(aux,"$",1) == 0){ //detecta que se desea imprimir variable de entorno
            strncpy(aux2,aux+1,MAX_LENGHT);
            char *temp = getenv(aux2);
            if(temp == NULL){
                fprintf(stderr,"Error, env variable -%s- doesn't exist\n",aux2);
            }
            else
                printf("%s\n",temp);
        }
        else{
            printf("%s\n",aux);
        }
    }
    else if (strncmp("quit",input,4)==0){  //comando quit
        exit(0);
    }

    else{ //comando que indica que se debe ejecutar un programa en un path relativo o absoluto
        //redirection manejara redirecciones de stdin/stdout y tambien diferenciara si se utilizan pipes para encadenar procesos
        redirection(input);
    }
}

void readCommand(char username[], char hostname[], int flag, char* argv[]){

    char input[MAX_LENGHT];
    char concat[MAX_LENGHT] = "/home/";
    strcat(concat, username); //string con el valor /home/username

    if(flag==1){
        char *a;
        char *buffer;
        while(1){
        buffer = getcwd(NULL,0);
        if (buffer == NULL) {
            fprintf(stderr,"getcwd() error");
            exit(1);
        }
        if(strncmp(concat,buffer,strlen(concat)-1) == 0){ //usuario se encuentra en
          if(strcmp(buffer,concat) == 0){                 //directorio /home/username
            printf("\033[0;31m");
            printf("%s@%s",username,hostname);
            printf("\033[0m");
            printf(":");
            printf("\033[0;33m");
            printf("~");
            printf("\033[0m");
            printf("$"); 
          }  
            
          else{                              //usuario se encuentra en algun
                                            //subdirectorio de /home/username
            a = strstr(buffer,concat)+(strlen(concat));
            printf("\033[0;31m");
            printf("%s@%s",username,hostname);
            printf("\033[0m");
            printf(":");
            printf("\033[0;33m");
            printf("~%s",a);
            printf("\033[0m");
            printf("$");
          }   
        }
        else{  //usuario se encuentra en otro PATH
            printf("\033[0;31m");
            printf("%s@%s",username,hostname);
            printf("\033[0m");
            printf(":");
            printf("\033[0;33m");
            printf("%s",buffer);
            printf("\033[0m");
            printf("$");
        }
          
        fgets(input, MAX_LENGHT, stdin);
        if(strcmp("\n",input) == 0){ //en caso de que solo se presione enter se imprime nuevamente el prompt para esperar input
            continue;
        }
        else if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')){ // Remover salto de línea
            input[strlen(input) - 1] = '\0';
        }
        executeCommand(input); //interpreta y ejecuta el comando ingresado
    }
    free(buffer);
    free(a);
    }
    
    else{ //caso batchfile
        FILE *batchfile = fopen(argv[1], "r"); //abro archivo en modo lectura
        if (!batchfile){
            printf("Error al abrir el archivo\n");
            exit(1);
        }

        while(!feof(batchfile)){
            fgets(input, MAX_LENGHT, batchfile);
            if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n')){ // Remover salto de línea
                input[strlen(input) - 1] = '\0';
            }
            printf("Command readed: %s\n", input);
            executeCommand(input); //interpreta y ejecuta el comando ingresado
        }
        fclose(batchfile);
        exit(0);
    }
}
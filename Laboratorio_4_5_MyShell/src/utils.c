#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "executeBinarys.h"

void removeChar(char * str, char charToRemmove){ //remueve un caracter de un string
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++)
    {
        if(str[i] == charToRemmove)
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }  
}

void removeSpaces(char *str1){ //remueve todos los espacios de un string
    int count = 0;
    for (int i = 0; str1[i]; i++)
        if (str1[i] != ' ')
            str1[count++] = str1[i];
    str1[count] = '\0';
}

void removeBeginning(char *str1){ //remueve solo el primer espacio de un string
    char *str2; 
    str2=str1;  
    while (*str2==' ') str2++;  
    if (str2!=str1) memmove(str1,str2,strlen(str2)+1);  
}

void redirection(char* input){

    if (strchr(input,'<') != NULL && strchr(input,'>') != NULL){
            char *token = strtok(input, "<");
            int counter = 0;
            char* program = NULL;
            char* redirectin = NULL;
            char* redirectout = NULL;
            while (token != NULL) {
                if(counter == 0){
                    program = (char*)malloc(sizeof(token));
                    strcpy(program,token);
                }
                else if(counter == 1){
                    int counter2 = 0;
                    char* token2 = strtok(token,">");
                    while(token2 != NULL){
                        removeSpaces(token2);
                        if(counter2 == 0){
                            redirectin = (char*)malloc(sizeof(token2));
                            strcpy(redirectin,token2);
                        }
                        else if (counter2 == 1){
                            redirectout = (char*)malloc(sizeof(token2));
                            strcpy(redirectout,token2);
                        }
                        token2 = strtok(NULL, ">");
                        counter2++;
                    }
                    free(token2);
                }
                token = strtok(NULL, "<");
                counter ++;
            }
            free(token);
            if(program == NULL){
                fprintf(stderr, "Error, comando invalido\n");
            }
            else{
                if(strchr(program,'|') != NULL){
                    executePipes(program,redirectin,redirectout);
                }
                else{
                    executeBinary(program,redirectin,redirectout);
                }
            }
            free(program);
            free(redirectin);
            free(redirectout);
        }  
        else if (strchr(input,'<') != NULL){
            int c = 0;
            char *token = strtok(input, "<");
            char* program = NULL;
            char* redirectin = NULL;
            while (token != NULL) {
                if(c == 0){
                    program = (char*)malloc(sizeof(token));
                    strcpy(program,token); 
                }
                else if (c == 1){
                    removeSpaces(token);
                    redirectin = (char*)malloc(sizeof(token));
                    strcpy(redirectin,token); 
                }
                else{
                fprintf(stderr, "Error, invalid command\n");
                }

                token = strtok(NULL, "<");
                c++;
            }
            free(token);
            if(program == NULL){
                fprintf(stderr, "Error, comando invalido\n");
            }
            else{
                if(strchr(program,'|') != NULL){
                    executePipes(program,redirectin,NULL);
                }
                else{
                    executeBinary(program,redirectin,NULL);
                }
            }
            free(program);
            free(redirectin);
        }
        else if (strchr(input,'>') != NULL){
            int c = 0;
            char *token = strtok(input, ">");
            char* program = NULL;
            char* redirectout = NULL;
            while (token != NULL) {
                if(c == 0){
                    program = (char*)malloc(sizeof(token));
                    strcpy(program,token); 
                }
                else if (c == 1){
                    removeSpaces(token);
                    redirectout = (char*)malloc(sizeof(token));
                    strcpy(redirectout,token); 
                }
                else{
                fprintf(stderr, "Error, invalid command\n");
                }

                token = strtok(NULL, ">");
                c++;
            }
            
            free(token);
            if(program == NULL){
                fprintf(stderr, "Error, comando invalido\n");
            }
            else{
                if(strchr(program,'|') != NULL){
                    executePipes(program,NULL,redirectout);
                }
                else{
                    executeBinary(program,NULL,redirectout);
                }
            }
            
            free(program);
            free(redirectout);
        }
        else{
            if(strchr(input,'|') != NULL){
                executePipes(input,NULL,NULL);
            }
            else{
                executeBinary(input,NULL,NULL);
            }
        }
}
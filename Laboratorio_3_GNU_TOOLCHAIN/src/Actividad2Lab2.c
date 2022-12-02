#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "cJSON.h"

void getLinuxVersion(int json){
    char * version;
    FILE *infoversion = fopen("/proc/version", "r"); //abro archivo en modo lectura
    if (!infoversion){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    int cont = 0;
    for (char c = fgetc(infoversion); c != EOF; c = fgetc(infoversion)){
        cont++; //para obtener cantidad de caracteres del texto
    }
    rewind(infoversion); //se vuelve el cursor al comienzo del texto

    version = (char *)malloc(cont * sizeof (char));

    int i = 0;
    do{
        int l = fgetc(infoversion);
        if(!feof(infoversion) && l != 10){ //excluye el salto de linea del final
            version[i] = (char)toupper( l); //copio caracter por caracter, pasando a mayuscula
            i++;
        }
    }
    while(!feof(infoversion));

    fclose(infoversion);


    if (json == 0){ //formato estandar
        for(int c=0; version[c] < strlen(version); c++){
            if(version[c] == ' '){
                printf("\n"); //se imprime salto de linea al encontrar espacio para tener palabra por palabra
            }
            else{
                if (version[c] == '(' || version[c] == ')' || version[c] == ','){} //se quitan estos caracteres para
                                                                               //vista mas limpia
                else
                    printf("%c",version[c]);
            }
        }
    }
    else{ //formato JSON
        cJSON *root;
        char substr[14];
        char *out;
        root = cJSON_CreateObject();
        strncpy(substr, version, 13); //se sustrae primer parte del texto para el nombre del par llave valor
        for(int c=0; version[c] < strlen(version) && c < strlen(version)-14; c++){ // se sustrae segunda parte para el valor del par llave valor
            version[c] = version[c+14];
        }
        cJSON_AddItemToObject(root, substr, cJSON_CreateString(version));
        out = cJSON_Print(root);
        printf("%s\n",out);
        free(out);
        cJSON_Delete(root);
    }

    printf("\n");
    free(version);//se libera memoria alocada

}
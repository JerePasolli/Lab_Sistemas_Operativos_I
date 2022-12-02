#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

void filesystems() {

    char line[70];
    char line2[70];
    FILE *file = fopen("/proc/filesystems", "r"); //abro archivo en modo lectura
    if (!file){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    cJSON *root;
    char *out;
    char number[5];
    root = cJSON_CreateObject(); //se crea objeto raiz del JSON
    int i = 1;
    
    while(fgets(line,70,file)){ //leo archivo linea por linea
        sprintf(number, "%d", i);
        sscanf(line," %69[^\n]s",line2);
        cJSON_AddItemToObject(root,  number, cJSON_CreateString(line2));
        i++;
    }

    fclose(file);
    out = cJSON_Print(root);
    printf("%s\n",out); //se imprime el JSON generado
    free(out);
    cJSON_Delete(root);
}
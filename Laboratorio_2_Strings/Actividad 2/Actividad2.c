#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(){
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
    printf("\n");
    free(version);//se libera memoria alocada

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct{
    char *nombre;
    int cantidad;
}memorias;


int main (){
    char temp[70];
    char temp1[70];
    char temp2[70];
    memorias mem[5];

    FILE *infomem = fopen("/proc/meminfo", "r"); //abro archivo en modo lectura
    if (!infomem){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    while(!feof(infomem)){
        fgets(temp,70,infomem);
        if(strncmp("MemTotal",temp,8)==0){ //busco linea en el archivo que contenga "MemTotal"
            mem[0].nombre = "MemTotal";
            sscanf(temp,"MemTotal: %d kB",&mem[0].cantidad); //copio cantidad de MemTotal en estructura
            mem[0].cantidad = mem[0].cantidad/1024; //transformo a MB
        }
        else if(strncmp("MemFree",temp,7)==0){ //busco linea en el archivo que contenga "MemFree"
            mem[1].nombre = "MemFree";
            sscanf(temp,"MemFree: %d kB",&mem[1].cantidad); //copio cantidad de MemFree en estructura
            mem[1].cantidad = mem[1].cantidad/1024; //transformo a MB
        }
        else if(strncmp("MemAvailable",temp,12)==0){ //busco linea en el archivo que contenga "MemAvailable"
            mem[2].nombre = "MemAvailable";
            sscanf(temp,"MemAvailable: %d kB",&mem[2].cantidad); //copio cantidad de MemAvailable en estructura
            mem[2].cantidad = mem[2].cantidad/1024; //transformo a MB
        }
        else if(strncmp("SwapTotal",temp,9)==0){ //busco linea en el archivo que contenga "SwapTotal"
            mem[3].nombre = "SwapTotal";
            sscanf(temp,"SwapTotal: %d kB",&mem[3].cantidad); //copio cantidad de SwapTotal en estructura
            mem[3].cantidad = mem[3].cantidad/1024; //transformo a MB
        }
        else if(strncmp("SwapFree",temp,8)==0){ //busco linea en el archivo que contenga "SwapFree"
            mem[4].nombre = "SwapFree";
            sscanf(temp,"SwapFree: %d kB",&mem[4].cantidad); //copio cantidad de SwapFree en estructura
            mem[4].cantidad = mem[4].cantidad/1024; //transformo a MB
        }
    }
    fclose(infomem);

    printf("%s: %d MB\n",mem[0].nombre,mem[0].cantidad);
    printf("%s: %d MB\n",mem[1].nombre,mem[1].cantidad);
    printf("%s: %d MB\n",mem[2].nombre,mem[2].cantidad);
    printf("%s: %d MB\n",mem[3].nombre,mem[3].cantidad);
    printf("%s: %d MB\n",mem[4].nombre,mem[4].cantidad); //se imprimen los datos
    printf("SwapOccupied: %d MB\n",(mem[3].cantidad/1024)-(mem[4].cantidad/1024));
    //se calcula e imprime swap ocupada

    FILE *infocpu = fopen("/proc/cpuinfo", "r"); //abro archivo en modo lectura
    if (!infocpu){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    while(!feof(infocpu)){
        fgets(temp,70,infocpu);
        if(strncmp("model name",temp,10)==0){ //busco linea en el archivo que contenga "model name"
            int a = strstr(temp,":")-temp;
            strncpy(temp1,temp+a,70); //extraigo la info luego del caracter ':' en temp1
            printf("CPU Model%s",temp1);
        }
        else if (strncmp("siblings",temp,8)==0){ //busco linea en el archivo que contenga "siblings"
            int b = strstr(temp,":")-temp;
            strncpy(temp1,temp+b,70); //extraigo la info luego del caracter ':' en temp1
        }
        else if(strncmp("cpu cores",temp,9)==0){ //busco linea en el archivo que contenga "cpu cores"
            int a = strstr(temp,":")-temp;
            strncpy(temp2,temp+a,70); //extraigo la info luego del caracter ':' en temp1
            printf("CPU cores%s",temp2);
            printf("Threads per core: %d\n",
                   (int) strtol(temp1+1, NULL, 10)/(int) strtol(temp2+1, NULL, 10));
            break; //debido a que "siblings" me da los hilos totales, divido por la cantidad de nucleos para obtener
                   //hilos por nucleo
        }
    }

    fclose(infocpu);
    return 0;
}
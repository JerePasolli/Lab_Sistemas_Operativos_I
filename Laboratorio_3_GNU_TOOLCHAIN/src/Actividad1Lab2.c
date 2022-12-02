#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"


typedef struct{
    char *nombre;
    int cantidad;
}memorias;


void getMemCpuInfo(int json){
    char temp[70];
    char model[70];
    char siblings[70];
    char cores[70];
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

    FILE *infocpu = fopen("/proc/cpuinfo", "r"); //abro archivo en modo lectura
    if (!infocpu){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    while(!feof(infocpu)){
        fgets(temp,70,infocpu);
        if(strncmp("model name",temp,10)==0){ //busco linea en el archivo que contenga "model name"
            int a = strstr(temp,":")-temp;
            strncpy(model,temp+a,70); //extraigo la info luego del caracter ':' en model
        }
        else if (strncmp("siblings",temp,8)==0){ //busco linea en el archivo que contenga "siblings"
            int b = strstr(temp,":")-temp;
            strncpy(siblings,temp+b,70); //extraigo la info luego del caracter ':' en siblings
        }
        else if(strncmp("cpu cores",temp,9)==0){ //busco linea en el archivo que contenga "cpu cores"
            int a = strstr(temp,":")-temp;
            strncpy(cores,temp+a,70); //extraigo la info luego del caracter ':' en cores
            break; 
        }
    }
    fclose(infocpu);


    if (json == 0){ //formato estandar
        printf("%s: %d MB\n",mem[0].nombre,mem[0].cantidad);
        printf("%s: %d MB\n",mem[1].nombre,mem[1].cantidad);
        printf("%s: %d MB\n",mem[2].nombre,mem[2].cantidad);
        printf("%s: %d MB\n",mem[3].nombre,mem[3].cantidad);
        printf("%s: %d MB\n",mem[4].nombre,mem[4].cantidad); //se imprimen los datos
        printf("SwapOccupied: %d MB\n",(mem[3].cantidad/1024)-(mem[4].cantidad/1024)); //se calcula e imprime swap ocupada
        printf("CPU Model%s",model);
        printf("CPU cores%s",cores);
        printf("Threads per core: %d\n", //debido a que "siblings" me da los hilos totales, divido por la cantidad de nucleos para obtener
                                     //hilos por nucleo
            (int)strtol(siblings+1, NULL, 10)/(int) strtol(cores+1, NULL, 10));
    }
    else{ //formato JSON
        cJSON *root;
        char *out;
        root = cJSON_CreateObject();  //se crea objeto raiz
        cJSON_AddItemToObject(root, mem[0].nombre, cJSON_CreateNumber(mem[0].cantidad));
        cJSON_AddItemToObject(root, mem[1].nombre, cJSON_CreateNumber(mem[1].cantidad));
        cJSON_AddItemToObject(root, mem[2].nombre, cJSON_CreateNumber(mem[2].cantidad));
        cJSON_AddItemToObject(root, mem[3].nombre, cJSON_CreateNumber(mem[3].cantidad));
        cJSON_AddItemToObject(root, mem[4].nombre, cJSON_CreateNumber(mem[4].cantidad));
        cJSON_AddItemToObject(root, "SwapOccupied", cJSON_CreateNumber((mem[3].cantidad/1024)-(mem[4].cantidad/1024)));
        sscanf(model,": %69[^\n]s",temp);
        cJSON_AddItemToObject(root, "CPU Model", cJSON_CreateString(temp));
        sscanf(cores,": %69s\n",temp);
        cJSON_AddItemToObject(root, "CPU Cores", cJSON_CreateString(temp));
        cJSON_AddItemToObject(root, "Threads per core", cJSON_CreateNumber((int)strtol(siblings+1, NULL, 10)/(int) strtol(cores+1, NULL, 10))); //se agregan todos los datos
        out = cJSON_Print(root);
        printf("%s\n",out); //se imprime el JSON generado
        free(out);
        cJSON_Delete(root);
    }

}
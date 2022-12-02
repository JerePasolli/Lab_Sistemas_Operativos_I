#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include "Lab2.h"

void fileSystems();
void invalidOption(int);

int main(int argc, char *argv[]){

    int options[4] = {0,0,0,0}; //corresponden a opciones s a j d

    if(argc<2){
        invalidOption(argc);
    }
	
    char selection;
    while((selection = getopt(argc, argv, "sajd")) != -1){
        int flag = -1;
		switch(selection){

			case 's': 	flag = 0;
						break;
			case 'a':	flag = 1;
						break;
			case 'j':	flag = 2;
						break;
			case 'd':	flag = 3;
						break;
			default:	invalidOption(argc);
		}
		
		if(options[flag]==1)
			invalidOption(argc);

		options[flag] = 1;
	}

    if(options[2]&&!options[0]&!options[1])
		invalidOption(argc);
    if(options[0]) //se selecciona ejercicio 1 del lab2
		getMemCpuInfo(options[2]); //indica formato json de ser requerido	
	if(options[1]) //se selecciona ejercicio 1 del lab2
		getLinuxVersion(options[2]); //indica formato json de ser requerido
	if(options[3]) //se carga libreria dinamica
		fileSystems();
   
    return 0;
}

void fileSystems(){
    void *lib = dlopen("./libFilesystems.so", RTLD_LAZY); //se abre la libreria dinamica
    int (*filesystems)();
    char* error;

    if (!lib){
        printf("Error al cargar libreria %s\n", dlerror()); //chequeo de errores
        exit(1);
    }
    dlerror();
    *(void **) (&filesystems) = dlsym(lib, "filesystems"); // filesystems ahora apunta a la funcion filesystems de la libreria
    if ((error = dlerror()) != NULL){
        printf("Error al cargar funcion de la libreria %s\n", error); //chequeo de errores
         exit(1);
    }
    (*filesystems)(); //se ejecuta funcion de la libreria
    dlclose(lib);
}

void invalidOption(int argc){
    if(argc == 1){
        printf("Ningun argumento ingresado, ingrese argumento valido\n");
    }
    else{
        printf("Argumento/s invalido/s ingresado/s, ingrese argumento/s valido/s\n");
    }
    exit(1);
}
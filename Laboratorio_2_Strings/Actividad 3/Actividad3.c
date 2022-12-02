#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    int dato;
    struct Nodo *siguiente;
} Nodo;

typedef struct Lista {
  Nodo* cabeza;
  int tamanio;
} Lista;

Nodo* crearNodo(int dato); //crea un nodo y lo retorna
void eliminarNodo(Nodo* nodo); //elimina un nodo
void insertarPrincipio(Lista* lista, int dato); //inserta un nodo al comienzo de la lista
void insertarFinal(Lista* lista, int dato); //inserta un nodo al final de la lista
int getTamanio(Lista* lista); //devuelve tamaño de lista (cantidad de nodos)
void imprimirLista(Lista* lista); //imprime en pantalla elementos en la lista

int main(){
    int numero;
    Lista lista = {NULL,0};
    for(int i = 0; i <= 5; i++){
        printf("Ingrese un numero para agregar al final de la lista:\n");
        scanf("%d", &numero);
        insertarFinal(&lista,numero);
    }
    imprimirLista(&lista);
    return 0;
}

Nodo* crearNodo(int dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo ->dato = dato;
    nuevo ->siguiente = NULL;
    return nuevo;
}

void eliminarNodo(Nodo* nodo){
    free(nodo);
}

void insertarPrincipio(Lista* lista, int dato){
    Nodo* nodo = crearNodo(dato);
    nodo->siguiente = lista->cabeza;
    lista->cabeza = nodo;
    lista->tamanio++;
}

void insertarFinal(Lista* lista, int dato){
    Nodo* nodo = crearNodo(dato);
    if(lista->cabeza == NULL){
        lista->cabeza = nodo;
    }
    else{
        Nodo* puntero = lista->cabeza;
        while(puntero->siguiente){
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nodo;
    }
    lista->tamanio++;
}

int getTamanio(Lista* lista){
    return lista->tamanio;
}

void imprimirLista(Lista* lista){
    if(lista->cabeza == NULL){
        printf("Lista vacia\n");
    }
    else{
        Nodo* puntero = lista->cabeza;
        printf("Datos en lista: ");
        while(puntero->siguiente){
            printf("%d  ",puntero->dato);
            puntero = puntero->siguiente;
        }
        printf("%d ",puntero->dato);
        printf("\n");
    }
}





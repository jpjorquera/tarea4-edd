#include <stdlib.h>
#include <stdio.h> //xd

typedef struct lista {              // Estructura lista
    tNodo *head;                   // Almacena el vertice que irá al arreglo
    tNodo *tail;                    //-------------------
    tNodo *curr;                    //--------------------
    unsigned int tamaño;             //-----------------
    unsigned int pos                 //-------------------- posicion acutal, borrar si no lo ocupamos
} tLista;

typedef struct nodo {
    unsigned long ciudad;
    struct nodo *adyacente;
}tNodo;

typedef struct {
    tLista vecinos;
} tGrafo;

Lista initialize(tLista lista){//head = tail = curr = NULL;
    lista->head = (tNodo *)malloc(sizeof(tNodo));       // tarea2 : lista.head = (tNodo *)malloc(sizeof(tNodo));  
    (lista->head)->(lista->adyacente) = NULL;        // tarea2 lista.head->adyacente = NULL;
    lista->tamaño=0;
    return lista;
}


void nextL(tLista *lista) {
    lista->curr=(lista->curr)->adyacente;
}


int insertar(tLista *lista, unsigned long elem) { //este insert es un append???
    tNodo *aux = (lista->curr)->adyacente;
    (lista->curr)->adyacente = (tNodo *) malloc(sizeof(tNodo));
    ((lista->curr)->adyacente)->ciudad = elem; ////---------------------revisar--------------
    ((lista->curr)->adyacente)->adyacente = aux;
    if (lista->curr == lista->tail){
        lista->tail = (lista->curr)->adyacente;
    } //DECÍA ->next, creo q es error del profe
    lista->tamaño++;
    return lista->pos;
}

int append(tLista *lista, unsigned long elem){
    
}
int main(){
    return 1;
}

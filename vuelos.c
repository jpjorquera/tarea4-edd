#include <stdlib.h>
#include <stdio.h> //xd

typedef struct lista {              // Estructura lista
    vertex *head;                   // Almacena el vertice que irá al arreglo
    vertex *tail;                    //-------------------
    vertex *curr;                    //--------------------
    unsigned int tamaño;             //-----------------
    unsigned int pos                 //-------------------- posicion acutal, borrar si no lo ocupamos
} tLista;

typedef struct vertex {
    unsigned long ciudad;
    struct vertex *adyacente;
} vertex;

typedef struct {
    tLista vecinos;
} tGrafo;

Lista initialize(tLista lista){//head = tail = curr = NULL;
    lista->head = (tNodo *)malloc(sizeof(tNodo));       // tarea2 : lista.head = (tNodo *)malloc(sizeof(tNodo));  
    (lista->head)->(lista->adyacente) = NULL;        // tarea2 lista.head->adyacente = NULL;
    lista->tamaño=0;
    return lista;
}

int insertar(tLista *lista, unsigned long elem) {
    vertex *aux = (lista->curr)->adyacente;
    (lista->curr)->adyacente = (vertex *) malloc(sizeof(vertex));
    ((lista->curr)->adyacente)->ciudad = elem; ////---------------------revisar--------------
    ((lista->curr)->adyacente)->adyacente = aux;
    if (lista->curr ==lista->tail) lista->tail = (lista->curr)->adyacente; //DECÍA ->next, creo q es error del profe
    lista->tamaño++;
    return lista->pos;

int main(){
    return 1;
}

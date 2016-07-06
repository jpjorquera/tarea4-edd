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
    vertex *head;
} tGrafo;

Lista initialize(tLista lista){//head = tail = curr = NULL;
    lista->head = (tNodo *)malloc(sizeof(tNodo));       // tarea2 : lista.head = (tNodo *)malloc(sizeof(tNodo));  
    (lista->head)->(lista->adyacente) = NULL;        // tarea2 lista.head->adyacente = NULL;
    lista->tamaño=0;
    return lista;
}    

int main(){
    return 1;
}

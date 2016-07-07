#include <stdlib.h>
#include <stdio.h>


typedef struct nodo {
    unsigned long ciudad;
    struct nodo *adyacente;
}tNodo;


typedef struct lista {              // Estructura lista
    tNodo *head;                   // Almacena el vertice que irá al arreglo
    tNodo *tail;                    //-------------------
    tNodo *curr;                    //--------------------
    unsigned int tamaño;             //-----------------
    unsigned int pos;            //-------------------- posicion acutal, borrar si no lo ocupamos
} tLista;

tLista initialize(tLista *lista){//head = tail = curr = NULL;
    lista->head = (tNodo *)malloc(sizeof(tNodo));       // tarea2 : lista.head = (tNodo *)malloc(sizeof(tNodo));  
    (lista->head)->adyacente = NULL;        // tarea2 lista.head->adyacente = NULL;
    lista->tamaño=0;
    return *lista;
}


void nextL(tLista *lista) {
    if ((lista->curr)->adyacente != NULL) {
        lista->curr = (lista->curr)->adyacente;
        (lista->pos)++;//REVISAR
    }
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

void append(tLista *lista, unsigned long elem){
    tNodo *ult=(tNodo *)malloc(sizeof(tNodo));
    (lista->tail)->adyacente=(tNodo *)malloc(sizeof(tNodo));
    ((lista->tail)->adyacente)->ciudad=elem;
    lista->tail=lista->tail->adyacente;
    lista->tail->adyacente=ult;
}

int moveToStart(tLista *lista){
    lista->curr=lista->head;
    lista->pos = 0;
    return 0;
    
}
int length(tLista *lista){
    return lista->tamaño;
}

unsigned long getValue(tLista *lista, int pos){
    return (lista->curr)->ciudad;
}

void liberar(tLista *base){
    if (base->head->adyacente == NULL){
        free(base->head);
        free(base);
        return;
    }
    tNodo *auxiliar = base->head;// liberar auxiliar
    base->head = base->head->adyacente;
    free(auxiliar);
    liberar(base);


}
int main(){
    return 1;
}

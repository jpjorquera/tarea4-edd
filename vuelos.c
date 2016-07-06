#include <stdlib.h>
#include <stdio.h> //xd
typedef struct node {               // Estructura nodo de lista enlazada
    int ciudad;
    struct node *next;
} tNodo;

typedef struct lista {              // Estructura lista
    tNodo *head;                    // Almacena la cabeza de la lista enlazada
} tLista;

typedef struct vertex {
    unsigned long ciudad;
    struct vertex *adyacente;
} vertex;

typedef struct {
    vertex *head;
} tGrafo;


int maint(){
    return 1;
}

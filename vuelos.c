#include <stdlib.h>
#include <stdio.h>
typedef struct {
    unsigned long ciudad;
    struct tLista *destinos;
} tVertice;

typedef struct {
    tVertice *ciudades;
    unsigned long nCiudades;
} tGrafo;

/* FUNCIONES LISTA ENLAZADA (ELI) */
int insert (tLista item);
int append (tLista item);
void moveToStart ();
void nextL ();
int length ();
tLista getValue ();
/*******************************/

/* FUNCIONES GRAFO (JORGE) */
void initGraph(tGrafo *G, int n);
void destroyGraph (tGrafo *G);
int nVertex (tGrafo *G);
tVertice first (tGrafo *G, tVertice v);
tVertice nextG (tGrafo *G, tVertice v, int i);
void setEdge (tGrafo *G, tVertice v1, tVertice v2, int peso);
int isEdge (tGrafo *G, tVertice v1, tVertice v2);
int getMark (tGrafo *G, tVertice v);
void setMark (tGrafo *G, tVertice v, int marca);
/**************************/

int main(){
	unsigned long nCiudades, nVuelos, i;
	scanf("%lu", &nCiudades);								// Cantidad de ciudades
	tGrafo *vuelos = (tGrafo *)malloc(sizeof(tGrafo) * nCiudades);
	initGraph(vuelos, nCiudades);							// Inicializar grafo
	scanf("%lu", &nVuelos);
	unsigned int partida, destino;
	for (i=0; i<nVuelos; i++){
		scanf("%du %du", &partida, &destino);
	}
    return 1;
}
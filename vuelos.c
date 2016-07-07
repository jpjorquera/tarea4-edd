#include <stdlib.h>
#include <stdio.h>
<<<<<<< HEAD
typedef struct {
    unsigned long ciudad;
    struct tLista *destinos;
    short int visitado;
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
int nVertex (tGrafo *G);
unsigned long first (tGrafo *G, unsigned long ciudad);
unsigned long nextG (tGrafo *G, unsigned long ciudad, int i);
void setEdge (tGrafo *G, unsigned long partida, unsigned long llegada);
int getMark (tGrafo *G, unsigned long ciudad);
void setMark (tGrafo *G, unsigned long ciudad, int marca);
void destroyGraph (tGrafo *G);
void cleanMark (tGrafo *G);
/**************************/

void DFS (tGrafo * G, unsigned long ciudad) {	// Marca todos los visitados con 1
	unsigned long destino;
	setMark(G, ciudad, 1);						// Visitado = True
	for (destino = first(G, ciudad); destino < nVertex(G); destino = nextG(G, ciudad, destino)){
		if (getMark(G, destino) == 0){
			DFS(G, destino);
		}
	}
}

int main(){
	unsigned long nCiudades, nVuelos, i;
	scanf("%lu", &nCiudades);								// Cantidad de ciudades
	tGrafo *vuelos = (tGrafo *)malloc(sizeof(tGrafo) * nCiudades);
	initGraph(vuelos, nCiudades);							// Inicializar grafo
	scanf("%lu", &nVuelos);
	unsigned int partida, destino;
	for (i=0; i<nVuelos; i++){							//Crea arcos O D
		scanf("%du %du", &partida, &destino);
		setEdge(vuelos, partida, destino);
	}
	unsigned int nConsultas;
	unsigned long j;
	scanf("%du", &nConsultas);
	tLista *unreachables = malloc(sizeof(tLista) * nConsultas);		// Lista con punteros de inalcanzables
	initialize(unreachables);
	for (i=0; i<nConsultas; i++){
		scanf("%du", &partida);
		DFS(vuelos, partida);								// Marcar visitados
		for (j=0; j<nCiudades; j++){
			if (getMark(vuelos, j) == 0){					// Si no ha sido visitado
				append(unreachables, j);					// Agregar valor
				unreachables[i].(tamano++);					// actualizar tamano
			}
		}
		cleanMark(vuelos);									// Reiniciar marcas
	}
	for (i=0; i<nConsultas; i++){							// Iterar sobre inalcanzables
		moveToStart(unreachables[i]);
		printf("%lu ", unreachables[i].tamano);				// imprimir tamano
		while (j<unreachables[i].tamano;){			// continuado por valores de destinos
			printf("%du ", getValue(unreachables[i]));
			nextL(unreachables[i]);						// siguiente
			j++;
		}
		printf("\n");
	}
	liberar(unreachables);						// Liberar memoria
	destroyGraph(vuelos);


=======


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

typedef struct {
    tLista vecinos;
} tGrafo;

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

int append(tLista *lista, unsigned long elem){
    tNodo *ult=(lista->tail)->adyacente;
    //arreglar esta, no cacho  q wea el tail despues.
}

int moveToStart(tLista *lista){
    lista->curr=lista->head;
    lista->pos = 0;
    return 0;
    
}
int length(tLista *lista){
    return lista->tamaño;
}

unsigned int getValue(tLista *lista, int pos){
    /////FALTA////
}
int main(){
>>>>>>> Copy-paste-descarado
    return 1;
}

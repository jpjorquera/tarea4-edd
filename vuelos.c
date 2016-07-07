#include <stdlib.h>
#include <stdio.h>
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
/*STRUCTS LISTA ENLAZADA */
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


/* FUNCIONES REALES */
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

unsigned int getValue(tLista *lista){
    /////FALTA////
}


/*Funciones tentativas*/
int insert (tLista item);
int append (tLista item);
void moveToStart ();
void nextL ();
int length ();
tLista getValue ();
/*******************************/

/* FUNCIONES GRAFO (JORGE) */
void initGraph(tGrafo *G, unsigned long n){
	unsigned long i;
	G.ciudades = calloc(sizeof(tVertice),n);
	G.nCiudades = n;
	for(i=0;i<n;i++){
		initialize((G->ciudades[i]).destinos);
	}
}

int nVertex (tGrafo *G){
	return G.nCiudades;
}


unsigned long first (tGrafo *G, unsigned long ver){
	return (((G->ciudades[ver])->destinos)->head).ciudad;
}


unsigned long nextG (tGrafo *G, unsigned long ver, int i){
	nextL((G->ciudades[ver])->destinos);
	return getValue((G->ciudades[ver])->destinos);
}


void setEdge (tGrafo *G, unsigned long partida, unsigned long llegada){
	append((G->ciudades[partida]->destinos),llegada);
}

short int getMark (tGrafo *G, unsigned long ciudad){
	return (G->ciudades[ciudad]).visitado;
}

void setMark (tGrafo *G, unsigned long ciudad, int marca){
	(G->ciudades[ciudad]).visitado = marca;
}

void destroyGraph (tGrafo *G){
	unsigned long i;
	int n = G.nCiudades;
	for(i=0;i<n;i++){
		liberar((G->ciudades[i]).destinos);
	}
	free(G.ciudades);
}

void cleanMark (tGrafo *G){
	unsigned long i;
	for(i=0;i<nVertex(G);i++){
		setMark(G,i,0);
	}
	
}

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
}

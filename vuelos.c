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
	unsigned int tamano;             //-----------------
	unsigned int pos;            //-------------------- posicion acutal, borrar si no lo ocupamos
} tLista;

typedef struct {
    tLista destinos;
    short int visitado;
} tVertice;

typedef struct {
    tVertice *ciudades;
    unsigned long nCiudades;
} tGrafo;

/* FUNCIONES LISTA ENLAZADA (ELI) */
/* FUNCIONES REALES */
tLista initialize(tLista *lista){//head = tail = curr = NULL;
    lista->head = (tNodo *)malloc(sizeof(tNodo));       // tarea2 : lista.head = (tNodo *)malloc(sizeof(tNodo));  
    (lista->head)->adyacente = NULL;        // tarea2 lista.head->adyacente = NULL;
	lista->curr = lista->head;
    lista->tamano=0;
    return *lista;
}


void nextL(tLista *lista) {
    if ((lista->curr)->adyacente != NULL) {
        lista->curr = (lista->curr)->adyacente;
        (lista->pos)++;//REVISAR
    }
}

int insertar(tLista *lista, unsigned long elem) {
	if (lista->curr == lista->head){
		lista->head->ciudad = elem;
		lista->head->adyacente = malloc(sizeof(tNodo));
		lista->curr = lista->head->adyacente;
		lista->tail = lista->curr;
	}
	else {
		lista->curr->ciudad = elem;
		lista->curr->adyacente = malloc(sizeof(tNodo));
		lista->curr = lista->curr->adyacente;
		lista->tail = lista->curr;
	}
	lista->tamano++;
    return lista->pos;
}

/*void append(tLista *lista, unsigned long elem){
    tNodo *ult=(lista->tail)->adyacente;
    //arreglar esta, no cacho  q wea el tail despues.
}*/

int moveToStart(tLista *lista){
    lista->curr=lista->head;
    lista->pos = 0;
    return 0;
}

unsigned long getValue(tLista *lista){
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

/* FUNCIONES GRAFO (JORGE) */
void initGraph(tGrafo *G, unsigned long n){
	unsigned long i;
	G->ciudades = calloc(sizeof(tVertice),n);
	G->nCiudades = n;
	for(i=0;i<n;i++){
		initialize(&(G->ciudades[i]).destinos);
	}
}

unsigned long nVertex (tGrafo *G){
	return G->nCiudades;
}


unsigned long first (tGrafo *G, unsigned long ver){
	moveToStart(&G->ciudades[ver].destinos);
	return (((G->ciudades[ver]).destinos).head)->ciudad;
}


unsigned long nextG (tGrafo *G, unsigned long ver){
	if (G->ciudades[ver].destinos.pos < G->ciudades[ver].destinos.tamano){
		nextL(&(G->ciudades[ver]).destinos);
		return getValue(&(G->ciudades[ver]).destinos);
	}
	else return 0;
}


void setEdge (tGrafo *G, unsigned long partida, unsigned long llegada){
	insertar(&(G->ciudades[partida].destinos),llegada);
}

short int getMark (tGrafo *G, unsigned long ciudad){
	return (G->ciudades[ciudad]).visitado;
}

void setMark (tGrafo *G, unsigned long ciudad, short int marca){
	(G->ciudades[ciudad]).visitado = marca;
}

void destroyGraph (tGrafo *G){
	unsigned long i;
	unsigned long n = G->nCiudades;
	for(i=0;i<n;i++){
		liberar(&(G->ciudades[i]).destinos);
	}
	free(G->ciudades);
}

void cleanMark (tGrafo *G){
	unsigned long i;
	for(i=0;i<nVertex(G);i++){
		setMark(G,i,0);
	}
	
}

/**************************/

void DFS (tGrafo * G, unsigned long ciudad) {	// Marca todos los visitados con 1
	int visitado = getMark(G, ciudad);
	if (getMark(G, ciudad)==1){
		return;
	}
	unsigned long destino;
	setMark(G, ciudad, 1);						// Visitado = True
	unsigned long i = 0;
	for (destino = first(G, ciudad); i<(G->ciudades[ciudad].destinos.tamano); destino = nextG(G, ciudad)){
		if (getMark(G, destino) == 0){
			DFS(G, destino);
		}
		i++;
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
		scanf("%u", &partida);
		scanf("%u", &destino);
		setEdge(vuelos, partida, destino);
	}
	unsigned int nConsultas;
	unsigned long j;
	scanf("%u", &nConsultas);
	tLista *unreachables = malloc(sizeof(tLista) * nConsultas);		// Lista con punteros de inalcanzables
	for (i=0; i<nConsultas; i++){
		initialize(&unreachables[i]);
		scanf("%u", &partida);
		DFS(vuelos, partida);								// Marcar visitados
		for (j=0; j<nCiudades; j++){
			if (getMark(vuelos, j) == 0){					// Si no ha sido visitado
				insertar(&unreachables[i], j);					// Agregar valor
			}
		}
		cleanMark(vuelos);									// Reiniciar marcas
	}
	printf("%u \n", nConsultas);
	for (i=0; i<nConsultas; i++){							// Iterar sobre inalcanzables
		moveToStart(&unreachables[i]);
		printf("%u ", unreachables[i].tamano);				// imprimir tamano
		j = 0;
		while (j<unreachables[i].tamano){			// continuado por valores de destinos
			printf("%lu ", getValue(&unreachables[i]));
			nextL(&unreachables[i]);						// siguiente
			j++;
		}
		printf("\n");
	}
	liberar(unreachables);						// Liberar memoria
	free(unreachables);
	destroyGraph(vuelos);
	free(vuelos);
	return 1;
}

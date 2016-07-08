#include <stdlib.h>
#include <stdio.h>

typedef struct nodo {				// Nodo lista enlazada
	unsigned long ciudad;
	struct nodo *adyacente;
}tNodo;

typedef struct lista {              // Estructura lista enlacada
	tNodo *head;                   // Almacena el vertice que irá al arreglo
	tNodo *tail;
	tNodo *curr;
	unsigned int tamano;
	unsigned int pos;
} tLista;

typedef struct {			// Estructura vertice
    tLista destinos;		// para lista de adyacencia
    short int visitado;
} tVertice;

typedef struct {			// Estructura grafo
    tVertice *ciudades;		// almacena los vertices
    unsigned long nCiudades;
} tGrafo;


/*****
*   tLista initialize
******
*   Inicializa los parametros del tLista necesitado
******
*	Input:
*		tLista * lista : lista que se desea inicializar
******
*   Returns:
*   	void
* *****/
void initialize(tLista *lista){
    lista->head = (tNodo *)malloc(sizeof(tNodo));  // Inicializar vacios
    (lista->head)->adyacente = NULL;
	lista->curr = lista->head;
    lista->tamano=0;
}

/*****
*   void nextL
******
*   Actualiza el nodo actual al siguiente
******
*	Input:
*		tLista * lista : lista enlazada que se desea actualizar
******
*   Returns:
*   	void
* *****/
void nextL(tLista *lista) {
    if ((lista->curr)->adyacente != NULL) {			// En caso de haber
        lista->curr = (lista->curr)->adyacente;		// avanzar
        (lista->pos)++;
    }
}

/*****
*   void insertar
******
*   Inserta el elemento deseado al final de la lista enlazada
******
*	Input:
*		tLista * lista : lista enlazada en la que se desea insertar elemento
*		unsigned long elem : elemento a insertar en el nodo
******
*   Returns:
*   	void
* *****/
void insertar(tLista *lista, unsigned long elem) {
	if (lista->curr == lista->head){							// Si actual es inicial
		lista->head->ciudad = elem;								// Insertar en cabeza
		lista->head->adyacente = calloc(sizeof(tNodo), 1);
		lista->curr = lista->head->adyacente;
		lista->tail = lista->curr;
	}
	else {
		lista->curr->ciudad = elem;								// Insertar en actual
		lista->curr->adyacente = calloc(sizeof(tNodo), 1);
		lista->curr = lista->curr->adyacente;
		lista->tail = lista->curr;
	}
	lista->tamano++;			// Actualizar tamano
}

/*****
*   void moveToStart
******
*   Actualiza el nodo actual al inicial
******
*	Input:
*		tLista * lista : lista enlazada que se desea reiniciar
******
*   Returns:
*   	void
* *****/
void moveToStart(tLista *lista){
    lista->curr=lista->head;		// Posicion inicial
    lista->pos = 0;
}

/*****
*   unsigned long getValue
******
*   Obtiene el valor actual de la lista enlazada
******
*	Input:
*		tLista * lista : lista enlazada que se busca obtener valor
******
*   Returns:
*   	unsigned long, retorna valor actual (ciudad) de la lista
* *****/
unsigned long getValue(tLista *lista){
    return (lista->curr)->ciudad;
}

/*****
*   void liberar
******
*   Libera memoria recursivamente de los nodos en la lista enlazada
******
*	Input:
*		tLista * base : lista enlazada que se desea liberar memoria
******
*   Returns:
*   	void
* *****/
void liberar(tLista *base){
    if (base->head == NULL){		// Caso base, no hay mas nodos
        return;
    }
    tNodo *auxiliar = base->head;	// Almacenar inicial en auxiliar
    base->head = base->head->adyacente;		// Avanzar a siguiente
    free(auxiliar);				// Liberar auxiliar
    liberar(base);				// Liberar siguiente recursivo
}

/*****
*   void initGraph
******
*   Inicializa un grafo para n vertices
******
*	Input:
*		tGrafo * G : grafo que se desea inicializar
*		unsigned long n : cantidad de vertcies del grafo
******
*   Returns:
*   	void
* *****/
void initGraph(tGrafo *G, unsigned long n){
	unsigned long i;
	G->ciudades = calloc(sizeof(tVertice),n);
	G->nCiudades = n;
	for(i=0;i<n;i++){
		initialize(&(G->ciudades[i]).destinos);
	}
}

/*****
*   unsigned long nVertex
******
*   Retorna el numero de vertices en el grafo
******
*	Input:
*		tGrafo * G : grafo al que se desea saber su cantidad de vertices 
******
*   Returns:
*   	unsigned long, retorna la cantidad de vertices
* *****/
unsigned long nVertex (tGrafo *G){
	return G->nCiudades;
}

/*****
*   unsigned long first
******
*   Devuelve el primer vecino de un vertice ver dado
******
*	Input:
*		tGrafo * G : grafo en el cual se encuentran los vertices a trabajar
*		unsigned long ver : posicion del vertice al cual se le desea saber su primer veciono
******
*   Returns:
*   	unsigned long, retorna el valor(posicion) del primer vertice vecino
* *****/
unsigned long first (tGrafo *G, unsigned long ver){
	moveToStart(&G->ciudades[ver].destinos);
	return (((G->ciudades[ver]).destinos).head)->ciudad;    //retorna el primer valor de la lista enlazada
}

/*****
*   unsigned long nextG
******
*   Devuelve el vecino siguiente al actual(current)
******
*	Input:
*		tGrafo * G : grafo en el cual se encuentran los vertices a trabajar
*		unsigned long ver : posicion vertice al cual se le desea saber su siguiente vecino
******
*   Returns:
*   	unsigned long, retorna el valor(posicion) del vertice siguiente al actual
* *****/
unsigned long nextG (tGrafo *G, unsigned long ver){
	if (G->ciudades[ver].destinos.pos < G->ciudades[ver].destinos.tamano){       //comprueba que no se haya llegado al final de la lista
		nextL(&(G->ciudades[ver]).destinos);                                     //lleva el valor actual de la lista, al siguiente
		return getValue(&(G->ciudades[ver]).destinos);
	}
	else return 0;
}

/*****
*   void setEdge
******
*   Agrega un nuevo arco al grafo dirigido desde partida hasta llegada 
******
*	Input:
*		tGrafo * G : grafo en el cual se encuentran los vertices a trabajar
*		unsigned long partida : posicion del vertice del cual surge el nuevo arco
*		unsigned long llegada : posicion del vertice al cual llega el nuevo arco
******
*   Returns:
*   	void
* *****/
void setEdge (tGrafo *G, unsigned long partida, unsigned long llegada){
	insertar(&(G->ciudades[partida].destinos),llegada);
}

/*****
*   short in getMark
******
*   Obtiene la marca asignada a un vertice dado
******
*	Input:
*		tGrafo * G : grafo en el cual se encuentra el vertice a trabajar
*		unsigned long ciudad : posicion del vertice que se desea obtener la marca
******
*   Returns:
*   	short int, devuelve 0(si no esta visitado) o 1(si esta visitado)
* *****/
short int getMark (tGrafo *G, unsigned long ciudad){
	return (G->ciudades[ciudad]).visitado;
}

/*****
*   void setMark
******
*   Marca un vertice con un valor dado
******
*	Input:
*		tGrafo * G : grafo en el cual se encuentra el vertice a trabajar
*		unsigned long ciudad : posicion del vertice que se desea marcar
*		short int marca : marca que se desea ingresar al vertice, 0(no visitado) o 1(visitado) 
******
*   Returns:
*   	void
* *****/
void setMark (tGrafo *G, unsigned long ciudad, short int marca){
	(G->ciudades[ciudad]).visitado = marca;
}

/*****
*   void destroyGraph
******
*   Libera la memoria utilizada por un grafo
******
*	Input:
*		tGrafo * G : grafo que se desea liberar
******
*   Returns:
*   	void
* *****/
void destroyGraph (tGrafo *G){
	unsigned long i;
	unsigned long n = G->nCiudades;
	for(i=0;i<n;i++){                                  //itera por todos los vertices
		liberar(&(G->ciudades[i]).destinos);           //libera las lista enlazada del vertice actual
	}
	free(G->ciudades);
}

/*****
*   void cleanMark
******
*   Borra todas las marcas de todos los vertices del grafo (borrar: dejarlas en 0-no visitado-)
******
*	Input:
*		tGrafo * G : grafo que se desea borrar las marcas
******
*   Returns:
*   	void
* *****/
void cleanMark (tGrafo *G){
	unsigned long i;
	for(i=0;i<nVertex(G);i++){
		setMark(G,i,0);
	}
	
}

/*****
*   void DFS
******
*   Realiza una busqueda en profundidad sobre el grafo dirigido, marcando los vertices
*   como visitados
******
*	Input:
*		tGrafo * G : grafo sobre el que se trabaja la busqueda
*		unsigned long ciudad : ciudad del vertice que se desea buscar
******
*   Returns:
*   	void
* *****/

void DFS (tGrafo * G, unsigned long ciudad) {
	if (getMark(G, ciudad)==1){			// Caso base, si ya ha sido visitado
		return;							// terminar
	}
	unsigned long destino;
	setMark(G, ciudad, 1);				// Marcar actual como visitado
	unsigned long i = 0;
	for (destino = first(G, ciudad); i<(G->ciudades[ciudad].destinos.tamano); destino = nextG(G, ciudad)){
		if (getMark(G, destino) == 0){			// Por vecinos al actual, si no han sido visitados
			DFS(G, destino);					// buscar recursivamente
		}
		i++;
	}
}

int main(){
	/* Input */
	unsigned long nCiudades, nVuelos, i;
	scanf("%lu", &nCiudades);								// Cantidad de ciudades
	tGrafo *vuelos = (tGrafo *)malloc(sizeof(tGrafo) * nCiudades);
	initGraph(vuelos, nCiudades);							// Inicializar grafo
	scanf("%lu", &nVuelos);									// Cantidad de vuelos
	unsigned int partida, destino;
	for (i=0; i<nVuelos; i++){								//Crea arcos O D
		scanf("%u", &partida);
		scanf("%u", &destino);
		setEdge(vuelos, partida, destino);
	}
	unsigned int nConsultas;
	unsigned long j;
	scanf("%u", &nConsultas);								// Cantidad de consultas
	tLista *unreachables = malloc(sizeof(tLista) * nConsultas);		// Lista con listas enlazadas de punteros de inalcanzables
	for (i=0; i<nConsultas; i++){
		initialize(&unreachables[i]);						// Inicializar inalcanzables
		scanf("%u", &partida);								// Ciudad a buscar
		DFS(vuelos, partida);								// Marcar visitados en partida
		for (j=0; j<nCiudades; j++){
			if (getMark(vuelos, j) == 0){					// Buscar no visitados en grafo
				insertar(&unreachables[i], j);				// Agregar valor a inalcanzables
			}
		}
		cleanMark(vuelos);									// Reiniciar marcas
	}
	/* Output */
	printf("%u \n", nConsultas);							// Numero de consultas
	for (i=0; i<nConsultas; i++){
		moveToStart(&unreachables[i]);						// Ir al principio
		printf("%u ", unreachables[i].tamano);				// Imprimir cantidad de inalcanzables
		j = 0;
		while (j<unreachables[i].tamano){					// Iterar sobre inalcanzables
			printf("%lu ", getValue(&unreachables[i]));		// Obtener valor actual
			nextL(&unreachables[i]);						// Siguiente
			j++;
		}
		printf("\n");
	}
	/* Liberar memoria */
	for (i=0; i<nConsultas; i++) {							// Liberar listas enlazadas inalcanzables
		liberar(&unreachables[i]);
	}
	free(unreachables);										// Liberar inalcanzables
	destroyGraph(vuelos);									// Liberar elementos grafo vuelos
	free(vuelos);											// Liberar grafo
	return 1;
}
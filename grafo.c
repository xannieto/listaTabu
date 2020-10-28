#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "grafo.h"

#define RADIO_TERRA 6371 
/////////////////////////////////////////////////////////// TIPOS DE DATOS

// Estructura privada
struct tipografo {
    int N; //número de vértices del grafo
    int MAXVERTICES;
    tipovertice *VERTICES; //vector de vértices
    int *A; //matriz de adyacencia
    double *distancias;
};

//////////////////////////////////////////////////////////////// FUNCIONES

/////////////////////////////////// INICIO PARTE MODIFICABLE

//HAY QUE MODIFICAR ESTA FUNCIÓN SI SE CAMBIA EL TIPO DE DATO tipovertice
/* 
 * Esta función devuelve 0 si los dos nodos son iguales
 * -1 si V1 está antes de V2 o 1 en otro caso.
 */
int _comparar_vertices(tipovertice V1, tipovertice V2){
    if (V1.latitude == V2.latitude && V1.lonxitude == V2.lonxitude) {
        return 0;
    }

    return 1;
}

////////////////////////////////////// FIN PARTE MODIFICABLE

//Creación del grafo con 0 nodos
void crear_grafo(grafo *G, int N) {
    *G = (struct tipografo*) malloc(sizeof (struct tipografo));
    (*G)->MAXVERTICES = N;
    (*G)->VERTICES = malloc(sizeof(tipovertice) * N);
    (*G)->A = (int *) malloc(sizeof(int) * N * N);
    (*G)->distancias = (double *) malloc(sizeof(double) * N * N);  

    for (int i = 0; i < (*G)->MAXVERTICES; i++) {
        for (int j = 0; j < (*G)->MAXVERTICES; j++) {
            (*G)->A[i * N + j] = 0;
            (*G)->distancias[i * N + j] = 0.0;
        }
    }
}

//Devuelve la posición del vértice Vert en el vector VERTICES del grafo G
//Si devuelve -1 es porque no encontró el vértice
int posicion(grafo G, tipovertice V) {
    int contador = 0;
    //comparo V con todos los vertices almacenados en VERTICES 
    while (contador < G->N) {
		if (_comparar_vertices(G->VERTICES[contador], V) == 0){
            return contador; 
        }
        contador++;
    }
    return -1;
}

//Devuelve 1 si el grafo G existe y 0 en caso contrario
int existe(grafo G) {
    return (G != NULL);
}

//Devuelve 1 si el vértice Vert existe en el grafo G
int existe_vertice(grafo G, tipovertice V) {
    return (posicion(G, V) >= 0);
}

//Inserta un vértice en el grafo
int insertar_vertice(grafo *G, tipovertice Vert) {
    int i;
    if ((*G)->N == (*G)->MAXVERTICES) {
    	// Se ha llegado al maximo numero de vertices
    	printf("Grafo lleno!\n");
    	return -1;
    }
   
    (*G)->N++;
    (*G)->VERTICES[((*G)->N) - 1] = Vert;
	
    return (*G)->N-1;
}

//Borra un vertice del grafo
void borrar_vertice(grafo *G, tipovertice Vert) {
    int F, C, P, N = (*G)->N;
    P = posicion(*G, Vert);
    if(P == -1){
    	printf("Vertice inexistente!\n");
    	return;
    }
    //if (P >= 0 && P < (*G)->N) {
    for (F = P; F < N - 1; F++){
        (*G)->VERTICES[F] = (*G)->VERTICES[F + 1];
	}

    for (C = P; C < N - 1; C++){
        for (F = 0; F < N; F++){
            (*G)->A[F * (*G)->MAXVERTICES + C] = (*G)->A[F * (*G)->MAXVERTICES + C + 1];
        }
	}
    for (F = P; F < N - 1; F++){
        for (C = 0; C < N; C++){
            (*G)->A[F * (*G)->MAXVERTICES + C] = (*G)->A[(F + 1) * (*G)->MAXVERTICES + C];
        }
	}
    (*G)->N--;    
}

//Crea el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void crear_arco(grafo *G, int pos1, int pos2) {
    (*G)->A[pos1 * (*G)->MAXVERTICES + pos2] = 1;
}

//Borra el arco de relación entre VERTICES(pos1) y VERTICES(pos2)
void borrar_arco(grafo *G, int pos1, int pos2) {
    (*G)->A[pos1 * (*G)->MAXVERTICES + pos2] = 0;
}

//Devuelve 1 si VERTICES(pos1) y VERTICES(pos2) son vértices adyacentes
int son_adyacentes(grafo G, int pos1, int pos2) {
    return (G->A[pos1 * G->MAXVERTICES + pos2]);
}

//Destruye el grafo
void borrar_grafo(grafo *G) {
    free((*G)->A);
    free((*G)->VERTICES);
    free((*G)->distancias);
    free(*G);
    *G = NULL;
}

//Devuelve el número de vértices del grafo G
int num_vertices(grafo G) {
    return G->N;
}

//Devuelve el vector de vértices VERTICES del grafo G
tipovertice* array_vertices(grafo G) {
    return G->VERTICES;
}

double calcular_distancia(grafo *G, int pos1, int pos2) {

    if ((*G)->distancias[pos1 * (*G)->MAXVERTICES + pos2] > 0) {
        return (*G)->distancias[pos1 * (*G)->MAXVERTICES + pos2];
    }

    double distancia = 0.0;
    /* conversión de graos a radiáns */
    double latitude_v1 = (*G)->VERTICES[pos1].latitude * M_PI / 180.0;
    double latitude_v2 = (*G)->VERTICES[pos2].latitude * M_PI / 180.0;
    double lonxitude_v1 = (*G)->VERTICES[pos1].lonxitude * M_PI / 180.0;
    double lonxitude_v2 = (*G)->VERTICES[pos2].lonxitude * M_PI / 180.0;

    /* operamos o que hai dentro da raíz */
    double tmp;
    tmp = sin((latitude_v2 - latitude_v1) / 2);
    distancia += tmp * tmp; //potencia ^ 2
    
    tmp = sin((lonxitude_v2 - lonxitude_v1) / 2);
    distancia += cos(latitude_v1) * cos(latitude_v2) * (tmp * tmp); 
    
    /* raíz cadrada */
    distancia = sqrt(distancia);
    distancia = 2 * RADIO_TERRA * distancia;

    /* gardamos a distancia calculada */
    (*G)->distancias[pos1 * (*G)->MAXVERTICES + pos2] = distancia;
    (*G)->distancias[pos2 * (*G)->MAXVERTICES + pos1] = distancia;

    return distancia;
}

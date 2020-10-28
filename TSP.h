#ifndef __TSP__
#define __TSP__
#include "grafo.h"

void cargar_grafo(grafo *G, char *nome_ficheiro);

void lista_tabu_basica(grafo *G);

void lista_tabu_mellorada(grafo *G);

#endif /* __TSP__ */

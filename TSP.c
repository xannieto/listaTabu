#include "TSP.h"
#include "grafo.h"
#include "lista.tabu.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PARADA 1E5
#define TAM_ALEATORIOS 99

void _producir_solucion_aleatoria(char *numeros_aleatorios, tipovertice *L, tipovertice *S_opt) {
    FILE *ficheiro;
    int v_producidos[TAM_ALEATORIOS], i;
    double r = 0.0;
    int v = 0;

    /* producindo solución aleatoria sen ficheiro */
    if (numeros_aleatorios == NULL) {
        for (i = 0; i < TAM_ALEATORIOS; i++) {
            v_producidos[i] = 0; // indica que a posición está libre
        }
        
        for (i = 0; i < TAM_ALEATORIOS; i++) {
            srand(time(NULL));
            r = (double) rand() / RAND_MAX;

            v = (int) 1 + (r * 99);
            
            /* comprobamos que non foi usado */
            while ( v_producidos[v] != 0 ) {
                v = (v + 1) % TAM_ALEATORIOS; 
            } 
            
            S_opt[i] = L[v];
            v_producidos[v] = 1;
        } 
    /* producindo solución aleatoria con ficheiro */
    } else if ((ficheiro = fopen(numeros_aleatorios, "r")) == NULL) {
        for (i = 0; i < TAM_ALEATORIOS; i++) {
            v_producidos[i] = 0; // indica que a posición está libre
        }

        for (i = 0; i < TAM_ALEATORIOS; i++) {
            fscanf(ficheiro, "%lf", &r);
            
            v = (int) 1 + (r * 99);
            
            /* comprobamos que non foi usado */
            while ( v_producidos[v] != 0 ) {
                v = (v + 1) % TAM_ALEATORIOS; 
            } 
            
            S_opt[i] = L[v];
            v_producidos[v] = 1;
        } 
        
    } else {
        fprintf(stderr,"ERRO: Problema para producir números aleatorios: non se pode abrir o ficheiro %s.\n", numeros_aleatorios);
    }
}

void _percorrido_inicial(grafo *G, tipovertice *S) {
    
}

void _calcular_custe(grafo *G, tipovertice *S, double distancia_S) {
    
}

void cargar_grafo(grafo *G, char *nome_ficheiro) {
    FILE *ficheiro;
    double latitude, lonxitude;
    tipovertice vertice;
    int N;

    if ((ficheiro = fopen(nome_ficheiro, "r")) != NULL) {
        fscanf(ficheiro, "%d", &N);

        if (N > 0) {
            printf("%d\n", N);
            
            crear_grafo(G, N);
            for ( int i = 0; i < N; i++) {
                fscanf(ficheiro, "%lf %lf", &latitude, &lonxitude);
                printf("Lat: %lf, Lon: %lf\n", latitude, lonxitude);
                
                vertice.latitude = latitude;
                vertice.lonxitude = lonxitude;
                insertar_vertice(G, vertice);
            }

        } 
    }

}

void lista_tabu_basica(grafo *G, char *numeros_aleatorios) {
    tipovertice *L = array_vertices_bis(*G);
    tipovertice *S_opt, *S_n;
    MOVEMENTO lista_tabu[100];
    int k = 0, sen_mellora = 0;
    double custe_opt = 0.0;
    double custe_n = 0.0;
    
    S_opt = malloc(sizeof(tipovertice) * num_vertices(*G));
    S_n = malloc(sizeof(tipovertice) * num_vertices(*G));

    /* hai que xerar a solucion inicial */
    _producir_solucion_aleatoria(numeros_aleatorios, L, S_opt);

    for (k = 0; k < PARADA; k++) {
        

    }

}

void lista_tabu_mellorada(grafo *G, char *numeros_aleatorios) {

}

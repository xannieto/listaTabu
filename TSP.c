#include "TSP.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

#define PARADA 1E5

void _calcular_custe(grafo *G, tipovertice *S, double distancia_S) {
    
}

void cargar_grafo(grafo *G, char *nome_ficheiro) {
    FILE *ficheiro;
    int N;
    double latitude, lonxitude;
    tipovertice vertice;

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

void lista_tabu_basica(grafo *G) {

}

void lista_tabu_mellorada(grafo *G) {

}

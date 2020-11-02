#include "TSP.h"
#include "grafo.h"
#include "lista.tabu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define PARADA 1E5
#define TAM_ALEATORIOS 99

int ITERACION = 0;
int TAMANHO_S = 0;
int TAMANHO_M = 0;
tipovertice ORIXE;

void _producir_solucion_aleatoria(char *numeros_aleatorios, tipovertice *L, tipovertice *S_opt) {
    FILE *ficheiro = NULL;
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
    } else if ((ficheiro = fopen(numeros_aleatorios, "r")) != NULL) {
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
        fclose(ficheiro);
        
    } else {
        fprintf(stderr,"ERRO: Problema para producir números aleatorios: non se pode abrir o ficheiro %s.\n", numeros_aleatorios);
    }
}

double _calcular_custe(grafo *G, tipovertice *S_n) {
    double distancia = 0.0;

    distancia += calcular_distancia(G, ORIXE.id, S_n[0].id);
    distancia += calcular_distancia(G, S_n[TAMANHO_S - 1].id, ORIXE.id);

    for (int i = 0; i < (TAMANHO_S - 2); i++) {
        distancia += calcular_distancia(G, S_n[i].id, S_n[i + 1].id);
    }

    return distancia;
}

int _posicion_actual(tipovertice *S_n, int id) {
    for (int pos = 0; pos < TAMANHO_S; pos++) {
        if (S_n[pos].id == id) {
            return pos;
        }
    }
    return -1;
}

void _realizar_movemento(tipovertice *S_n, MOVEMENTO movemento) {
    int pos_i = _posicion_actual(S_n, movemento.i);
    int pos_j = _posicion_actual(S_n, movemento.j);

    tipovertice tmp = S_n[pos_i];
    S_n[pos_i] = S_n[pos_j];
    S_n[pos_j] = tmp;
}

double _calcular_custe_n(grafo *G, tipovertice *S_n, int i, int j) {
    double distancia = 0.0;
    tipovertice *S_copia = malloc(sizeof(tipovertice) * TAMANHO_S);
    MOVEMENTO movemento;

    S_copia = memcpy(S_copia, S_n, sizeof(tipovertice) * TAMANHO_S);
    movemento.i = i;
    movemento.j = j;
    _realizar_movemento(S_copia, movemento);

    distancia += calcular_distancia(G, ORIXE.id, S_copia[0].id);
    distancia += calcular_distancia(G, S_copia[TAMANHO_S - 1].id, ORIXE.id);

    for (int i = 0; i < (TAMANHO_S - 2); i++) {
        distancia += calcular_distancia(G, S_copia[i].id, S_copia[i + 1].id);
    }

    free(S_copia);
    return distancia;
}

MOVEMENTO *_producir_movementos(tipovertice *S_n) {
    MOVEMENTO *movementos;
    MOVEMENTO tmp;
    int i, j, k;
    movementos = (MOVEMENTO *) malloc(sizeof(MOVEMENTO) * TAMANHO_M);

    for (i = 0, k = 0; i < (TAMANHO_S - 2); i++) {
        for (j = (i + 1); j < (TAMANHO_S - 1); j++, k++) {
            tmp.i = S_n[i].id;
            tmp.j = S_n[j].id;
            movementos[k] = tmp;
        }
    }

    return movementos;
}

void cargar_grafo(grafo *G, char *nome_ficheiro) {
    FILE *ficheiro = NULL;
    double latitude, lonxitude;
    tipovertice vertice;
    int N;

    if ((ficheiro = fopen(nome_ficheiro, "r")) != NULL) {
        fscanf(ficheiro, "%d", &N);

        if (N > 0) {
            crear_grafo(G, N);
            for ( int i = 0; i < N; i++) {
                fscanf(ficheiro, "%lf %lf", &latitude, &lonxitude);
                
                vertice.latitude = latitude;
                vertice.lonxitude = lonxitude;
                insertar_vertice(G, vertice);
            }

        } 
        fclose(ficheiro);
    }
}

void _imprimir_info(tipovertice *S_n, LISTATABU lista_tabu, MOVEMENTO intercambio, double custe, int iteracions_sen_mellora) {
    int i;

    printf("ITERACIÓN: %d\n", ITERACION + 1);
    printf("\tINTERCAMBIO: (%d, %d)\n", intercambio.i, intercambio.j);
    printf("\tPERCORRIDO: ");
    for (i = 0; i < (TAMANHO_S - 1); i++) {
        printf("%d ", S_n[i].id);
    }
    printf("\n");
    printf("\tCUSTE (km): %d\n", (int) custe);
    printf("\tITERACIÓNS SEN MELLORA: %d\n", iteracions_sen_mellora);
    imprimir_lista_tabu(lista_tabu);

}

void lista_tabu_basica(grafo *G, char *numeros_aleatorios) {
    tipovertice *L = array_vertices_bis(*G);
    tipovertice *S_opt, *S_n;
    LISTATABU lista_tabu;
    MOVEMENTO *movementos;
    MOVEMENTO mellor_vecinho;
    int k = 0, iteracions_sen_mellora = 0, reinicios = 0;
    double custe_opt = 0.0;
    double custe_n = 0.0;
    double custe_mellor_vecinho = 0.0, custe_vecinho = 0.0;
    
    /* iniciamos as reservas de memoria e outras cousas*/
    ORIXE = array_vertices(*G)[0];
    TAMANHO_S = (num_vertices(*G) - 1);
    TAMANHO_M = (TAMANHO_S * (TAMANHO_S - 1) / 2);

    S_opt = malloc(sizeof(tipovertice) * TAMANHO_S);
    S_n = malloc(sizeof(tipovertice) * TAMANHO_S);
    
    inicializar_lista_tabu(&lista_tabu);

    /* hai que xerar a solucion inicial */
    _producir_solucion_aleatoria(numeros_aleatorios, L, S_opt);

    printf("PERCORRIDO INICIAL\n");
    printf("\tPERCORRIDO:");
    for (k = 0; k < (TAMANHO_S - 1); k++) {
        printf("%d ", S_opt[k].id);
    }
    printf("\n");

    custe_opt = _calcular_custe(G, S_opt);
    printf("\tCUSTE (km): %d\n", (int) custe_opt);

    /* gardamos a informacion en S_n para traballar con ela */
    custe_n = custe_opt;
    S_n = memcpy(S_n, S_opt, sizeof(tipovertice) * TAMANHO_S);

    /* BUCLE GRANDE */
    for (ITERACION = 0; ITERACION < PARADA; ITERACION++) {

        if (iteracions_sen_mellora == 100) {
            /* recuperamos a mellor solución */
            S_n = memcpy(S_n, S_opt, sizeof(tipovertice) * TAMANHO_S);
            custe_n = custe_opt;
            iteracions_sen_mellora = 0;

            inicializar_lista_tabu(&lista_tabu);

            printf("***************\n");
            printf("REINICIO: %d\n", ++reinicios);
            printf("***************\n");
        }

        movementos = _producir_movementos(S_n);
        custe_mellor_vecinho = INT_MAX;
        /* busca do mellor veciño */
        for ( k = 0; k < TAMANHO_M; k++) {

            if (e_movemento_tabu(&lista_tabu, movementos[k].i, movementos[k].j)) {
                continue;
            }

            custe_vecinho = _calcular_custe_n(G, S_n, movementos[k].i, movementos[k].j);
            
            if ( custe_vecinho < custe_mellor_vecinho ) {
                custe_mellor_vecinho = custe_vecinho;
                mellor_vecinho = movementos[k];
            }
        }
  
        _realizar_movemento(S_n, mellor_vecinho);
        custe_n = custe_mellor_vecinho;
        inserir_movemento(&lista_tabu, mellor_vecinho.i, mellor_vecinho.j);

        if (custe_n < custe_opt) {
            custe_opt = custe_n;
            S_n = memcpy(S_n, S_opt, sizeof(tipovertice) * TAMANHO_S);
            iteracions_sen_mellora = 0;
        
        } else {
            iteracions_sen_mellora++;
        }

        _imprimir_info(S_n, lista_tabu, mellor_vecinho, custe_n, iteracions_sen_mellora);

        /* liberación do punteiro */
        free(movementos);
    }

    free(L);
    free(S_n);
    free(S_opt);

}

void lista_tabu_mellorada(grafo *G, char *numeros_aleatorios) {

}

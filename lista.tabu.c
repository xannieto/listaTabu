#include "lista.tabu.h"
#include <stdio.h>

void inicializar_lista_tabu(LISTATABU *lista_tabu) {
    MOVEMENTO movemento;
    movemento.i = -1;
    movemento.j = -1;

    for (int i = 0; i < TAMANHO_LISTA_TABU; i++ ) {
        (*lista_tabu).movementos[i] = movemento;
    }
    
    (*lista_tabu).pos_actual = 0;
}

void inserir_movemento(LISTATABU *lista_tabu, int i, int j) {
    MOVEMENTO movemento;
    movemento.i = i;
    movemento.j = j;

    (*lista_tabu).movementos[(*lista_tabu).pos_actual] = movemento;
    
    (*lista_tabu).pos_actual = ((*lista_tabu).pos_actual + 1) % TAMANHO_LISTA_TABU; 
}

int e_movemento_tabu(LISTATABU lista_tabu, int i, int j) {
    for (int k = 0; k < TAMANHO_LISTA_TABU; k++) {
        if ((lista_tabu.movementos[k].i == i && lista_tabu.movementos[k].j == j) || (lista_tabu.movementos[k].i == j && lista_tabu.movementos[k].j == i)) {
            return 1;
        }    
    }

    return 0;
} 

void imprimir_lista_tabu(LISTATABU lista_tabu) {
    printf("\tLISTA TABU:\n");

    for (int i = 0; i < TAMANHO_LISTA_TABU; i++) {
        if ( lista_tabu.movementos[i].i == -1 ) {
            break;
        }
        printf("\t%d %d\n",lista_tabu.movementos[i].i, lista_tabu.movementos[i].j );
    }
}

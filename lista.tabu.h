#ifndef __LISTA_TABU__
#define __LISTA_TABU__

#define TAMANHO_LISTA_TABU 100

typedef struct {
    int i;
    int j;
} MOVEMENTO;

typedef struct {
    int pos_actual;
    MOVEMENTO movementos[TAMANHO_LISTA_TABU];
} LISTATABU;

void inicializar_lista_tabu(LISTATABU *lista_tabu);

void inserir_movemento(LISTATABU *lista_tabu, int i, int j);

int e_movemento_tabu(LISTATABU *lista_tabu, int i, int j);

#endif /* __LISTA_TABU__ */

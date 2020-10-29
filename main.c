#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TSP.h"
#include "grafo.h"

int main(int argc, char *argv[]) {
    char *nome_ficheiro = NULL;
    grafo G;
    
    /* só está o ficheiro cos concellos */
    if (argc == 2) {
        nome_ficheiro = malloc(sizeof(argv[1]));
        strcpy(nome_ficheiro, argv[1]);
        printf("INFO: Ficheiro recibido: %s.\n", nome_ficheiro);

        cargar_grafo(&G, nome_ficheiro); 
        
        /* ficheiro dos concellos e tamén de números aleatorios */
        if (argc == 3) {
            free(&nome_ficheiro);
            nome_ficheiro = malloc(sizeof(argv[2]));
            strcpy(nome_ficheiro, argv[1]);
            printf("INFO: Ficheiro de números aleatorios recibido: %s.\n", nome_ficheiro);
            
            lista_tabu_basica(&G, nome_ficheiro);

        } else {
            lista_tabu_basica(&G, NULL);
        }

        free(&nome_ficheiro);

    } else {
        printf("ERRO: Non se proporcionou ningún ficheiro.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

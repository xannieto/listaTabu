#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TSP.h"
#include "grafo.h"

int main(int argc, char *argv[]) {
    char nome_ficheiro[20];
    grafo G;
    
    /* só está o ficheiro cos concellos */
    if (argc > 1) {
        strcpy(nome_ficheiro, argv[1]);

        cargar_grafo(&G, nome_ficheiro); 
        
        /* ficheiro dos concellos e tamén de números aleatorios */
        if (argc == 3) {
            strcpy(nome_ficheiro, argv[2]);
            
            lista_tabu_basica(&G, nome_ficheiro);
            borrar_grafo(&G);

        } else {
            lista_tabu_basica(&G, NULL);
            borrar_grafo(&G);
        }

    } else {
        printf("ERRO: Non se proporcionou ningún ficheiro.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

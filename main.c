#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main(int argc, char **argv){

    // confere se o num de argumentos ta certo
    if (argc != 3)
    {
        printf("\nErro de Sintaxe\n");
        printf("Usar: ./biblioteca.bin <entrada> <saida>\n\n");
        return 1;
    }

    // se os argumentos estao certos, recebe eles
    char *StrEntrada = argv[1];
    char *StrSaida = argv[2];
    ListaLivro lista;
    inicializaLista(&lista);

    // traz o arquivo de texto para a memoria, guardando na lista
    lerArquivoEntrada(StrEntrada, &lista);
    imprimirLista(&lista);
}


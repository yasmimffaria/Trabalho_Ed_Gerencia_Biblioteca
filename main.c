#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "arvore.h"

void menu() {
    printf("========SISTEMA DE GERENCIAMENTO BIBLIOTECA=======\n");
    printf("1- Cadastrar livro\n");
    printf("2- Remover livro\n");
    printf("3- Buscar livro por título\n");
    printf("4- Emprestar livro\n");
    printf("5- Devolver livro\n");
    printf("6- Gerar relatório\n");
    printf("7- Sair\n");
    printf("Escolha uma opção: ");
}

int main(int argc, char **argv) {
    //if (argc != 3) {
       // printf("\nErro de Sintaxe\n");
      //  printf("Usar: ./biblioteca.bin <entrada> <saida>\n\n");
//return 1;
   // }

    char *StrEntrada = "/home/yasmim/CLionProjects/untitled/entrada.txt";
    char *StrSaida = argv[2];
    ListaLivro lista;
    inicializaLista(&lista);

    lerArquivoEntrada(StrEntrada, &lista);
    NodoArvore* raiz = NULL;

    NodoLivro* atual = lista.primeiro;
    while (atual != NULL) {
        raiz = inserirLivroArvore(raiz, atual->livro);
        atual = atual->proximo;
    }

    int opcao;
    char titulo[100];
    int id;
    do {
        menu();
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                {
                    printf("Digite o ID do livro: ");
                    scanf("%d", &id);
                    printf("Digite o título do livro: ");
                    scanf(" %[^\n]", titulo);
                    printf("Digite o autor do livro: ");
                    char autor[100];
                    scanf(" %[^\n]", autor);
                    printf("Digite o ano de publicação: ");
                    int ano;
                    scanf("%d", &ano);
                    printf("Digite o gênero do livro: ");
                    char genero[50];
                    scanf(" %[^\n]", genero);
                    Livro *novoLivro = (Livro*) malloc(sizeof(Livro));
                    novoLivro->id = id;
                    strcpy(novoLivro->titulo, titulo);
                    strcpy(novoLivro->autor, autor);
                    novoLivro->anoPubl = ano;
                    strcpy(novoLivro->genero, genero);
                    novoLivro->disponivel = 1; // 1 indicates the book is available
                    raiz = inserirLivroArvore(raiz, novoLivro);
                    adicionaLivro(&lista, novoLivro);
                    break;
                }
            case 2:
                {
                    //printf("Digite o ID do livro que deseja remover: ");
                    //scanf("%d", &id);
                    printf("Digite o título do livro que deseja buscar: ");
                    scanf(" %[^\n]", titulo);
                    NodoArvore* result = buscarLivroPorTitulo(raiz, titulo);
                    raiz = removerLivroArvore(result, result->livro->id);
                    if (raiz != NULL)
                    {
                        removeLivro(&lista, result->livro->id);
                    }else
                    {
                        printf("O livro foi removido ou nao existe!");
                    }

                    break;
                }
            case 3:
                printf("Digite o título do livro que deseja buscar: ");
                scanf(" %[^\n]", titulo);
                NodoArvore* resultado = buscarLivroPorTitulo(raiz, titulo);
                if (resultado != NULL) {
                    printf("Livro encontrado: SIM \n ID: %d, \n Titulo: %s, \n Autor: %s, \n Ano: %d, \n Genero: %s\n", resultado->livro->id, resultado->livro->titulo, resultado->livro->autor, resultado->livro->anoPubl, resultado->livro->genero);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;
            case 4:
                printf("Digite o título do livro que deseja emprestar: ");
                scanf(" %[^\n]", titulo);
                //emprestarLivro(raiz, titulo);
                break;
            case 5:
                printf("Digite o título do livro que deseja devolver: ");
                scanf(" %[^\n]", titulo);
                //devolverLivro(raiz, titulo);
                break;
            case 6:
                //gerarRelatorio(raiz);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 7);

    liberarArvore(raiz);
    return 0;
}
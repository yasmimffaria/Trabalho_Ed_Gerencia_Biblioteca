#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"
#include "arvore.h"
#include "fila.h"

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

    Fila* fila = criarFila(); // Criar a fila para empréstimos e devoluções

    int opcao;
    char titulo[100];
    int id;
    char usuario[100];
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
                    novoLivro->disponivel = 1; // 1 indica que o livro está disponível
                    raiz = inserirLivroArvore(raiz, novoLivro);
                    adicionaLivro(&lista, novoLivro);
                    break;
                }
            case 2:
                {
                    printf("Digite o título do livro que deseja buscar: ");
                    scanf(" %[^\n]", titulo);
                    NodoArvore* result = buscarLivroPorTitulo(raiz, titulo);
                    raiz = removerLivroArvore(result, result->livro->id);
                    if (raiz != NULL) {
                        removeLivro(&lista, result->livro->id);
                    } else {
                        printf("O livro foi removido ou não existe!\n");
                    }
                    break;
                }
            case 3:
                printf("Digite o título do livro que deseja buscar: ");
                scanf(" %[^\n]", titulo);
                NodoArvore* resultado = buscarLivroPorTitulo(raiz, titulo);
                if (resultado != NULL) {
                    printf("Livro encontrado: SIM\nID: %d\nTítulo: %s\nAutor: %s\nAno: %d\nGênero: %s\n", resultado->livro->id, resultado->livro->titulo, resultado->livro->autor, resultado->livro->anoPubl, resultado->livro->genero);
                } else {
                    printf("Livro não encontrado.\n");
                }
                break;
            case 4:
                {
                    printf("Digite o título do livro que deseja emprestar: ");
                    scanf(" %[^\n]", titulo);
                    NodoArvore* resultadoEmprestimo = buscarLivroPorTitulo(raiz, titulo);
                    if (resultadoEmprestimo != NULL && resultadoEmprestimo->livro->disponivel) {
                        printf("Digite o nome do usuário que está emprestando o livro: ");
                        scanf(" %[^\n]", usuario);
                        emprestarLivro(resultadoEmprestimo->livro, usuario, fila);
                    } else {
                        printf("Livro não disponível para empréstimo.\n");
                    }
                    break;
                }
            case 5:
                {
                    printf("Digite o título do livro que deseja devolver: ");
                    scanf(" %[^\n]", titulo);
                    NodoArvore* resultadoDevolucao = buscarLivroPorTitulo(raiz, titulo);
                    if (resultadoDevolucao != NULL && !resultadoDevolucao->livro->disponivel) {
                        devolverLivro(resultadoDevolucao->livro, fila);
                    } else {
                        printf("Livro não encontrado ou já está disponível.\n");
                    }
                    break;
                }
            case 6:
                //gerarRelatorio(raiz);
                break;
            case 7:
                printf("Saindo...\n");
                destruirFila(fila); // Destruir a fila antes de sair
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 7);

    liberarArvore(raiz);
    return 0;
}
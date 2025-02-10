#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

void inicializaLista(ListaLivro* lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
}

void adicionaLivro(ListaLivro* lista, Livro* livro) {
    livro->disponivel = 1; // inicializa o disponivel
    NodoLivro* novoNodo = (NodoLivro*)malloc(sizeof(NodoLivro));
    novoNodo->livro = livro;
    novoNodo->proximo = NULL;

    if (lista->ultimo != NULL) {
        lista->ultimo->proximo = novoNodo;
    } else {
        lista->primeiro = novoNodo;
    }
    lista->ultimo = novoNodo;
}

void removeLivro(ListaLivro* lista, int id) {
    //procura na lista, algum item com esse id, aí remove ele

    // variaveis de auxilio
    NodoLivro* atual = lista->primeiro;
    NodoLivro* anterior = NULL;

    //enquanto nao chegar no final, percorre procurando esse id
    while (atual != NULL) {
        //confere se o atual e o q tem q deletar
        if (atual->livro->id == id) {

            // se achei o item, mas e o primeiro
            if (anterior == NULL) {
                // atualiza o primeiro da lista
                lista->primeiro = atual->proximo;
                // se e' o ultimo, atualiza a lista
                if (atual->proximo == NULL) lista->ultimo = NULL;
            }

            // se achei mas nao e' o primeiro
            else {
                //atualiza o proximo do anterior
                anterior->proximo = atual->proximo;
                // se e' o ultimo, atualiza a lista
                if (atual == lista->ultimo) lista->ultimo = anterior;
            }

            // libera a memoria do item
            free(atual->livro);  // Libera a memória do livro
            free(atual);         // Libera a memória do nó
            printf("\n - Livro com id %d foi removido com sucesso \n", id);
            return;

        }

        //avanca as variaveis
        anterior = atual;
        atual = atual->proximo;
    }

    // se nao achou o item, mostra isso
    printf("\n - Nao foi encontrado nenhum livro com o id %d. - ", id);
    return;
}

void imprimirLista(ListaLivro* lista) {
    NodoLivro* atual = lista->primeiro;
    while (atual != NULL) {
        Livro* livro = atual->livro;
       // printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Genero: %s\n",
               //livro->id, livro->titulo, livro->autor, livro->anoPubl, livro->genero);
        atual = atual->proximo;
    }
}

void lerArquivoEntrada(char *StrEntrada, ListaLivro* lista) {

    char Controle;
    char auxFinalLinha;
    FILE *arquivo = fopen(StrEntrada, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    do {
        fscanf(arquivo, " %c", &Controle);
        switch (Controle) {
            case 'I': {
                Livro* livro = (Livro*)malloc(sizeof(Livro));
                fscanf(arquivo, "%d %[^,],%[^,],%d,%s", &livro->id, livro->titulo, livro->autor, &livro->anoPubl, livro->genero);
                adicionaLivro(lista, livro);
                break;
            }
            case '#':
                do {
                    fscanf(arquivo, "%c", &auxFinalLinha);
                } while (auxFinalLinha != '\n');
                break;
            case 'F':
                fclose(arquivo);
                return;
        }
    } while (1);
}

// livro disponivel ou indisponivel verificacao
void verificaDisponibilidade(ListaLivro* lista) {
    NodoLivro* atual = lista->primeiro;
    while(atual != NULL) {
        Livro* livro = atual->livro;
        if(livro->disponivel == 1) {
            printf("Livro disponivel: id %d, titulo %s\n", livro->id, livro->titulo);
        } else {
            printf("Livro indisponivel: id %d, titulo %s\n", livro->id, livro->titulo);
        }
        atual = atual->proximo;
    }
}
void emprestarLivro(Livro* livro, const char* usuario, Fila* fila) {
    if (livro->disponivel) {
        livro->disponivel = 0;
        strcpy(livro->usuario, usuario);
        Registro reg = {livro->id, 'E'};
        strcpy(reg.usuario, usuario);
        enfileirar(fila, reg);
        printf("Livro emprestado com sucesso para %s.\n", usuario);
    } else {
        printf("Livro não disponível para empréstimo.\n");
    }
}

// Função para devolver um livro
void devolverLivro(Livro* livro, Fila* fila) {
    if (!livro->disponivel) {
        livro->disponivel = 1;
        Registro reg = {livro->id, 'D'};
        strcpy(reg.usuario, livro->usuario);
        enfileirar(fila, reg);
        printf("Livro devolvido com sucesso por %s.\n", livro->usuario);
        strcpy(livro->usuario, ""); // Limpa o usuário que fez o empréstimo
    } else {
        printf("Livro já está disponível.\n");
    }
}
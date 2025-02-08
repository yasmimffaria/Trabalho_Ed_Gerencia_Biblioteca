#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

void inicializaLista(ListaLivro* lista) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
}

void adicionaLivro(ListaLivro* lista, Livro* livro) {
    livro->disponivel = 1;// inicializa o disponivel
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

void removeLivro(ListaLivro* lista, int id){
    //procura na lista, algum item com esse id, aí remove ele

    // variaveis de auxilio
    NodoLivro atual = lista->primeiro;
    NodoLivroanterior = NULL;

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

            // libera a memmoria do item
            free(atual->livro);  // Libera a memória do livro
            free(atual);         // Libera a memória do nó
            printf("\n - Livro com id %d foi removido com sucesso", id);
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
        printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Genero: %s\n",
               livro->id, livro->titulo, livro->autor, livro->anoPubl, livro->genero);
        atual = atual->proximo;
    }
}

void lerArquivoEntrada(char *StrEntrada,ListaLivro* lista) {

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

//livro dispponivel ou indisponivel verificacao
void verificaDisponibildiade(ListaLivro* lista){
  NodoLivro* atual = lista->primeiro;
      while(atual != NULL){
        Livro* livro = atual->livro;
        if(livro->disponivel == 1){
          printf("Livro disponivel: id %d, titulo %d", livro->id, livro->titulo);
        } else {
            printf("Livro indisponivel: id %d, titulo %d", livro->id, livro->titulo);
        }
        atual = atual->proximo;
      }
}

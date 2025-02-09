#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

int altura(NodoArvore* nodo) {
    return (nodo != NULL) ? nodo->altura : 0;
}

int fatorBalanceamento(NodoArvore* nodo) {
    if (nodo == NULL) return 0;
    return altura(nodo->esquerda) - altura(nodo->direita);
}

NodoArvore* rotacaoDireita(NodoArvore* y) {
    if (y == NULL || y->esquerda == NULL) return y;
    NodoArvore* x = y->esquerda;
    NodoArvore* z = x->direita;

    x->direita = y;
    y->esquerda = z;

    y->altura = 1 + ((altura(y->esquerda) > altura(y->direita)) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + ((altura(x->esquerda) > altura(x->direita)) ? altura(x->esquerda) : altura(x->direita));

    return x;
}
NodoArvore* removerLivroArvore(NodoArvore *raiz, int id) {
    if (raiz == NULL) {
        printf("Livro com ID %d não encontrado.\n", id);
        return NULL;
    }

    if (id < raiz->livro->id) {
        raiz->esquerda = removerLivroArvore(raiz->esquerda, id);
    } else if (id > raiz->livro->id) {
        raiz->direita = removerLivroArvore(raiz->direita, id);
    } else {
        // Caso o livro tenha sido encontrado
        printf("Livro com ID %d removido com sucesso.\n", id);

        if (raiz->esquerda == NULL) {
            NodoArvore *temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            NodoArvore *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Encontrar o sucessor in-order (menor valor da subárvore direita)
        NodoArvore *temp = raiz->direita;
        while (temp && temp->esquerda != NULL) {
            temp = temp->esquerda;
        }

        raiz->livro = temp->livro;
        raiz->direita = removerLivroArvore(raiz->direita, temp->livro->id);
    }

    return raiz;
}

NodoArvore* rotacaoEsquerda(NodoArvore* x) {
    if (x == NULL || x->direita == NULL) return x;
    NodoArvore* y = x->direita;
    NodoArvore* z = y->esquerda;

    y->esquerda = x;
    x->direita = z;

    x->altura = 1 + ((altura(x->esquerda) > altura(x->direita)) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + ((altura(y->esquerda) > altura(y->direita)) ? altura(y->esquerda) : altura(y->direita));

    return y;
}

NodoArvore* balancear(NodoArvore* nodo) {
    if (nodo == NULL) return NULL;
    int fb = fatorBalanceamento(nodo);

    if (fb > 1) {
        if (fatorBalanceamento(nodo->esquerda) < 0)
            nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
        return rotacaoDireita(nodo);
    }

    if (fb < -1) {
        if (fatorBalanceamento(nodo->direita) > 0)
            nodo->direita = rotacaoDireita(nodo->direita);
        return rotacaoEsquerda(nodo);
    }

    return nodo;
}

NodoArvore* inserirLivroArvore(NodoArvore* raiz, Livro* livro) {
    if (raiz == NULL) {
        NodoArvore* novoNodo = (NodoArvore*)malloc(sizeof(NodoArvore));
        if (novoNodo == NULL) {
            printf("Erro ao alocar memória para NodoArvore.\n");
            exit(1);
        }
        novoNodo->livro = (Livro*)malloc(sizeof(Livro));
        if (novoNodo->livro == NULL) {
            printf("Erro ao alocar memória para Livro.\n");
            exit(1);
        }
        *(novoNodo->livro) = *livro;
        novoNodo->esquerda = NULL;
        novoNodo->direita = NULL;
        novoNodo->altura = 1;
        return novoNodo;
    }

    if (strcmp(livro->titulo, raiz->livro->titulo) < 0) {
        raiz->esquerda = inserirLivroArvore(raiz->esquerda, livro);
    } else if (strcmp(livro->titulo, raiz->livro->titulo) > 0) {
        raiz->direita = inserirLivroArvore(raiz->direita, livro);
    } else {
        return raiz;
    }

    raiz->altura = 1 + ((altura(raiz->esquerda) > altura(raiz->direita)) ? altura(raiz->esquerda) : altura(raiz->direita));
    return balancear(raiz);
}

NodoArvore* buscarLivroPorTitulo(NodoArvore* raiz, char* titulo) {
    if (raiz == NULL || raiz->livro == NULL) return NULL;

    int cmp = strcmp(titulo, raiz->livro->titulo);
    if (cmp == 0) return raiz;
    else if (cmp < 0) return buscarLivroPorTitulo(raiz->esquerda, titulo);
    else return buscarLivroPorTitulo(raiz->direita, titulo);
}

void imprimirArvoreEmOrdem(NodoArvore* raiz) {
    if (raiz != NULL) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        //printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Genero: %s\n", raiz->livro->id, raiz->livro->titulo, raiz->livro->autor, raiz->livro->anoPubl, raiz->livro->genero);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

NodoArvore* liberarArvore(NodoArvore* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        if (raiz->livro != NULL) free(raiz->livro);
        free(raiz);
    }
    return NULL;
}

#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// funcao que retorna a altura de um nodo qualquer
int altura(NodoArvore* nodo) {
    // se o nodo for nulo, retorna 0, se n, retorna a altura
    if (nodo != NULL) return nodo->altura;
    else return 0;
}

// funcao que calcula o fb de um no' qualquer
int fatorBalanceamento(NodoArvore* nodo) {
    if (nodo == NULL) {
        return 0;
    } else {
        int alturaEsquerda = altura(nodo->esquerda);
        int alturaDireita = altura(nodo->direita);
        return alturaEsquerda - alturaDireita;
    }
}

// rotacao simples pra direita
NodoArvore* rotacaoDireita(NodoArvore* y) {

    //        y                 x
    //       / \               / \
    //      x   T2     =>     T1  y
    //     / \                   / \
    //   T1   z                 z  T2

    //atribui variaveis auxiliares
    NodoArvore* x = y->esquerda;
    NodoArvore* z = x->direita;

    //faz a rotacao em si
    x->direita = y;
    y->esquerda = z;

    //ajusta as alturas
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));

    //retorna a nova raiz
    return x;
}

// rotacao simples pra esquerda
NodoArvore* rotacaoEsquerda(NodoArvore* x) {

    //     x                y
    //    / \              / \
    //  T1   y     =>     x   T2
    //      / \          / \
    //     z   T2      T1   z

    //atribui variaveis auxiliares
    NodoArvore* y = x->direita;
    NodoArvore* z = y->esquerda;

    //faz a rotacao em si
    y->esquerda = x;
    x->direita = z;

    //ajusta as alturas
    x->altura = 1 + (altura(x->esquerda) > altura(x->direita) ? altura(x->esquerda) : altura(x->direita));
    y->altura = 1 + (altura(y->esquerda) > altura(y->direita) ? altura(y->esquerda) : altura(y->direita));

    //retorna a nova raiz
    return y;
}


// equilibra a arvore depois de inserir
NodoArvore* balancear(NodoArvore* nodo) {
    // calcula o fb
    int fb = fatorBalanceamento(nodo);

    //===================================================
    // FB positivo -> rotacao a direita
    if (fb > 1) {
        if (fatorBalanceamento(nodo->esquerda) >= 0){
            // rotacao simples pra direita
            return rotacaoDireita(nodo);
        } else {
            //rotacao esquerda dps direita
            nodo->esquerda = rotacaoEsquerda(nodo->esquerda);
            return rotacaoDireita(nodo);
        }
    }

    //===================================================
    // FB negativo -> rotacao a esquerda
    if (fb < -1) {
        if (fatorBalanceamento(nodo->direita) >= 0){
            //rotacao simples pra esquerda
            return rotacaoEsquerda(nodo);
        } else {
            //rotacao dupla - esquerda direita
            nodo->direita = rotacaoDireita(nodo->direita);
            return rotacaoEsquerda(nodo);
        }
    }

    //retorna a raiz
    return nodo;
}

// insere um livro na arvore
NodoArvore* inserirLivroArvore(NodoArvore* raiz, Livro* livro) {
    if (raiz == NULL) {
        // se a arvore for vazia, coloca o livro no primeiro lugar
        NodoArvore* novoNodo = (NodoArvore*)malloc(sizeof(NodoArvore));
        novoNodo->livro = livro;
        // coloca os dois filhos como nulos
        novoNodo->esquerda = NULL;
        novoNodo->direita = NULL;
        //coloca a altura na arvore
        novoNodo->altura = 1;
        //retorna a nova raiz
        return novoNodo;
    }

    //se n e' vazia, descobre se tenho que ir pra esquerda ou pra direita
    if (livro->id < raiz->livro->id) {
        raiz->esquerda = inserirLivroArvore(raiz->esquerda, livro);
    } else if (livro->id > raiz->livro->id) {
        raiz->direita = inserirLivroArvore(raiz->direita, livro);
    } else {
        //se ja tem um nodo com esse valor, retorna ele
        return raiz;
    }

    //depois de inserir, ajusa a altura de cada nodo, e retorna a raaiz
    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));
    return balancear(raiz);
}

// funcao recursiva pra imprimir a arvore, usa in ordem
void imprimirArvoreEmOrdem(NodoArvore* raiz) {
    if (raiz != NULL) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf("ID: %d, Titulo: %s, Autor: %s, Ano: %d, Genero: %s\n", raiz->livro->id, raiz->livro->titulo, raiz->livro->autor, raiz->livro->anoPubl, raiz->livro->genero);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

// funcao recursiva pra liberara a memoria
NodoArvore* liberarArvore(NodoArvore* raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz->livro);
        free(raiz);
    }
    return NULL;
}

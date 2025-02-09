#ifndef ARVORE_H
#define ARVORE_H

#include "biblioteca.h"

typedef struct NodoArvore {
	Livro* livro;                // item em si do nodo
	int altura;                  // altura desse nodo
	struct NodoArvore* esquerda; // filho da esquerda
	struct NodoArvore* direita;  // filho da direita
} NodoArvore;

int altura(NodoArvore* nodo);
int fatorBalanceamento(NodoArvore* nodo);
NodoArvore* rotacaoDireita(NodoArvore* y);
NodoArvore* rotacaoEsquerda(NodoArvore* x);
NodoArvore* balancear(NodoArvore* nodo);
NodoArvore* inserirLivroArvore(NodoArvore* raiz, Livro* livro);
void imprimirArvoreEmOrdem(NodoArvore* raiz);
NodoArvore* buscarLivroPorTitulo(NodoArvore* raiz, char* titulo);
NodoArvore* removerLivroArvore(NodoArvore *raiz, int id);
NodoArvore* liberarArvore(NodoArvore* raiz);

#endif

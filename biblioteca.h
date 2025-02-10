//
// Created by yasmim on 04/02/25.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "fila.h"

typedef struct {
    int id;
    char titulo[100];
    char autor[100];
    int anoPubl;
    char genero[50];
    int disponivel; // 1 indica disponível, 0 indica emprestado
    char usuario[100]; // Nome do usuário que emprestou o livro
} Livro;

typedef struct NodoLivro {
    Livro* livro;
    struct NodoLivro* proximo;
} NodoLivro;

typedef struct {
    NodoLivro* primeiro;
    NodoLivro* ultimo;
} ListaLivro;

void inicializaLista(ListaLivro* lista);
void adicionaLivro(ListaLivro* lista, Livro* livro);
void removeLivro(ListaLivro* lista, int id);
void imprimirLista(ListaLivro* lista);
void lerArquivoEntrada(char *StrEntrada,ListaLivro* lista);
void menuBiblioteca(ListaLivro* lista);
void verificaDisponibildiade(ListaLivro* lista);
void emprestarLivro(Livro* livro, const char* usuario, Fila* fila);
void devolverLivro(Livro* livro, Fila* fila);




#endif


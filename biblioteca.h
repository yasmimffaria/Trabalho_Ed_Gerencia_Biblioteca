//
// Created by yasmim on 04/02/25.
//

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

typedef struct Livro{
    int id;
    int anoPubl;
    char titulo[200];
    char autor[200];
    char genero[200];
    int disponivel; //1 para disponivel e 0 para indis.
}Livro;

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



#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

// Função para criar uma nova fila
Fila* criarFila() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

// Função para destruir a fila e liberar memória
void destruirFila(Fila* fila) {
    while (!filaVazia(fila)) {
        desenfileirar(fila);
    }
    free(fila);
}

// Função para verificar se a fila está vazia
int filaVazia(Fila* fila) {
    return (fila->frente == NULL);
}

// Função para adicionar um novo elemento à fila
void enfileirar(Fila* fila, Registro dado) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dado = dado;
    novoNo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->frente = novoNo;
    } else {
        fila->tras->proximo = novoNo;
    }
    fila->tras = novoNo;
}

// Função para remover um elemento da fila
Registro desenfileirar(Fila* fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        exit(1);
    }

    No* temp = fila->frente;
    Registro dado = temp->dado;
    fila->frente = fila->frente->proximo;

    if (fila->frente == NULL) {
        fila->tras = NULL;
    }

    free(temp);
    return dado;
}
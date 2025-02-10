#ifndef FILA_H
#define FILA_H

// Estrutura para armazenar informações de empréstimo/devolução
typedef struct {
    int id; // Identificador do livro
    char tipo; // 'E' para empréstimo, 'D' para devolução
    char usuario[100]; // Nome do usuário que fez a operação
} Registro;

// Estrutura do nó da fila
typedef struct No {
    Registro dado;
    struct No* proximo;
} No;

// Estrutura da fila
typedef struct {
    No* frente;
    No* tras;
} Fila;

// Funções para manipulação da fila
Fila* criarFila();
void destruirFila(Fila* fila);
int filaVazia(Fila* fila);
void enfileirar(Fila* fila, Registro dado);
Registro desenfileirar(Fila* fila);

#endif // FILA_H
#include <stdio.h>
#include <stdlib.h>

// Definindo o número máximo de peças no jogo
#define MAX_PEÇAS 10

// Estrutura para representar uma peça do Tetris
typedef struct {
    int forma[4][4];  // Representação da forma da peça
    char cor;         // Cor da peça
} Peça;

// Fila Circular - usada para as peças futuras
typedef struct {
    Peça itens[MAX_PEÇAS];
    int frente, tras;
} FilaCircular;

// Pilha - usada para armazenar peças reservadas
typedef struct {
    Peça itens[MAX_PEÇAS];
    int topo;
} Pilha;

// Funções para manipulação da fila

void inicializarFila(FilaCircular *f) {
    f->frente = f->tras = 0;
}

int filaVazia(FilaCircular *f) {
    return f->frente == f->tras;
}

void inserirFila(FilaCircular *f, Peça p) {
    if ((f->tras + 1) % MAX_PEÇAS == f->frente) {
        printf("Fila cheia!\n");
        return;
    }
    f->itens[f->tras] = p;
    f->tras = (f->tras + 1) % MAX_PEÇAS;
}

Peça removerFila(FilaCircular *f) {
    Peça p;
    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        exit(1);
    }
    p = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX_PEÇAS;
    return p;
}

// Funções para manipulação da pilha

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, Peça pe) {
    if (p->topo == MAX_PEÇAS - 1) {
        printf("Pilha cheia!\n");
        return;
    }
    p->itens[++(p->topo)] = pe;
}

Peça desempilhar(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia!\n");
        exit(1);
    }
    return p->itens[(p->topo)--];
}

// Funções para mover peças entre fila e pilha

void moverParaPilha(FilaCircular *f, Pilha *p) {
    if (!filaVazia(f)) {
        Peça peca = removerFila(f);
        empilhar(p, peca);
    }
}

void moverParaFila(Pilha *p, FilaCircular *f) {
    if (!pilhaVazia(p)) {
        Peça peca = desempilhar(p);
        inserirFila(f, peca);
    }
}

int main() {
    FilaCircular fila;
    Pilha pilha;
    Peça p1 = {{{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 'R'};  // Exemplo de peça vermelha

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Inserindo uma peça na fila
    inserirFila(&fila, p1);

    // Movendo a peça da fila para a pilha
    moverParaPilha(&fila, &pilha);

    // Movendo a peça de volta para a fila
    moverParaFila(&pilha, &fila);

    return 0;
}

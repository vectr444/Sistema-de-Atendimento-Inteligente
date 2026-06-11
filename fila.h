#ifndef FILA_H
#define FILA_H

#include "atendimento.h"

typedef struct noh_fila {
    Atendimento* atendimento;
    struct noh_fila* proximo;
} NohFila;

typedef struct {
    NohFila* inicio;
    NohFila* fim;
    int tamanho;
} Fila;

// Funções da fila
Fila* criar_fila();
int enfileirar(Fila* f, Atendimento* a);
Atendimento* desenfileirar(Fila* f);
void listar_fila(Fila* f);
void liberar_fila(Fila* f);

#endif

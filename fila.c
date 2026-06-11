#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* criar_fila() {
    Fila* f = (Fila*) malloc(sizeof(Fila));
    if (f != NULL) {
        f->inicio = NULL;
        f->fim = NULL;
        f->tamanho = 0;
    }
    return f;
}

int enfileirar(Fila* f, Atendimento* a) {
    if (f == NULL || a == NULL) return 0;
    
    NohFila* novo = (NohFila*) malloc(sizeof(NohFila));
    if (novo == NULL) return 0;
    
    novo->atendimento = a;
    novo->proximo = NULL;
    
    if (f->fim == NULL) {
        f->inicio = novo;
    } else {
        f->fim->proximo = novo;
    }
    f->fim = novo;
    f->tamanho++;
    
    return 1;
}

Atendimento* desenfileirar(Fila* f) {
    if (f == NULL || f->inicio == NULL) return NULL;
    
    NohFila* temp = f->inicio;
    Atendimento* a = temp->atendimento;
    
    f->inicio = f->inicio->proximo;
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(temp);
    f->tamanho--;
    
    return a;
}

void listar_fila(Fila* f) {
    if (f == NULL || f->inicio == NULL) {
        printf("A fila de espera esta vazia.\n");
        return;
    }
    
    NohFila* atual = f->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%d. ", pos++);
        imprimir_atendimento(atual->atendimento);
        atual = atual->proximo;
    }
}

void liberar_fila(Fila* f) {
    if (f != NULL) {
        NohFila* atual = f->inicio;
        while (atual != NULL) {
            NohFila* temp = atual;
            atual = atual->proximo;
            // A fila não deve liberar o atendimento se ele for passado para o histórico
            // Mas para casos de encerramento do programa sem atender:
            liberar_atendimento(temp->atendimento);
            free(temp);
        }
        free(f);
    }
}

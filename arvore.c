#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

Arvore* criar_arvore() {
    Arvore* arv = (Arvore*) malloc(sizeof(Arvore));
    if (arv != NULL) {
        arv->raiz = NULL;
        arv->tamanho = 0;
    }
    return arv;
}

// Cria um no isolado da arvore.
static NohArvore* criar_noh(Atendimento* a) {
    NohArvore* novo = (NohArvore*) malloc(sizeof(NohArvore));
    if (novo != NULL) {
        novo->atendimento = a;
        novo->esquerda = NULL;
        novo->direita = NULL;
    }
    return novo;
}

// Insercao recursiva: IDs menores vao para a esquerda, maiores para a direita.
static NohArvore* inserir_rec(NohArvore* raiz, Atendimento* a, int* ok) {
    if (raiz == NULL) {
        NohArvore* novo = criar_noh(a);
        if (novo != NULL) *ok = 1;
        return novo;
    }

    if (a->id < raiz->atendimento->id) {
        raiz->esquerda = inserir_rec(raiz->esquerda, a, ok);
    } else if (a->id > raiz->atendimento->id) {
        raiz->direita = inserir_rec(raiz->direita, a, ok);
    }
    // IDs iguais nao sao inseridos (sao gerados de forma unica no cadastro).

    return raiz;
}

int inserir_arvore(Arvore* arv, Atendimento* a) {
    if (arv == NULL || a == NULL) return 0;

    int ok = 0;
    arv->raiz = inserir_rec(arv->raiz, a, &ok);
    if (ok) arv->tamanho++;
    return ok;
}

// Busca recursiva pelo ID.
static Atendimento* buscar_rec(NohArvore* raiz, int id) {
    if (raiz == NULL) return NULL;

    if (id == raiz->atendimento->id) {
        return raiz->atendimento;
    } else if (id < raiz->atendimento->id) {
        return buscar_rec(raiz->esquerda, id);
    } else {
        return buscar_rec(raiz->direita, id);
    }
}

Atendimento* buscar_arvore(Arvore* arv, int id) {
    if (arv == NULL) return NULL;
    return buscar_rec(arv->raiz, id);
}

// Percurso em-ordem: esquerda, raiz, direita -> imprime ordenado por ID.
static void em_ordem_rec(NohArvore* raiz) {
    if (raiz == NULL) return;
    em_ordem_rec(raiz->esquerda);
    imprimir_atendimento(raiz->atendimento);
    em_ordem_rec(raiz->direita);
}

void listar_em_ordem(Arvore* arv) {
    if (arv == NULL || arv->raiz == NULL) {
        printf("A arvore esta vazia.\n");
        return;
    }
    em_ordem_rec(arv->raiz);
}

// Libera os nos em pos-ordem (filhos antes do pai). Nao toca nos atendimentos.
static void liberar_rec(NohArvore* raiz) {
    if (raiz == NULL) return;
    liberar_rec(raiz->esquerda);
    liberar_rec(raiz->direita);
    free(raiz);
}

void liberar_arvore(Arvore* arv) {
    if (arv == NULL) return;
    liberar_rec(arv->raiz);
    free(arv);
}

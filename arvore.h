#ifndef ARVORE_H
#define ARVORE_H

#include "atendimento.h"

/*
 * Arvore Binaria de Busca (ABB) indexada pelo ID do atendimento.
 *
 * Permite buscar um atendimento por ID em tempo medio O(log n), bem mais
 * rapido que a busca sequencial na lista. A arvore NAO e dona dos
 * atendimentos: ela apenas referencia os objetos que pertencem a lista.
 */

typedef struct noh_arvore {
    Atendimento* atendimento;
    struct noh_arvore* esquerda;
    struct noh_arvore* direita;
} NohArvore;

typedef struct {
    NohArvore* raiz;
    int tamanho;
} Arvore;

// Cria e inicializa uma arvore vazia.
Arvore* criar_arvore();

// Insere um atendimento na arvore usando o ID como chave. Retorna 1 em sucesso.
int inserir_arvore(Arvore* arv, Atendimento* a);

// Busca um atendimento pelo ID. Retorna o ponteiro encontrado ou NULL.
Atendimento* buscar_arvore(Arvore* arv, int id);

// Lista os atendimentos em ordem crescente de ID (percurso em-ordem).
void listar_em_ordem(Arvore* arv);

// Libera apenas os nos da arvore (NAO libera os atendimentos).
void liberar_arvore(Arvore* arv);

#endif

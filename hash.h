#ifndef HASH_H
#define HASH_H

#include "atendimento.h"

/*
 * Tabela Hash para agrupar/buscar atendimentos por CATEGORIA.
 *
 * Usa encadeamento separado (cada posicao da tabela e uma lista encadeada),
 * o que resolve colisoes e ainda agrupa naturalmente os atendimentos de
 * categorias que caem na mesma posicao. A hash NAO e dona dos atendimentos:
 * apenas referencia os objetos que pertencem a lista (historico).
 */

#define TAMANHO_HASH 101   // numero primo reduz colisoes

typedef struct noh_hash {
    Atendimento* atendimento;
    struct noh_hash* proximo;
} NohHash;

typedef struct {
    NohHash* tabela[TAMANHO_HASH];
    int tamanho;
} TabelaHash;

// Cria e inicializa uma tabela hash vazia.
TabelaHash* criar_hash();

// Insere um atendimento usando a categoria como chave. Retorna 1 em sucesso.
int inserir_hash(TabelaHash* h, Atendimento* a);

// Imprime todos os atendimentos de uma categoria. Retorna a quantidade.
int buscar_por_categoria(TabelaHash* h, const char* categoria);

// Descobre a categoria com maior numero de atendimentos (extra).
// Copia o nome para 'saida' (tam. >= 30) e retorna a quantidade (0 se vazia).
int categoria_mais_frequente(TabelaHash* h, char* saida);

// Libera apenas os nos da tabela (NAO libera os atendimentos).
void liberar_hash(TabelaHash* h);

#endif

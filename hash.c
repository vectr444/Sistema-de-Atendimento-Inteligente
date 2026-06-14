#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

/*
 * Funcao de hash djb2 (Daniel J. Bernstein): combina os caracteres da
 * categoria gerando um indice bem distribuido na tabela.
 */
static unsigned int funcao_hash(const char* chave) {
    unsigned long hash = 5381;
    int c;
    while ((c = *chave++)) {
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    }
    return (unsigned int)(hash % TAMANHO_HASH);
}

TabelaHash* criar_hash() {
    TabelaHash* h = (TabelaHash*) malloc(sizeof(TabelaHash));
    if (h != NULL) {
        for (int i = 0; i < TAMANHO_HASH; i++) {
            h->tabela[i] = NULL;
        }
        h->tamanho = 0;
    }
    return h;
}

int inserir_hash(TabelaHash* h, Atendimento* a) {
    if (h == NULL || a == NULL) return 0;

    NohHash* novo = (NohHash*) malloc(sizeof(NohHash));
    if (novo == NULL) return 0;

    unsigned int indice = funcao_hash(a->categoria);
    novo->atendimento = a;
    novo->proximo = h->tabela[indice];  // insere no inicio da lista do bucket
    h->tabela[indice] = novo;
    h->tamanho++;

    return 1;
}

// Conta (sem imprimir) quantos atendimentos existem numa categoria.
static int contar_categoria(TabelaHash* h, const char* categoria) {
    unsigned int indice = funcao_hash(categoria);
    int total = 0;
    for (NohHash* n = h->tabela[indice]; n != NULL; n = n->proximo) {
        if (strcmp(n->atendimento->categoria, categoria) == 0) {
            total++;
        }
    }
    return total;
}

int buscar_por_categoria(TabelaHash* h, const char* categoria) {
    if (h == NULL || categoria == NULL) return 0;

    unsigned int indice = funcao_hash(categoria);
    int encontrados = 0;

    NohHash* atual = h->tabela[indice];
    while (atual != NULL) {
        // Confere a categoria pois categorias diferentes podem colidir no bucket.
        if (strcmp(atual->atendimento->categoria, categoria) == 0) {
            imprimir_atendimento(atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

int categoria_mais_frequente(TabelaHash* h, char* saida) {
    if (h == NULL || saida == NULL) return 0;

    int melhor_contagem = 0;
    saida[0] = '\0';

    // Para cada categoria encontrada, conta quantos atendimentos ela possui.
    for (int i = 0; i < TAMANHO_HASH; i++) {
        for (NohHash* n = h->tabela[i]; n != NULL; n = n->proximo) {
            int contagem = contar_categoria(h, n->atendimento->categoria);
            if (contagem > melhor_contagem) {
                melhor_contagem = contagem;
                strncpy(saida, n->atendimento->categoria, 29);
                saida[29] = '\0';
            }
        }
    }
    return melhor_contagem;
}

void liberar_hash(TabelaHash* h) {
    if (h == NULL) return;

    for (int i = 0; i < TAMANHO_HASH; i++) {
        NohHash* atual = h->tabela[i];
        while (atual != NULL) {
            NohHash* temp = atual;
            atual = atual->proximo;
            free(temp);  // libera apenas o no, nao o atendimento
        }
    }
    free(h);
}

#ifndef LISTA_H
#define LISTA_H

#include "atendimento.h"

/*
 * Lista encadeada simples usada como HISTORICO de atendimentos.
 *
 * A lista e a "dona" dos atendimentos: e ela quem libera a memoria de cada
 * Atendimento ao final do programa. A fila, a arvore e a hash apenas
 * referenciam (apontam para) esses mesmos atendimentos, sem liberar.
 */

typedef struct noh_lista {
    Atendimento* atendimento;
    struct noh_lista* proximo;
} NohLista;

typedef struct {
    NohLista* inicio;
    int tamanho;
} Lista;

// Cria e inicializa uma lista vazia.
Lista* criar_lista();

// Insere um atendimento no historico (no inicio da lista). Retorna 1 em sucesso.
int inserir_lista(Lista* l, Atendimento* a);

// Lista (imprime) todo o historico de atendimentos.
void listar_historico(Lista* l);

// Busca SEQUENCIAL por nome do cliente (parcial e ignorando maiusc/minusc).
// Imprime todos os atendimentos encontrados e retorna a quantidade.
int buscar_por_cliente(Lista* l, const char* cliente);

// Busca SEQUENCIAL por prioridade (1=baixa, 2=media, 3=alta).
// Imprime todos os atendimentos encontrados e retorna a quantidade.
int buscar_por_prioridade(Lista* l, int prioridade);

// Libera os nos da lista E os atendimentos apontados por ela.
void liberar_lista(Lista* l);

#endif

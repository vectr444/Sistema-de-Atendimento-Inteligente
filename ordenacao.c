#include <stdio.h>
#include "ordenacao.h"

// Troca os atendimentos apontados por dois nos da lista.
static void trocar(NohLista* a, NohLista* b) {
    Atendimento* temp = a->atendimento;
    a->atendimento = b->atendimento;
    b->atendimento = temp;
}

/*
 * Bubble Sort generico sobre a lista encadeada.
 * O parametro 'comparar' devolve > 0 quando 'a' deve vir DEPOIS de 'b',
 * ou seja, quando os dois precisam ser trocados.
 */
static void bubble_sort(Lista* l, int (*comparar)(Atendimento*, Atendimento*)) {
    if (l == NULL || l->inicio == NULL) return;

    int trocou;
    NohLista* atual;
    NohLista* fim = NULL;  // marca a parte ja ordenada no final

    do {
        trocou = 0;
        atual = l->inicio;
        while (atual->proximo != fim) {
            if (comparar(atual->atendimento, atual->proximo->atendimento) > 0) {
                trocar(atual, atual->proximo);
                trocou = 1;
            }
            atual = atual->proximo;
        }
        fim = atual;  // o ultimo elemento da passada ja ficou no lugar
    } while (trocou);
}

// Maior prioridade primeiro: troca quando 'a' tem prioridade menor que 'b'.
static int comparar_prioridade(Atendimento* a, Atendimento* b) {
    return b->prioridade - a->prioridade;
}

// Menor tempo primeiro: troca quando 'a' demora mais que 'b'.
static int comparar_tempo(Atendimento* a, Atendimento* b) {
    return a->tempo_estimado - b->tempo_estimado;
}

void ordenar_por_prioridade(Lista* l) {
    bubble_sort(l, comparar_prioridade);
}

void ordenar_por_tempo(Lista* l) {
    bubble_sort(l, comparar_tempo);
}

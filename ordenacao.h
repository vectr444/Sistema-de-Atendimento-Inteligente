#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "lista.h"

/*
 * Ordenacao do historico (lista encadeada).
 *
 * As funcoes reordenam a propria lista usando Bubble Sort implementado pela
 * equipe. A troca e feita apenas nos ponteiros de Atendimento entre os nos,
 * sem realocar memoria e sem afetar a arvore ou a hash (que continuam
 * apontando para os mesmos objetos).
 */

// Ordena o historico por prioridade, da mais alta para a mais baixa.
void ordenar_por_prioridade(Lista* l);

// Ordena o historico por tempo estimado, do menor para o maior.
void ordenar_por_tempo(Lista* l);

#endif

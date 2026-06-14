#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

Lista* criar_lista() {
    Lista* l = (Lista*) malloc(sizeof(Lista));
    if (l != NULL) {
        l->inicio = NULL;
        l->tamanho = 0;
    }
    return l;
}

int inserir_lista(Lista* l, Atendimento* a) {
    if (l == NULL || a == NULL) return 0;

    NohLista* novo = (NohLista*) malloc(sizeof(NohLista));
    if (novo == NULL) return 0;

    novo->atendimento = a;
    novo->proximo = l->inicio;   // insercao no inicio: O(1)
    l->inicio = novo;
    l->tamanho++;

    return 1;
}

void listar_historico(Lista* l) {
    if (l == NULL || l->inicio == NULL) {
        printf("O historico esta vazio.\n");
        return;
    }

    NohLista* atual = l->inicio;
    int pos = 1;
    while (atual != NULL) {
        printf("%d. ", pos++);
        imprimir_atendimento(atual->atendimento);
        atual = atual->proximo;
    }
}

/*
 * Verifica se 'sub' aparece dentro de 'texto', ignorando maiusculas/minusculas.
 * Implementacao propria para permitir busca PARCIAL por nome (extra).
 */
static int contem_ignore_case(const char* texto, const char* sub) {
    if (texto == NULL || sub == NULL) return 0;
    if (sub[0] == '\0') return 1;

    for (int i = 0; texto[i] != '\0'; i++) {
        int j = 0;
        while (sub[j] != '\0' &&
               tolower((unsigned char) texto[i + j]) == tolower((unsigned char) sub[j])) {
            j++;
        }
        if (sub[j] == '\0') return 1;  // casou o trecho inteiro
    }
    return 0;
}

int buscar_por_cliente(Lista* l, const char* cliente) {
    if (l == NULL) return 0;

    int encontrados = 0;
    NohLista* atual = l->inicio;
    while (atual != NULL) {
        if (contem_ignore_case(atual->atendimento->cliente, cliente)) {
            imprimir_atendimento(atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

int buscar_por_prioridade(Lista* l, int prioridade) {
    if (l == NULL) return 0;

    int encontrados = 0;
    NohLista* atual = l->inicio;
    while (atual != NULL) {
        if (atual->atendimento->prioridade == prioridade) {
            imprimir_atendimento(atual->atendimento);
            encontrados++;
        }
        atual = atual->proximo;
    }
    return encontrados;
}

void liberar_lista(Lista* l) {
    if (l == NULL) return;

    NohLista* atual = l->inicio;
    while (atual != NULL) {
        NohLista* temp = atual;
        atual = atual->proximo;
        // A lista e a dona dos atendimentos: libera o atendimento e o no.
        liberar_atendimento(temp->atendimento);
        free(temp);
    }
    free(l);
}

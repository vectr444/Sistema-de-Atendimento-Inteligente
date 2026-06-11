#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "atendimento.h"

Atendimento* criar_atendimento(int id, const char* cliente, const char* categoria, int prioridade, int tempo_estimado) {
    Atendimento* a = (Atendimento*) malloc(sizeof(Atendimento));
    if (a != NULL) {
        a->id = id;
        strncpy(a->cliente, cliente, 49);
        a->cliente[49] = '\0';
        strncpy(a->categoria, categoria, 29);
        a->categoria[29] = '\0';
        a->prioridade = prioridade;
        a->tempo_estimado = tempo_estimado;
        strcpy(a->status, "aberto");
    }
    return a;
}

void imprimir_atendimento(Atendimento* a) {
    if (a != NULL) {
        printf("ID: %d | Cliente: %s | Categoria: %s | Prior: %d | Tempo: %dmin | Status: %s\n",
               a->id, a->cliente, a->categoria, a->prioridade, a->tempo_estimado, a->status);
    }
}

void liberar_atendimento(Atendimento* a) {
    if (a != NULL) {
        free(a);
    }
}

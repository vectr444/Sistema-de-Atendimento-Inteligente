#include <stdio.h>
#include <stdlib.h>
#include "estatisticas.h"

Estatisticas* criar_estatisticas() {
    Estatisticas* est = (Estatisticas*) malloc(sizeof(Estatisticas));
    if (est != NULL) {
        est->total_cadastrados = 0;
        est->total_atendidos = 0;
        est->total_cancelados = 0;
        est->prioridade_baixa = 0;
        est->prioridade_media = 0;
        est->prioridade_alta = 0;
    }
    return est;
}

void registrar_cadastro(Estatisticas* est, Atendimento* a) {
    if (est == NULL || a == NULL) return;
    
    est->total_cadastrados++;
    if (a->prioridade == 1) est->prioridade_baixa++;
    else if (a->prioridade == 2) est->prioridade_media++;
    else if (a->prioridade == 3) est->prioridade_alta++;
}

void registrar_atendimento(Estatisticas* est, Atendimento* a) {
    if (est == NULL || a == NULL) return;
    est->total_atendidos++;
}

void registrar_cancelamento(Estatisticas* est, Atendimento* a) {
    if (est == NULL || a == NULL) return;
    est->total_cancelados++;
}

void exibir_estatisticas(Estatisticas* est) {
    if (est == NULL) return;
    
    printf("\n--- ESTATISTICAS DO SISTEMA ---\n");
    printf("Total de atendimentos cadastrados: %d\n", est->total_cadastrados);
    printf("Total de atendimentos realizados: %d\n", est->total_atendidos);
    printf("Total de atendimentos cancelados: %d\n", est->total_cancelados);
    printf("\nDistribuicao por Prioridade (Cadastrados):\n");
    printf("- Baixa: %d\n", est->prioridade_baixa);
    printf("- Media: %d\n", est->prioridade_media);
    printf("- Alta:  %d\n", est->prioridade_alta);
    printf("-------------------------------\n");
}

void liberar_estatisticas(Estatisticas* est) {
    if (est != NULL) {
        free(est);
    }
}

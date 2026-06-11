#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include "atendimento.h"

// Estrutura para armazenar as estatísticas do sistema
typedef struct {
    int total_cadastrados;
    int total_atendidos;
    int total_cancelados;
    int prioridade_baixa;
    int prioridade_media;
    int prioridade_alta;
} Estatisticas;

// Funções para estatísticas
Estatisticas* criar_estatisticas();
void registrar_cadastro(Estatisticas* est, Atendimento* a);
void registrar_atendimento(Estatisticas* est, Atendimento* a);
void registrar_cancelamento(Estatisticas* est, Atendimento* a);
void exibir_estatisticas(Estatisticas* est);
void liberar_estatisticas(Estatisticas* est);

#endif

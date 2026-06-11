#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atendimento.h"
#include "fila.h"
#include "estatisticas.h"

// TODO: Incluir cabeçalhos da Fase 2 (lista, arvore, hash, ordenacao) quando implementados

void exibir_menu() {
    printf("\n===== SISTEMA DE ATENDIMENTOS =====\n");
    printf("1  - Cadastrar atendimento\n");
    printf("2  - Atender proximo da fila\n");
    printf("3  - Cancelar atendimento\n");
    printf("4  - Listar fila de espera\n");
    printf("5  - Listar historico (Nao implementado)\n");
    printf("6  - Buscar por nome do cliente (Nao implementado)\n");
    printf("7  - Buscar por prioridade (Nao implementado)\n");
    printf("8  - Buscar por ID usando arvore (Nao implementado)\n");
    printf("9  - Buscar por categoria usando hash (Nao implementado)\n");
    printf("10 - Ordenar historico por prioridade (Nao implementado)\n");
    printf("11 - Ordenar historico por tempo estimado (Nao implementado)\n");
    printf("12 - Exibir estatisticas\n");
    printf("0  - Sair\n");
    printf("===================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Fila* fila_espera = criar_fila();
    Estatisticas* est = criar_estatisticas();
    
    // Variável para gerar IDs sequenciais automaticamente
    int proximo_id = 1;
    int opcao;

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            // Limpar buffer em caso de entrada invalida
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Entrada invalida!\n");
            continue;
        }

        switch (opcao) {
            case 1: { // Cadastrar atendimento
                char cliente[50], categoria[30];
                int prioridade, tempo;

                printf("Nome do cliente: ");
                scanf(" %49[^\n]", cliente);
                printf("Categoria do atendimento: ");
                scanf(" %29[^\n]", categoria);
                
                do {
                    printf("Prioridade (1=Baixa, 2=Media, 3=Alta): ");
                    scanf("%d", &prioridade);
                } while(prioridade < 1 || prioridade > 3);
                
                printf("Tempo estimado (minutos): ");
                scanf("%d", &tempo);

                Atendimento* novo = criar_atendimento(proximo_id++, cliente, categoria, prioridade, tempo);
                if (enfileirar(fila_espera, novo)) {
                    registrar_cadastro(est, novo);
                    printf("Atendimento cadastrado com sucesso! ID: %d\n", novo->id);
                } else {
                    printf("Erro ao enfileirar atendimento.\n");
                    liberar_atendimento(novo);
                }
                break;
            }
            case 2: { // Atender proximo
                Atendimento* atendido = desenfileirar(fila_espera);
                if (atendido != NULL) {
                    strcpy(atendido->status, "atendido");
                    registrar_atendimento(est, atendido);
                    printf("Atendimento realizado:\n");
                    imprimir_atendimento(atendido);
                    
                    // TODO: Mover o 'atendido' para a Lista de Historico (Fase 2)
                    liberar_atendimento(atendido);
                } else {
                    printf("Nao ha atendimentos na fila.\n");
                }
                break;
            }
            case 3: { // Cancelar atendimento
                // Na versao basica vamos apenas desenfileirar o primeiro
                Atendimento* cancelado = desenfileirar(fila_espera);
                if (cancelado != NULL) {
                    strcpy(cancelado->status, "cancelado");
                    registrar_cancelamento(est, cancelado);
                    printf("Atendimento cancelado:\n");
                    imprimir_atendimento(cancelado);
                    
                    // TODO: Mover para o Historico (Fase 2)
                    liberar_atendimento(cancelado);
                } else {
                    printf("Nao ha atendimentos na fila para cancelar.\n");
                }
                break;
            }
            case 4: { // Listar fila
                printf("\n--- FILA DE ESPERA ---\n");
                listar_fila(fila_espera);
                break;
            }
            case 12: { // Estatisticas
                exibir_estatisticas(est);
                break;
            }
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                if (opcao >= 5 && opcao <= 11) {
                    printf("Funcionalidade da Fase 2. Ainda nao implementada.\n");
                } else {
                    printf("Opcao invalida!\n");
                }
        }
    } while (opcao != 0);

    // Liberar memoria
    liberar_fila(fila_espera);
    liberar_estatisticas(est);

    return 0;
}

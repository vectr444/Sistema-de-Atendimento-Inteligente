#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "atendimento.h"
#include "fila.h"
#include "estatisticas.h"
#include "lista.h"
#include "arvore.h"
#include "hash.h"
#include "ordenacao.h"

void exibir_menu() {
    printf("\n===== SISTEMA DE ATENDIMENTOS =====\n");
    printf("1  - Cadastrar atendimento\n");
    printf("2  - Atender proximo da fila\n");
    printf("3  - Cancelar atendimento\n");
    printf("4  - Listar fila de espera\n");
    printf("5  - Listar historico\n");
    printf("6  - Buscar por nome do cliente\n");
    printf("7  - Buscar por prioridade\n");
    printf("8  - Buscar por ID usando arvore\n");
    printf("9  - Buscar por categoria usando hash\n");
    printf("10 - Ordenar historico por prioridade\n");
    printf("11 - Ordenar historico por tempo estimado\n");
    printf("12 - Exibir estatisticas\n");
    printf("13 - Categoria com mais atendimentos\n");
    printf("0  - Sair\n");
    printf("===================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    // Estruturas de dados do sistema.
    Fila* fila_espera = criar_fila();      // ordem de atendimento
    Lista* historico = criar_lista();      // historico (dono dos atendimentos)
    Arvore* arvore_ids = criar_arvore();   // busca por ID
    TabelaHash* hash_cat = criar_hash();   // busca por categoria
    Estatisticas* est = criar_estatisticas();

    // Variável para gerar IDs sequenciais automaticamente.
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
                    if (scanf("%d", &prioridade) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) {}
                        prioridade = 0;
                    }
                } while (prioridade < 1 || prioridade > 3);

                do {
                    printf("Tempo estimado (minutos): ");
                    if (scanf("%d", &tempo) != 1) {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF) {}
                        tempo = -1;
                    }
                } while (tempo < 0);

                Atendimento* novo = criar_atendimento(proximo_id, cliente, categoria, prioridade, tempo);
                if (novo == NULL) {
                    printf("Erro de memoria ao criar atendimento.\n");
                    break;
                }

                // A lista (historico) e a dona; as demais estruturas referenciam.
                inserir_lista(historico, novo);
                inserir_arvore(arvore_ids, novo);
                inserir_hash(hash_cat, novo);
                enfileirar(fila_espera, novo);
                registrar_cadastro(est, novo);

                printf("Atendimento cadastrado com sucesso! ID: %d\n", novo->id);
                proximo_id++;
                break;
            }
            case 2: { // Atender proximo
                Atendimento* atendido = desenfileirar(fila_espera);
                if (atendido != NULL) {
                    strcpy(atendido->status, "atendido");
                    registrar_atendimento(est, atendido);
                    printf("Atendimento realizado:\n");
                    imprimir_atendimento(atendido);
                    // Nao libera: o atendimento continua no historico (lista).
                } else {
                    printf("Nao ha atendimentos na fila.\n");
                }
                break;
            }
            case 3: { // Cancelar atendimento (o proximo da fila)
                Atendimento* cancelado = desenfileirar(fila_espera);
                if (cancelado != NULL) {
                    strcpy(cancelado->status, "cancelado");
                    registrar_cancelamento(est, cancelado);
                    printf("Atendimento cancelado:\n");
                    imprimir_atendimento(cancelado);
                    // Nao libera: o atendimento continua no historico (lista).
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
            case 5: { // Listar historico
                printf("\n--- HISTORICO DE ATENDIMENTOS ---\n");
                listar_historico(historico);
                break;
            }
            case 6: { // Buscar por nome do cliente (sequencial / parcial)
                char busca[50];
                printf("Nome (ou parte do nome) do cliente: ");
                scanf(" %49[^\n]", busca);

                printf("\n--- RESULTADO DA BUSCA ---\n");
                int qtd = buscar_por_cliente(historico, busca);
                if (qtd == 0) {
                    printf("Nenhum atendimento encontrado para \"%s\".\n", busca);
                } else {
                    printf("%d atendimento(s) encontrado(s).\n", qtd);
                }
                break;
            }
            case 7: { // Buscar por prioridade (sequencial)
                int prioridade;
                printf("Prioridade (1=Baixa, 2=Media, 3=Alta): ");
                if (scanf("%d", &prioridade) != 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    printf("Prioridade invalida!\n");
                    break;
                }

                printf("\n--- RESULTADO DA BUSCA ---\n");
                int qtd = buscar_por_prioridade(historico, prioridade);
                if (qtd == 0) {
                    printf("Nenhum atendimento com prioridade %d.\n", prioridade);
                } else {
                    printf("%d atendimento(s) encontrado(s).\n", qtd);
                }
                break;
            }
            case 8: { // Buscar por ID usando arvore
                int id;
                printf("ID do atendimento: ");
                if (scanf("%d", &id) != 1) {
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {}
                    printf("ID invalido!\n");
                    break;
                }

                Atendimento* encontrado = buscar_arvore(arvore_ids, id);
                printf("\n--- RESULTADO DA BUSCA ---\n");
                if (encontrado != NULL) {
                    imprimir_atendimento(encontrado);
                } else {
                    printf("Nenhum atendimento com ID %d.\n", id);
                }
                break;
            }
            case 9: { // Buscar por categoria usando hash
                char categoria[30];
                printf("Categoria: ");
                scanf(" %29[^\n]", categoria);

                printf("\n--- RESULTADO DA BUSCA ---\n");
                int qtd = buscar_por_categoria(hash_cat, categoria);
                if (qtd == 0) {
                    printf("Nenhum atendimento na categoria \"%s\".\n", categoria);
                } else {
                    printf("%d atendimento(s) na categoria \"%s\".\n", qtd, categoria);
                }
                break;
            }
            case 10: { // Ordenar historico por prioridade
                ordenar_por_prioridade(historico);
                printf("\n--- HISTORICO ORDENADO POR PRIORIDADE (alta -> baixa) ---\n");
                listar_historico(historico);
                break;
            }
            case 11: { // Ordenar historico por tempo estimado
                ordenar_por_tempo(historico);
                printf("\n--- HISTORICO ORDENADO POR TEMPO ESTIMADO (menor -> maior) ---\n");
                listar_historico(historico);
                break;
            }
            case 12: { // Estatisticas
                exibir_estatisticas(est);
                break;
            }
            case 13: { // Categoria com mais atendimentos (extra)
                char categoria[30];
                int qtd = categoria_mais_frequente(hash_cat, categoria);
                if (qtd > 0) {
                    printf("Categoria com mais atendimentos: \"%s\" (%d atendimentos).\n",
                           categoria, qtd);
                } else {
                    printf("Ainda nao ha atendimentos cadastrados.\n");
                }
                break;
            }
            case 0:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    // Liberar memoria. A ordem importa: arvore, hash e fila liberam apenas seus
    // nos; a lista e a ultima a liberar, pois e a dona dos atendimentos.
    liberar_arvore(arvore_ids);
    liberar_hash(hash_cat);
    liberar_fila(fila_espera);
    liberar_lista(historico);
    liberar_estatisticas(est);

    return 0;
}

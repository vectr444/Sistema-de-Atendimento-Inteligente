# Sistema de Atendimento Inteligente

Projeto desenvolvido para a disciplina de Estruturas de Dados | Linguagem C.

## Integrantes
- Juan Carlos
- Gabriel Blank

## Descrição
Sistema de terminal para controlar os atendimentos técnicos de uma empresa.
Os atendimentos são cadastrados, organizados em uma fila de espera, registrados
em um histórico e analisados por diferentes critérios. O sistema implementa as
seguintes estruturas de dados (todas feitas pela equipe): **Fila Dinâmica**,
**Lista Encadeada**, **Árvore Binária de Busca** e **Tabela Hash**.

## Como compilar e executar

Para compilar:
```bash
gcc main.c atendimento.c fila.c estatisticas.c lista.c arvore.c hash.c ordenacao.c -o sistema
```

Para executar:

No Windows:
```cmd
sistema.exe
```
No Linux/Mac:
```bash
./sistema
```

## Funcionalidades (menu)
| Opção | Descrição |
|-------|-----------|
| 1  | Cadastrar atendimento |
| 2  | Atender próximo da fila (status → `atendido`) |
| 3  | Cancelar atendimento (status → `cancelado`) |
| 4  | Listar fila de espera |
| 5  | Listar histórico |
| 6  | Buscar por nome do cliente (busca sequencial, parcial e sem diferenciar maiúsculas) |
| 7  | Buscar por prioridade (busca sequencial) |
| 8  | Buscar por ID usando a árvore binária |
| 9  | Buscar por categoria usando a tabela hash |
| 10 | Ordenar histórico por prioridade |
| 11 | Ordenar histórico por tempo estimado |
| 12 | Exibir estatísticas |
| 13 | Categoria com mais atendimentos *(extra)* |
| 0  | Sair |

## Organização dos arquivos
| Arquivo | Responsabilidade |
|---------|------------------|
| `atendimento.h/.c` | TAD do atendimento (struct e operações básicas) |
| `fila.h/.c` | Fila dinâmica (ordem de atendimento) |
| `lista.h/.c` | Lista encadeada (histórico de atendimentos) |
| `arvore.h/.c` | Árvore binária de busca (busca por ID) |
| `hash.h/.c` | Tabela hash (busca/agrupamento por categoria) |
| `ordenacao.h/.c` | Ordenação do histórico (Bubble Sort) |
| `estatisticas.h/.c` | Estatísticas do sistema |
| `main.c` | Menu e integração das estruturas |

## Explicação técnica das estruturas

**Gerência de memória (propriedade dos atendimentos).** Cada atendimento é
alocado uma única vez no cadastro e referenciado simultaneamente pela fila, pela
lista, pela árvore e pela hash. A **lista (histórico) é a dona** da memória: no
encerramento, a árvore, a hash e a fila liberam apenas os seus próprios nós,
enquanto a lista libera os nós **e** os atendimentos. Assim cada atendimento é
liberado exatamente uma vez, sem vazamentos e sem *double-free*.

**Fila Dinâmica (`fila.c`)** — fila encadeada com ponteiros para o início e o
fim. Operações de enfileirar e desenfileirar em **O(1)**. É a estrutura ideal
para respeitar a ordem de chegada (FIFO) dos atendimentos.

**Lista Encadeada (`lista.c`)** — guarda o histórico de todos os atendimentos
cadastrados. Inserção no início em **O(1)** e crescimento dinâmico (sem tamanho
fixo). É percorrida sequencialmente nas buscas por cliente e por prioridade.

**Árvore Binária de Busca (`arvore.c`)** — indexa os atendimentos pelo `id`.
A busca aproveita a ordenação da árvore (IDs menores à esquerda, maiores à
direita), alcançando tempo médio **O(log n)** — muito mais rápido que a busca
sequencial **O(n)** da lista quando há muitos atendimentos.

**Tabela Hash (`hash.c`)** — agrupa os atendimentos por `categoria` usando a
função de hash *djb2* e **encadeamento separado** para tratar colisões. A busca
por categoria fica próxima de **O(1)** no caso médio. A mesma estrutura permite
descobrir a categoria com mais atendimentos.

**Ordenação (`ordenacao.c`)** — Bubble Sort implementado pela equipe sobre a
lista do histórico, trocando os ponteiros de atendimento entre os nós. Ordena
por prioridade (da mais alta para a mais baixa) e por tempo estimado (do menor
para o maior) sem afetar a árvore nem a hash.

## Divisão de Responsabilidades
- **Juan Carlos**: TAD Atendimento, Fila Dinâmica, Menu Principal e Estatísticas.
- **Gabriel Blank**: Lista Encadeada (Histórico), Ordenação, Árvore Binária e Tabela Hash.

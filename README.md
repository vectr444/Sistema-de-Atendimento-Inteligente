# Sistema de Atendimento Inteligente

Projeto desenvolvido para a disciplina de Estruturas de Dados | Linguagem C.

## Integrantes
- Juan Carlos
- Gabriel Blank

## Descrição
Sistema de terminal para controlar os atendimentos técnicos de uma empresa.
Utiliza estruturas de dados como Fila Dinâmica, Lista Encadeada, Árvore Binária de Busca e Tabela Hash.

## Como compilar e executar

Para compilar:
```bash
gcc main.c atendimento.c fila.c estatisticas.c -o sistema
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

## Divisão de Responsabilidades
- **Juan Carlos**: TAD Atendimento, Fila Dinâmica, Menu Principal e Estatísticas.
- **Gabriel Blank**: Lista Encadeada (Histórico), Ordenação, Árvore Binária e Tabela Hash.

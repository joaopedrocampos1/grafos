#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "grafo_lista.h"

typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha *criar_pilha(int capacidade);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);
int pilha_vazia(Pilha *p);
void destruir_pilha(Pilha *p);

void dfs_recursiva(GrafoLista *g, int u, int *visitado,
                   int *entrada, int *saida, int *tempo);

void dfs_iterativa(GrafoLista *g, int origem, int *visitado);

int tem_ciclo(GrafoLista *g);

#endif

#include <stdio.h>
#include <stdlib.h>
#include "busca_profundidade.h"

Pilha *criar_pilha(int capacidade) {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->dados = (int *)malloc(sizeof(int) * capacidade);
    p->capacidade = capacidade;
    p->topo = -1;             
    return p;
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}
void empilhar(Pilha *p, int v) {
    p->topo++;
    p->dados[p->topo] = v;
}
int desempilhar(Pilha *p) {
    int v = p->dados[p->topo];
    p->topo--;
    return v;
}
void destruir_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

void dfs_recursiva(GrafoLista *g, int u, int *visitado,
                   int *entrada, int *saida, int *tempo) {
    visitado[u] = 1;
    entrada[u] = ++(*tempo);
    printf("  Empilha %i (entrada = %i)\n", u + 1, entrada[u]);

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        if (!visitado[no->vertice]) {
            dfs_recursiva(g, no->vertice, visitado, entrada, saida, tempo);
        }
    }

    saida[u] = ++(*tempo);
    printf("  Desempilha %i (saida = %i)\n", u + 1, saida[u]);
}
void dfs_iterativa(GrafoLista *g, int origem, int *visitado) {
    Pilha *p = criar_pilha(g->num_vertices);

    visitado[origem] = 1;
    empilhar(p, origem);

    while (!pilha_vazia(p)) {
        int u = desempilhar(p);
        printf("  Visita %i\n", u + 1);

        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            if (!visitado[v]) {
                visitado[v] = 1;
                empilhar(p, v);
            }
        }
    }
    destruir_pilha(p);
}

static int ciclo_dfs(GrafoLista *g, int u, int pai, int *visitado) {
    visitado[u] = 1;

    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;
        if (!visitado[v]) {
            if (ciclo_dfs(g, v, u, visitado)) return 1;
        } else if (v != pai) {
            return 1;              
        }
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int n = g->num_vertices;
    int visitado[n];
    for (int i = 0; i < n; i++) visitado[i] = 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i] && ciclo_dfs(g, i, -1, visitado)) return 1;
    }
    return 0;
}

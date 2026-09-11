#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"

Fila *criar_fila(int capacidade) {
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->dados = (int *)malloc(sizeof(int) * capacidade);
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}
int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}
void enfileirar(Fila *f, int v) {
    f->dados[f->fim] = v;
    f->fim = (f->fim + 1) % f->capacidade; 
    f->tamanho++;
}
int desenfileirar(Fila *f) {
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}
void destruir_fila(Fila *f) {
    free(f->dados);
    free(f);
}
void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->num_vertices);
    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);
        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            if (dist[v] == -1) {       
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
        }
    }
    destruir_fila(f);
}
void imprimir_caminho(int *pred, int destino) {
    if (pred[destino] != -1) {
        imprimir_caminho(pred, pred[destino]);
        printf(" -> ");
    }
    printf("%i", destino + 1);
}
int contar_componentes(GrafoLista *g) {
    int n = g->num_vertices;
    int dist[n], pred[n], visitado[n];
    for (int i = 0; i < n; i++) visitado[i] = 0;

    int componentes = 0;
    for (int i = 0; i < n; i++) {
        if (visitado[i]) continue;

        componentes++;
        bfs(g, i, dist, pred);
        for (int v = 0; v < n; v++) {
            if (dist[v] != -1) visitado[v] = 1;
        }
    }
    return componentes;
}
int eh_bipartido(GrafoLista *g) {
    int n = g->num_vertices;
    int cor[n];
    for (int i = 0; i < n; i++) cor[i] = -1;

    Fila *f = criar_fila(n);

    for (int i = 0; i < n; i++) {
        if (cor[i] != -1) continue;

        cor[i] = 0;                
        enfileirar(f, i);

        while (!fila_vazia(f)) {
            int u = desenfileirar(f);
            for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
                int v = no->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                } else if (cor[v] == cor[u]) {
                    destruir_fila(f);
                    return 0;
                }
            }
        }
    }

    destruir_fila(f);
    return 1;
}

#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No *) * n);
    for (int i = 0; i < n; i++) {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = NULL;

    if (g->lista[u] == NULL) {
        g->lista[u] = no;
        return;
    }

    No *atual = g->lista[u];
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }
    atual->proximo = no;
}

void liberar_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista[i];
        while (atual != NULL) {
            No *proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
    }
    free(g->lista);
    free(g);
}

void imprimir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        printf("  %d ->", i + 1);
        for (No *atual = g->lista[i]; atual != NULL; atual = atual->proximo) {
            printf(" %d", atual->vertice + 1);
        }
        printf("\n");
    }
}

void calcular_graus_entrada(GrafoLista *g, int *grau_entrada) {
    for (int i = 0; i < g->num_vertices; i++) {
        grau_entrada[i] = 0;
    }
    for (int u = 0; u < g->num_vertices; u++) {
        for (No *atual = g->lista[u]; atual != NULL; atual = atual->proximo) {
            grau_entrada[atual->vertice]++;
        }
    }
}

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *grau_entrada = (int *)malloc(sizeof(int) * n);
    int *ordem = (int *)malloc(sizeof(int) * n);
    int *fila = (int *)malloc(sizeof(int) * n);
    int inicio = 0, fim = 0, visitados = 0;

    calcular_graus_entrada(g, grau_entrada);

    for (int v = 0; v < n; v++) {
        if (grau_entrada[v] == 0) {
            fila[fim++] = v;
        }
    }

    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[visitados++] = u;

        for (No *atual = g->lista[u]; atual != NULL; atual = atual->proximo) {
            int v = atual->vertice;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
        }
    }

    free(grau_entrada);
    free(fila);

    if (visitados != n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    *tamanho = n;
    return ordem;
}

static int visitar(GrafoLista *g, int u, int *cor, int *pilha, int *topo) {
    cor[u] = 1;

    for (No *atual = g->lista[u]; atual != NULL; atual = atual->proximo) {
        int v = atual->vertice;
        if (cor[v] == 1) {
            return 1;
        }
        if (cor[v] == 0 && visitar(g, v, cor, pilha, topo)) {
            return 1;
        }
    }

    cor[u] = 2;
    pilha[(*topo)++] = u; /* empilha na SAIDA da recursao */
    return 0;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    int n = g->num_vertices;
    int *cor = (int *)calloc(n, sizeof(int));
    int *pilha = (int *)malloc(sizeof(int) * n);
    int topo = 0;
    int tem_ciclo = 0;

    for (int v = 0; v < n && !tem_ciclo; v++) {
        if (cor[v] == 0) {
            tem_ciclo = visitar(g, v, cor, pilha, &topo);
        }
    }
    free(cor);

    if (tem_ciclo) {
        free(pilha);
        *tamanho = 0;
        return NULL;
    }

    int *ordem = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        ordem[i] = pilha[n - 1 - i];
    }
    free(pilha);
    *tamanho = n;
    return ordem;
}

int eh_dag(GrafoLista *g) {
    int n = g->num_vertices;
    int *cor = (int *)calloc(n, sizeof(int));
    int *pilha = (int *)malloc(sizeof(int) * n);
    int topo = 0;
    int tem_ciclo = 0;

    for (int v = 0; v < n && !tem_ciclo; v++) {
        if (cor[v] == 0) {
            tem_ciclo = visitar(g, v, cor, pilha, &topo);
        }
    }
    free(cor);
    free(pilha);
    return !tem_ciclo;
}

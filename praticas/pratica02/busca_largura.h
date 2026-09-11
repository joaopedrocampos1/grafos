#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include "grafo_lista.h"
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila *criar_fila(int capacidade);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);
int fila_vazia(Fila *f);
void destruir_fila(Fila *f);
void bfs(GrafoLista *g, int origem, int *dist, int *pred);
void imprimir_caminho(int *pred, int destino);
int contar_componentes(GrafoLista *g);
int eh_bipartido(GrafoLista *g);

#endif

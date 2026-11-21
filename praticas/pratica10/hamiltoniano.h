#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

#define MAX_VERTICES 15

// adjacencia[u][v] guarda o peso da aresta, ou 0 se ela não existe
typedef struct {
    int adjacencia[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} GrafoMatriz;

void inicializar(GrafoMatriz *g, int n);
void inserir_aresta(GrafoMatriz *g, int u, int v, int peso);
void exibir_matriz(GrafoMatriz *g);

// Preenche caminho[] com um caminho que passa uma vez por cada vértice.
// Retorna 1 se encontrou ou 0 se não existe.
int encontrar_caminho_hamiltoniano_bt(GrafoMatriz *g, int *caminho);

// Igual ao caminho, mas o último vértice também precisa voltar ao primeiro.
int encontrar_ciclo_hamiltoniano_bt(GrafoMatriz *g, int *ciclo);

#endif

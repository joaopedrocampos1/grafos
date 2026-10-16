#ifndef DAG_H
#define DAG_H


typedef struct No
{
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    No **lista;
    int num_vertices;
} GrafoLista;

GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v); 
void liberar_grafo(GrafoLista *g);
void imprimir_grafo(GrafoLista *g);

void calcular_graus_entrada(GrafoLista *g, int *grau_entrada);

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

int eh_dag(GrafoLista *g);

#endif

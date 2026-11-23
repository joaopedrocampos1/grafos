#include <stdio.h>
#include <string.h>
#include "hamiltoniano.h"

void inicializar(GrafoMatriz *g, int n)
{
    memset(g, 0, sizeof(GrafoMatriz));
    g->num_vertices = n;
}

void inserir_aresta(GrafoMatriz *g, int u, int v, int peso)
{
    g->adjacencia[u][v] = peso;
    g->adjacencia[v][u] = peso;
}

void exibir_matriz(GrafoMatriz *g)
{
    printf("   ");
    for (int j = 0; j < g->num_vertices; j++)
    {
        printf("%3c", 'A' + j);
    }
    printf("\n");

    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%3c", 'A' + i);
        for (int j = 0; j < g->num_vertices; j++)
        {
            printf("%3i", g->adjacencia[i][j]);
        }
        printf("\n");
    }
}

// verificador do slide da Aula 10: confere uma resposta em tempo polinomial
int eh_caminho_hamiltoniano(GrafoMatriz *g, int *caminho)
{
    int n = g->num_vertices;
    int visitado[MAX_VERTICES] = {0};

    // verifica se todos os vértices aparecem exatamente uma vez
    for (int i = 0; i < n; i++)
    {
        int v = caminho[i];
        if (v < 0 || v >= n || visitado[v])
            return 0;
        visitado[v] = 1;
    }

    // verifica se existem arestas entre vértices consecutivos
    for (int i = 0; i < n - 1; i++)
    {
        int u = caminho[i];
        int v = caminho[i + 1];
        if (g->adjacencia[u][v] == 0)
            return 0;
    }

    return 1;
}

// caminho[0..pos-1] já está montado; tenta colocar na posição pos cada
// vizinho ainda não visitado do último vértice e desfaz se não der certo
int estender(GrafoMatriz *g, int *caminho, int *visitado, int pos, int fechar_ciclo)
{
    int n = g->num_vertices;

    if (pos == n)
        return !fechar_ciclo || g->adjacencia[caminho[n - 1]][caminho[0]];

    int ultimo = caminho[pos - 1];
    for (int v = 0; v < n; v++)
    {
        if (!visitado[v] && g->adjacencia[ultimo][v])
        {
            caminho[pos] = v;
            visitado[v] = 1;
            if (estender(g, caminho, visitado, pos + 1, fechar_ciclo))
                return 1;
            visitado[v] = 0;
        }
    }

    return 0;
}

int encontrar_caminho_hamiltoniano_bt(GrafoMatriz *g, int *caminho)
{
    int visitado[MAX_VERTICES] = {0};

    // o caminho pode começar em qualquer vértice
    for (int inicio = 0; inicio < g->num_vertices; inicio++)
    {
        caminho[0] = inicio;
        visitado[inicio] = 1;
        if (estender(g, caminho, visitado, 1, 0))
            return 1;
        visitado[inicio] = 0;
    }

    return 0;
}

int encontrar_ciclo_hamiltoniano_bt(GrafoMatriz *g, int *ciclo)
{
    int visitado[MAX_VERTICES] = {0};

    // um ciclo passa por todos os vértices, então basta começar no A
    ciclo[0] = 0;
    visitado[0] = 1;
    return estender(g, ciclo, visitado, 1, 1);
}

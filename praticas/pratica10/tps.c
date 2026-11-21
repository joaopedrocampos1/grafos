#include <limits.h>
#include "tps.h"

int custo_rota(GrafoMatriz *g, int *rota)
{
    int n = g->num_vertices;
    int custo = 0;
    for (int i = 0; i < n; i++)
    {
        custo += g->adjacencia[rota[i]][rota[(i + 1) % n]];
    }
    return custo;
}

// gera as permutações de atual[k..n-1] trocando cada candidato para a posição k;
// custo é o que já foi gasto de atual[0] até atual[k-1]
void permutar(GrafoMatriz *g, int *atual, int k, int custo, int *melhor, int *custo_melhor)
{
    int n = g->num_vertices;

    if (k == n)
    {
        custo += g->adjacencia[atual[n - 1]][atual[0]]; // volta para a origem
        if (custo < *custo_melhor)
        {
            *custo_melhor = custo;
            for (int i = 0; i < n; i++)
            {
                melhor[i] = atual[i];
            }
        }
        return;
    }

    for (int i = k; i < n; i++)
    {
        int aux = atual[k];
        atual[k] = atual[i];
        atual[i] = aux;

        permutar(g, atual, k + 1, custo + g->adjacencia[atual[k - 1]][atual[k]], melhor, custo_melhor);

        aux = atual[k];
        atual[k] = atual[i];
        atual[i] = aux;
    }
}

int tsp_forca_bruta(GrafoMatriz *g, int *rota)
{
    int atual[MAX_VERTICES];
    for (int i = 0; i < g->num_vertices; i++)
    {
        atual[i] = i;
    }

    // atual[0] = 0 nunca sai do lugar: a origem fica fixa
    int custo_melhor = INT_MAX;
    permutar(g, atual, 1, 0, rota, &custo_melhor);
    return custo_melhor;
}

int tsp_vizinho_mais_proximo(GrafoMatriz *g, int origem, int *rota)
{
    int n = g->num_vertices;
    int visitado[MAX_VERTICES] = {0};

    rota[0] = origem;
    visitado[origem] = 1;

    for (int i = 1; i < n; i++)
    {
        int atual = rota[i - 1];
        int proximo = -1;
        for (int v = 0; v < n; v++)
        {
            if (!visitado[v] && (proximo == -1 || g->adjacencia[atual][v] < g->adjacencia[atual][proximo]))
                proximo = v;
        }
        rota[i] = proximo;
        visitado[proximo] = 1;
    }

    return custo_rota(g, rota);
}

int tsp_insercao(GrafoMatriz *g, int *rota)
{
    int n = g->num_vertices;
    int no_ciclo[MAX_VERTICES] = {0};

    // ciclo inicial: o vértice 0 e o vizinho mais próximo dele
    int mais_proximo = 1;
    for (int v = 2; v < n; v++)
    {
        if (g->adjacencia[0][v] < g->adjacencia[0][mais_proximo])
            mais_proximo = v;
    }
    rota[0] = 0;
    rota[1] = mais_proximo;
    no_ciclo[0] = 1;
    no_ciclo[mais_proximo] = 1;
    int tamanho = 2;

    while (tamanho < n)
    {
        // escolhe o vértice fora do ciclo que está mais perto de algum vértice do ciclo
        int k = -1;
        int menor_distancia = 0;
        for (int v = 0; v < n; v++)
        {
            if (no_ciclo[v])
                continue;
            for (int i = 0; i < tamanho; i++)
            {
                int d = g->adjacencia[rota[i]][v];
                if (k == -1 || d < menor_distancia)
                {
                    k = v;
                    menor_distancia = d;
                }
            }
        }

        // insere k entre rota[i] e rota[i+1] onde o aumento de custo for menor
        int posicao = 0;
        int menor_aumento = 0;
        for (int i = 0; i < tamanho; i++)
        {
            int a = rota[i];
            int b = rota[(i + 1) % tamanho];
            int aumento = g->adjacencia[a][k] + g->adjacencia[k][b] - g->adjacencia[a][b];
            if (i == 0 || aumento < menor_aumento)
            {
                posicao = i;
                menor_aumento = aumento;
            }
        }

        for (int i = tamanho; i > posicao + 1; i--)
        {
            rota[i] = rota[i - 1];
        }
        rota[posicao + 1] = k;
        no_ciclo[k] = 1;
        tamanho++;
    }

    return custo_rota(g, rota);
}

void grafo_para_tsp(GrafoMatriz *g, GrafoMatriz *tsp)
{
    int n = g->num_vertices;
    inicializar(tsp, n);

    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (u != v)
                tsp->adjacencia[u][v] = g->adjacencia[u][v] ? 1 : 2;
        }
    }
}

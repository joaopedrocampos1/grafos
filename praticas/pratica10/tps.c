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

// estado da busca, como no slide da Aula 10
int melhor_custo;
int melhor_rota[MAX_VERTICES];
int rota_atual[MAX_VERTICES];
int usado[MAX_VERTICES];

// rota_atual[0..pos-1] já está escolhida e custa custo_atual;
// tenta cada cidade ainda não usada na posição pos
void tsp(GrafoMatriz *g, int n, int pos, int custo_atual, int origem)
{
    if (pos == n)
    {
        int custo_total = custo_atual + g->adjacencia[rota_atual[pos - 1]][origem];
        if (custo_total < melhor_custo)
        {
            melhor_custo = custo_total;
            for (int i = 0; i < n; i++)
            {
                melhor_rota[i] = rota_atual[i];
            }
        }
        return;
    }

    for (int cidade = 0; cidade < n; cidade++)
    {
        if (!usado[cidade])
        {
            usado[cidade] = 1;
            rota_atual[pos] = cidade;
            int novo_custo = custo_atual + g->adjacencia[rota_atual[pos - 1]][cidade];
            tsp(g, n, pos + 1, novo_custo, origem);
            usado[cidade] = 0;
        }
    }
}

int tsp_forca_bruta(GrafoMatriz *g, int *rota)
{
    int n = g->num_vertices;
    for (int i = 0; i < n; i++)
    {
        usado[i] = 0;
    }
    melhor_custo = INT_MAX;

    // a origem (vértice 0) já começa na posição 0, então só as outras n-1
    // cidades são permutadas: (n-1)! rotas em vez de n!
    rota_atual[0] = 0;
    usado[0] = 1;
    tsp(g, n, 1, 0, 0);

    for (int i = 0; i < n; i++)
    {
        rota[i] = melhor_rota[i];
    }
    return melhor_custo;
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

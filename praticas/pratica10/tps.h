#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

// Nas funções do TSP o grafo é completo: adjacencia[u][v] é o custo de ir de u a v.
// Todas preenchem rota[] com a ordem de visita e retornam o custo, já contando
// a volta do último vértice para o primeiro.

// Soma o custo de percorrer rota[] e voltar ao início.
int custo_rota(GrafoMatriz *g, int *rota);

// Testa as (n-1)! ordens possíveis com o vértice 0 fixo como origem.
int tsp_forca_bruta(GrafoMatriz *g, int *rota);

// Sai da origem e vai sempre para o vértice mais próximo ainda não visitado.
int tsp_vizinho_mais_proximo(GrafoMatriz *g, int origem, int *rota);

// Começa com um ciclo de 2 vértices e insere, a cada passo, o vértice mais
// próximo do ciclo no ponto onde ele aumenta menos o custo.
int tsp_insercao(GrafoMatriz *g, int *rota);

// Redução de Ciclo Hamiltoniano para TSP: custo 1 onde existe aresta e 2 onde
// não existe. O grafo tem ciclo hamiltoniano se e só se o TSP custa n.
void grafo_para_tsp(GrafoMatriz *g, GrafoMatriz *tsp);

#endif

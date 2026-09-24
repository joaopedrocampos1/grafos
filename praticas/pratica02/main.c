#include <stdio.h>
#include "grafo_lista.h"
#include "busca_largura.h"
#include "busca_profundidade.h"

static void analisar(const char *titulo, GrafoLista *g, int origem) {
    int n = g->num_vertices;

    printf("================================================\n");
    printf(" %s\n", titulo);
    printf("================================================\n");

    printf("\nLista de adjacencia:\n");
    exibir_grafo(g);

    // ---- BFS ----
    int dist[n], pred[n];
    bfs(g, origem, dist, pred);

    printf("\nBFS a partir do vertice %i:\n", origem + 1);
    for (int v = 0; v < n; v++) {
        if (dist[v] == -1) {
            printf("  vertice %i: inalcancavel\n", v + 1);
        } else {
            printf("  vertice %i: dist = %i, pred = ", v + 1, dist[v]);
            if (pred[v] == -1) printf("- ");
            else printf("%i ", pred[v] + 1);
            printf("| caminho: ");
            imprimir_caminho(pred, v);
            printf("\n");
        }
    }
    int visitado[n], entrada[n], saida[n];
    for (int v = 0; v < n; v++) {
        visitado[v] = 0;
        entrada[v] = 0;
        saida[v] = 0;
    }
    int tempo = 0;
    printf("\nDFS recursiva a partir do vertice %i:\n", origem + 1);
    dfs_recursiva(g, origem, visitado, entrada, saida, &tempo);
    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            printf("  -- novo componente, reinicia em %i --\n", v + 1);
            dfs_recursiva(g, v, visitado, entrada, saida, &tempo);
        }
    }
    printf("\nTempos de entrada/saida:\n");
    for (int v = 0; v < n; v++) {
        printf("  vertice %i: entrada = %i, saida = %i\n",
               v + 1, entrada[v], saida[v]);
    }
    for (int v = 0; v < n; v++) visitado[v] = 0;
    printf("\nDFS iterativa (pilha) a partir do vertice %i:\n", origem + 1);
    dfs_iterativa(g, origem, visitado);
    printf("\nPropriedades:\n");
    printf("  componentes conexos : %i\n", contar_componentes(g));
    printf("  possui ciclo        : %s\n", tem_ciclo(g) ? "sim" : "nao");
    printf("  e bipartido         : %s\n", eh_bipartido(g) ? "sim" : "nao");
    printf("\n");
}
int main(void) {
    GrafoLista *g1 = criar_grafo(5);
    adicionar_aresta(g1, 0, 1);
    adicionar_aresta(g1, 0, 2);
    adicionar_aresta(g1, 1, 3);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 4);
    analisar("G1 - grafo da aula 03 (5 vertices)", g1, 0);
    liberar_grafo(g1);
    GrafoLista *g2 = criar_grafo(4);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 3);
    adicionar_aresta(g2, 3, 0);
    analisar("G2 - ciclo par C4 (bipartido)", g2, 0);
    liberar_grafo(g2);
    GrafoLista *g3 = criar_grafo(3);
    adicionar_aresta(g3, 0, 1);
    adicionar_aresta(g3, 1, 2);
    adicionar_aresta(g3, 2, 0);
    analisar("G3 - triangulo C3 (nao bipartido)", g3, 0);
    liberar_grafo(g3);
    GrafoLista *g4 = criar_grafo(6);
    adicionar_aresta(g4, 0, 1);
    adicionar_aresta(g4, 1, 2);
    adicionar_aresta(g4, 3, 4);
    adicionar_aresta(g4, 4, 5);
    analisar("G4 - duas arvores (2 componentes, sem ciclo)", g4, 0);
    liberar_grafo(g4);

    return 0;
}

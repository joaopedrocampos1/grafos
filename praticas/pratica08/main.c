#include <stdio.h>
#include "agm.h"

int main()
{
    // grafo de aulas/aula04/grafo_kruskal.dot e grafo_prim.dot (A=0 ... E=4)
    GrafoListaPonderado *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 1, 2, 1); // B - C
    adicionar_aresta(grafo, 0, 1, 2); // A - B
    adicionar_aresta(grafo, 0, 2, 3); // A - C
    adicionar_aresta(grafo, 1, 3, 4); // B - D
    adicionar_aresta(grafo, 2, 3, 5); // C - D
    adicionar_aresta(grafo, 3, 4, 6); // D - E
    adicionar_aresta(grafo, 2, 4, 7); // C - E

    printf("Grafo ponderado\n");
    imprimir_grafo(grafo);

    Aresta agm[4];
    int total = kruskal(grafo, agm);

    printf("Kruskal\n");
    for (int i = 0; i < grafo->num_vertices - 1; i++)
    {
        printf("%c - %c (%i)\n", 'A' + agm[i].u, 'A' + agm[i].v, agm[i].peso);
    }
    printf("Peso total = %i\n\n", total);

    int pred[5];
    total = prim(grafo, 0, pred);

    printf("Prim a partir de A\n");
    for (int v = 0; v < grafo->num_vertices; v++)
    {
        if (pred[v] != -1)
            printf("%c - %c\n", 'A' + pred[v], 'A' + v);
    }
    printf("Peso total = %i\n", total);

    return 0;
}

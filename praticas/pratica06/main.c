#include <stdio.h>
#include "dijkstra.h"

int main()
{
    // grafo de aulas/aula04/grafo_dijkstra.dot (A=0, B=1, C=2, D=3)
    GrafoListaPonderado *digrafo = criar_grafo(4);

    adicionar_arco(digrafo, 0, 1, 4);
    adicionar_arco(digrafo, 0, 2, 1);
    adicionar_arco(digrafo, 1, 3, 1);
    adicionar_arco(digrafo, 2, 1, 2);
    adicionar_arco(digrafo, 2, 3, 5);

    printf("Digrafo ponderado\n");
    imprimir_grafo(digrafo);

    int dist[4];
    int pred[4];
    dijkstra(digrafo, 0, dist, pred);

    printf("Dijkstra a partir de A\n");
    for (int v = 0; v < digrafo->num_vertices; v++)
    {
        printf("A ate %c: distancia %i, caminho ", 'A' + v, dist[v]);
        reconstruir_caminho(0, v, pred);
        printf("\n");
    }
    printf("\n");

    // grafo não orientado de aulas/aula04/grafo_prim.dot (A=0 ... E=4)
    GrafoListaPonderado *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1, 2);
    adicionar_aresta(grafo, 0, 2, 3);
    adicionar_aresta(grafo, 1, 2, 1);
    adicionar_aresta(grafo, 1, 3, 4);
    adicionar_aresta(grafo, 2, 3, 5);
    adicionar_aresta(grafo, 2, 4, 7);
    adicionar_aresta(grafo, 3, 4, 6);

    printf("Grafo ponderado nao orientado\n");
    imprimir_grafo(grafo);

    int dist2[5];
    int pred2[5];
    dijkstra(grafo, 0, dist2, pred2);

    printf("Menor caminho de A ate E: distancia %i, caminho ", dist2[4]);
    reconstruir_caminho(0, 4, pred2);
    printf("\n\n");

    // vértice isolado não é alcançado
    GrafoListaPonderado *desconexo = criar_grafo(3);
    adicionar_aresta(desconexo, 0, 1, 2);

    int dist3[3];
    int pred3[3];
    dijkstra(desconexo, 0, dist3, pred3);

    printf("Grafo desconexo\n");
    printf("A ate C: ");
    reconstruir_caminho(0, 2, pred3);
    printf("\n");

    return 0;
}

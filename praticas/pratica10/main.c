#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hamiltoniano.h"
#include "tps.h"

void imprimir_rota(int *rota, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c -> ", 'A' + rota[i]);
    }
    printf("%c", 'A' + rota[0]);
}

// grafo completo com custos aleatórios de 1 a 100
void gerar_grafo_completo(GrafoMatriz *g, int n)
{
    inicializar(g, n);
    for (int u = 0; u < n; u++)
    {
        for (int v = u + 1; v < n; v++)
        {
            inserir_aresta(g, u, v, 1 + rand() % 100);
        }
    }
}

void experimento(int n)
{
    GrafoMatriz g;
    gerar_grafo_completo(&g, n);
    int rota[MAX_VERTICES];

    clock_t inicio = clock();
    int custo_fb = tsp_forca_bruta(&g, rota);
    double tempo_fb = (double)(clock() - inicio) * 1000 / CLOCKS_PER_SEC;

    inicio = clock();
    int custo_vmp = tsp_vizinho_mais_proximo(&g, 0, rota);
    double tempo_vmp = (double)(clock() - inicio) * 1000 / CLOCKS_PER_SEC;

    inicio = clock();
    int custo_ins = tsp_insercao(&g, rota);
    double tempo_ins = (double)(clock() - inicio) * 1000 / CLOCKS_PER_SEC;

    printf("%2i | %4i %11.3f | %4i %8.3f | %4i %8.3f\n",
           n, custo_fb, tempo_fb, custo_vmp, tempo_vmp, custo_ins, tempo_ins);
}

int main()
{
    // grafo de grafo.dot das práticas anteriores (A=0, B=1, C=2, D=3, E=4, F=5)
    GrafoMatriz grafo;
    inicializar(&grafo, 6);

    inserir_aresta(&grafo, 0, 1, 4);  // A - B
    inserir_aresta(&grafo, 0, 2, 2);  // A - C
    inserir_aresta(&grafo, 1, 2, 1);  // B - C
    inserir_aresta(&grafo, 1, 3, 5);  // B - D
    inserir_aresta(&grafo, 1, 4, 8);  // B - E
    inserir_aresta(&grafo, 2, 3, 4);  // C - D
    inserir_aresta(&grafo, 2, 4, 10); // C - E
    inserir_aresta(&grafo, 3, 4, 2);  // D - E
    inserir_aresta(&grafo, 3, 5, 1);  // D - F
    inserir_aresta(&grafo, 4, 5, 3);  // E - F

    printf("Grafo (0 = sem aresta)\n");
    exibir_matriz(&grafo);
    printf("\n");

    int caminho[MAX_VERTICES];
    printf("Caminho hamiltoniano: ");
    if (encontrar_caminho_hamiltoniano_bt(&grafo, caminho))
    {
        for (int i = 0; i < grafo.num_vertices; i++)
        {
            printf("%c ", 'A' + caminho[i]);
        }
        printf("\n");
    }
    else
    {
        printf("nao existe\n");
    }

    printf("Ciclo hamiltoniano: ");
    if (encontrar_ciclo_hamiltoniano_bt(&grafo, caminho))
    {
        imprimir_rota(caminho, grafo.num_vertices);
        printf("\n");
    }
    else
    {
        printf("nao existe\n");
    }
    printf("\n");

    // caminho A - B - C - D: tem caminho hamiltoniano, mas não tem ciclo
    GrafoMatriz linha;
    inicializar(&linha, 4);
    inserir_aresta(&linha, 0, 1, 1);
    inserir_aresta(&linha, 1, 2, 1);
    inserir_aresta(&linha, 2, 3, 1);

    printf("Grafo A - B - C - D\n");
    printf("Caminho hamiltoniano: %s\n", encontrar_caminho_hamiltoniano_bt(&linha, caminho) ? "existe" : "nao existe");
    printf("Ciclo hamiltoniano: %s\n\n", encontrar_ciclo_hamiltoniano_bt(&linha, caminho) ? "existe" : "nao existe");

    // redução: o grafo tem ciclo hamiltoniano se o TSP custar n
    GrafoMatriz tsp;
    int rota[MAX_VERTICES];

    grafo_para_tsp(&grafo, &tsp);
    int custo = tsp_forca_bruta(&tsp, rota);
    printf("TSP do grafo reduzido (1 = aresta, 2 = sem aresta)\n");
    exibir_matriz(&tsp);
    printf("Forca bruta: custo %i, rota ", custo);
    imprimir_rota(rota, tsp.num_vertices);
    printf("\n");
    printf("Custo %s n = %i, entao o grafo %s ciclo hamiltoniano\n\n",
           custo == tsp.num_vertices ? "==" : "!=", tsp.num_vertices,
           custo == tsp.num_vertices ? "tem" : "nao tem");

    grafo_para_tsp(&linha, &tsp);
    custo = tsp_forca_bruta(&tsp, rota);
    printf("TSP do grafo A - B - C - D reduzido: custo %i, n = %i, entao %s ciclo hamiltoniano\n\n",
           custo, tsp.num_vertices, custo == tsp.num_vertices ? "tem" : "nao tem");

    // semente fixa para o experimento dar os mesmos grafos a cada execução
    srand(42);

    printf("Experimento com grafos completos aleatorios (custo e tempo em ms)\n");
    printf(" n |    forca bruta   | vizinho proximo |   insercao\n");
    printf("   | custo      tempo | custo     tempo | custo    tempo\n");
    int tamanhos[] = {5, 8, 10, 12};
    for (int i = 0; i < 4; i++)
    {
        experimento(tamanhos[i]);
    }

    return 0;
}

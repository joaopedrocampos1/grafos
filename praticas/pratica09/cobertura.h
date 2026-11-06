#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct {
    int u;
    int v;
} Aresta;

// Retorna 1 se toda aresta tem ao menos uma ponta em cobertura[] ou 0 caso contrário.
int eh_cobertura(Aresta *a, int *cobertura, int m);

// Preenche melhor[] com uma cobertura mínima e retorna o tamanho dela.
int cobertura_minima_bt(Aresta *a, int m, int n, int *melhor);

// Preenche cobertura[] escolhendo sempre o vértice de maior grau restante e
// retorna o tamanho. A resposta é válida, mas pode não ser a mínima.
int cobertura_gulosa(Aresta *a, int m, int n, int *cobertura);

#endif

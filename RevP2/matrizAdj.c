#include <stdio.h>
#include <stdlib.h>

typedef struct tipoItem {
  int valor;
  int indice;
} tipoItem;

typedef struct tipoLista {
  tipoItem *vertices;
  int qtd;
} tipoLista;

typedef struct TipoGrafo {
  tipoLista lista;
  int **adj; // Matriz de adjacência
} TipoGrafo;

void inicializaGrafo(TipoGrafo *grafo, int numVertices) {
  grafo->lista.vertices = (tipoItem *)malloc(numVertices * sizeof(tipoItem));
  grafo->lista.qtd = 0;

  grafo->adj = (int **)malloc(numVertices * sizeof(int *));
  for (int i = 0; i < numVertices; i++) {
    grafo->adj[i] = (int *)malloc(numVertices * sizeof(int));
    for (int j = 0; j < numVertices; j++) {
      grafo->adj[i][j] = 0; // Inicializa a matriz de adjacência com zeros
    }
  }
}

void insereAresta(TipoGrafo *grafo, int peso, int vert1, int vert2) {
  tipoLista *lista = &(grafo->lista);
  int n = -1, m = -1;
  for (int i = 0; i < lista->qtd; i++) {
    if (lista->vertices[i].valor == vert1)
      n = i;
    if (lista->vertices[i].valor == vert2)
      m = i;
  }
  if (n == -1) {
    tipoItem *vertice1 = (tipoItem *)malloc(sizeof(tipoItem));
    vertice1->valor = vert1;
    vertice1->indice = lista->qtd;
    n = vertice1->indice;
    lista->vertices[lista->qtd] = *vertice1;
    lista->qtd++;
  }
  if (m == -1) {
    tipoItem *vertice2 = (tipoItem *)malloc(sizeof(tipoItem));
    vertice2->valor = vert2;
    vertice2->indice = lista->qtd;
    m = vertice2->indice;
    lista->vertices[lista->qtd] = *vertice2;
    lista->qtd++;
  }
  grafo->adj[n][m] = peso;
}

int main() {
  TipoGrafo grafo;
  int numVertices = 5;
  inicializaGrafo(&grafo, numVertices);

  insereAresta(&grafo, 1, 0, 1);
  insereAresta(&grafo, 2, 1, 2);
  insereAresta(&grafo, 3, 2, 3);


  for (int i = 0; i < numVertices; i++) {
    free(grafo.adj[i]);
  }
  free(grafo.adj);
  free(grafo.lista.vertices);

  return 0;
}

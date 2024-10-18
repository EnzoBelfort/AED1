#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *prox;
}tipoNo;

typedef struct tipoGrafo{
  tipoNo **lista_adj;
  int V;
}tipoGrafo;


void inicializaGrafo(tipoGrafo* grafo, int V){
  grafo->lista_adj = (tipoNo**)malloc(V*sizeof(tipoNo*));
  for(int i=0; i<V; i++){
    grafo->lista_adj[i] = (tipoNo*)malloc(sizeof(tipoNo));
    grafo->lista_adj[i]->prox = NULL;
    grafo->lista_adj[i]->valor = -1;
  }
  grafo->V = V;
}

int buscaNaLista (tipoGrafo *grafo, int busca){
  for(int i=0; i<grafo->V; i++){
    if(grafo->lista_adj[i]->valor == busca)
      return 1;
  }
  return 0;
}

void insereNaListaAdj (tipoGrafo *grafo, int valor){
  int i=0;

  while(grafo->lista_adj[i]->valor != -1)
    i++;
  
  grafo->lista_adj[i]->valor = valor;
}

void insereNaListaEnc (tipoGrafo *grafo, int no_pai, int no_filho){
  int i=0;

  while(grafo->lista_adj[i]->valor != no_pai)
    i++;

  tipoNo *p = grafo->lista_adj[i];

  while(p->prox != NULL && p->prox->valor <= no_filho)
    p = p->prox;
  
  tipoNo *q;
  q = (tipoNo*)malloc(sizeof(tipoNo));
  q->valor = no_filho;
  q->prox = p->prox;
  p->prox = q;
}

void imprimeArestas (tipoGrafo *grafo, int selecionado){
  int i=0;
  
  while(grafo->lista_adj[i]->valor != selecionado)
    i++;

  tipoNo *p = grafo->lista_adj[i];
  if(p->prox != NULL){
    p = p->prox;
    while(p != NULL){
      printf("%i ",p->valor);
      p = p->prox;
    }
  }
}

int main(){
  tipoGrafo grafo;
  int selecionado, totalVertices, totalArestas;
  int vertice1, vertice2;

  scanf("%i",&selecionado);
  scanf("%i %i",&totalVertices, &totalArestas);

  inicializaGrafo(&grafo, totalVertices);

  for(int i=0; i<totalArestas; i++){
    scanf("%i %i", &vertice1, &vertice2);
    if(buscaNaLista(&grafo, vertice1)==0)
      insereNaListaAdj(&grafo, vertice1);
    if(buscaNaLista(&grafo, vertice2)==0)
      insereNaListaAdj(&grafo, vertice2);

    insereNaListaEnc(&grafo, vertice1, vertice2);
  }

  imprimeArestas(&grafo, selecionado);
  return 0;
}
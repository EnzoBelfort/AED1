#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct tipoitem{
  char nome[16]; 
  int indice; 
}tipoItem;

typedef struct tipoLista{
  tipoItem *vertices;
  int qtd;
}tipoLista;

typedef struct tipoGrafoMatrizAdj{
  tipoLista Lista;
  int **matrizAdj;
}tipoGrafoMatrizAdj;


void inicializaGrafo(tipoGrafoMatrizAdj *grafo, int V, int A){
  int i, j;
  grafo->Lista.vertices = (tipoItem*)malloc(V*sizeof(tipoItem));
  grafo->Lista.qtd = 0;
  
  grafo->matrizAdj = (int**)malloc(V*sizeof(int*));
  for(i=0; i<V; i++){
    grafo->matrizAdj[i] = (int*)malloc(V*sizeof(int));
  }

  for(i=0; i<V; i++){
    for(j=0; j<V; j++){
      grafo->matrizAdj[i][j] = 0;
    }
  }
}

void insereNaLista(tipoLista *lista, char nome_vertice[16]){
  tipoItem *vertice;
  int qtd = lista->qtd;
  
  vertice = (tipoItem*)malloc(sizeof(tipoItem));
  strcpy(vertice->nome, nome_vertice);
  vertice->indice = qtd;
  lista->vertices[qtd] = *vertice;

  lista->qtd++;
}


int buscaNo (tipoLista *lista, char nome[16]){
  for(int i=0; i<lista->qtd; i++){
    if(strcmp(lista->vertices[i].nome, nome)==0)
      return 1;
  }
  return 0;
}

int indiceNo (tipoLista *lista, char nome[16]){
  for(int i=0; i<lista->qtd; i++){
    if(strcmp(lista->vertices[i].nome, nome)==0)
      return i;
  }
  return 0;
}

int Amigos_SegundoGrau (tipoGrafoMatrizAdj *grafo, int indice){
  int V = grafo->Lista.qtd, cont = 0, m = 0;
  int *aux = (int*)malloc(V*sizeof(int));
  
  for(int j=0; j<V; j++){
    if(grafo->matrizAdj[indice][j]==1){
      for(int k=0; k<V; k++){
        if(grafo->matrizAdj[k][j]==1 && grafo->matrizAdj[k][indice]==0 && k!=indice){
          aux[m] = k;
          m++;
        }
      }
    }
  }
  for(int l=0; l<m; l++){
    for(int h=l+1; h<m; h++){
      if(aux[l] == aux[h])
        aux[h] = -1;
    }
    if(aux[l] != -1)
      cont++;
  }
  return cont;
}


int main(){
  tipoGrafoMatrizAdj Grafo;
  char *pessoa_selecionada, *vertice1, *vertice2;
  int totalPessoas, totalConexoes;

  pessoa_selecionada = (char*)malloc(16*sizeof(char));
  vertice1 = (char*)malloc(16*sizeof(char));
  vertice2 = (char*)malloc(16*sizeof(char));
  scanf("%s",pessoa_selecionada);
  scanf("%i %i",&totalPessoas, &totalConexoes);

  inicializaGrafo(&Grafo, totalPessoas, totalConexoes);

  for(int i=0; i<totalConexoes; i++){
    scanf("%s %s", vertice1, vertice2);
    
    if(buscaNo(&Grafo.Lista, vertice1)==0){
      insereNaLista(&Grafo.Lista, vertice1);
    }
    if(buscaNo(&Grafo.Lista, vertice2)==0){
      insereNaLista(&Grafo.Lista, vertice2);
    }
    int indice1 = indiceNo(&Grafo.Lista, vertice1);
    int indice2 = indiceNo(&Grafo.Lista, vertice2);
    
    Grafo.matrizAdj[indice1][indice2] = 1;
    Grafo.matrizAdj[indice2][indice1] = 1;
  }

  int indice_selecionada = indiceNo(&Grafo.Lista, pessoa_selecionada);
  printf("%i", Amigos_SegundoGrau(&Grafo, indice_selecionada));

  free(Grafo.Lista.vertices);
  free(vertice1);
  free(vertice2);
  free(pessoa_selecionada);
  return 0;
}
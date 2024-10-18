#include <stdio.h>
#include <stdlib.h>

typedef struct TipoCliente {
    int numero;
    int T;
    struct TipoCliente *prox;
} TipoCliente;

typedef struct TipoFilaD {
    TipoCliente *inicio, *fim;
    int tempo;
} TipoFilaD;

void inicializaFilaD(TipoFilaD *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tempo = 0;
}

int insereNoFinal(TipoFilaD *fila, int x, int T) {
  TipoCliente *novo = (TipoCliente*) malloc(sizeof(TipoCliente));
  novo->T = T;
  novo->numero = x;
  novo->prox = NULL;

  if(fila->inicio == NULL) {
    fila->fim = novo;
    fila->inicio = novo;
  } 
  else {
    fila->fim->prox = novo;
    fila->fim = novo;
  }
  
  fila->tempo += T;

  return 1; //retorna 1 se deu tudo certo
}

TipoCliente* removeDoComeco(TipoFilaD *fila) {
  if(fila->inicio == NULL) {
    return NULL;
  }
  else {
    TipoCliente *aux = fila->inicio;
    fila->inicio = fila->inicio->prox;
    
    if(fila->inicio == NULL) {
      fila->fim = NULL;
    }
    fila->tempo -= aux->T;\
    return aux;
  }
}

TipoCliente* buscaCliente(TipoFilaD *fila, int x) {
  TipoCliente *clienteAtual = fila->inicio;

  while(clienteAtual != NULL) {
    if(clienteAtual->numero == x) {
      return clienteAtual;
    }

    clienteAtual = clienteAtual->prox;
  }
  
  return NULL; // se nao achar retorna NULL
}

int main() {
  int N, A, T;
  int i, j, id, menorTempo;
  TipoFilaD *atendentes;

  scanf("%i %i", &N, &A);
  atendentes = (TipoFilaD*) malloc(A * sizeof(TipoFilaD));
    
  for(i=0; i<A; i++){
    inicializaFilaD(&atendentes[i]);  //vetor de filas de atendentes
  }

  for(i=0; i<N; i++){
    scanf("%i", &T);
    id = 0;
    menorTempo = atendentes[0].tempo;
    
    for(j=1; j<A; j++) {
      if(atendentes[j].tempo < menorTempo) {
        id = j;
        menorTempo = atendentes[j].tempo;
      }
    }

    insereNoFinal(&atendentes[id], i+1, T);
  }

  for(i=0; i<A; i++) {
    printf("%d:", i+1);
        
    while(atendentes[i].inicio != NULL) {
      TipoCliente *cliente = removeDoComeco(&atendentes[i]);
      printf(" %d", cliente->numero);
      free(cliente);
    }
        
    printf("\n");
  }
  
  free(atendentes);
  return 0;
}
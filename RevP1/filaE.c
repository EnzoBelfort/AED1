#include<stdio.h>
#include<stdlib.h>

typedef struct TipoItem{
  int chave;
  struct TipoItem *proximo;
}TipoItem;

typedef struct FilaE{
  struct TipoItem *inicio;
  struct TipoItem *fim;
}FilaE;

void inicializaFila(FilaE*);
int insereNoFinal(FilaE*, TipoItem novo);
int FilaVazia(FilaE*);
TipoItem removeDoInicio(FilaE*);
void imprimeFila(FilaE*);

int main(){
  
}

void inicializaFila(FilaE *fila){
  fila->inicio = NULL;
  fila->fim = NULL;
}

int filaVazia(FilaE *fila){
  if(fila->inicio == NULL)
    return 1;
  return 0;
}

int insereNoFinal(FilaE *fila, TipoItem novoNo){
  TipoItem *novo;
  novo = (TipoItem*)malloc(sizeof(TipoItem));   //aloca memoria para o TipoItem novo
  *novo = novoNo;                               //copia as caracteristicas de TipoItem novoNo para novo 
  if(novo == NULL)
    exit(1);
  
  if(filaVazia(fila)){                          //fila esta vazia
    fila->inicio = novo;                        
    fila->fim = novo;
    novo->proximo = NULL;
  }
  else{
    fila->fim->proximo = novo;
    fila->fim = novo;
    novo->proximo = NULL;
  }
  return 1;
}

TipoItem removeDoInicio(FilaE *fila){
  TipoItem ItemRemovido;

  if(filaVazia(fila)){
    printf("Não há o que remover \n");
    exit(1);
  }
  else{
    TipoItem *noRemovido;
    noRemovido = fila->inicio;
    ItemRemovido = *noRemovido; // Copia o item antes de liberar a memória
    fila->inicio = fila->inicio->proximo;
    free(noRemovido);
  }
  return ItemRemovido;
}


void ImprimeFila(FilaE *fila){
  TipoItem *aux;

  aux = fila->inicio;
  while(aux!=NULL){
    printf("%i",aux->chave);
    aux = aux->proximo;
  }
}
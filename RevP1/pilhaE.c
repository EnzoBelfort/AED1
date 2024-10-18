#include<stdio.h> 
#include<stdlib.h>

typedef struct tipoItem{
  int num;
  struct tipoItem *prox;
}tipoItem;

typedef struct pilhaE{
  tipoItem *topo;
//int tam; (opcional)
}pilhaE;

void inicializaPilha(pilhaE*);
int pilhaVazia(pilhaE*);
int push(pilhaE*, tipoItem);
tipoItem pop(pilhaE*);
void imprimePilha(pilhaE*);

int main(){
  
}

void inicializaPilha(pilhaE *pilha){
  pilha->topo = NULL;
}

int pilhaVazia(pilhaE *pilha){
  if(pilha->topo == NULL)
    return 1;
  return 0;
}

int push(pilhaE *pilha, tipoItem novo){
  tipoItem *novoNo;
  novoNo = (tipoItem*)malloc(sizeof(tipoItem));
  if(novoNo == NULL)
    exit(1);

  *novoNo = novo;
  if(pilhaVazia(pilha)){
    pilha->topo = novoNo;
    novoNo->prox = NULL;
  }
  else{
    novoNo->prox = pilha->topo;
    pilha->topo = novoNo;    
  }
  return 1;
}

tipoItem pop(pilhaE *pilha){
  tipoItem itemRemovido;
  tipoItem *aux;

  if(pilhaVazia(pilha)){
    printf("Não há o que remover.\n");
    itemRemovido.num = -1;
    return itemRemovido;
  }
  else{
    aux = pilha->topo;
    itemRemovido = *aux;
    pilha->topo = aux->prox;
    free(aux);
  }
  return itemRemovido;
}

void imprimePilha(pilhaE *pilha){
  tipoItem *p;
  p = pilha->topo;

  if(pilhaVazia(pilha)){
    printf("A pilha está vazia.\n");
  }
  else{
    while(p!=NULL){
      printf("%i ",p->num); // Adiciona um espaço após cada número
      p = p->prox;
    }
    printf("\n"); // Adiciona uma nova linha no final
  }
}

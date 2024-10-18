#include<stdio.h>
#include<stdlib.h>

typedef struct tipoItem{
  int num;
  struct tipoItem *prox;
  struct tipoItem *ant;
}tipoItem;

typedef struct listaDEC{  
  tipoItem *fim;
}listaDEC;

void incializaLDEC(listaDEC*);
int LDECvazia(listaDEC*);
int insereLDEC(listaDEC*, tipoItem);
tipoItem removeLDEC(listaDEC*, int);
void imprimeLDEC(listaDEC*);

int main(){
  
}

void inicializaLDEC(listaDEC *lista){
  lista->fim = NULL;
}

int LDECvazia(listaDEC *lista){
  if(lista->fim == NULL){
    return 1;
  }
  return 0;
}

int insereLDEC(listaDEC *lista, tipoItem novoNo){
  tipoItem *novo;
  novo = (tipoItem*)malloc(sizeof(tipoItem));
  if(novo == NULL){
    printf("Error\n");
    exit(1);
  }
  *novo = novoNo;
  if(LDECvazia(lista)){
    lista->fim = novo;
    novo->ant = novo;
    novo->prox = novo;
  }
  else if(){ //inserir no comeco 
    tipoItem *aux;
    aux = lista->fim->prox;
    lista->fim->prox = novo;
    novo->prox = aux;
    novo->ant = lista->fim;
    aux->ant = novo;
  }
  else if(){ //inserir no final
    novo->prox = lista->fim->prox;
    novo->ant = lista->fim;
    lista->fim->prox->ant = novo;
    lista->fim->prox = novo;
  }
  else{ //inserir no meio
    tipoItem *p;
    while(p<x){ //x sendo um parametro de comparação
      p = p->prox;
    }
    novo->ant = p->ant;
    novo->prox = p;
    p->ant->prox = novo;
    p->ant = novo;
  }
}

tipoItem removeLDEC(listaDEC *lista, int x){
  tipoItem *p, itemRemovido, *aux;
  p = lista->fim->prox;

  while(p->num!=x){
    p = p->prox;
  }
  aux = lista->fim->prox;
  itemRemovido = *p;
  if(p == lista->fim){
    aux->ant = p->ant;
    p->ant->prox = aux;
    free(p);
  }
  else if(p == lista->fim->prox){
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
    free(p);
  }
  else{
    p->prox->ant = p->ant;
    p->ant->prox = p->prox;
    free(p);
  }
  return itemRemovido;
}

void imprimeLDEC(listaDEC *lista){
  tipoItem *p;

  p = lista->fim->prox;
  while(p!=lista->fim){
    printf("%i ",p->num);
    p = p->prox;
  }
}



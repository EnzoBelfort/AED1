#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;


tipoNo* removeABB(tipoNo *no, int valor){
  tipoNo *p, *pai;
  if(no == NULL)
    return NULL;
  if(valor < no->valor){
    no->esq = removeABB(no->esq, valor);
  }
  if(valor > no->valor){
    no->dir = removeABB(no->dir, valor);
  }
  else{
    if(no->dir == NULL && no->esq == NULL){
      free(no);
      return NULL;
    }
    else if(no->dir==NULL){
      p = no->esq;
      free(no);
      return p;
    }
    else if(no->esq==NULL){
      p = no->dir;
      free(no);
      return p;
    }
    else{
      for(pai=no, p=no->dir; p->esq!=NULL; pai=p, p=p->esq);
      no->valor = p->valor;
      if(pai==no)
        no->dir = p->dir;
      else
        pai->esq = p->dir;
      free(p);
    }
  }
  return no;
}
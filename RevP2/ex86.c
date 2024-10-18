#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;

void ordem_decrescente (tipoNo *raiz){
  if(raiz == NULL){
    return;
  }
  ordem_decrescente(raiz->dir);
  printf("%i", raiz->valor);
  ordem_decrescente(raiz->esq);
}
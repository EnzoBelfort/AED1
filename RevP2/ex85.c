#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;


int qtd_filhos (tipoNo *no){
  int cont=0;
  if(no == NULL){
    return 0;
  }
  if(no->dir != NULL)
    cont++;
  if(no->esq != NULL)
    cont++;
  return cont;
}
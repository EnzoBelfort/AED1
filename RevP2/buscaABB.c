#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;

tipoNo* buscaABB(tipoNo *no, int valor){
  if(no==NULL)
    return NULL;
  if(no->valor == valor)
    return no;
  if(valor < no->valor)
    return buscaABB(no->esq, valor);
  else
    return buscaABB(no->dir, valor);
}
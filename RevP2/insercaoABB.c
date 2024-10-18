#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  int valor;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;


tipoNo* insereABB(tipoNo *no, int valor){
  if(no==NULL){
    no = (tipoNo*)malloc(sizeof(tipoNo));
    no->valor = valor;
    no->esq = NULL;
    no->dir = NULL;
    return no;
  }
  if(valor < no->valor)
    return insereABB(no->esq, valor);
  if(valor > no->valor)
    return insereABB(no->dir, valor);
  return no;
}
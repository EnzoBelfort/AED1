#include<stdio.h>
#include<stdlib.h>

typedef struct tipoNo{
  char lugar;
  struct tipoNo *esq, *dir;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;


int calc_museus(tipoNo *no){
  if(no == NULL)
    return 0;
  if(no->lugar == 'M')
    return 1 + calc_museus(no->esq) + calc_museus(no->dir);
  
  return calc_museus(no->esq) + calc_museus(no->dir);
}


int calc_maior(ABB *a){
  if(a == NULL)
    return 0;
    
  else{
    int caminho_esq = calc_museus(a->raiz->esq);
    int caminho_dir = calc_museus(a->raiz->dir);

    if(caminho_dir > caminho_esq)
      return caminho_dir;
    else
      return caminho_esq;
  }
}
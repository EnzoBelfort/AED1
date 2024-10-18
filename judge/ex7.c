#include<stdio.h>
#include<stdlib.h>

typedef struct tipoItem{
  int valor;
  struct tipoItem *esquerda, *direita;
}tipoItem;

typedef struct ABB{
  tipoItem *raiz;
}ABB;

void inicializaABB(ABB*);
int insereNaABB(ABB*, int);
int buscaNaABB(ABB*, int);
void pre_ordem(tipoItem*); 
void em_ordem(tipoItem*);
void pos_ordem(tipoItem*);
int altura(tipoItem*);

int main(){
  ABB arvore;
  int n, elemento, v;

  inicializaABB(&arvore);

  scanf("%i %i",&n, &v);

  for(int i=0;i<n;i++){
    scanf("%i",&elemento);
    insereNaABB(&arvore, elemento);
  }

  pre_ordem(arvore.raiz);
  printf("\n");
  em_ordem(arvore.raiz);
  printf("\n");
  pos_ordem(arvore.raiz);
  printf("\n");
  buscaNaABB(&arvore, v);
  printf("\n");
  int h = altura(arvore.raiz);
  printf("%i \n",h);

  
  return 0;
}

  
void inicializaABB(ABB *arvore){
  arvore->raiz = NULL;
}

int insereNaABB(ABB *arvore, int x){
  tipoItem *novo;

  novo = (tipoItem*)malloc(sizeof(tipoItem));
  novo->valor = x;
  novo->esquerda = NULL;
  novo->direita = NULL;

  if(arvore->raiz==NULL){
    arvore->raiz = novo;
  }
  else{
    tipoItem *p;
    p = arvore->raiz;
    while(p!=NULL){
      if(novo->valor < p->valor){
        if(p->esquerda == NULL){
          p->esquerda = novo;
          return 1;
        }
        p = p->esquerda;
      }
      else{
        if(p->direita == NULL){
          p->direita = novo;
          return 1;
        }
        p = p->direita;
      }
    }
  }
  return 1;
}

int buscaNaABB(ABB *arvore, int busca){
  tipoItem *p;
  p = arvore->raiz;

  while(p!=NULL){
    if(busca==p->valor)
      break;
    else if(busca < p->valor){
      p = p->esquerda;
    }
    else{
      p = p->direita;
    }
  }

  if(p==NULL){
    printf("-1");
    return -1;
  }
  p = arvore->raiz;
  while(p!=NULL){
    printf("%i ",p->valor);
    if(busca == p->valor){
      return 1;
    }
    else if(busca < p->valor){
      p = p->esquerda;
    }
    else{
      p = p->direita;
    }
  }
  return 1;
}


void pre_ordem(tipoItem *no){
  if(no == NULL)
    return;
  
  printf("%i ",no->valor);
  pre_ordem(no->esquerda);
  pre_ordem(no->direita);
}

void em_ordem(tipoItem *no){
  if(no == NULL)
    return;

  em_ordem(no->esquerda);
  printf("%i ",no->valor);
  em_ordem(no->direita);
}

void pos_ordem(tipoItem *no){
  if(no == NULL)
    return;

  pos_ordem(no->esquerda);
  pos_ordem(no->direita);
  printf("%i ",no->valor);
}


int altura(tipoItem *no){
  if(no == NULL)
    return -1; 
  else{
    int alturaEsquerda = altura(no->esquerda);
    int alturaDireita = altura(no->direita);
    if(alturaEsquerda > alturaDireita)
      return alturaEsquerda + 1;
    else
      return alturaDireita + 1;
  }
}
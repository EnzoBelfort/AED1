#include<stdio.h>
#include<stdlib.h>  
#include<string.h>

typedef struct tipoNo{
  char letra;
  int freq;
  struct tipoNo *esquerda;
  struct tipoNo *direita;
}tipoNo;

typedef struct ABB{
  tipoNo *raiz;
}ABB;

void inicializaABB(ABB*);
int insereNaABB(ABB*, tipoNo);
void busca_remove(ABB*, char, int);
void substituiPeloSucessor(tipoNo*, tipoNo*);
void em_ordem(tipoNo*);

int main(){
  char intrusa1, intrusa2, letra=65;
  ABB arvore;
  tipoNo novoNo;
  char *string, letras[26];
  int cont, aux1, aux2, i, j=0, frequencias[26];

  string = (char*)malloc(1024*sizeof(char));

  inicializaABB(&arvore);

  scanf(" %c %c",&intrusa1,&intrusa2);
  scanf("%s",string);

  while(letra>=65 && letra<=90){
    cont = 0;
    for(i=0;i<strlen(string);i++){
      if(string[i]==letra)
        cont++;
    }
    if(cont!=0){
      letras[j] = letra;
      frequencias[j] = cont;
      j++;
    }
    letra++;
  }

  for(i=0;i<j;i++){
    novoNo.freq = frequencias[i];
    novoNo.letra = letras[i];
    insereNaABB(&arvore, novoNo);

    if(letras[i]==intrusa1)
      aux1 = frequencias[i];
    if(letras[i]==intrusa2)
      aux2 = frequencias[i];
  }

  em_ordem(arvore.raiz);
  printf("\n");

  busca_remove(&arvore, intrusa1, aux1);
  busca_remove(&arvore, intrusa2, aux2);

  em_ordem(arvore.raiz);
  printf("\n");

  free(string);
  return 0;
}



void inicializaABB(ABB *arvore){
  arvore->raiz = NULL;
}

int insereNaABB(ABB *arvore, tipoNo novo){
  tipoNo *novoNo;

  novoNo = (tipoNo*)malloc(sizeof(tipoNo));
  novoNo->freq = novo.freq;
  novoNo->letra = novo.letra;
  novoNo->direita = NULL;
  novoNo->esquerda = NULL;

  if(arvore->raiz == NULL)
    arvore->raiz = novoNo;

  else{
    tipoNo *p;
    p = arvore->raiz;
    while(p!=NULL){
      if(novoNo->freq < p->freq){
        if(p->esquerda == NULL){
          p->esquerda = novoNo;
          return 1;
        }
        p = p->esquerda;
      }
      else{
        if(p->direita == NULL){
          p->direita = novoNo;
          return 1;
        }
        p = p->direita;
      }
    }
  }
  return 1;
}

void em_ordem(tipoNo *p){
  if(p == NULL)
    return;

  em_ordem(p->esquerda);
  printf("%c",p->letra);
  em_ordem(p->direita);
}


void busca_remove(ABB *arvore, char intruso, int freq_intruso){
  tipoNo *p, *pai;
  p = arvore->raiz;
  pai = p;

  while(p != NULL && p->letra != intruso){
    pai = p;
    if(freq_intruso < p->freq)
      p = p->esquerda;
    else
      p = p->direita;
  }
  if(p==NULL)
    return;

  if(p->direita == NULL && p->esquerda == NULL){
    if(p->freq < pai->freq)
      pai->esquerda = NULL;
    else
      pai->direita = NULL;
    free(p);
  }  

  else if(p->direita == NULL){
    if(p->freq < pai->freq)
      pai->esquerda = p->esquerda;
    else
      pai->direita = p->esquerda;
    free(p);
  }
  else if(p->esquerda == NULL){
    if(p->freq < pai->freq)
      pai->esquerda = p->direita;
    else
      pai->direita = p->direita;
    free(p);
  }
  else
    substituiPeloSucessor(p, p->direita);
}

void substituiPeloSucessor (tipoNo *no, tipoNo*direita_No){
  tipoNo *pai;
  pai = direita_No;

  while(direita_No->esquerda != NULL){
    pai = direita_No;
    direita_No = direita_No->esquerda;
  }

  no->freq = direita_No->freq;
  no->letra = direita_No->letra;

  if(pai == direita_No){
    no->direita = pai->direita;
    free(direita_No);
    return;
  }

  pai->esquerda = direita_No->direita;
  free(direita_No);
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct tipoItem{
  int repeticao;
  char letra;
  struct tipoItem *anterior;
  struct tipoItem *proximo;
}tipoItem;

typedef struct listaDPE{
  struct tipoItem *inicio;
  struct tipoItem *fim;
}listaDPE;

int insereNaListaDPE(listaDPE*, tipoItem);
void inicializaLista(listaDPE*);
int listaVazia(listaDPE*);
tipoItem removeDaLista(listaDPE*, tipoItem*);
void imprimeLista(listaDPE*);



int main(){
  char string[1025];
  int i=0,j,k=0,cont=0;
  char letra[1025];
  int qtd[1025];
  tipoItem novo;
  listaDPE lista;

  scanf("%s",string);
  while(i<strlen(string)){
    cont=1;
    letra[k] = string[i];
    j=i+1;
    if(string[i]==string[j]){
      while(string[i]==string[j]){
        cont++;
        i++;
      }
      cont--;
    }
    else{
      i++;
    }
    qtd[k] = cont;
    k++;
  }

  inicializaLista(&lista);
  for(i=0;i<k;i++){
    novo.letra = letra[i];
    novo.repeticao = qtd[i];
    insereNaListaDPE(&lista, novo);
  }
  imprimeLista(&lista);
  printf("\n");

  tipoItem *aux;
  aux = lista.inicio;

  do{
    if(aux==lista.inicio){
      if(aux->repeticao==1 && aux->proximo->repeticao>1){
        aux->proximo->repeticao++;
        aux = aux->proximo;
        removeDaLista(&lista, aux->anterior);
      }
      else
        aux = aux->proximo;
    }
    else if(aux==lista.fim){
      if(aux->repeticao==1 && aux->anterior->repeticao>1){
        aux->anterior->repeticao++;
        removeDaLista(&lista, aux);
      }
    }
    else{
      if(aux->repeticao==1 && aux->anterior->repeticao>1 && aux->proximo->repeticao>1){
        if(aux->anterior->repeticao >= aux->proximo->repeticao){
          aux->anterior->repeticao++;
          aux = aux->proximo;
          removeDaLista(&lista, aux->anterior);
        }  
        else{
          aux->proximo->repeticao++;
          aux = aux->proximo;
          removeDaLista(&lista, aux->anterior);
        }
      }
      else
        aux = aux->proximo;
    }
  }while(aux!=lista.fim);

  imprimeLista(&lista);
  printf("\n");
  return 0;
}





void inicializaLista(listaDPE *lista){
  lista->fim = NULL;
  lista->inicio = NULL;
}

int listaVazia(listaDPE *lista){
  if(lista->inicio == NULL)
    return 1;
    
  else
    return 0;
}

int insereNaListaDPE(listaDPE *lista, tipoItem novo){
  tipoItem *novoItem, *aux;
  novoItem = (tipoItem*)malloc(sizeof(tipoItem));
  novoItem->letra = novo.letra;
  novoItem->repeticao = novo.repeticao;
  if(listaVazia(lista)){
    lista->inicio = novoItem;
    lista->fim = novoItem;
    novoItem->anterior = NULL;
    novoItem->proximo = NULL;
    return 1;
  }
  else{
    lista->fim->proximo = novoItem;
    novoItem->anterior = lista->fim;
    novoItem->proximo = NULL;
    lista->fim = novoItem;
    return 1;
  }
}

tipoItem removeDaLista(listaDPE *lista, tipoItem *ruido){
  tipoItem *itemRemovido, *p;

  if(listaVazia(lista)){
    itemRemovido->letra = 0;
  }
  else{       
    itemRemovido = ruido;
    p = lista->inicio;

    while(p!=NULL && p!=itemRemovido){
      p = p->proximo;
    }

    if(p != NULL) {
      if(p->anterior != NULL) {
        p->anterior->proximo = p->proximo;
      } 
      else {
        lista->inicio = p->proximo;
      }

      if(p->proximo != NULL) {
        p->proximo->anterior = p->anterior;
      } 
      else {
        lista->fim = p->anterior;
      }

      free(p);
    }
  }
  return *itemRemovido;
}


void imprimeLista(listaDPE *lista){
  int cont=0;
  tipoItem *p;

  p = lista->inicio;
  while(p!=NULL){
    cont++;
    if((p->repeticao/1000)>=1)
      cont+=4;
    else if((p->repeticao/100)>=1)
      cont+=3;
    else if((p->repeticao/10)>=1)
      cont+=2;
    else
      cont++;
    p = p->proximo;
  }
  printf("%i\n",cont);
  p = lista->inicio;
  while(p!=NULL){
    printf("%i%c",p->repeticao,p->letra);
    p = p->proximo;
  }
}
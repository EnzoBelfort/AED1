#include <stdio.h>
#include <stdlib.h>
     
#define ALOCA_TAM 10 //aloca a cada 10
     
typedef struct {
  int coef;
  int exp;
}TipoItem;
     
typedef struct {
  TipoItem *itens;
  int ultimo;
  int tamanho;
}ListaLinearSD;
     
int inicializaLLSD(ListaLinearSD *lista);
void imprimeLLSD(ListaLinearSD *lista);
int insereLLSD(ListaLinearSD *lista, TipoItem novoItem);
int buscaLLSD(ListaLinearSD *lista, int exp);
void removeLLSD(ListaLinearSD *lista, int exp);
     
int main() {
  int i, n;
  int coef = 0, exp = 0;
  ListaLinearSD lista;
  TipoItem item;
  inicializaLLSD(&lista);
  if (inicializaLLSD(&lista) < 0) {
    printf("ERRO! Nao foi possivel alocar memoria.\n");
    exit(1);
  }
     
  scanf("%d", &n);
     
  for (i = 0; i < n; i++) {
    scanf("%d %d", &item.coef, &item.exp);
    if (item.coef != 0) {
      insereLLSD(&lista, item);
    }
  }
  imprimeLLSD(&lista);
  printf("\n%d\n", lista.ultimo);
  return 0;
}
     
int inicializaLLSD(ListaLinearSD *lista) {
  lista->ultimo = 0;
  lista->tamanho = ALOCA_TAM;
  lista->itens = (TipoItem *)malloc(ALOCA_TAM * sizeof(TipoItem));
  if (lista->itens == NULL) return -1;
  lista->itens == NULL;
  return 0;
}
     
void imprimeLLSD(ListaLinearSD *lista) {
  int i = 0;
  if (lista->ultimo < 1) {
    printf("nulo");
  }
  else {
    for (i = 0; i < lista->ultimo; i++)
      printf("%d %d ", lista->itens[i].coef, lista->itens[i].exp);
  }
}
     
int buscaLLSD(ListaLinearSD * lista, int exp)
{
  int i = 0;
  for (i = 0; i < lista->ultimo; i++) {
    if (lista->itens[i].exp == exp) {
      return i;
    }
  }
  return -1;
}
     
void removeLLSD(ListaLinearSD *lista, int exp)
{
  int i = 0;
  for (i = exp; i < lista->tamanho; i++) {
    lista->itens[i] = lista->itens[i+1];
  }
  lista->ultimo -= 1;
}
     
int insereLLSD(ListaLinearSD *lista, TipoItem novoItem) 
{     
  int pos = lista->ultimo;
  int j = 0;
  if (pos == lista->tamanho) {
    TipoItem *aux = lista->itens; //guarda endereco antigo
    TipoItem *novaLista = (TipoItem *)malloc((lista->tamanho+ALOCA_TAM) *sizeof(TipoItem));
    if(novaLista == NULL) return -1;
    for(j=0; j<pos; j++)
      novaLista[j] = lista->itens[j];
    lista->itens = novaLista;
    lista->tamanho += ALOCA_TAM;
    if(aux!=NULL)
      free(aux); //libera memoria
  }     
  int idx = buscaLLSD(lista, novoItem.exp);  
  if (idx == -1) {
    int exp_aux = -1, i = 0, n= 0;
    while (novoItem.exp < lista->itens[i].exp && i < lista->ultimo) {
      exp_aux = lista->itens[i].exp;
      i++;
    }
    if (exp_aux == -1) {
      for (n = pos - 1; n >= 0; n--) {
    lista->itens[n + 1].exp = lista->itens[n].exp;
    lista->itens[n + 1].coef = lista->itens[n].coef;
      }
      lista->itens[0].exp = novoItem.exp;
      lista->itens[0].coef = novoItem.coef;
    }
    else if (i < lista->ultimo) {
      for (n = pos; n >= i; n--) {
    lista->itens[n].exp = lista->itens[n - 1].exp;
    lista->itens[n].coef = lista->itens[n - 1].coef;
      }
      lista->itens[n + 1].exp = novoItem.exp;
      lista->itens[n + 1].coef = novoItem.coef;
    }
    else {
      lista->itens[lista->ultimo].exp = novoItem.exp;
      lista->itens[lista->ultimo].coef = novoItem.coef;
    }
    lista->ultimo += 1;
  }
  else {
    lista->itens[idx].coef = lista->itens[idx].coef + novoItem.coef;
    if (lista->itens[idx].coef == 0) {
      removeLLSD(lista, idx);
    }
  }
  return 0;
}
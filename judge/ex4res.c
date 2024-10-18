#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TipoItem {
  int valor;
  struct TipoItem *prox;
} TipoItem;

typedef struct {
  TipoItem *topo;
} TipoPilhaD;

void inicializaPilha(TipoPilhaD *pilha) { pilha->topo = NULL; }

int pilhaVazia(TipoPilhaD *pilha) {
  if (pilha->topo == NULL)
    return 1;
  return 0;
}

void imprimePilha(TipoPilhaD *pilha) {
  TipoItem *p = pilha->topo;
  while (p != NULL) {
    printf("%c ", p->valor);
    p = p->prox;
  }
  printf("\n");
}

void push(TipoPilhaD *pilha, int ch) {
  TipoItem *novo = (TipoItem *)malloc(sizeof(TipoItem));
  if (!novo) {
    exit(-1);
  }
  novo->valor = ch;
  novo->prox = pilha->topo;
  pilha->topo = novo;
}

int pop(TipoPilhaD *pilha) {
  int c;
  if (pilhaVazia(pilha)) {
    return -1;
  }
  TipoItem *paux;
  paux = pilha->topo;
  pilha->topo = paux->prox;
  c = paux->valor;
  free(paux);
  return c;
}

int main() {
  char vetor[1024];
  TipoPilhaD s;
  inicializaPilha(&s);
  scanf("%s", vetor);
  int len = strlen(vetor);
  int idx = 0;
  int v1, v2;

  while (idx < len) {
    if (vetor[idx] >= '0' && vetor[idx] <= '9') {
      push(&s, vetor[idx] - 48);
    }

    else if (vetor[idx] == '+' || vetor[idx] == '-' || vetor[idx] == '*' ||
             vetor[idx] == '/') {

      v1 = (int)pop(&s);
      if (v1 == -1) {
        printf("Invalid Expression\n");
        return 0;
      }

      v2 = (int)pop(&s);
      if (v2 == -1) {
        printf("Invalid Expression\n");
        return 0;
      }

      if (vetor[idx] == '+') {
        push(&s, v2 + v1);
      } else if (vetor[idx] == '-') {
        push(&s, v2 - v1);
      } else if (vetor[idx] == '*') {
        push(&s, v2 * v1);
      } else if (vetor[idx] == '/') {
        push(&s, v2 / v1);
      }
    }

    idx++;
  }

  v1 = (int)pop(&s);
  if (v1 == -1) {
    printf("Invalid Expression\n");
    return 0;
  }

  if (!pilhaVazia(&s)) {
    printf("Invalid Expression\n");
    return 0;
  }

  printf("%d\n", v1);

  return 0;
}
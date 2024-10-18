#include <stdio.h>
#include <stdlib.h>
 
#define MAX 1024
 
typedef struct {
    int chave;
    int valor;
}TipoItem;
 
typedef struct {
    TipoItem vet[MAX];
    int inicio;
    int fim;
    int tam;
    int qtd;
}TipoFilaSE;
 
void inicializaFilaES(TipoFilaSE *fila) {
    fila->inicio = -1;
    fila->fim = -1;
    fila->qtd = 0;
    fila->tam = MAX;
}
 
int filaVazia(TipoFilaSE *fila) {
    if (fila->qtd == 0) return 1;
    return 0;
    // return(fila->inicio == fila->fim);
}
 
int filaCheia(TipoFilaSE *fila) {
    if (fila->qtd == fila->tam)
        return 1;
    return 0;
    //return ((fila->fim+1) % fila->tam == fila->inicio);
}
 
void inserirFilaSE(TipoFilaSE *fila, TipoItem novo) {
    if (!filaCheia(fila)) {
        if (fila->qtd == 0) {
            fila->inicio++;
        }
        fila->fim++;
        if (fila->fim == MAX) {
            fila->fim = 0;
        }
        fila->qtd++;
        fila->vet[fila->fim] = novo;
    }
}
 
TipoItem removerFilaSE(TipoFilaSE *fila) {
    TipoItem item = fila->vet[fila->inicio];
    fila->inicio++;
    if (fila->inicio == MAX) {
        fila->inicio = 0;
    }
    fila->qtd--;
    return item;
}
 
void imprimeFila(TipoFilaSE *fila) {
    TipoItem p;
    int i;
    int q = fila->inicio + fila->qtd;
    if (!filaVazia(fila)) { //se lista não for vazia
        for (i = fila->inicio; i < q; i++) {
            p = fila->vet[i % fila->tam];
            printf("%d, %d\n", p.chave, p.valor);
        }
    }
}
 
void imprimeFilaAtendimento(TipoFilaSE *fila, int tam) {
    TipoItem p;
    int i, j, q;
    for (i = 0; i < tam; i++) {
        q = fila[i].inicio + fila[i].qtd;
        printf("%d: ", i + 1);
        if (!filaVazia(fila)) { //se lista não for vazia
            for (j = fila[i].inicio; j < q; j++) {
                p = fila[i].vet[j % fila->tam];
                printf("%d ", p.chave);
            }
        }
        printf("\n");
    }
}
 
int main() {
 
    TipoFilaSE filageral;
    TipoFilaSE *filaatend;
    TipoItem item;
    inicializaFilaES(&filageral);
    int *atendimento;
    int N, A, i, j;
 
    scanf("%d %d", &N, &A);
    atendimento = (int *)malloc(A*sizeof(int));
    if (!atendimento) {
        exit(-1);
    }
    filaatend = (TipoFilaSE *)malloc(A * sizeof(TipoFilaSE));
    if (!filaatend) {
        exit(-1);
    }
    for (i = 0; i < A; i++) {
        atendimento[i] = 0;
        inicializaFilaES(&filaatend[i]);
    }
 
    int id, tempo;
 
    for (i = 0; i < N; i++) {
        id = i + 1;
        scanf("%d", &tempo);
        item.chave = id;
        item.valor = tempo;
        inserirFilaSE(&filageral, item);
    }
 
    int min = 9999999;
    int min_idx = 0;
 
    for (i = 0; i < N; i++) {
        item = removerFilaSE(&filageral);
        for (j = 0; j < A; j++) {
            if (atendimento[j] < min) {
                min_idx = j;
                min = atendimento[j];
            }
        }

        inserirFilaSE(&filaatend[min_idx], item);
        atendimento[min_idx] = atendimento[min_idx] + item.valor;
        min = 9999999;
        min_idx = -1;
     }
 
    imprimeFilaAtendimento(filaatend, A);
  
    return 0;
}
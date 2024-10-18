#include <stdio.h>
#include <stdlib.h>

#define ALOCA_TAM 5

typedef struct {
    int C;
    int E;
} TipoMonomio;

typedef struct {
    TipoMonomio *monomios;
    int ultimo;
    int tamanho;
} ListaLinearSD;

int inicializaLLSD(ListaLinearSD *);
int insereNoFinalLLSD(ListaLinearSD *, TipoMonomio);
int buscaMonomioLLSD(ListaLinearSD *, int, int);
void removeMonomioLLSD(ListaLinearSD *, int);
void exibePolinomioLLSD(ListaLinearSD *);

int compararMonomios(const void *a, const void *b) {
    return ((TipoMonomio *)b)->E - ((TipoMonomio *)a)->E;
}

int main() {
    int N, i, x;
    TipoMonomio monomio;
    ListaLinearSD lista;

    scanf("%i", &N);

    if (inicializaLLSD(&lista) < 0) {
        printf("ERRO! Não foi possível alocar memória.\n");
        exit(1);
    }

    for (i = 0; i < N; i++) {
        scanf("%i %i", &monomio.C, &monomio.E);
        x = buscaMonomioLLSD(&lista, monomio.C, monomio.E);
        if (x != -1) {
            lista.monomios[x].C += monomio.C;
            if (lista.monomios[x].C == 0) {
                removeMonomioLLSD(&lista, x);
            }
        } else {
            insereNoFinalLLSD(&lista, monomio);
        }
    }

    if (lista.ultimo == 0) {
        printf("nulo\n0\n");
    } else {
        qsort(lista.monomios, lista.ultimo, sizeof(TipoMonomio), compararMonomios);
        exibePolinomioLLSD(&lista);
    }

    return 0;
}

int inicializaLLSD(ListaLinearSD *lista) {
    lista->ultimo = 0;
    lista->tamanho = ALOCA_TAM;
    lista->monomios = malloc(ALOCA_TAM * sizeof(TipoMonomio));
    if (lista->monomios == NULL)
        return -1;
    return 0;
}

int insereNoFinalLLSD(ListaLinearSD *lista, TipoMonomio novoItem) {
    int pos = lista->ultimo, i;

    if (pos == lista->tamanho) {
        TipoMonomio *novaLista = realloc(lista->monomios, (lista->tamanho + ALOCA_TAM) * sizeof(TipoMonomio));
        if (novaLista == NULL) {
            printf("ERRO! Não foi possível alocar memória.\n");
            return -1;
        }
        lista->tamanho += ALOCA_TAM;
        lista->monomios = novaLista;
    }
    lista->monomios[pos] = novoItem;
    lista->ultimo++;
    return 0;
}

int buscaMonomioLLSD(ListaLinearSD *lista, int c, int e) {
    int i;
    for (i = 0; i < lista->ultimo; i++) {
        if (lista->monomios[i].C == c && lista->monomios[i].E == e) {
            return i;
        } else if (lista->monomios[i].E == e) {
            return i;
        }
    }
    return -1;
}

void removeMonomioLLSD(ListaLinearSD *lista, int pos) {
    int i;
    for (i = pos; i < lista->ultimo - 1; i++) {
        lista->monomios[i] = lista->monomios[i + 1];
    }
    lista->ultimo--;
}

void exibePolinomioLLSD(ListaLinearSD *lista) {
    int i;
    for (i = 0; i < lista->ultimo; i++) {
        printf("%d %d ", lista->monomios[i].C, lista->monomios[i].E);
    }
    printf("\n%d\n", lista->ultimo);
}
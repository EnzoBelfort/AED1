#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct TipoItem {
    char digito;
    struct TipoItem *prox;
} TipoItem;

typedef struct TipoPilhaD {
    TipoItem *topo;
} TipoPilhaD;

void inicializaPilha(TipoPilhaD *);
int pilhaVazia(TipoPilhaD *);
void push(TipoPilhaD *, char);
char pop(TipoPilhaD *);

int main() {
    char expressao[1024];
    TipoPilhaD pilha;
    inicializaPilha(&pilha);

    scanf("%s", expressao);

    for (int i = 0; expressao[i] != '\0'; i++) {
        char token = expressao[i];

        if (isdigit(token)) {
            push(&pilha, token - '0'); // Converte caractere para número inteiro
        } else if (token == '+' || token == '-' || token == '*' || token == '/') {
            if (pilhaVazia(&pilha)) {
                printf("Invalid Expression\n");
                return 1;
            }

            int segundo = pop(&pilha);
            if (pilhaVazia(&pilha)) {
                printf("Invalid Expression\n");
                return 1;
            }

            int primeiro = pop(&pilha);

            switch (token) {
                case '+':
                    push(&pilha, primeiro + segundo);
                    break;
                case '-':
                    push(&pilha, primeiro - segundo);
                    break;
                case '*':
                    push(&pilha, primeiro * segundo);
                    break;
                case '/':
                    push(&pilha, primeiro / segundo);
                    break;
            }
        } else {
            printf("Invalid Expression\n");
            return 1;
        }
    }

    if (pilhaVazia(&pilha)) {
        printf("Invalid Expression\n");
        return 1;
    }

    int resultado = pop(&pilha);

    if (!pilhaVazia(&pilha)) {
        printf("Invalid Expression\n");
        return 1;
    }

    printf("%d\n", resultado);

    return 0;
}

void inicializaPilha(TipoPilhaD *pilha) {
    pilha->topo = NULL;
}

int pilhaVazia(TipoPilhaD *pilha) {
    return (pilha->topo == NULL);
}

void push(TipoPilhaD *pilha, char novo) {
    TipoItem *novoItem = (TipoItem *)malloc(sizeof(TipoItem));
    if (novoItem == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }
    novoItem->digito = novo;
    novoItem->prox = pilha->topo;
    pilha->topo = novoItem;
}

char pop(TipoPilhaD *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Erro: Pilha vazia, não é possível fazer pop.\n");
        exit(1);
    }
    TipoItem *temp = pilha->topo;
    char item = temp->digito;
    pilha->topo = pilha->topo->prox;
    free(temp);
    return item;
}
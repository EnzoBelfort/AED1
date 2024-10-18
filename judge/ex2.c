#include <stdio.h>
#include <stdlib.h>

int main() {
  int maximo1, maximo2, k = 0;
  int tamanho1 = 0, tamanho2 = 0, cont = 0;
  char *stringX, *stringY, *stringZ, busca, aux;

  scanf("%i %i %c", &maximo1, &maximo2, &busca);

  stringX = malloc(maximo1);
  stringY = malloc(maximo2);

  scanf("%s %s", stringX, stringY);

  for (int i = 0; i < maximo1; i++) {
    if (busca == stringX[i]) {
      cont++;
    }
    if (stringX[i] == '\0') {
      break;
    }
    tamanho1++;
  }
  for (int i = 0; i < maximo2; i++) {
    if (busca == stringY[i]) {
      cont++;
    }
    if (stringY[i] == '\0') {
      break;
    }
    tamanho2++;
  }

  for (int i = 0, j = tamanho1 - 1; i < tamanho1 / 2; i++, j--) {
    aux = stringX[i];
    stringX[i] = stringX[j];
    stringX[j] = aux;
  }
  for (int i = 0, j = tamanho2 - 1; i < tamanho2 / 2; i++, j--) {
    aux = stringY[i];
    stringY[i] = stringY[j];
    stringY[j] = aux;
  }

  stringZ = malloc(tamanho1 + tamanho2);

  for (int i = 0; i < (tamanho1 + tamanho2); i++) {
    if (i < tamanho1) {
      stringZ[i] = stringX[i];
    } else if (i < tamanho1 + tamanho2) {
      stringZ[i] = stringY[k];
      k++;
    }
  }
  printf("%s\n", stringZ);
  printf("%i\n", tamanho1 + tamanho2);
  printf("%i\n", cont);

  free(stringX);
  free(stringY);
  free(stringZ);
  return 0;
}
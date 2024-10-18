#include<stdio.h>
#include<string.h>

int main() {
    char string[256], aux[256];
    int auxiliar = 0;
  
    fgets(string, sizeof(string), stdin);
    string[strlen(string) - 1] = '\0';
    
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] >= 'a' && string[i] <= 'z') {
            string[i] = string[i] - 32;
        }
    }

    for (int i = 0; i < strlen(string); i++) {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            int found = 0;
            for (int j = 0; j < auxiliar; j++) {
                if (aux[j] == string[i]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                aux[auxiliar] = string[i];
                auxiliar++;
            }
        }
    }

    for (int i = 0; i < auxiliar - 1; i++) {
        for (int j = 0; j < auxiliar - i - 1; j++) {
            if (aux[j] > aux[j + 1]) {
                char temp = aux[j];
                aux[j] = aux[j + 1];
                aux[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < auxiliar; i++) {
        int count = 0;
        for (int j = 0; j < strlen(string); j++) {
            if (string[j] == aux[i]) {
                count++;
            }
        }
        printf("%c %d\n", aux[i], count);
    }

    return 0;
}
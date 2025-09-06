#include <stdio.h>

int main() {
    int tamanho;
    scanf("%d", &tamanho);
    int vetor[tamanho];
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
        mergesort(vetor)
    }


    return 0;
}
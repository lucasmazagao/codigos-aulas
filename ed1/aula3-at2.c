#include <stdio.h>

void calcular(int vetor[], int tamanho) {
    int soma = 0;
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
        
        if (vetor[i] % 2 == 0) {
            soma += vetor[i];
        }
    }
    printf("Soma dos pares: %d\n", soma);
}

int main() {
    int tamanho;
    scanf("%d", &tamanho);

    int vetor[tamanho];

    calcular(vetor, tamanho);

    return 0;
}
#include <stdio.h>

int EhPerfeito(int n) {
    int soma = 0;
    for (int i = 1; i < n; i++) {
        if (n % i == 0) {
            soma += i;
        }
    }
    return soma == n;
}

void PreencheVetor(int a[], int b[], int n, int *tam) {
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] <= 0) {
            printf("Identificador invalido\n");
            *tam = -1;
            return;
        }
        if (EhPerfeito(a[i])) {
            b[*tam] = a[i];
            (*tam)++;
        }
    }
}

void MostraVetor(int b[], int tam) {
    for (int i = 0; i < tam; i++) {
        for (int j = i + 1; j < tam; j++) {
            if (b[i] > b[j]) {
                int aux = b[i];
                b[i] = b[j];
                b[j] = aux;
            }
        }
    }
    
    for (int i = 0; i < tam; i++) {
        printf("%d", b[i]);
        if (i != tam - 1) printf(" ");
    }

    printf("\n");
    if (tam % 2 == 1) {
        printf("%d\n", b[tam / 2]);
    } else {
        printf("%d\n", (b[tam / 2 - 1] + b[tam / 2]) / 2);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    if (n < 2 || n > 100) {
        printf("Tamanho invalido");
        return 0;
    }

    int a[100], b[100];
    int tam = 0;

    PreencheVetor(a, b, n, &tam);
    if (tam == -1) return 0;
    if (tam == 0) {
        printf("Nao tem nenhum espiao");
        return 0;
    }
    MostraVetor(b, tam);
    return 0;
}

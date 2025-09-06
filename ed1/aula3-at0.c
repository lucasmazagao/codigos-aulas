#include <stdio.h>

int fatorial(int n) {
    printf("Entrando em fatorial(%d)\n", n);

    if (n == 0 || n == 1) {
        printf("Caso base atingido: fatorial(%d) = 1\n", n);
        return 1;
    } else {
        int resultado = n * fatorial(n - 1);
        printf("Retornando de fatorial(%d) = %d\n", n, resultado);
        return resultado;
    }
}

int main() {
    int numero;

    do {
        scanf("%d", &numero);

        if (numero < 0) {
            printf("Valor invalido! Tente novamente.\n");
        }
    } while (numero < 0);

    printf("Calculando fatorial de %d...\n", numero);
    int resultado = fatorial(numero);

    printf("Resultado final: %d\n", resultado);

    return 0;
}

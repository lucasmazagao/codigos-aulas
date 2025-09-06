#include <stdio.h>

int fibonacci(int n) {
    printf("Entrando em fibonacci(%d)\n", n);

    // caso base
    if (n == 0) {
        printf("Caso base atingido: fibonacci(0) = 0\n");
        return 0;
    } else if (n == 1) {
        printf("Caso base atingido: fibonacci(1) = 1\n");
        return 1;
    } 
    // caso geral
    else {
        int resultado = fibonacci(n - 1) + fibonacci(n - 2);
        printf("Retornando de fibonacci(%d) = %d\n", n, resultado);
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

    printf("Calculando fibonacci de %d...\n", numero);
    int resultado = fibonacci(numero);

    printf("Resultado final: %d\n", resultado);

    return 0;
}
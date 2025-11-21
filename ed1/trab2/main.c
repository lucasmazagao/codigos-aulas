#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

#define MAX_INPUT 10000

int main(void) {
    char operacao[20];
    char num_a[MAX_INPUT];
    char num_b[MAX_INPUT];
    
    // Lê a operação e os dois números
    if (scanf("%s %s %s", operacao, num_a, num_b) != 3) {
        return 1;
    }
    
    // Cria BigInts com capacidade suficiente
    BigInt *a = criar(MAX_INPUT);
    BigInt *b = criar(MAX_INPUT);
    
    if (!a || !b) {
        if (a) destruir(&a);
        if (b) destruir(&b);
        return 1;
    }
    
    // Define os valores dos BigInts
    if (!definir(a, num_a) || !definir(b, num_b)) {
        destruir(&a);
        destruir(&b);
        return 1;
    }
    
    if (strcmp(operacao, "soma") == 0) {
        BigInt *resultado = soma(a, b);
        if (!resultado) {
            destruir(&a);
            destruir(&b);
            return 1;
        }
        printf("Resultado :: ");
        imprimir(resultado);
        printf("\n");
        destruir(&resultado);
    }
    else if (strcmp(operacao, "igual") == 0) {
        int resultado = maior(a, b);
        printf("Resultado :: %s\n", resultado == 0 ? "True" : "False");
    }
    else if (strcmp(operacao, "maior") == 0) {
        int resultado = maior(a, b);
        printf("Resultado :: %s\n", resultado == 1 ? "True" : "False");
    }
    else if (strcmp(operacao, "menor") == 0) {
        int resultado = menor(a, b);
        printf("Resultado :: %s\n", resultado == 1 ? "True" : "False");
    }
    else {
        destruir(&a);
        destruir(&b);
        return 1;
    }
    
    // Libera memória
    destruir(&a);
    destruir(&b);
    
    return 0;
}

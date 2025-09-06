#include <stdio.h>

int main() {
    float nota, soma = 0;
    int contador = 0;

    while (1) {
        scanf("%f", &nota);

        if (nota < 0) {
            break;
        }

        soma += nota;
        contador++;
    }

    if (contador == 0) {
        printf("A media aritmetica do aluno eh 0.00\n");
    } else {
        printf("A media aritmetica do aluno eh %.2f\n", soma / contador);
    }

    return 0;
}
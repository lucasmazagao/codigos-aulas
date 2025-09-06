#include <stdio.h>

int main() {
    int num, num2, casas[10], inicio, fim;
    int i = 0, palin = 1;
    
    scanf("%d", &num);

    if (num <= 0) {
        printf("O numero nao pode ser negativo.\n");
        return 0;
    }

    num2 = num;

    while (num2 > 0) {
        casas[i] = num2 % 10;
        num2 /= 10;
        i++;
    }

    inicio = 0;
    fim = i - 1;

    while (inicio < fim) {
        if (casas[inicio] != casas[fim]) {
            palin = 0;
            break;
        }
        inicio++;
        fim--;
    } 

    printf("%d ", num);
    if (palin) {
        printf("eh um palindromo.\n");
    } else {
        printf("nao eh um palindromo.\n");
    }

    return 0;
}

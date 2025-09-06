#include <stdio.h>

void hanoi(int n, char origem, char destino, char auxiliar) {
    if (n == 1) {
        printf("Mova o disco 1 de %c para %c\n", origem, destino);
    } else {
        hanoi(n - 1, origem, auxiliar, destino);
        printf("Mova o disco %d de %c para %c\n", n, origem, destino);
        hanoi(n - 1, auxiliar, destino, origem);
    }
}

int main() {
    int tamanho;
    scanf("%d", &tamanho);
    hanoi(tamanho, 'A', 'C', 'B'); 
    return 0;
}
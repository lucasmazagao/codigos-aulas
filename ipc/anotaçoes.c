estruturas basicas

---
corpo

#include <stdio.h>

int main() {

    int c;

    scanf("%d", &c);

    printf("exemplo %d", c);

    return 0;
}

---
for e matriz

int i, j, n, matriz[100][100];

for (n = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
        scanf("%d", &matriz[i][j]);
    }
}

---
do-while

int i, j;

scanf("%d %d", &i, &j);

do {
    int x = j - i;

    printf("%d - %d = %d", j, i, x);
    i++;
} while (i < j);

---
if-else

int a;
scanf("%d", &a);

if (a > 0) {
    printf("Número positivo\n");
} else if (a < 0) {
    printf("Número negativo\n");
} else {
    printf("Zero\n");
}

---
arrays


---
switch-case

int opcao;
scanf("%d", &opcao);
switch (opcao) {
    case 1:
        printf("Opção 1 selecionada\n");
        break;
    case 2:
        printf("Opção 2 selecionada\n");
           break;
    default:
        printf("Opção inválida\n");
        break;
}

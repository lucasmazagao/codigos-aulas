#include <stdio.h>

int main() {
    int pessoas, formas = 0;

    scanf("%d", &pessoas);

    if (pessoas <= 0) {
        printf("Numero invalido de pessoas para formacao de fileiras.\n");
    } else {
        for (int i = 1; i <= pessoas; i++) {
            if (pessoas % i == 0) {
                formas++;
            }
        }
        printf("Eh possivel organizar as cadeiras de %d formas diferentes.\n", formas);
    }

    return 0;
}

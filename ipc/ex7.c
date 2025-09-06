#include <stdio.h>

int main() {
    int num, n, div;
    scanf("%d", &num);

    if (num < 2) {
        printf("Nao pode numero menor que 2.");
        return 0;
    }

    for (n = 2; n <= num; n++) {
        for (div = 2; div <= n / 2; div++) {
            if (n % div == 0) {
                break;
            }
        }

        if (div > n / 2) {
            printf("%d ", n);
        }
    }

    return 0;
}
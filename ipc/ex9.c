# include <stdio.h>

int main() {

    int n, m, i, j, matriz[100][100], mat2[100], c = 0, começo, fim;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    
    scanf("%d", &m);

    for (i = 0; i < m; i++) {
        scanf("%d", &mat2[i]);

        if (mat2[i] < 1 || mat2[i] > n) {
            printf("Cidade invalida fornecida.");
            return 0;
        }
    }

    for (i = 0; i < m - 1; i++) {
        começo = mat2[i] - 1;
        fim = mat2[i + 1] - 1;
        c += matriz[começo][fim];
    }

    printf("O custo total da viagem foi de %d reais.", c);
    return 0;
}
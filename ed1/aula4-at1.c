#include <stdio.h>
#include <stdlib.h>

void intercalacao(int vetor[], int l, int r) {
    printf("INTERCALACAO [%d,%d]:", l, r);
    for (int i = l; i <= r; i++) {
        printf(" %d", vetor[i]);
    }
    printf("\n");
}

void merge(int vetor[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int*) malloc(n1 * sizeof(int));
    int *R = (int*) malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = vetor[l + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k++] = L[i++];
        } else {
            vetor[k++] = R[j++];
        }
    }

    while (i < n1) vetor[k++] = L[i++];
    while (j < n2) vetor[k++] = R[j++];
    intercalacao(vetor, l, r);

    free(L);
    free(R);
}

void mergesort(int v[], int l, int r) {
    if (l < r) {
        printf("DIVISAO [%d,%d]\n", l, r);
        int m = (l + r) / 2;
        mergesort(v, l, m);
        mergesort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

int main() {
    int tamanho;
    scanf("%d", &tamanho);

    int vetor[tamanho];
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }

    mergesort(vetor, 0, tamanho - 1);

    return 0;
}

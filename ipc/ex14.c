#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int tamanho;
    int *elementos;
} Conjunto;

Conjunto Union(Conjunto A, Conjunto B);
Conjunto Inter(Conjunto A, Conjunto B);
Conjunto Diff(Conjunto A, Conjunto B);
int EstaDentro(Conjunto A, int e);

void print_conjunto(Conjunto C) {
    if (C.tamanho == 0) {
        printf("Conjunto vazio\n");
        return;
    }

    for (int i = 0; i < C.tamanho; i++) {
        printf("%d", C.elementos[i]);
        if (i < C.tamanho - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int EstaDentro(Conjunto A, int e) {
    for (int i = 0; i < A.tamanho; i++) {
        if (A.elementos[i] == e) {
            return 1;
        }
    }
    return 0;
}

Conjunto Union(Conjunto A, Conjunto B) {
    Conjunto C;
    C.elementos = (int *)malloc((A.tamanho + B.tamanho) * sizeof(int));
    C.tamanho = 0;

    for (int i = 0; i < A.tamanho; i++) {
        C.elementos[C.tamanho++] = A.elementos[i];
    }

    for (int i = 0; i < B.tamanho; i++) {
        if (!EstaDentro(A, B.elementos[i])) {
            C.elementos[C.tamanho++] = B.elementos[i];
        }
    }
    return C;
}

Conjunto Inter(Conjunto A, Conjunto B) {
    Conjunto C;
    C.elementos = (int *)malloc(A.tamanho * sizeof(int));
    C.tamanho = 0;

    for (int i = 0; i < A.tamanho; i++) {
        if (EstaDentro(B, A.elementos[i])) {
            C.elementos[C.tamanho++] = A.elementos[i];
        }
    }
    return C;
}

Conjunto Diff(Conjunto A, Conjunto B) {
    Conjunto C;
    C.elementos = (int *)malloc(A.tamanho * sizeof(int));
    C.tamanho = 0;

    for (int i = 0; i < A.tamanho; i++) {
        if (!EstaDentro(B, A.elementos[i])) {
            C.elementos[C.tamanho++] = A.elementos[i];
        }
    }
    return C;
}

int main() {
    Conjunto A, B;
    int n_temp;

    scanf("%d", &n_temp);
    if (n_temp < 0) {
        printf("Tamanho invalido");
        return 0;
    }
    
    A.elementos = (int *)malloc(n_temp * sizeof(int));
    A.tamanho = 0;
    
    for (int i = 0; i < n_temp; i++) {
        int elem;
        scanf("%d", &elem);
        if (!EstaDentro(A, elem)) {
            A.elementos[A.tamanho] = elem;
            A.tamanho++;
        }
    }

    scanf("%d", &n_temp);
    if (n_temp < 0) {
        printf("Tamanho invalido");
        free(A.elementos);
        return 0;
    }

    B.elementos = (int *)malloc(n_temp * sizeof(int));
    B.tamanho = 0;
    
    for (int i = 0; i < n_temp; i++) {
        int elem;
        scanf("%d", &elem);
        if (!EstaDentro(B, elem)) {
            B.elementos[B.tamanho] = elem;
            B.tamanho++;
        }
    }

    Conjunto C_union = Union(A, B);
    Conjunto C_inter = Inter(A, B);
    Conjunto C_diff = Diff(A, B);

    print_conjunto(C_union);
    print_conjunto(C_inter);
    print_conjunto(C_diff);

    free(A.elementos);
    free(B.elementos);
    free(C_union.elementos);
    free(C_inter.elementos);
    free(C_diff.elementos);

    return 0;
}
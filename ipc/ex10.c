#include <stdio.h>

struct veiculo {
    int id;
    int categoria;
    int velocidade_max;
};

int main() {
    int n;
    scanf("%d", &n);

    struct veiculo veiculos[100];
    int ids_usados[100];
    int usados = 0;

    for (int i = 0; i < n; i++) {
        int id, cat, vel;
        scanf("%d %d %d", &id, &cat, &vel);

        if (id < 1 || cat < 1 || cat > 3 || vel < 0) {
            printf("identificador, categoria ou velocidade invalida...");
            return 0;
        }

        for (int j = 0; j < usados; j++) {
            if (ids_usados[j] == id) {
                printf("identificador repetido...");
                return 0;
            }
        }

        ids_usados[usados++] = id;

        veiculos[i].id = id;
        veiculos[i].categoria = cat;
        veiculos[i].velocidade_max = vel;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (veiculos[j].velocidade_max > veiculos[i].velocidade_max) {
                struct veiculo temp = veiculos[i];
                veiculos[i] = veiculos[j];
                veiculos[j] = temp;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (i < n)
            printf("%d ", veiculos[i].id);
        else
            printf("0 ");
    }

    printf("\n");

    int car = 0, moto = 0, f1 = 0;
    for (int i = 0; i < n; i++) {
        if (veiculos[i].categoria == 1 && car == 0)
            car = veiculos[i].id;
        if (veiculos[i].categoria == 2 && moto == 0)
            moto = veiculos[i].id;
        if (veiculos[i].categoria == 3 && f1 == 0)
            f1 = veiculos[i].id;
    }

    printf("Carro: %d\n", car);
    printf("Moto: %d\n", moto);
    printf("F1: %d\n", f1);

    return 0;
}

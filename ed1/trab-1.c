#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // timeval gettimeofday


void mostrar_menu() {
    printf("\nEscolha uma opcao:\n");
    printf("1 - Inverter Ordem\n");
    printf("2 - Busca Sequencial\n");
    printf("3 - Busca Binaria Iterativa\n");
    printf("4 - Busca Binaria Recursiva\n");
    printf("5 - Encerrar\n");
}

void merge(int *vetor, int esquerda, int meio, int direita) {
    int i, j, k;
    int tamanho_esquerda = meio - esquerda + 1;
    int tamanho_direita = direita - meio;

    int *temp_esquerda = malloc(sizeof(int) * tamanho_esquerda);
    int *temp_direita = malloc(sizeof(int) * tamanho_direita);
    
    for (int i = 0; i < tamanho_esquerda; i++) {
        temp_esquerda[i] = vetor[esquerda + i];
    }
    for (int i = 0; i < tamanho_direita; i++) {
        temp_direita[i] = vetor[meio + 1 + i];
    }

    i = esquerda;
    j = 0;
    k = 0;
    while (j < tamanho_esquerda && k < tamanho_direita) {
        if (temp_esquerda[j] <= temp_direita[k]) {
            vetor[i] = temp_esquerda[j];
            j++;
        } else {
            vetor[i] = temp_direita[k];
            k++;
        }
        i++;
    }

    free(temp_esquerda);
    free(temp_direita);
}

void ordenar_vetor(int *vetor, int esquerda, int direita) {
    if (esquerda >= direita) {
        return;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    ordenar_vetor(vetor, esquerda, meio);
    ordenar_vetor(vetor, meio + 1, direita);

    merge(vetor, esquerda, meio, direita);
}

void inverter_ordem(int *vetor, int tamanho) {
    int *inverso = malloc(sizeof(int) * tamanho);

    for (int i = 0; i < tamanho; i++) {
        inverso[i] = vetor[tamanho - 1 - i];
    }

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = inverso[i];
    }

    free(inverso);

    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void busca_sequencial(int *vetor, int tamanho) {
    int sucesso = 0;
    int numero_buscado;

    printf("Digite o numero a ser buscado:\n");
    scanf("%d", &numero_buscado);

    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == numero_buscado) {
            sucesso = 1;
            break;
        }
    }

    if (sucesso == 0) {
        printf("NAO\n");
    } else {
        printf("SIM\n");
    }
}

void busca_binaria_iter(int *vetor, int tamanho) {
    int sucesso = 0;
    int numero_buscado;
    int loop = 1;
    scanf("%d", &numero_buscado);

    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == numero_buscado) {
            sucesso = 1;
            break;
        } else if (vetor[meio] > numero_buscado) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (sucesso == 0) {
        printf("NAO\n");
    } else {
        printf("SIM\n");
    }
}

void busca_binaria_rec(int *vetor, int tamanho) {
    int numero_buscado;
    scanf("%d", &numero_buscado);

    int inicio = 0;
    int fim = tamanho - 1;
    int sucesso = 0;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == numero_buscado) {
            sucesso = 1; 
            break;
        } else if (vetor[meio] > numero_buscado) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    if (sucesso == 0) {
        printf("NAO\n");
    } else {
        printf("SIM\n");
    }
}

int main () {
    int tamanho, opcao;
    int *vetor = NULL;
    int loop = 1;
    tamanho = 0;

    
    while (tamanho < 1 || tamanho > 5000) {
        printf("Digite o tamanho do vetor, de 1 a 5000:\n");
        scanf("%d", &tamanho);
    }

    vetor = malloc(sizeof(int) * tamanho);

    int esquerda = 0;
    int direita = tamanho - 1;

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }

    ordenar_vetor(vetor, esquerda, direita);

    while (loop) {
        mostrar_menu();

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inverter_ordem(vetor, tamanho);
                break;
            case 2:
                busca_sequencial(vetor, tamanho);
                break;
            case 3:
                busca_binaria_rec(vetor, tamanho);
                break;
            case 4:
                busca_binaria_iter(vetor, tamanho);
                break;
            case 5:
                loop = 0;
                break;
            default:
            printf("Opcao invalida.\n");
        }
    }
    free(vetor);
}
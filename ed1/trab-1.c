#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void merge(int *vetor, int esquerda, int meio, int direita) {
    int i, j, k;
    int tamanho_esquerda = meio - esquerda + 1;
    int tamanho_direita = direita - meio;

    // Cria arrays temporarios para armazenar os dados
    int *temp_esquerda = malloc(sizeof(int) * tamanho_esquerda);
    int *temp_direita = malloc(sizeof(int) * tamanho_direita);

    // Copia os dados para os arrays temporarios
    for (int i = 0; i < tamanho_esquerda; i++) {
        temp_esquerda[i] = vetor[esquerda + i];
    }
    for (int i = 0; i < tamanho_direita; i++) {
        temp_direita[i] = vetor[meio + 1 + i];
    }

    // Merge os arrays temporarios de volta no array original
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

     // Copia os elementos restantes de um dos temps, se houver
    while (j < tamanho_esquerda) {
        vetor[i] = temp_esquerda[j];
        j++;
        i++;
    }

    while (k < tamanho_direita) {
        vetor[i] = temp_direita[k];
        k++;
        i++;
    }

    free(temp_esquerda);
    free(temp_direita);
}

void ordenar_vetor(int *vetor, int esquerda, int direita) {
    // Condicao base para a recursao
    if (esquerda >= direita) {
        return;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    // Ordena as duas metades do vetor
    // Chama a funcao recursivamente para as duas metades
    ordenar_vetor(vetor, esquerda, meio);
    ordenar_vetor(vetor, meio + 1, direita);

    merge(vetor, esquerda, meio, direita);
}

void inverter_ordem(int *vetor, int tamanho) {

    // Usando um vetor temporario para armazenar o vetor invertido com malloc
    // pois o tamanho do vetor inverso nao pode ser maior que 5000
    int *inverso = malloc(sizeof(int) * tamanho);

    // Copia os elementos do vetor original para o vetor inverso
    for (int i = 0; i < tamanho; i++) {
        inverso[i] = vetor[tamanho - 1 - i];
    }

    for (int i = 0; i < tamanho; i++) {
        vetor[i] = inverso[i];
    }

    free(inverso);

    // Mostra o vetor invertido
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void busca_sequencial(int *vetor, int tamanho) {
    int sucesso = 0;
    int numero_buscado;

    scanf("%d", &numero_buscado);

    // Busca sequencial a partir do inicio do vetor
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

    // Enquanto o inicio for menor ou igual ao fim, continua a busca
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

int busca_binaria_rec(int *vetor, int inicio, int fim, int numero_buscado) {
    // Condicao base: se o inicio for maior que o fim, o elemento nao esta no vetor
    if (fim < inicio) {
        return 0;
    }

    int meio = inicio + ((fim - inicio) / 2);

    // Verifica se o elemento do meio é o que estamos buscando
    // Se o elemento do meio for maior que o numero buscado, chama a funcao novamente
    // para a metade esquerda do vetor, senao, chama para a metade direita
    if(vetor[meio] == numero_buscado) {
        return 1;
    } else if (vetor[meio] > numero_buscado) {
        return busca_binaria_rec(vetor, inicio, meio - 1, numero_buscado);
    } else {
        return busca_binaria_rec(vetor, meio + 1, fim, numero_buscado);
    }
}

int main () {
    // Declaracao das variaveis
    int tamanho, opcao;
    int *vetor = NULL;
    int loop = 1;
    tamanho = 0;

    // Validacao do tamanho do vetor
    while (tamanho < 1 || tamanho > 5000) {
        scanf("%d", &tamanho);
    }

    // Alocacao dinamica do vetor
    vetor = malloc(sizeof(int) * tamanho);

    // Inicializacao dos indices para ordenacao
    int esquerda = 0;
    int direita = tamanho - 1;
    for (int i = 0; i < tamanho; i++) {
        scanf("%d", &vetor[i]);
    }

    // Ordena o vetor antes de entrar no menu, como pedido no enunciado
    ordenar_vetor(vetor, esquerda, direita);

    while (loop) {
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inverter_ordem(vetor, tamanho);
                break;
            case 2:
                busca_sequencial(vetor, tamanho);
                break;
            case 3:
                busca_binaria_iter(vetor, tamanho);
                break;
            case 4:
            // Pela logica da busca recursiva, passamos os valores iniciais
            // de inicio e fim antes de chamar a funcao
                int inicio = 0;
                int fim = tamanho - 1;
                int numero_buscado;

                scanf("%d", &numero_buscado);
                
                int sucesso = busca_binaria_rec(vetor, inicio, fim, numero_buscado);
                if (sucesso == 0) {
                    printf("NAO\n");
                } else {
                    printf("SIM\n");
                }
                break;
            case 5:
                loop = 0;
                break;
        }
    }
    free(vetor);
}
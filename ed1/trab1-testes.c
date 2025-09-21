#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Funcoes de ordenacao e busca
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
}

void busca_sequencial(int *vetor, int tamanho, int numero_buscado) {
    // Busca sequencial a partir do inicio do vetor
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == numero_buscado) {
            break;
        }
    }
}

void busca_binaria_iter(int *vetor, int tamanho, int numero_buscado) {
    int inicio = 0;
    int fim = tamanho - 1;

    // Enquanto o inicio for menor ou igual ao fim, continua a busca
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        if (vetor[meio] == numero_buscado) {
            break;
        } else if (vetor[meio] > numero_buscado) {
            // Elemento procurado esta na metade esquerda
            fim = meio - 1;
        } else {
            // Elemento procurado esta na metade direita
            inicio = meio + 1;
        }
    }
}

void busca_binaria_rec(int *vetor, int inicio, int fim, int numero_buscado) {
    // Condicao base: se o inicio for maior que o fim, o elemento nao esta no vetor
    if (fim < inicio) {
        return;
    }

    int meio = inicio + ((fim - inicio) / 2);

    // Verifica se o elemento do meio e o que estamos buscando
    if(vetor[meio] == numero_buscado) {
        // Elemento encontrado, retorna
        return;
    } else if (vetor[meio] > numero_buscado) {
        // Se o elemento do meio for maior que o numero buscado, 
        // chama a funcao recursivamente para a metade esquerda do vetor
        return busca_binaria_rec(vetor, inicio, meio - 1, numero_buscado);
    } else {
        // Caso contrario, chama a funcao recursivamente para a metade direita
        return busca_binaria_rec(vetor, meio + 1, fim, numero_buscado);
    }
}

// Funcões auxiliares para os testes de desempenho
void gerar_vetor_aleatorio(int *vetor, int tamanho) {
    // Preenche o vetor com numeros aleatorios entre 0 e 999
    // Utiliza a funcao rand() para gerar valores pseudo-aleatorios
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = rand() % 1000; // Numeros entre 0 e 999
    }
}

void executar_teste(int *vetor, int tamanho, int opcao, int numero_buscado) {
    // Executa o teste de acordo com a opcao selecionada
    // Opcao 1: Inverte a ordem do vetor
    // Opcao 2: Realiza busca sequencial
    // Opcao 3: Realiza busca binaria iterativa
    // Opcao 4: Realiza busca binaria recursiva
    switch (opcao) {
        case 1:
            inverter_ordem(vetor, tamanho);
            break;
        case 2:
            busca_sequencial(vetor, tamanho, numero_buscado);
            break;
        case 3:
            busca_binaria_iter(vetor, tamanho, numero_buscado);
            break;
        case 4:
            // Pela logica da busca recursiva, passamos os valores iniciais
            // de inicio e fim antes de chamar a funcao
            busca_binaria_rec(vetor, 0, tamanho - 1, numero_buscado);
            break;
                
    }
}

int main() {
    // Inicializacao do gerador de numeros aleatorios com base no tempo atual
    srand(time(NULL));
    LARGE_INTEGER freq, inicio, fim;
    double tempo_decorrido;
    double soma;
    double media;

    QueryPerformanceFrequency(&freq);
    
    // Arrays com os tamanhos de vetor e opcoes de teste a serem executados
    int tamanhos_testes[] = {10, 100, 1000, 5000};
    int opcoes_testes[] = {1, 2, 3, 4};

    // Loop principal que testa cada tamanho de vetor
    for (int i = 0; i < 4; i++) {
        int tamanho = tamanhos_testes[i];
        
        // Alocacao dinamica do vetor com o tamanho especificado
        int *vetor = malloc(sizeof(int) * tamanho);
        
        // Gera numero aleatorio que sera usado nas buscas
        int numero_buscado = rand() % 1000;
        for (int j = 0; j < 4; j++) {
            int opcao = opcoes_testes[j];
            soma = 0.0;

            printf("Teste de vetor de tamanho %d no metodo %d\n", tamanho, opcao);
            
            // Gera um novo vetor aleatorio para o teste e ordena
            gerar_vetor_aleatorio(vetor, tamanho);
            ordenar_vetor(vetor, 0, tamanho - 1);
            
            // Executa o mesmo teste 100 vezes para obter media requerida
            for (int k = 0; k < 100; k++) {
                QueryPerformanceCounter(&inicio);
                executar_teste(vetor, tamanho, opcao, numero_buscado);
                QueryPerformanceCounter(&fim);
                
                tempo_decorrido = (double)(fim.QuadPart - inicio.QuadPart) / freq.QuadPart;
                soma = soma + tempo_decorrido;
            }
            media = soma / 100;

            printf("Tempo medio decorrido: %.9f segundos\n", media);
            printf("--------------------------------------------\n");
        }
        free(vetor);
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h> // timeval gettimeofday


void mostrar_menu() {
    printf("Escolha uma opcao:\n");
    printf("1 - Inverter Ordem\n");
    printf("2 - Busca Sequencial\n");
    printf("3 - Busca Binaria Iterativa\n");
    printf("4 - Busca Binaria Recursiva\n");
    printf("5 - Encerrar\n");
}

void inverter_ordem() {
}

void busca_sequencial() {
}

void busca_binaria_iter() {
}

void busca_binaria_rec() {
}

int main () {
    int tamanho, opcao;

    mostrar_menu();
    scanf("%d", &opcao);

    if (opcao == 1) {
        inverter_ordem();
    } else if (opcao == 2) {
        busca_sequencial();
    } else if (opcao == 3) {
        busca_binaria_rec();
    } else if (opcao == 4) {
        busca_binaria_iter();
    } else if (opcao == 5) {
        printf("Encerrando o programa.\n");
    } else {
        printf("Opcao invalida.\n");
    }
}
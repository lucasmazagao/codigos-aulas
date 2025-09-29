#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSD.h"

int main() {
    LSD *lista = lsd_cria();
    if (!lista) {
        return 1; // Erro na criação da lista
    }
    
    int opcao;
    while (1) {
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Inserir x no final
                int x;
                scanf("%d", &x);
                int resultado = lsd_insere_final(lista, x);
                
                if (resultado == 1) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            }
            case 2: { // Inserir x na posição p
                int p, x;
                scanf("%d %d", &p, &x);
                int resultado = lsd_insere_pos(lista, p, x);

                if (resultado == 1) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            }
            case 3: { // Remover elemento da posição p
                int p;
                scanf("%d", &p);
                LSD_Tipo removido;
                int resultado = lsd_remove_pos(lista, p, &removido);

                if (resultado == 1) {
                    printf("%d\n", removido);
                } else {
                    printf("ERRO\n");
                }
                break;
            }
            case 4: { // Consultar elemento da posição p
                int p;
                scanf("%d", &p);
                LSD_Tipo elem;
                int resultado = lsd_consulta_pos(lista, p, &elem);

                if (resultado == 1) {
                    printf("%d\n", elem);
                } else {
                    printf("ERRO\n");
                }
                break;
            }
            case 5: { // Buscar primeira ocorrência de x
                int x;
                scanf("%d", &x);
                int pos;
                int resultado = lsd_busca(lista, x, &pos);

                if (resultado == 1) {
                    printf("%d\n", pos);
                } else {
                    printf("-1\n");
                }
                break;
            }
            case 6: { // Imprimir tamanho da lista
                int tamanho = lsd_tamanho(lista);
                printf("%d\n", tamanho);
                break;
            }
            case 7: { // Imprimir a lista
                lsd_imprime(lista);
                break;
            }
            case 8: { // Esvaziar a lista
                lsd_limpa(lista);
                break;
            }
            case 9: { // Encerrar o programa
                lsd_destroi(&lista);
                return 0;
            }
            default:
                break;
        }
    }
    
    lsd_destroi(&lista);
    return 0;
}

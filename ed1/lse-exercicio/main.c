#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSE.h"

int main() {
    LSE *lista = lse_cria();
    if (!lista) {
        return 1; // Erro na criação da lista
    }
    
    int opcao;
    while (scanf("%d", &opcao) == 1) {
        switch (opcao) {
            case 1: { // Inserir x no final
                int x;
                scanf("%d", &x);
                int resultado = lse_insere_final(lista, x);
                printf("%d\n", (resultado == 1) ? 1 : 0);
                break;
            }
            case 2: { // Inserir x na posição p
                int p, x;
                scanf("%d %d", &p, &x);
                int resultado = lse_insere_pos(lista, p, x);
                printf("%d\n", (resultado == 1) ? 1 : 0);
                break;
            }
            case 3: { // Remover elemento da posição p
                int p;
                scanf("%d", &p);
                LSE_Tipo removido;
                int resultado = lse_remove_pos(lista, p, &removido);
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
                LSE_Tipo elem;
                int resultado = lse_consulta_pos(lista, p, &elem);
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
                int resultado = lse_busca(lista, x, &pos);
                if (resultado == 1) {
                    printf("%d\n", pos);
                } else {
                    printf("-1\n");
                }
                break;
            }
            case 6: { // Imprimir tamanho da lista
                int tamanho = lse_tamanho(lista);
                printf("%d\n", tamanho);
                break;
            }
            case 7: { // Imprimir a lista
                lse_imprime(lista);
                break;
            }
            case 8: { // Esvaziar a lista
                lse_limpa(lista);
                break;
            }
            case 9: { // Encerrar o programa
                lse_destroi(&lista);
                return 0;
            }
            default:
                break;
        }
    }
    
    lse_destroi(&lista);
    return 0;
}
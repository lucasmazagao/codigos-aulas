#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LSE.h"

int main() {
    LSE *lista = lse_cria();
    if (!lista) {
        return 1; // Erro em criar lista
    }
    
    int opcao;
    while (1) {
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Inserir x no final
                int x;
                scanf("%d", &x);
                int resultado = lse_insere_final(lista, x);
                if (resultado == 1) { // sucesso
                    printf("1\n");
                } else { // falha
                    printf("0\n");
                }
                break;
            }
            case 2: { // Inserir x na posição p
                int p, x;
                scanf("%d %d", &p, &x);
                int resultado = lse_insere_pos(lista, p, x);

                if (resultado == 1) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            }
            case 3: { // remove elemento da posição p
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
            case 5: { // buscar primeira vez que x aparece
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
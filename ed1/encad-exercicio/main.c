#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// concatena lista_origem no final da lista_destino
void concatena_listas(LinkedList *destino, LinkedList *origem)
{
	int tamanho = size_list(origem);
	int pos_destino = size_list(destino);
	
	// percorre lista origem e insere cada elemento no final da destino
	for (int i = 0; i < tamanho; i++) {
		int valor;
		if (get_node(origem, i, &valor) == 1) {
			insert_node(destino, pos_destino + i, valor);
		}
	}
}

// imprime os elementos da lista no formato [1 2 3]
void imprime_lista(const LinkedList *lista)
{
	int tamanho = size_list(lista);
	printf("[");
	
	for (int i = 0; i < tamanho; i++) {
		int valor;
		if (get_node(lista, i, &valor) == 1) {
			printf("%d", valor);
			if (i < tamanho - 1) {
				printf(" ");
			}
		}
	}
	
	printf("]\n");
}

int main(void)
{
	LinkedList *lista1 = create_linked_list();
	LinkedList *lista2 = create_linked_list();
	
	if (!lista1 || !lista2) {
		free_linked_list(&lista1);
		free_linked_list(&lista2);
		return 1;
	}
	
	int comando;
	
	while (scanf("%d", &comando) == 1) {
		switch (comando) {
			case 1: {
				// insere x na lista1 na posicao p
				int x, p;
				if (scanf("%d %d", &x, &p) == 2) {
					insert_node(lista1, p, x);
				}
				break;
			}
			case 2: {
				// insere x na lista2 na posicao p
				int x, p;
				if (scanf("%d %d", &x, &p) == 2) {
					insert_node(lista2, p, x);
				}
				break;
			}
			case 3: {
				// remove da posicao p da lista1
				int p, removido;
				if (scanf("%d", &p) == 1) {
					remove_node(lista1, p, &removido);
				}
				break;
			}
			case 4: {
				// remove da posicao p da lista2
				int p, removido;
				if (scanf("%d", &p) == 1) {
					remove_node(lista2, p, &removido);
				}
				break;
			}
			case 5:
				// lista2 no final da lista1
				concatena_listas(lista1, lista2);
				break;
			case 6:
				// lista1 no final da lista2
				concatena_listas(lista2, lista1);
				break;
			case 7:
				// imprime lista1
				imprime_lista(lista1);
				break;
			case 8:
				// imprime lista2
				imprime_lista(lista2);
				break;
			case 9:
				// encerra
				goto fim;
			default:
				// comando desconhecido: ignora
				break;
		}
	}
	fim: ;
	
	free_linked_list(&lista1);
	free_linked_list(&lista2);
	return 0;
}
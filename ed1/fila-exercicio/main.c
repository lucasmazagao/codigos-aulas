#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    // Criar duas pilhas independentes (usando como "filas")
    Stack *pilha1 = create_stack();
    Stack *pilha2 = create_stack();
    
    if (!pilha1 || !pilha2) {
        return 1; // Erro na criação das pilhas
    }
    
    int comando;
    while (1) {
        scanf("%d", &comando);

        switch (comando) {
            case 0: { // Encerrar o programa
                free_stack(&pilha1);
                free_stack(&pilha2);
                return 0;
            }
            
            case 1: { // Inserir x na pilha 1
                int x;
                scanf("%d", &x);
                push(pilha1, x);
                break;
            }
            
            case 2: { // Inserir x na pilha 2
                int x;
                scanf("%d", &x);
                push(pilha2, x);
                break;
            }
            
            case 3: { // Remoção priorizada em três etapas
                int removido;
                
                // A. tenta remover da pilha 2, se não houver remove da pilha 1
                if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                }
                
                // B. tenta remover da pilha 2, se não houver remove da pilha 1
                if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                }
                
                // C. tenta remover da pilha 1, se não houver remove da pilha 2
                if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                }
                
                break;
            }
            
            default:
                // Comando inválido, ignora
                break;
        }
    }
    
    // Limpeza de segurança (nunca deve chegar aqui)
    free_stack(&pilha1);
    free_stack(&pilha2);
    return 0;
}

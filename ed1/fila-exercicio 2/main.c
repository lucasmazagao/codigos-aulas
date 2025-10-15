#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main() {
    Stack *pilha1 = create_stack();
    Stack *pilha2 = create_stack();
    if (!pilha1 || !pilha2) {
        return 1;
    }
    int comando;
    while (1) {
        scanf("%d", &comando);
        switch (comando) {
            case 0: {
                free_stack(&pilha1);
                free_stack(&pilha2);
                return 0;
            }
            case 1: {
                int x;
                scanf("%d", &x);
                push(pilha1, x);
                break;
            }
            case 2: {
                int x;
                scanf("%d", &x);
                push(pilha2, x);
                break;
            }
            case 3: {
                int removido;
                if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                }
                if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                }
                if (pop(pilha1, &removido) == 1) {
                    printf("%d\n", removido);
                } else if (pop(pilha2, &removido) == 1) {
                    printf("%d\n", removido);
                }
                break;
            }
            default:
                break;
        }
    }
    free_stack(&pilha1);
    free_stack(&pilha2);
    return 0;
}

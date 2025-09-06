#include <stdio.h>

int main()
{
    int M, G, Sm, Sc, H, V = 0;
    
    scanf("%d %d %d %d %d", &M, &G, &Sm, &Sc, &H);

    if ((M <= 0) || (M > 5)) {
        printf("O identificador %d nao eh uma mistura valida...", M);
        return 0; 
    }

    if ((G <= 0) || (G > 5)) {
        printf("O identificador %d nao eh uma guarnicao valida...", G);
        return 0; 
    }

    if ((Sm <= 0) || (Sm > 5)) {
        printf("O identificador %d nao eh uma sobremesa valida...", Sm);
        return 0; 
    }

    if ((Sc <= 0) || (Sc > 5)) {
        printf("O identificador %d nao eh um suco valido...", Sc);
        return 0; 
    }

    if ((H <= 0) || (H > 2)) {
        printf("O identificador %d nao eh um horario valido...", H);
        return 0; 
    }
 
    switch(M) {
        case 2:
            V += 1;
            break;
        case 4:
            V -= 1;
            break;
        case 5:
            V -= 1;
            break;
    }

    switch(G) {
        case 1:
            V += 1;
            break;
        case 2:
            V += 1;
            break;
        case 4:
            V -= 1;
            break;
    }

    switch(Sm) {
        case 1:
            V += 1;
            break;
        case 2:
            V += 1;
            break;
        case 3:
            V -= 1;
            break;
        case 5:
            V -= 1;
            break;
    }

    switch(Sc) {
        case 1:
            V += 1;
            break;
        case 3:
            V -= 1;
            break;
    }

    if (H == 1) {
        if (V >= 1) {
            printf("Compensa bandecar. A vantagem eh de %d.", V);
        }
        else {
            printf("Nao compensa bandecar. A vantagem eh de %d.", V);
        }
    }

    if (H == 2) {
        if (V > 1) {
            printf("Compensa bandecar. A vantagem eh de %d.", V);
        }
        else {
            printf("Nao compensa bandecar. A vantagem eh de %d.", V);
        }
    }

    return 0;

}
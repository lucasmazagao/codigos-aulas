#include <stdio.h>

int main()
{

    int hoje, dias;
    int result;
    scanf("%d", &hoje);
    scanf("%d", &dias);
    
    if ((hoje > 7) || (hoje <= 0)) {
        printf("Este dia da semana nao existe");
        return 0;
    }
    
    if (dias < 0 ) {
        printf("Nao eh possivel voltar ao passado");
        return 0;
    }
    
    
    result = (hoje + dias) % 7;
    
    switch(result) {
        case 1:
            printf("Domingo");
        case 2:
            break;
            printf("Segunda-feira");
            break;
        case 3:
            printf("Terça-feira");
            break;
        case 4:
            printf("Quarta-feira");
            break;
        case 5:
            printf("Quinta-feira");
            break;
        case 6:
            printf("Sexta-feira");
            break;
        case 0:
            printf("Sabado");
            break;
    }
    
    return 0;
}
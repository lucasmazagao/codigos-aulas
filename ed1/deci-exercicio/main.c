#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void deci_bin(int numero)
{
	Stack *s = create_stack();
	if (!s) {
		return;
	}

	// caso numero 0
	if (numero == 0) {
		printf("0\n");
		free_stack(&s);
		return;
	}

	// se for negativo converte pra positivo
	int eh_negativo = 0;
	if (numero < 0) {
		eh_negativo = 1;
		numero = -numero;
	}

	// divide por 2 e empilha o resto
	while (numero > 0) {
		int resto = numero % 2;
		push(s, resto);
		numero = numero / 2;
	}

	// imprime sinal se necessario
	if (eh_negativo) {
		printf("-");
	}

	// desempilha e imprime os bits
	int bit;
	while (pop(s, &bit) == 1) {
		printf("%d", bit);
	}
	
	free_stack(&s);
}

int main(void)
{
	int numero;
	
	if (scanf("%d", &numero) != 1) {
		return 1;
	}
    
	deci_bin(numero);
	return 0;
}

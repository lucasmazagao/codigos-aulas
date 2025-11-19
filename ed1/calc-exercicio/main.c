#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack.h"

void avalia_expressao(const char *linha)
{
	Stack *s = create_stack();
	if (!s) {
		return;
	}

	char buf[512];
	strncpy(buf, linha, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';

	// strtok vai quebrar a string usando espaco de delim
	char *tok = strtok(buf, " ");
	while (tok != NULL) {
		char *endptr = NULL;
		long v = strtol(tok, &endptr, 10);
		
		if (endptr != tok && *endptr == '\0') {
			push(s, (int)v);
		} else {
			// considera o token um operador
			// faz pop de dois valores e aplica a operação
            // e dps push do que sobra
			int b, a;
			if (pop(s, &b) != 1 || pop(s, &a) != 1) {
				free_stack(&s);
				return;
			}

			int r;
			switch (tok[0]) {
				case '+':
					r = a + b;
					break;
				case '-':
					r = a - b;
					break;
				case '*':
					r = a * b;
					break;
				case '/':
                    // verifica divisão por zero
					if (b == 0) {
						free_stack(&s);
						return;
					}
					r = a / b;
					break;
                    // operador nao possivel
				default:
					free_stack(&s);
					return;
			}
			push(s, r);
		}

        // vai atras do outro token
		tok = strtok(NULL, " ");
	}

	int resultado;

	if (pop(s, &resultado) == 1) {
		printf("%d\n", resultado);
	}

    free_stack(&s);
}

int main(void)
{
	char linha[256];

	if (fgets(linha, sizeof(linha), stdin) == NULL) {
		return 1;
	}

    // tira o \n
	linha[strcspn(linha, "\n")] = '\0';
	avalia_expressao(linha);

	return 0;
}


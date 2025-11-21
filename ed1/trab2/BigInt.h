#ifndef BIGINT_H
#define BIGINT_H

// Tipo opaco definido no .c
typedef struct BigInt BigInt;

// Cria um BigInt com espaço para 'digitos' dígitos
BigInt *criar(int digitos);

// Define o valor de n a partir de uma string decimal
// retorna:  1 se sucesso;  0 se falhar
int definir(BigInt *n, const char *decimal);

// Retorna a soma de a e b (novo BigInt)
BigInt *soma(const BigInt *a, const BigInt *b);

// Retorna o maior entre a e b
// retorno: 1 se a > b, 0 se a == b, -1 se a < b
int maior(const BigInt *a, const BigInt *b);

// Retorna o menor entre a e b
// retorno: 1 se a < b, 0 se a == b, -1 se a > b
int menor(const BigInt *a, const BigInt *b);

// Libera a memória e zera o ponteiro
void destruir(BigInt **n);

// Imprime o BigInt na saída padrão
void imprimir(const BigInt *n);

#endif /* BIGINT_H */

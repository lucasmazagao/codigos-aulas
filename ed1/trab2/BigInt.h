#ifndef BIGINT_H
#define BIGINT_H

typedef struct BigInt BigInt;

BigInt *criar(int capacidade_digitos);

int definir(BigInt *numero, const char *texto_decimal);

BigInt *soma(const BigInt *primeiro_numero, const BigInt *segundo_numero);

int maior(const BigInt *primeiro_numero, const BigInt *segundo_numero);

int menor(const BigInt *primeiro_numero, const BigInt *segundo_numero);

void destruir(BigInt **ponteiro_numero);

void imprimir(const BigInt *numero);

#endif /* BIGINT_H */

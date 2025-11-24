#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"
#define TAMANHO_MAX_ENTRADA 10001 

// Lucas Ferreira Mazagão - 16304606

int main() {
    char nome_operacao[20];
    char texto_primeiro_numero[TAMANHO_MAX_ENTRADA];
    char texto_segundo_numero[TAMANHO_MAX_ENTRADA];
    
    // Lê o número de operações que virão
    int numero_operacoes = 0;
    if (scanf("%d", &numero_operacoes) != 1) {
        return 1; // erro de leitura
    }
    // Loop: processa exatamente n operações
    for (int i = 0; i < numero_operacoes; i++) {
        // Lê três tokens: operação e dois números
        if (scanf("%19s %10000s %10000s", nome_operacao, texto_primeiro_numero, texto_segundo_numero) != 3) {
            break;
        }
    
        // Cria dois BigInts para representar números grandes
        // (criar aloca memória dinamicamente conforme o tamanho necessário)
        BigInt *primeiro_numero = criar(TAMANHO_MAX_ENTRADA);
        BigInt *segundo_numero = criar(TAMANHO_MAX_ENTRADA);
        
        // Verifica se a alocação funcionou
        if (!primeiro_numero || !segundo_numero) {
            if (primeiro_numero) destruir(&primeiro_numero);
            if (segundo_numero) destruir(&segundo_numero);
            continue;  // Pula para próxima entrada
        }
        
        // Converte as strings lidas para BigInts internamente
        // (definir parseia a string e armazena os dígitos na estrutura)
        if (!definir(primeiro_numero, texto_primeiro_numero) || 
            !definir(segundo_numero, texto_segundo_numero)) {
            destruir(&primeiro_numero);
            destruir(&segundo_numero);
            continue;  // Pula para próxima entrada
        }
        
        // Processa a operação solicitada
        if (strcmp(nome_operacao, "soma") == 0) {
            // Soma os dois BigInts e retorna um novo BigInt com o resultado
            BigInt *resultado_soma = soma(primeiro_numero, segundo_numero);
            
            if (resultado_soma) {
                // Imprime o resultado da soma
                printf("Resultado :: ");
                imprimir(resultado_soma);
                printf("\n");
                
                destruir(&resultado_soma);
            }
        }
        else if (strcmp(nome_operacao, "igual") == 0) {
            // Verifica se os dois números são exatamente iguais
            // maior() retorna 0 quando são iguais, 1 se primeiro > segundo, -1 se primeiro < segundo
            int comparacao = maior(primeiro_numero, segundo_numero);
            printf("Resultado :: %s\n", comparacao == 0 ? "True" : "False");
        }
        else if (strcmp(nome_operacao, "maior") == 0) {
            // Verifica se o primeiro número é estritamente maior que o segundo
            // maior() retorna 1 se primeiro > segundo
            int comparacao = maior(primeiro_numero, segundo_numero);
            printf("Resultado :: %s\n", comparacao == 1 ? "True" : "False");
        }
        else if (strcmp(nome_operacao, "menor") == 0) {
            // se primeiro número é estritamente menor que o segundo
            // menor() retorna 1 se primeiro < segundo
            int comparacao = menor(primeiro_numero, segundo_numero);
            printf("Resultado :: %s\n", comparacao == 1 ? "True" : "False");
        }
        // Se operação não reconhecida, simplesmente ignora e continua
        
        // Libera memória antes da próxima iteração do loop
        destruir(&primeiro_numero);
        destruir(&segundo_numero);
        
    }

    return 0;
}

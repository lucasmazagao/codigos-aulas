#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"

struct BigInt {
    int len;
    int cap;
    char sinal;
    char *digitos;
};

BigInt *criar(int digitos) {
    BigInt *novo = (BigInt *)malloc(sizeof(BigInt));
    if (!novo) {
        return NULL;
    }
    
    novo->cap = digitos;
    novo->len = 0;
    novo->sinal = 1;
    
    novo->digitos = (char *)calloc(digitos, sizeof(char));
    if (!novo->digitos) {
        free(novo);
        return NULL;
    }
    
    return novo;
}

int definir(BigInt *n, const char *decimal) {
    if (!n || !decimal) {
        return 0;
    }
    
    int inicio = 0;
    int tam = strlen(decimal);
    
    if (decimal[0] == '-') {
        n->sinal = -1;
        inicio = 1;
    } else if (decimal[0] == '+') {
        n->sinal = 1;
        inicio = 1;
    } else {
        n->sinal = 1;
    }
    
    while (inicio < tam && decimal[inicio] == '0') {
        inicio++;
    }
    
    if (inicio == tam) {
        n->len = 1;
        n->digitos[0] = 0;
        n->sinal = 1;
        return 1;
    }
    
    int num_digitos = tam - inicio;
    
    if (num_digitos > n->cap) {
        return 0;
    }
    
    n->len = num_digitos;
    for (int i = 0; i < num_digitos; i++) {
        char c = decimal[tam - 1 - i];
        if (c < '0' || c > '9') {
            return 0;
        }
        n->digitos[i] = c - '0';
    }
    
    return 1;
}

int maior(const BigInt *a, const BigInt *b) {
    if (!a || !b) {
        return 0;
    }
    
    if (a->sinal > b->sinal) {
        return 1;
    }
    if (a->sinal < b->sinal) {
        return -1;
    }
    
    int resultado_comparacao;
    
    if (a->len > b->len) {
        resultado_comparacao = 1;
    } else if (a->len < b->len) {
        resultado_comparacao = -1;
    } else {
        resultado_comparacao = 0;
        for (int i = a->len - 1; i >= 0; i--) {
            if (a->digitos[i] > b->digitos[i]) {
                resultado_comparacao = 1;
                break;
            } else if (a->digitos[i] < b->digitos[i]) {
                resultado_comparacao = -1;
                break;
            }
        }
    }
    
    if (a->sinal == -1) {
        resultado_comparacao = -resultado_comparacao;
    }
    
    return resultado_comparacao;
}

int menor(const BigInt *a, const BigInt *b) {
    return -maior(a, b);
}

BigInt *soma(const BigInt *a, const BigInt *b) {
    if (!a || !b) {
        return NULL;
    }
    
    int tamanho_max = (a->len > b->len ? a->len : b->len) + 1;
    BigInt *resultado = criar(tamanho_max);
    if (!resultado) {
        return NULL;
    }
    
    if (a->sinal == b->sinal) {
        int carry = 0;
        int i;
        
        for (i = 0; i < tamanho_max; i++) {
            int digito_a = (i < a->len) ? a->digitos[i] : 0;
            int digito_b = (i < b->len) ? b->digitos[i] : 0;
            
            int soma_parcial = digito_a + digito_b + carry;
            resultado->digitos[i] = soma_parcial % 10;
            carry = soma_parcial / 10;
        }
        
        resultado->len = tamanho_max;
        while (resultado->len > 1 && resultado->digitos[resultado->len - 1] == 0) {
            resultado->len--;
        }
        
        resultado->sinal = a->sinal;
    }
    else {
        const BigInt *maior_abs, *menor_abs;
        
        int comparacao = maior(a, b);
        if (a->sinal == 1) {
            if (a->len > b->len || (a->len == b->len && comparacao >= 0)) {
                maior_abs = a;
                menor_abs = b;
                resultado->sinal = 1;
            } else {
                maior_abs = b;
                menor_abs = a;
                resultado->sinal = -1;
            }
        } else {
            if (b->len > a->len || (b->len == a->len && comparacao <= 0)) {
                maior_abs = b;
                menor_abs = a;
                resultado->sinal = 1;
            } else {
                maior_abs = a;
                menor_abs = b;
                resultado->sinal = -1;
            }
        }
        
        int emprestimo = 0;
        for (int i = 0; i < maior_abs->len; i++) {
            int digito_maior = maior_abs->digitos[i];
            int digito_menor = (i < menor_abs->len) ? menor_abs->digitos[i] : 0;
            
            int diferenca = digito_maior - digito_menor - emprestimo;
            if (diferenca < 0) {
                diferenca += 10;
                emprestimo = 1;
            } else {
                emprestimo = 0;
            }
            
            resultado->digitos[i] = diferenca;
        }
        
        resultado->len = maior_abs->len;
        while (resultado->len > 1 && resultado->digitos[resultado->len - 1] == 0) {
            resultado->len--;
        }
        
        if (resultado->len == 1 && resultado->digitos[0] == 0) {
            resultado->sinal = 1;
        }
    }
    
    return resultado;
}

void destruir(BigInt **n) {
    if (n && *n) {
        if ((*n)->digitos) {
            free((*n)->digitos);
        }
        
        free(*n);
        
        *n = NULL;
    }
}

void imprimir(const BigInt *n) {
    if (!n) {
        printf("NULL");
        return;
    }
    
    if (n->sinal == -1 && !(n->len == 1 && n->digitos[0] == 0)) {
        printf("-");
    }
    
    for (int i = n->len - 1; i >= 0; i--) {
        printf("%d", n->digitos[i]);
    }
}

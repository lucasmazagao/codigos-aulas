#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BigInt.h"
#include "LinkedList.h"

// Usamos base 10^4: cada bloco guarda até 4 dígitos decimais (0 a 9999)
// Isso facilita multiplicação/divisão futuras e evita overflow rápido
#define BASE 10000
#define DIGITOS_POR_BLOCO 4

struct BigInt {
    LinkedList *blocos_digitos;  // Lista encadeada de blocos (cada nó = até 4 dígitos)
    int sinal;                   // 1 = positivo, -1 = negativo
};

// Funções auxiliares privadas (usadas internamente para operações)
int comparar_magnitude(const BigInt *primeiro, const BigInt *segundo);
BigInt *somar_magnitude(const BigInt *primeiro, const BigInt *segundo);
BigInt *subtrair_magnitude(const BigInt *numero_maior, const BigInt *numero_menor);

// criar: aloca memória e inicializa um BigInt vazio
BigInt *criar(int capacidade_digitos) {
    // Nota: capacidade_digitos é ignorado (lista cresce dinamicamente),
    // mas mantemos o parâmetro para compatibilidade com a interface
    (void)capacidade_digitos;  // Evita warning de parâmetro não usado
    
    BigInt *novo_numero = (BigInt *)malloc(sizeof(BigInt));
    if (!novo_numero) return NULL;
    
    novo_numero->blocos_digitos = create_linked_list();
    if (!novo_numero->blocos_digitos) {
        free(novo_numero);
        return NULL;
    }
    
    novo_numero->sinal = 1;  // Positivo por padrão
    return novo_numero;
}

// definir: converte uma string decimal para BigInt
// Ex: "123456789" vira blocos [6789], [2345], [1] (da direita pra esquerda)
int definir(BigInt *numero, const char *texto_decimal) {
    if (!numero || !texto_decimal) return 0;
    
    // Limpa a lista atual (se já tinha algum número armazenado)
    while (!is_empty_list(numero->blocos_digitos)) {
        remove_node(numero->blocos_digitos, 0, NULL);
    }

    int tamanho_texto = strlen(texto_decimal);
    int posicao_inicio = 0;

    // Detecta e processa o sinal (+ ou -)
    if (texto_decimal[0] == '-') {
        numero->sinal = -1;
        posicao_inicio = 1;
    } else if (texto_decimal[0] == '+') {
        numero->sinal = 1;
        posicao_inicio = 1;
    } else {
        numero->sinal = 1;
    }

    // Lê a string da DIREITA para ESQUERDA em blocos de até 4 dígitos
    // Exemplo: "123456789" → blocos [6789], [2345], [1]
    int posicao_fim = tamanho_texto;
    while (posicao_fim > posicao_inicio) {
        int inicio_bloco = posicao_fim - DIGITOS_POR_BLOCO;
        if (inicio_bloco < posicao_inicio) {
            inicio_bloco = posicao_inicio;
        }

        // Extrai o pedaço da string e converte para inteiro
        char buffer_bloco[DIGITOS_POR_BLOCO + 1];
        int indice_buffer = 0;
        for (int i = inicio_bloco; i < posicao_fim; i++) {
            buffer_bloco[indice_buffer++] = texto_decimal[i];
        }
        buffer_bloco[indice_buffer] = '\0';

        int valor_bloco = atoi(buffer_bloco);
        
        // Insere no final da lista (ordem: menos significativo → mais significativo)
        insert_node(numero->blocos_digitos, size_list(numero->blocos_digitos), valor_bloco);

        posicao_fim = inicio_bloco;
    }
    
    // Se a string estava vazia (ou só tinha sinal), representa como zero
    if (is_empty_list(numero->blocos_digitos)) {
        insert_node(numero->blocos_digitos, 0, 0);
    }

    return 1;
}

// soma: calcula primeiro + segundo, tratando sinais positivos e negativos
BigInt *soma(const BigInt *primeiro, const BigInt *segundo) {
    if (!primeiro || !segundo) return NULL;

    BigInt *resultado = NULL;

    // Caso 1: Ambos têm o mesmo sinal → soma as magnitudes e mantém o sinal
    // Ex: (+5) + (+3) = +8  ou  (-5) + (-3) = -8
    if (primeiro->sinal == segundo->sinal) {
        resultado = somar_magnitude(primeiro, segundo);
        resultado->sinal = primeiro->sinal;
    } 
    // Caso 2: Sinais opostos → subtrai o menor do maior (em valor absoluto)
    // Ex: (+5) + (-3) = +2  ou  (-5) + (+3) = -2
    else {
        int comparacao = comparar_magnitude(primeiro, segundo);
        if (comparacao >= 0) { 
            // |primeiro| >= |segundo| → resultado mantém o sinal do primeiro
            resultado = subtrair_magnitude(primeiro, segundo);
            resultado->sinal = primeiro->sinal;
        } else {
            // |segundo| > |primeiro| → resultado mantém o sinal do segundo
            resultado = subtrair_magnitude(segundo, primeiro);
            resultado->sinal = segundo->sinal;
        }
    }
    return resultado;
}

// somar_magnitude: soma os valores absolutos (ignora sinal)
BigInt *somar_magnitude(const BigInt *primeiro, const BigInt *segundo) {
    BigInt *resultado = criar(0);
    int quantidade_blocos_primeiro = size_list(primeiro->blocos_digitos);
    int quantidade_blocos_segundo = size_list(segundo->blocos_digitos);
    int quantidade_maxima_blocos = (quantidade_blocos_primeiro > quantidade_blocos_segundo) 
                                    ? quantidade_blocos_primeiro : quantidade_blocos_segundo;
    int carry = 0;  // Carry (transporte para próximo bloco)

    // Percorre todos os blocos, somando e propagando o carry
    for (int i = 0; i < quantidade_maxima_blocos || carry > 0; i++) {
        int valor_bloco_primeiro = 0;
        int valor_bloco_segundo = 0;

        if (i < quantidade_blocos_primeiro) {
            get_node(primeiro->blocos_digitos, i, &valor_bloco_primeiro);
        }
        if (i < quantidade_blocos_segundo) {
            get_node(segundo->blocos_digitos, i, &valor_bloco_segundo);
        }

        int soma_blocos = valor_bloco_primeiro + valor_bloco_segundo + carry;
        insert_node(resultado->blocos_digitos, size_list(resultado->blocos_digitos), soma_blocos % BASE);
        carry = soma_blocos / BASE;
    }
    return resultado;
}

// subtrair_magnitude: subtrai os valores absolutos (assume que numero_maior >= numero_menor)
// Usa algoritmo de subtração com "empresta um" (borrow)
BigInt *subtrair_magnitude(const BigInt *numero_maior, const BigInt *numero_menor) {
    BigInt *resultado = criar(0);
    int quantidade_blocos_maior = size_list(numero_maior->blocos_digitos);
    int quantidade_blocos_menor = size_list(numero_menor->blocos_digitos);
    int empresta_um = 0;  // Borrow (empréstimo do próximo bloco)

    // Percorre todos os blocos do número maior, subtraindo e propagando empréstimos
    for (int i = 0; i < quantidade_blocos_maior; i++) {
        int valor_bloco_maior = 0;
        int valor_bloco_menor = 0;

        get_node(numero_maior->blocos_digitos, i, &valor_bloco_maior);
        if (i < quantidade_blocos_menor) {
            get_node(numero_menor->blocos_digitos, i, &valor_bloco_menor);
        }

        int diferenca = valor_bloco_maior - valor_bloco_menor - empresta_um;
        if (diferenca < 0) {
            diferenca += BASE;  // Pega emprestado do próximo bloco
            empresta_um = 1;
        } else {
            empresta_um = 0;
        }

        insert_node(resultado->blocos_digitos, size_list(resultado->blocos_digitos), diferenca);
    }

    // Remove zeros à esquerda (que são zeros à direita na nossa lista)
    // Exemplo: 001000 vira 1000, mas mantém pelo menos um zero se resultado é 0
    int quantidade_blocos_resultado = size_list(resultado->blocos_digitos);
    while (quantidade_blocos_resultado > 1) {
        int valor_bloco = 0;
        get_node(resultado->blocos_digitos, quantidade_blocos_resultado - 1, &valor_bloco);
        if (valor_bloco == 0) {
            remove_node(resultado->blocos_digitos, quantidade_blocos_resultado - 1, NULL);
            quantidade_blocos_resultado--;
        } else {
            break;
        }
    }
    return resultado;
}

// comparar_magnitude: Retorna 1 se |a|>|b|, -1 se |a|<|b|, 0 se iguais
int comparar_magnitude(const BigInt *primeiro, const BigInt *segundo) {
    int qtd_prim = size_list(primeiro->blocos_digitos);
    int qtd_seg = size_list(segundo->blocos_digitos);

    if (qtd_prim > qtd_seg) return 1;
    if (qtd_prim < qtd_seg) return -1;

    for (int i = qtd_prim - 1; i >= 0; i--) {
        int val1, val2;
        get_node(primeiro->blocos_digitos, i, &val1);
        get_node(segundo->blocos_digitos, i, &val2);
        
        if (val1 > val2) return 1;
        if (val1 < val2) return -1;
    }
    return 0;
}

// maior: Retorna 1 se a > b, 0 se a == b, -1 se a < b
int maior(const BigInt *primeiro, const BigInt *segundo) {
    // 1. Comparação de Sinais
    if (primeiro->sinal > segundo->sinal) return 1;  // + > -
    if (primeiro->sinal < segundo->sinal) return -1; // - < +
    
    // 2. Sinais iguais: compara magnitude
    int comp = comparar_magnitude(primeiro, segundo);
    
    // 3. Ajusta pelo sinal
    if (primeiro->sinal == 1) {
        return comp; // Positivos: maior magnitude = maior número
    } else {
        return -comp; // Negativos: maior magnitude = menor número (ex: -5 < -2)
    }
}

// menor: Retorna 1 se a < b, 0 se a == b, -1 se a > b
int menor(const BigInt *primeiro, const BigInt *segundo) {
    // Inverte o resultado de maior
    return -maior(primeiro, segundo);
}

// destruir: libera toda a memória alocada e zera o ponteiro
void destruir(BigInt **ponteiro_numero) {
    if (ponteiro_numero && *ponteiro_numero) {
        free_linked_list(&((*ponteiro_numero)->blocos_digitos));
        free(*ponteiro_numero);
        *ponteiro_numero = NULL;
    }
}

//mostra BigInt na saída padrão (formato decimal)
void imprimir(const BigInt *numero) {
    if (!numero) {
        printf("NULL");
        return;
    }
    
    //verifica se é zero para não imprimir -0
    int quantidade_blocos = size_list(numero->blocos_digitos);
    int valor_bloco_mais_significativo;
    get_node(numero->blocos_digitos, quantidade_blocos - 1, &valor_bloco_mais_significativo);

    // Imprime sinal negativo se necessário
    if (numero->sinal == -1 && !(quantidade_blocos == 1 && valor_bloco_mais_significativo == 0)) {
        printf("-");
    }
    
    // Imprime os blocos do mais significativo (fim da lista) ao inicio
    for (int i = quantidade_blocos - 1; i >= 0; i--) {
        int valor_bloco;
        get_node(numero->blocos_digitos, i, &valor_bloco);
        
        if (i == quantidade_blocos - 1) {
            // Primeiro bloco: imprime sem zeros à esquerda (ex: 123, não 0123)
            printf("%d", valor_bloco);
        } else {
            // Blocos seguintes: preenche com zeros à esquerda (ex: 0005)
            printf("%04d", valor_bloco);
        }
    }
}

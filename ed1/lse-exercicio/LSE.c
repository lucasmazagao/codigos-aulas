#include <stdio.h>
#include <stdlib.h>
#include "LSE.h"

// Convenção de retorno
// 1 sucesso
// 0 condição falsa ou não encontrado
// −1 erro

// Invariante da estrutura
// 0 <= qtd <= LSE_MAX
// elementos válidos estão em dados[0..qtd-1]

// Cria a lista e inicia com quantidade zero
LSE *lse_cria() {
	LSE *l = malloc(sizeof(LSE));
	if (!l) {                // falha de alocação
		return NULL;         // quem chamou deve verificar retorno
	}
	l->qtd = 0;              // lista lógica vazia
	return l;
}

// Libera a lista e zera o ponteiro externo
int lse_destroi(LSE **l) {
	if (!l) {                 // valida o ponteiro duplo
		return -1;
	}
	free(*l);                 // free(NULL) é seguro
	*l = NULL;                // previne uso após liberação
	return 1;
}

// Retorna 1 se vazia, 0 se não vazia, −1 se ponteiro inválido
int lse_vazia(const LSE *l) {
	if (!l) {
		return -1;
	}
	if (l->qtd == 0) {
		return 1;
	}
	return 0;
}

// Retorna 1 se cheia, 0 caso contrário, −1 se ponteiro inválido
// Cheia significa sem espaço no vetor estático dados
int lse_cheia(const LSE *l) {
	if (!l) {
		return -1;
	}
	if (l->qtd == LSE_MAX) {
		return 1;
	}
	return 0;
}

// Informa o número de elementos
int lse_tamanho(const LSE *l) {
	if (!l) {
		return -1;
	}
	return l->qtd;
}

// Insere no final em custo O(1)
// Pré: lista não pode estar cheia
int lse_insere_final(LSE *l, LSE_Tipo elem) {
	if (!l) {
		return -1;
	}
	if (lse_cheia(l)) {       // se 1 está cheia, se −1 já houve erro antes
		return -1;
	}
	l->dados[l->qtd] = elem;  // grava no próximo índice livre
	l->qtd++;                 // mantém invariante 0 <= qtd <= LSE_MAX
	return 1;
}

// Insere na posição pos deslocando os seguintes para a direita em custo O(n)
// pos pode ser igual a qtd para inserir exatamente no fim
int lse_insere_pos(LSE *l, int pos, LSE_Tipo elem) {
	if (!l) {
		return -1;
	}
	if (lse_cheia(l)) {       // não há espaço para mais um elemento
		return -1;
	}
	if (pos < 0 || pos > l->qtd) {  // valida intervalo de inserção
		return -1;
	}
	// abre espaço do fim até pos, inclusive
	for (int i = l->qtd; i > pos; i--) {
		l->dados[i] = l->dados[i-1];
	}
	l->dados[pos] = elem;     // escreve na posição desejada
	l->qtd++;                 // atualiza tamanho
	return 1;
}

// Remove na posição pos e devolve o elemento removido em *removido
// Desloca os seguintes para a esquerda em custo O(n)
int lse_remove_pos(LSE *l, int pos, LSE_Tipo *removido) {
	if (!l) {
		return -1;
	}
	if (pos < 0 || pos >= l->qtd) { // pos deve ser índice válido existente
		return -1;
	}
	if (!removido) {           // saída obrigatória para devolver o valor
		return -1;
	}
	*removido = l->dados[pos]; // captura o valor removido
	// fecha o buraco puxando os seguintes para a esquerda
	for (int i = pos; i < l->qtd-1; i++) {
		l->dados[i] = l->dados[i+1];
	}
	l->qtd--;                  // último elemento agora está fora da fronteira lógica
	return 1;
}

// Lê o elemento da posição pos em *elem sem alterar a lista
int lse_consulta_pos(const LSE *l, int pos, LSE_Tipo *elem) {
	if (!l) {
		return -1;
	}
	if (pos < 0 || pos >= l->qtd) { // consulta exige índice válido
		return -1;
	}
	if (!elem) {               // ponteiro de saída não pode ser nulo
		return -1;
	}
	*elem = l->dados[pos];     // cópia por valor
	return 1;
}

// Busca linear em custo O(n)
// Se encontrar retorna 1 e grava a posição em *pos
// Se não encontrar retorna 0 e grava −1 em *pos
int lse_busca(const LSE *l, LSE_Tipo elem, int *pos) {
	if (!l) {
		return -1;
	}
	if (!pos) {                // precisa de saída para devolver a posição
		return -1;
	}
	*pos = -1;                 // padrão para não encontrado
	for (int i = 0; i < l->qtd; i++) {
		if (l->dados[i] == elem) {
			*pos = i;
			return 1;         // término imediato ao encontrar
		}
	}
	return 0;                  // não achou
}

// Esvazia logicamente a lista em custo O(1)
// Os valores antigos permanecem no vetor, porém desconsiderados
int lse_limpa(LSE *l) {
	if (!l) {
		return -1;
	}
	l->qtd = 0;                // nenhum laço nem realocação
	return 1;
}

// Impressão simples no formato [a, b, c]
// Aqui supomos LSE_Tipo como int para o printf
int lse_imprime(const LSE *l) {
	if (!l) {
		return -1;
	}
	printf("[");
	if (l->qtd > 0) {
		for (int i = 0; i < l->qtd - 1; i++) {
			printf("%d, ", l->dados[i]); // para tipo genérico trocar o formato
		}
		printf("%d", l->dados[l->qtd-1]);
	}
	printf("]\n");
	return 1;
}
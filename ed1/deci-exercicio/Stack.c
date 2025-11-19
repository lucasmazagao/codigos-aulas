#include <stdlib.h>  // para usar malloc
#include "Stack.h"

#define MAX 100  // capacidade (espaço) da pilha

struct stack {
	int dados[MAX];  // vetor de elementos
	int qtd; // num. elementos
};

Stack *create_stack() {
	Stack *s = malloc(sizeof(Stack));
	if (!s) {
		return NULL;
	}
	s->qtd = 0;
	return s;
}

int is_empty(const Stack *s) {
	if (!s) {
		return -1; // erro,pilha não inicializada
	}
	if (s->qtd == 0) {
		return 1; // true, é vazia
	}
	// false, pilha não vazia
	return 0;
}


int is_full(const Stack *s) {
	if (!s) {
		return -1; // erro,pilha não inicializada
	}
	if (s->qtd == MAX) {
		return 1; // true, está cheia
	}
	// false, pilha não está cheia
	return 0;
}

int push(Stack *s, int value) {
	if (!s) {
		return -1; // não inicializado
	}
	if (is_full(s)) {
		return 0; // pilha cheia
	}
	// inserir o elemento no topo
	s->dados[s->qtd] = value;
	// incrementa o qtd
	s->qtd++;
	// sucesso, inserido
	return 1;
}

int pop(Stack *s, int *value) {
	if (!s) {
		return -1; // não inicializada
	}
	// verifica se está vazio
	if (is_empty(s)) {
		return 0;
	}
	// se ponteiro de value não é nulo
	// preciso salvar elemento antes de remover
	if (value != NULL) {
		*value = s->dados[s->qtd-1];
	}
	// vamos agora, remover o elemento
	s->qtd--;
	// sucesso
	return 1;
}


int peek(const Stack *s, int *value) {
	if ((!s) || (!value)) {
		return -1; // não inicializada
	}
	// verifica se está vazio
	if (is_empty(s)) {
		return 0;
	}
	*value = s->dados[s->qtd-1];
	// sucesso
	return 1;
}

void free_stack(Stack **s) {
	if (s) { 
		free(*s);
		*s = NULL;
	}
}
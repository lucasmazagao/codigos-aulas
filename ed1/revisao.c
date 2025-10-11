// revisao

int push(Stack *s, int value) {
    if (s == NULL) {
        return -1;
    }
    if(s-> qtd == MAX) {
        return 0; // Stack is full
    }
    s -> dados[s -> qtd] = value;
    s -> qtd++;
    return 1; // Success
    
    // ESTUDAR .C E .H
}

//ex 11

//implementar struct queue

#define MAX 100

struct queue{
    int dados[MAX];
    int inicio;
    int fim;
    int qtd; // nao eh obrigatorio
};

//ex 12

//lista encadeada

typedef struct node {
    int data;
    struct node* next;
} Node;

struct linked_list {
    Node* head; // aponteiro para o primeiro no
    int qtd; // quantidade de elementos na lista
};

// com ctz cai algo assim

/// revisao aulas com codigos e conceitos
Os temas da P1 abrangem tudo que vimos até aqui (Aula 1 a 12):
- Recursão
- Algoritmos de Busca
- Introdução à Análise de Algoritmos
- Conceitos de TAD
- Listas Sequenciais Estáticas e Dinâmicas
- Listas Encadeadas Simples
- Listas Duplamente Encadeadas (apenas o conceito)
- Pilha
- Fila
- Fila de Prioridade (apenas o conceito)
- Fila Dupla (apenas o conceito)

// aula 1

// aula 2

// aula 3

// aula 4

// aula 5 e 6- analise de algoritmos
    funcao de custo T(n) mede o numero de operacoes basicas 
    executadas por um algoritmo em funcao do tamanho da entrada n
    
    funcao linear = T(n) = O(n)
    fibonacci recursivo = T(n) = O(2^n)
    busca sequencial = T(n) = O(n)
    busca binaria = T(n) = O(log n)
    busca linear = T(n) = O(n)
    bubble sort = T(n) = O(n^2)
    merge sort = T(n) = O(n log n)
    quick sort = T(n) = O(n log n) - O(n^2)

    analise assintotica é quando estudamos as taxas de crescimento 
    conforme os problemas forem crescendo, tres notacoes:
    notacao O(grande) = limite superior - pior caso
    notacao Omega = limite inferior - melhor caso
    notacao Theta = limite medio - caso medio

    g(n) é O(f(n)) se existirem constantes c > 0 e n0 >= 0 tais que
    g(n) <= c*f(n) para todo n >= n0, ou seja, g(n) cresce no maximo
    tanto quanto f(n)

    para omega, g(n) é omega(f(n)) se existirem constantes c > 0
    e n0 >= 0 tais que g(n) >= c*f(n) para todo n >= n0,
    ou seja, g(n) cresce no minimo tanto quanto f(n)

    para theta, g(n) é theta(f(n)) se existirem constantes c1, c2 > 0
    e n0 >= 0 tais que c1*f(n) <= g(n) <= c2*f(n) para todo n >= n0,
    ou seja, g(n) cresce tanto quanto f(n)

// aula 7 - TAD
    TAD - Tipo Abstrato de Dados
    define um conjunto de dados e as operacoes que podem ser realizadas
    sobre esses dados, sem especificar a implementacao dessas operacoes

    - vantagens: modularidade, reutilizacao de codigo, encapsulamento,
    seguranca, flexibilidade
    - desvantagens: overhead de desempenho, complexidade adicional

    estruturas de dados vs TAD:
    estrutura de dados: implementacao concreta de um conjunto de dados
    - ex: array, lista encadeada, arvore binaria, grafo
    TAD: definicao abstrata de um conjunto de dados e suas operacoes
    - ex: pilha, fila, lista, arvore, grafo

    composicao do tad:
    - header .h: definicao do TAD, declaracao das funcoes
        usuario interage aqui, acessivel globalmente
    - source .c: implementacao das funcoes declaradas no header
        onde os dados sao manipulados, implementacao das funcoes
    - main .c: uso do TAD, chamadas das funcoes
        onde o programa principal roda, chamadas das funcoes do TAD
    - makefile: instrucao da compilacao

// aula 8 - listas sequenciais estaticas
    - nao possui buracos
    - tamanho fixo
    - um antecessor e um sucessor

    - insercao, remocao, busca e consulta

    - vantagens:
        acesso direto, melhor controle de memoria, simples
    - desvantagens:
        tamanho fixo, custo de insercao e remocao, desperdicio de memoria

// aula 9 - listas sequenciais dinamicas
    - diferencial: tamanho flexivel, geralmente dobrar

    - vantagens:
        tamanho flexivel, melhor controle de memoria, otimizado
    - desvantagens:
        custo de insercao e remocao, frag de memoria, complexidade

// aula 10 - pilhas
    - LIFO - last in, first out
    - push, pop, top/peek, isEmpty, isFull, freeStack

    - vantagens:
        simples, eficiente, controle de memoria
    - desvantagens:
        tamanho fixo (se estatica), acesso restrito

    - stack de tipo opaco, declara apenas stack*

// aula 11 - filas
    - FIFO - first in, first out
    - enqueue, dequeue, front/peek, isEmpty, isFull, freeQueue

    - linear ou circular
    - vantagens:
        simples, eficiente, controle de memoria
    - desvantagens:
        tamanho fixo (se estatica), acesso restrito

    - queue de tipo opaco, declara apenas queue*

    - em linear:
        fila enfileira no fim e desenfileira no inicio
        problema: quando desenfileira, inicio anda pra frente
        solucao: mover todos os elementos pra frente (custo O(n))
    - em circular:
        fila enfileira no fim e desenfileira no inicio
        q->fim = (q->fim + 1) % MAX ou
        q->fim++; if q->fim == MAX q->fim = 0;
        q->inicio = (q->inicio + 1) % MAX ou
        q->inicio++; if q->inicio == MAX q->inicio = 0;

    variantes:
    - fila de prioridade: cada elemento tem uma prioridade
        elementos com maior prioridade sao atendidos primeiro
        podem ser vetores estaticos, listas encadeadas ou heaps
    - fila dupla: permite insercao e remocao em ambas as extremidades
        tambem conhecida como deque (double-ended queue)

// aula 12 - listas encadeadas e sequenciais
    - lista sequencial:
    - blocos que se ligam por ponteiros para formar uma cadeia
    com o anterior e o proximo
    - cada bloco possui um item data, e outro next
    - nos alocados sob demanda, acessos sequenciais
    - primeiramente head aponta para NULL, depois head aponta 
    para o primeiro no

    - para lista encadeada inserindo na posicao p:
        criar novo no
        se p == 0:
            novo->next = head
            head = novo
        senao:
            percorrer ate o no anterior a p
            novo->next = anterior->next
            anterior->next = novo

    - para lista encadada circular:
        o ultimo no aponta para o primeiro
        head aponta para o primeiro no
        fim aponta para o ultimo no

    - para encadeada duplamente:
        cada no possui um ponteiro para o proximo e para o anterior
        permite navegacao em ambas as direcoes
        existe um null em head e em fim
        insercao e remocao mais simples, mas ocupa mais memoria

    - para encadeada duplamente circular:
        existe head e tail,
        head->prev aponta para tail
        tail->next aponta para head

    lista encadeada vs lista sequencial:
    - lista encadeada:
        tamanho flexivel, insercao e remocao eficientes no
        meio da lista.
        nao precisa mover elementos de posicao, apenas ajustar ponteiros
    - lista sequencial:
        acesso aleatorio aos elementos, melhor localidade de referencia
        e menor overhead de memoria (sem ponteiros adicionais)

// lista exercicios
1- e) eh exponencial
    *a diferenca entre T(1) e T(n) eh que T(1) eh uma operacao basica
    e T(n) eh a soma de todas as operacoes basicas ate chegar em T(1)
2- d) estar ordenada na binaria garante encontrar no max log n
3- e) 
    *a complexidade media é definida pelo caso medio de uso do algoritmo,
    dado por T(n) = (T(pior caso) + T(melhor caso)) / 2
4- b) 
    *os algoritmos recursivos e iterativos tem complexidades
    diferentes, recursivo eh exponencial e iterativo eh linear
    *estouro de pilha ocorre quando a recursao eh muito profunda
5- e)

6-
f, todo algoritmo iterativo pode ser escrito de forma recursiva
e todo algoritmo recursivo pode ser escrito de forma iterativa
v, toda recursao precisa de uma condicao de parada
f, nem sempre recursao eh melhor que iteracao
v, uma recursao eh uma funcao de lacos
f, no melhor caso uma busca binaria faz a mesma quantidade de
comparacoes que uma busca linear, no pior caso, a busca binaria
faz menos comparacoes que a busca linear
v, a notacao theta existindo, indica que as notacoes O e omega
existem, pois theta eh o limite medio entre O e omega
v
v
f, a capacidade muda conforme necessidade
f, na estatica, o tamanho eh fixo

v
f, na dinamica inserir elementos em uma posicao requer mover os elementos
v
f, checar apenas é o(1)
f, nao necessariamente em ordem crescente
f, no pior caso a a busca binaria é O(log n) pois divide a lista ao meio
v, para chaves repetidas, a busca binaria pode retornar qualquer posicao
f, custa o(1)
v, precisa-se criar n espacos e inserir n elementos, logo n2
f, devolve o mais novo

8- classes assintoticas sao os termos dominantes
    - O(grande) = limite superior - pior caso
    - Omega = limite inferior - melhor caso
    - Theta = limite medio - caso medio

9- melhor caso se da por n², pior caso por n³, o caso medio eh
n³ + n² / 2 = n³

10- exemplo completo complexo.c
# include <stdio.h>
# include <stdlib.h>
# include "complexo.h"

struct TComplexo {
    float real;
    float imag;
};

TComplexo criarComplexo(float real, float imag) {
    TComplexo c;
    c.real = real;
    c.imag = imag;
    return c;
}

TComplexo somarComplexos(TComplexo a, TComplexo b) {
    TComplexo s;
    s.real = a.real + b.real;
    s.imag = a.imag + b.imag;
    return s;
}

TComplexo subtrairComplexos(TComplexo a, TComplexo b) {
    TComplexo s;
    s.real = a.real - b.real;
    s.imag = a.imag - b.imag;
    return s;
}

TComplexo multiplicarComplexos(TComplexo a, TComplexo b) {
    TComplexo s;
    s.real = a.real * b.real - a.imag * b.imag;
    s.imag = a.real * b.imag + a.imag * b.real;
    return s;
}

void imprimirComplexo(TComplexo c) {
    if () {

    } else {

    }
}

11- certo

# ifndef STACK_H
# define STACK_H

typedef struct stack Stack ;

Stack * create_stack ( void );
int is_empty ( const Stack * s );
int is_full ( const Stack * s );
int push ( Stack *s , int value );
int pop ( Stack *s , int * value );
int peek ( const Stack *s , int * value );
void free_stack ( Stack ** s );
# endif

---

lista 2

1- 
pilha ok
fila ok
fila dupla ok
lista sequencial
lista encadeada
pilha
fila
lista sequencial
fila 
lista encadeada
fila dupla
lista sequencial
lista sequencial
lista encadeada
lista encadeada

2- ao utilizar tads, o usuario nao tem acesso a estrutura interna
dos dados, apenas as funcoes gerais. o resto estara em outro arquivo
privado. encapsul melhor, promove abstracao, modularidade, reutilizacao
de codigo, flexibilidade, seguranca

3- um tipo opaco é uma struct que nao esta definida no header,
tendo apenas uma descricao breve que precisa ser definida no .c
ex:
typedef struct stack Stack;

struct stack {
    int dados[MAX];
    int qtd;
};

4- lista seq
    vantagens:
        acesso aleatorio por indice O(1)
        lida melhor com memoria, mais barato
        mais eficiente, facil de implementar
    desvantagens:
        para inserir no meio precisa mover todos os itens, O(n)
        precisa gerenciar tamanho
        desperdicio de espaco e possiveis falhas de redimensionamento

    lista enc
    vant:
        lidar apenas com ponteiros para remanejar
        tamanho dinamico, sem precisar gerenciar dimensao
        nao precisa mudar os itens de posicao
    desvant:
        acesso é por posicao, sendo O(n)
        mais dificil de implementar e mais perigos de fragmentacao
        precisa lidar com memoria dos ponteiros, mais caro

5- listas encadeadas comum possuem um head que aponta para o primeiro
termo, um ultimo termo que aponta para NULL. na encadeada circular,
o ultimo termo aponta para o primeiro. o cuidado que precisa se ter é
garantir que, ao chegar no head(primeiro termo), o codigo encerra

### listas encadeadas sao estruturas de struct de structs,
typedef struct node {
    int dado;
    struct node *next;
    struct node *prev;
} Node;

struct linked_list {
    Node *head;
    int size;
}
###

6- na encadeada simples, apontamos apenas para o proximo no, tendo que
iterar do head ate o proximo. na dupla, cada no possui prev e next, assim
pode-se iterar de frente para tras e tras para frente
    vant: 
        pode-se iterar em ambas direcoes
        nao precisa iniciar do primeiro para chegar no que quer ser lido
        nao precisa conhecer o no anterior 

    desvant:
        problemas de aloacacao de memoria
        custos com ponteiros
        perigo de fragmentar

7- a melhor estrutura é a pilha, pois para cada dado removido, a pilha
ganha um dado. sendo assim, o controle de acoes mais recentes para redo.
sendo de uma pilha main para uma pilha removida

8- a) fila de prioridade tem um valor que, dado a maior delas entre
os itens, se refaz a fila para sair. na fila comum eh sempre fifo, logo
menos complexo O(1)
b) na primeira versao a saida seguiria a ordem de entrada, sendo 
na segunda seguiria os dados primeiros inputados, logo precisa iterar
do inicial ao final, O(n). aqui vai ter de ter busca binaria para 
saber onde colocar o novo elemento, logo O(log n)

9-nesse caso o melhor uso esta na lista encadeada, pois ja como nao
precisamos de acesso a um numero especico/acesso direto, nao precisamos
ter uma sequencia. alem de tambem nao precisarmos de aumentar o tamanho
da lista, e nem mover os elementos para inserir um novo. alem do mais,
a insercao no meio eh mais facil, bastando mudar a ordem de quem vem
depois de quem

10- a)

struct stack {
    int dados[MAX];
    int qtd;
}

b)
int push(Stack *s, int value);
    if(!s) {
        return -1;
    };

    if(isFull(s)) {
        return 0;
    }

    s->dados[s->qtd] = value;
    s->qtd++;
    return 1;

11- a)
struct queue {
    int dados[MAX];
    int inicio;
    int fim;
    int qtd;
};

b)
int front(const Queue *q, int *value) {
    if((!q) || (!value)) {
        return -1;
    }

    if(is_empty(q)) {
        return 0;
    } else {
        *value = q->dados[q->inicio];
    }
    return 1;
};

12- a)

struct node {
    int data;
    struct node *next;
} Node;

struct linked_list {
    Node *head;
    int size;
};

b)

int get_node(const LinkedList *list, int pos, int *value) {
    if((!list) || (!pos) || (!value))  {
        return -1;
    }

    for (int i = 0; i < pos; i++) {
        list->head == i
    }
    return 1;
} sei la ta errado

13- refazer

14- 
push 1 2 3
push 0
peek 0
pop 0
push 9
peek 9
pop 9
push 18
peek 18
pop 18
push 27

15- mesma coisa para filas



aprender de cabo a rabo:
    entradas, saidas, definições, estruturas, funções, requisitos
    excecoes, casos de teste, struct, chamada

- Listas Sequenciais Estáticas e Dinâmicas
    struct list{
        int tamanho;
        int *dados;
        int qtd;
    }

    vant:
        acesso direto O(1)
        facil de implementar
        tudo contiguo na memoria
    desvant:
        tamanho fixo ou dinamico gasta memoria
        inserir e remover no meio O(n)

- Listas Encadeadas Simples
    typedef struct node{
        int data;
        struct node *next;
    } Node;
    struct linked_list{
        Node *head;
        int qtd;
    };

    vant:
        tamanho flexivel
        lidar apenas com ponteiros
        inserir e remover no meio O(1)
    desvant:
        acesso sequencial O(n)
        mais dificil de implementar
        caro para memoria, pode fragmentar muito

- Pilha
    struct stack{
        int dados[MAX];
        int qtd;
    }

    vant:
        simples, eficiente
        controle de memoria
        acesso sequencial
    desvant:
        tamanho fixo
        pode causar overflow
        não permite acesso aleatório, apenas o topo

- Fila
    struct queue{
        int dados[MAX];
        int inicio;
        int fim;
        int qtd;
    }

    vant:
        simples, eficiente
        controle de memoria
        acesso sequencial
    desvant:
        tamanho fixo
        pode causar overflow
        não permite acesso aleatório, apenas a frente e o fim

###
tipo opaco é quando a struct nao é definida no header, garantindo
o encapsulamento e a seguranca dos dados. o usuario so ve o que
pode fazer com o TAD, nao como ele é feito. criacao e liberacao
de memoria apenas na api, nao no main
###
O representa o pior caso
theta representa o caso medio
omega representa o melhor caso
calculamos a complexidade observando o maior grau de n nas operacoes
###

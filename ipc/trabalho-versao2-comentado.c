#include <stdio.h>
#include <stdlib.h> // funcao system clear
#include <unistd.h> // funcao sleep
#include <time.h>   // funcao rand

// Lucas Ferreira Mazagão - 16304606

// Define uma estrutura de movimento para armazenar as coordenadas
// de um movimento completo (origem e destino) e sua validade.
typedef struct
{
    int linha_inicial;
    int coluna_inicial;
    int linha_final;
    int coluna_final;
    int validade; // 1 se o movimento é válido, 0 caso contrário
} movimento;

// Mostra o tabuleiro atual na tela.
// Limpa o console, depois percorre a matriz do tabuleiro e imprime
// 'X' para o jogador 1, 'O' para o jogador 2, e um espaço em branco
// para casas vazias
void mostrar_tabuleiro(int tabuleiro[3][3])
{
    int lin, col;
    char simbolo;

    system("clear"); // para nao ficar poluido

    printf("Tabuleiro:\n\n");
    for (lin = 0; lin < 3; lin++)
    {
        printf(" ");
        for (col = 0; col < 3; col++)
        {
            if (tabuleiro[lin][col] == 1)
            {
                simbolo = 'X';
            }
            else if (tabuleiro[lin][col] == 2)
            {
                simbolo = 'O';
            }
            else
            {
                simbolo = ' ';
            }
            printf(" %c ", simbolo);
            if (col < 2)
            {
                printf("|");
            }
        }
        printf("\n");
        if (lin < 2)
        {
            printf("-----------\n");
        }
    }
    printf("\n");

    return;
}

// As três funções a seguir são auxiliares para checar se houve vitória.

// Verifica se todos os elementos de uma coluna 'y' são iguais e não vazios.
// Retorna 1 se a coluna forma uma linha vencedora, senão 0.
int testar_coluna(int tab[3][3], int y)
{
    if (tab[0][y] != 0 && tab[0][y] == tab[1][y] && tab[1][y] == tab[2][y])
    {
        return 1;
    }
    return 0;
}

// Verifica se todos os elementos de uma linha 'x' são iguais e não vazios.
// Retorna 1 se a linha forma uma linha vencedora, senão 0.
int testar_linha(int tab[3][3], int x)
{
    if (tab[x][0] != 0 && tab[x][0] == tab[x][1] && tab[x][1] == tab[x][2])
    {
        return 1;
    }
    return 0;
}

// Verifica se qualquer uma das duas diagonais forma uma linha vencedora.
// A casa central (1,1) deve ser não vazia para qualquer vitória diagonal.
// Retorna 1 se houver vitória em uma diagonal, senão 0.
int testar_diagonal(int tab[3][3])
{
    if (tab[1][1] != 0)
    {
        if (tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2])
        {
            return 1;
        }
        if (tab[2][0] == tab[1][1] && tab[1][1] == tab[0][2])
        {
            return 1;
        }
    }
    return 0;
}

// Utiliza as funções de teste para verificar se o jogador da rodada venceu.
// Percorre todas as linhas e colunas, e também as diagonais.
// Uma regra específica do jogo implementado é que um jogador não pode
// vencer na sua linha inicial (linha 2 para jogador 1, linha 0 para jogador 2).
int checar_vitoria(int tabuleiro[3][3], int jogador_rodada)
{
    int vitoria = 0;
    int i;

    for (i = 0; i < 3; i++)
    {
        if (vitoria == 0)
        {
            if (testar_linha(tabuleiro, i))
            {
                if (tabuleiro[i][0] == jogador_rodada)
                {
                    // impede vitória na linha inicial
                    if ((jogador_rodada == 1 && i != 2) || (jogador_rodada == 2 && i != 0))
                    {
                        vitoria = jogador_rodada;
                    }
                }
            }
        }
        if (vitoria == 0)
        {
            if (testar_coluna(tabuleiro, i))
            {
                if (tabuleiro[0][i] == jogador_rodada)
                {
                    vitoria = jogador_rodada;
                }
            }
        }
    }
    if (vitoria == 0)
    {
        if (testar_diagonal(tabuleiro))
        {
            if (tabuleiro[1][1] == jogador_rodada)
            {
                vitoria = jogador_rodada;
            }
        }
    }

    return vitoria;
}

// A partir de uma peça de origem, esta função encontra todos os movimentos
// válidos (para casas adjacentes e vazias) e os armazena em um vetor.
// Retorna o número total de movimentos válidos encontrados.
int obter_movimentos_possiveis(int linha_inicial, int coluna_inicial, movimento lista_movimentos[], int tabuleiro[3][3])
{
    int casa_origem = linha_inicial * 3 + coluna_inicial + 1;
    int num_destinos = 0;
    int movimentos_validos = 0;
    int possiveis[8]; // No máximo 8 destinos

    // Define os destinos possíveis para cada casa de origem (1-9)
    switch (casa_origem)
    {
    case 1:
        num_destinos = 3;
        possiveis[0] = 2;
        possiveis[1] = 4;
        possiveis[2] = 5;
        break;
    case 2:
        num_destinos = 3;
        possiveis[0] = 1;
        possiveis[1] = 3;
        possiveis[2] = 5;
        break;
    case 3:
        num_destinos = 3;
        possiveis[0] = 2;
        possiveis[1] = 6;
        possiveis[2] = 5;
        break;
    case 4:
        num_destinos = 3;
        possiveis[0] = 1;
        possiveis[1] = 7;
        possiveis[2] = 5;
        break;
    case 5:
        num_destinos = 8;
        possiveis[0] = 1;
        possiveis[1] = 2;
        possiveis[2] = 3;
        possiveis[3] = 4;
        possiveis[4] = 6;
        possiveis[5] = 7;
        possiveis[6] = 8;
        possiveis[7] = 9;
        break;
    case 6:
        num_destinos = 3;
        possiveis[0] = 3;
        possiveis[1] = 9;
        possiveis[2] = 5;
        break;
    case 7:
        num_destinos = 3;
        possiveis[0] = 4;
        possiveis[1] = 8;
        possiveis[2] = 5;
        break;
    case 8:
        num_destinos = 3;
        possiveis[0] = 7;
        possiveis[1] = 9;
        possiveis[2] = 5;
        break;
    case 9:
        num_destinos = 3;
        possiveis[0] = 6;
        possiveis[1] = 8;
        possiveis[2] = 5;
        break;
    }

    // Filtra os destinos para incluir apenas casas vazias
    for (int i = 0; i < num_destinos; i++)
    {
        int casa_destino = possiveis[i];
        int linha_final = (casa_destino - 1) / 3;
        int coluna_final = (casa_destino - 1) % 3;

        if (tabuleiro[linha_final][coluna_final] == 0)
        {
            lista_movimentos[movimentos_validos].linha_inicial = linha_inicial;
            lista_movimentos[movimentos_validos].coluna_inicial = coluna_inicial;
            lista_movimentos[movimentos_validos].linha_final = linha_final;
            lista_movimentos[movimentos_validos].coluna_final = coluna_final;
            lista_movimentos[movimentos_validos].validade = 1;
            movimentos_validos++;
        }
    }

    return movimentos_validos;
}

// Processa a jogada de um jogador humano.
// Primeiro, pede para o jogador escolher a peça que deseja mover, validando
// se a casa pertence a ele e se a peça não está bloqueada.
// Depois, pede para escolher a casa de destino, validando se o movimento
// é permitido e se a casa de destino está vazia.
// Ao final, atualiza a matriz do tabuleiro com a jogada válida.
void realizar_jogada(int tabuleiro[3][3], int jogador_rodada)
{
    int casa_escolhida;
    int loop_escolha;
    int loop_casa;
    int possiveis[8];
    int tamanho_possiveis;
    int casa_jogada;
    int linha, coluna;
    int alvo_x, alvo_y;
    int n;
    int casa_permitida;

    casa_escolhida = 0;
    loop_escolha = 1;
    loop_casa = 1;
    tamanho_possiveis = 0;
    casa_jogada = 0;
    linha = -1;
    coluna = -1;
    alvo_x = -1;
    alvo_y = -1;
    casa_permitida = 0;

    for (n = 0; n < 8; n++)
    {
        possiveis[n] = 0;
    }

    printf("Rodada do Jogador %d.\n", jogador_rodada);

    // Loop para escolher uma peça válida para mover. quando encontrarmos uma peca valida o loop termina.
    while (loop_escolha == 1)
    {
        printf("Escolha um número de 1 a 9 para representar a peça desejada: \n");
        scanf("%d", &casa_escolhida);
        loop_escolha = 0;

        // Converte o número da casa (1-9) para coordenadas (linha, coluna)
        if (casa_escolhida < 1 || casa_escolhida > 9)
        {
            system("clear");
            printf("Entrada inválida.\n");
            loop_escolha = 1;
            mostrar_tabuleiro(tabuleiro);
        }
        else
        {
            linha = -1;
            coluna = -1;

            // Converte o número da casa (1-9) para coordenadas (linha, coluna)
            switch (casa_escolhida)
            { // possiveis[] demonstra quais casas podem ser usadas
            case 1:
                linha = 0;
                coluna = 0;
                possiveis[0] = 2;
                possiveis[1] = 4;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 2:
                linha = 0;
                coluna = 1;
                possiveis[0] = 1;
                possiveis[1] = 3;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 3:
                linha = 0;
                coluna = 2;
                possiveis[0] = 2;
                possiveis[1] = 6;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 4:
                linha = 1;
                coluna = 0;
                possiveis[0] = 1;
                possiveis[1] = 7;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 5:
                linha = 1;
                coluna = 1;
                possiveis[0] = 1;
                possiveis[1] = 2;
                possiveis[2] = 3;
                possiveis[3] = 4;
                possiveis[4] = 6;
                possiveis[5] = 7;
                possiveis[6] = 8;
                possiveis[7] = 9;
                tamanho_possiveis = 8;
                break;
            case 6:
                linha = 1;
                coluna = 2;
                possiveis[0] = 3;
                possiveis[1] = 9;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 7:
                linha = 2;
                coluna = 0;
                possiveis[0] = 4;
                possiveis[1] = 8;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 8:
                linha = 2;
                coluna = 1;
                possiveis[0] = 7;
                possiveis[1] = 9;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            case 9:
                linha = 2;
                coluna = 2;
                possiveis[0] = 6;
                possiveis[1] = 8;
                possiveis[2] = 5;
                tamanho_possiveis = 3;
                break;
            }

            if (tabuleiro[linha][coluna] == 0)
            {
                system("clear");
                mostrar_tabuleiro(tabuleiro);
                printf("Casa vazia. Escolha uma que tenha tua peça.\n");
                loop_escolha = 1;
            }
            // Valida se a peça escolhida pertence ao jogador atual
            else if (tabuleiro[linha][coluna] != jogador_rodada)
            {
                system("clear");
                mostrar_tabuleiro(tabuleiro);
                printf("Peça do jogador adversário. Escolha tua peça.\n");
                loop_escolha = 1;
            }
            else
            {
                // Valida se a peça escolhida tem algum movimento possível
                movimento movimentos_da_peca[8];
                int num_movimentos = obter_movimentos_possiveis(linha, coluna, movimentos_da_peca, tabuleiro);

                if (num_movimentos == 0)
                {
                    system("clear");
                    mostrar_tabuleiro(tabuleiro);
                    printf("Esta peça está bloqueada e não pode se mover. Escolha outra.\n");
                    loop_escolha = 1;
                }
            }
        }
    }

    // Loop para escolher uma casa de destino válida. se for valida fecha o loop
    while (loop_casa == 1)
    {
        printf("Escolha um número de 1 a 9 para depositar a peça n°%d: ", casa_escolhida);
        scanf("%d", &casa_jogada);
        loop_casa = 0;
        casa_permitida = 0;

        if (casa_jogada < 1 || casa_jogada > 9)
        {
            printf("Entrada inválida.\n");
            loop_casa = 1;
        }
        else
        {
            // Converte o número da casa de destino para coordenadas
            switch (casa_jogada)
            {
            case 1:
                alvo_x = 0;
                alvo_y = 0;
                break;
            case 2:
                alvo_x = 0;
                alvo_y = 1;
                break;
            case 3:
                alvo_x = 0;
                alvo_y = 2;
                break;
            case 4:
                alvo_x = 1;
                alvo_y = 0;
                break;
            case 5:
                alvo_x = 1;
                alvo_y = 1;
                break;
            case 6:
                alvo_x = 1;
                alvo_y = 2;
                break;
            case 7:
                alvo_x = 2;
                alvo_y = 0;
                break;
            case 8:
                alvo_x = 2;
                alvo_y = 1;
                break;
            case 9:
                alvo_x = 2;
                alvo_y = 2;
                break;
            }

            for (n = 0; n < tamanho_possiveis; n++)
            {
                if (casa_jogada == possiveis[n])
                {
                    casa_permitida = 1;
                }
            }

            if (casa_permitida == 0)
            {
                system("clear");
                mostrar_tabuleiro(tabuleiro);
                printf("Casa não pode ser escolhida. Escolha uma que tenha conexão com a casa inicial.\n");
                loop_casa = 1;
            }
            else
            {
                if (tabuleiro[alvo_x][alvo_y] != 0)
                {
                    system("clear");
                    mostrar_tabuleiro(tabuleiro);
                    printf("Casa já preenchida. Escolha uma casa vazia.\n");
                    loop_casa = 1;
                }
            }
        }
    }

    // Efetua a troca de posições no tabuleiro. usa um tabuleiro provisorio com alvo x e y
    tabuleiro[alvo_x][alvo_y] = tabuleiro[linha][coluna];
    tabuleiro[linha][coluna] = 0;

    return;
}

// Alterna o jogador da rodada. Se for o jogador 1, passa para o 2, e vice-versa.
// Retorna o número do próximo jogador.
int proximo_jogador(int jogador_rodada)
{
    if (jogador_rodada == 1)
    {
        jogador_rodada = 2;
    }
    else
    {
        jogador_rodada = 1;
    }
    return jogador_rodada;
}

// Imprime na tela um guia visual do tabuleiro, mostrando o número
// correspondente a cada casa, e as regras iniciais de posicionamento.
void tabuleiro_explicativo()
{
    printf("O número de cada casa no tabuleiro segue abaixo: \n\n");
    printf("  1 | 2 | 3\n");
    printf(" -----------\n");
    printf("  4 | 5 | 6\n");
    printf(" -----------\n");
    printf("  7 | 8 | 9\n\n");
    printf("O jogador 1 começará na linha de baixo como 'X'. O jogador 2 começará na linha de cima como 'O'.\n");

    return;
}

// Pergunta ao usuário qual modo de jogo ele deseja e depois itera pela arvore de decisao
// valida a entrada para garantir que seja 1 ou 2.
int opcao_jogo()
{
    int escolha;
    printf("Qual versão de Shisima deseja jogar?\n");
    printf("Escolha 1 (Humano vs Humano) ou 2 (Humano vs Computador): ");
    do
    {
        scanf("%d", &escolha);
        if (escolha < 1 || escolha > 2)
        {
            printf("Opção inválida. Digite 1 ou 2:");
        }
    } while (escolha < 1 || escolha > 2);

    return escolha;
}

// inicio logica de ia
// funcoes auxiliares de estrategia de jogo
// copia o conteúdo de um tabuleiro para outro pro computador simular a jogada
void copiar_tabuleiro(int destino[3][3], int origem[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            destino[i][j] = origem[i][j];
        }
    }
    
    return;
}

// Procura por uma jogada que resulte em vitória para o jogador especificado.
// Simula cada movimento possível e verifica se ele leva a uma vitória.
// Se encontrar, retorna a jogada vencedora. Caso contrário, retorna um movimento inválido.
movimento encontrar_jogada_vencedora(int tabuleiro[3][3], int jogador)
{
    movimento jogada;
    jogada.validade = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tabuleiro[i][j] == jogador)
            {
                movimento possiveis[8];
                int total = obter_movimentos_possiveis(i, j, possiveis, tabuleiro);
                for (int k = 0; k < total; k++)
                {
                    int copia[3][3];
                    copiar_tabuleiro(copia, tabuleiro);

                    // movimento simulado pra achar a jogada vencedora
                    copia[possiveis[k].linha_final][possiveis[k].coluna_final] = jogador;
                    copia[possiveis[k].linha_inicial][possiveis[k].coluna_inicial] = 0;
                    if (checar_vitoria(copia, jogador) == jogador)
                    {
                        return possiveis[k]; // retorna a jogada vencedora imediatamente
                    }
                }
            }
        }
    }
    return jogada;
}

// tenta mover uma peça para a casa central que tem mais controle do tabuleiro.
// Retorna o movimento para o centro se for possível.
movimento buscar_estrategia(int tabuleiro[3][3])
{
    movimento jogada;
    jogada.validade = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tabuleiro[i][j] == 2)
            {
                movimento possiveis[8];
                int total = obter_movimentos_possiveis(i, j, possiveis, tabuleiro);
                for (int k = 0; k < total; k++)
                {
                    if (possiveis[k].linha_final == 1 && possiveis[k].coluna_final == 1)
                    {
                        return possiveis[k]; // Retorna a jogada para o centro
                    }
                }
            }
        }
    }
    return jogada;
}

// Se nenhuma outra estratégia se aplicar, seleciona um movimento válido de forma aleatória.
// gera uma lista de todos os movimentos possíveis e escolhe um ao acaso.
movimento movimento_aleatorio(int tabuleiro[3][3])
{
    movimento jogada;
    jogada.validade = 0;
    movimento lista_total[24]; // todos os movimentos possíveis
    int total_movimentos = 0;

    // Coleta todos os movimentos possíveis para o computador
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tabuleiro[i][j] == 2)
            {
                movimento possiveis[8];
                int n = obter_movimentos_possiveis(i, j, possiveis, tabuleiro);
                for (int k = 0; k < n; k++)
                {
                    lista_total[total_movimentos++] = possiveis[k];
                }
            }
        }
    }

    // pega um movimento aleatório da lista
    if (total_movimentos > 0)
    {
        int indice_aleatorio = rand() % total_movimentos;
        return lista_total[indice_aleatorio];
    }

    return jogada;
}

// funcao principal da ia que decide e executa a jogada do computador.
// esquema de prioridades:
// procura uma jogada q venca imediatamente
// bloquear o adversário se o oponente estiver prestes a vencer
// executar tenta mover para a casa central
// mover aleatoriamente se nada acima for possível, faz uma jogada aleatória.
void realizar_jogada_computador(int tabuleiro[3][3])
{
    movimento jogada_final;
    jogada_final.validade = 0;

    // tentar vencer
    jogada_final = encontrar_jogada_vencedora(tabuleiro, 2);

    // bloquear adversário
    if (jogada_final.validade == 0)
    {
        movimento jogada_vencedora_inimiga = encontrar_jogada_vencedora(tabuleiro, 1);
        if (jogada_vencedora_inimiga.validade == 1)
        {
            // encontra uma peça que possa ser movida para a casa de bloqueio
            // precisa ter a flag em 0 para que o loop termine quando o bloqueio for feito
            int bloqueio_requerido = 0;
            for (int i = 0; i < 3 && bloqueio_requerido == 0; i++)
            {
                for (int j = 0; j < 3 && bloqueio_requerido == 0; j++)
                {
                    if (tabuleiro[i][j] == 2)
                    {
                        movimento possiveis_bloqueios[8];
                        int total = obter_movimentos_possiveis(i, j, possiveis_bloqueios, tabuleiro);

                        for (int k = 0; k < total && bloqueio_requerido == 0; k++)
                        {
                            if (possiveis_bloqueios[k].linha_final == jogada_vencedora_inimiga.linha_final &&
                                possiveis_bloqueios[k].coluna_final == jogada_vencedora_inimiga.coluna_final)
                            {

                                jogada_final = possiveis_bloqueios[k];
                                bloqueio_requerido = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    // estratégia de ocupar o centro
    if (jogada_final.validade == 0)
    {
        jogada_final = buscar_estrategia(tabuleiro);
    }

    // aleatório se nada deu certo
    if (jogada_final.validade == 0)
    {
        jogada_final = movimento_aleatorio(tabuleiro);
    }

    // aplica jogada trocando no tabuleiro temporario
    if (jogada_final.validade == 1)
    {
        tabuleiro[jogada_final.linha_final][jogada_final.coluna_final] = tabuleiro[jogada_final.linha_inicial][jogada_final.coluna_inicial];
        tabuleiro[jogada_final.linha_inicial][jogada_final.coluna_inicial] = 0;
    }

    return;
}

// Na main, criamos o tabuleiro e o loop que faz possível o código
// fluir por turnos. Parando se for retornado vitória pela função
// e definindo as regras do jogo.
// Segue-se a recomendação do arquivo do trabalho, com as funções na ordem explicitada.
int main()
{
    // inicializa o gerador de números aleatórios
    srand(time(NULL));

    int vitoria_j1 = 0;
    int vitoria_j2 = 0;
    int jogador_rodada = 1;
    int turno = 0;
    int resultado_rodada;
    int modo_jogo;
    int tabuleiro[3][3] = {{2, 2, 2}, {0, 0, 0}, {1, 1, 1}}; // Posição inicial requerida.

    modo_jogo = opcao_jogo();

    // Mostra as regras e o layout do tabuleiro.
    tabuleiro_explicativo();
    sleep(7); // pausa para o jogador ler as instruções

    while (vitoria_j1 == 0 && vitoria_j2 == 0 && turno < 60)
    {
        mostrar_tabuleiro(tabuleiro);

        // Estrutura de decisão para alocar a jogada do turno
        if (jogador_rodada == 1)
        {
            // O jogador 1 é sempre humano
            realizar_jogada(tabuleiro, jogador_rodada);
        }
        else // vez do jogador 2
        {
            if (modo_jogo == 1)
            {
                // Modo 1: Jogador 2 é humano
                realizar_jogada(tabuleiro, jogador_rodada);
            }
            else // Modo 2: Jogador 2 é o computador
            {
                printf("Vez do Computador.\n");
                realizar_jogada_computador(tabuleiro);
            }
        }

        // Verifica se a jogada resultou em vitória
        resultado_rodada = checar_vitoria(tabuleiro, jogador_rodada);
        if (resultado_rodada == 1)
        {
            vitoria_j1 = 1;
        }
        else if (resultado_rodada == 2)
        {
            vitoria_j2 = 1;
        }

        // Troca de jogador se o jogo não acabou
        if (vitoria_j1 == 0 && vitoria_j2 == 0)
        {
            jogador_rodada = proximo_jogador(jogador_rodada);
            turno++;
        }
    }

    mostrar_tabuleiro(tabuleiro);

    // Print com o resultado final do jogo.
    if (vitoria_j1 == 1)
    {
        printf("Vitória do Jogador 1.\n");
    }
    else if (vitoria_j2 == 1)
    {
        printf("Vitória do Jogador 2.\n");
    }
    else
    {
        printf("Empate por turno máximo atingido.\n");
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h> // funcao system clear
#include <unistd.h> // funcao sleep

// Lucas Ferreira Mazagão - 16304606

// Mostra o tabuleiro atual para que se tenha um visual do jogo.
// Aqui define-se X para o jogador 1, e O para o jogador 2. Espaços
// sem valor recebem ' ' para clareza visual.
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

// As três primeiras funções são auxiliares para checar se houve condição
// para acontecer vitória. Estamos checando se na matriz há uma sequência
// de três números que representariam a vitória do jogador atual.
int testar_coluna(int tab[3][3], int y)
{
    if (tab[0][y] != 0 && tab[0][y] == tab[1][y] && tab[1][y] == tab[2][y])
    {
        return 1;
    }
    return 0;
}

int testar_linha(int tab[3][3], int x)
{
    if (tab[x][0] != 0 && tab[x][0] == tab[x][1] && tab[x][1] == tab[x][2])
    {
        return 1;
    }
    return 0;
}

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

// Dado o novo tabuleiro, vamos retornar vitória caso as funções
// auxiliares tenham encontrado uma sequência válida.
// excluimos a possibilidade de vitoria na posição inicial para cada jogador
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

// Para realizar a jogada, criamos dois loops que identificam a validade de
// cada entrada e realizam a troca de valores escolhidos dentro da matriz.
// Para que o código consiga fluir e não travar, os loops possuem a mesma
// lógica dos comandos break e continue.
// OK
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

    // escolher peça para mover
    // define linha, coluna, poossiveis e tamanho_possiveis
    // OK
    while (loop_escolha == 1)
    {
        printf("Escolha um número de 1 a 9 para representar a peça desejada: \n");
        scanf("%d", &casa_escolhida);
        loop_escolha = 0;

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
            else if (tabuleiro[linha][coluna] != jogador_rodada)
            {
                system("clear");
                mostrar_tabuleiro(tabuleiro);
                printf("Peça do jogador adversário. Escolha tua peça.\n");
                loop_escolha = 1;
            }
        }
    }

    // escolhe alvo
    // realiza jogada alterando o tabuleiro
    // OK
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

    // realizar jogada
    tabuleiro[alvo_x][alvo_y] = tabuleiro[linha][coluna];
    tabuleiro[linha][coluna] = 0;

    return;
}

// Função para troca de jogadores para que a mesma estrutura
// consiga ser utilizada.
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

// OK
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

// OK
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


void realizar_jogada_computador(int tabuleiro[3][3]) {
    // computador sempre é o jogador 2
    // ele tem 3 peças no tabuleiro, e quer escolher a melhor jogada
    
    const int jogador = 2;
    int count = 0;
    
    for (int i = 0; i < 3; i++ ) {
        for (int j = 0; j++; j < 3) {
            if (tabuleiro[i][j] == jogador) {
                
            }
        }
    }
}

// Na main, criamos o tabuleiro e o loop que faz possível o código
// fluir por turnos. Parando se for retornado vitória pela função
// e definindo as regras do jogo.
// Segue-se a recomendação do arquivo do trabalho, com as funções na ordem explicitada.
int main()
{
    int vitoria_j1 = 0, vitoria_j2 = 0;
    int jogador_rodada = 1;
    int turno = 0;
    int resultado_rodada;
    int modo_jogo;
    int tabuleiro[3][3] = {{2, 2, 2}, {0, 0, 0}, {1, 1, 1}}; // Posição inicial requerida.

    modo_jogo = opcao_jogo();

    tabuleiro_explicativo();
    sleep(7);

    while (vitoria_j1 == 0 && vitoria_j2 == 0 && turno < 60)
    {
        mostrar_tabuleiro(tabuleiro);

        // Estrutura de decisão para alocar a jogada do turno
        if (jogador_rodada == 1)
        {
            // O jogador 1 é sempre humano
            realizar_jogada(tabuleiro, jogador_rodada);
        }
        else // Vez do jogador 2
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

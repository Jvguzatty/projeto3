/*============================================================================*/
/* CAVERNA MARCIANA                                                           */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu                                                     */
/*============================================================================*/
/** Fun��es para manipula��o da "caverna marciana". A caverna � representada
 * como uma matriz alocada dinamicamente e preenchida aleatoriamente. Os valores
 * de cada posi��o da matriz indicam o conte�do daquela casa no tabuleiro:
 *
 * 0: Casa livre/vazia.
 * -1: Po�o de lava.
 * 1 a 4: Casa contendo "calor" - o n�mero diz quantas casas vizinhas cont�m
 *   po�os de lava.
 * 5: Po�a d'�gua.
 * 6 a 9: Casa contendo po�a d'�gua E calor - o n�mero-5 diz quantas casas
 *   vizinhas cont�m po�os de lava.*/
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>

#include "caverna.h"

/*============================================================================*/

void preencheCaverna (Caverna* caverna, int n_pocos_lava);
void incrementaVizinhosTabuleiro (Caverna* caverna, Coordenada c);
int cavernaValida (Caverna* caverna);

/*============================================================================*/
/** Gera uma caverna. Aloca o tabuleiro e o preenche aleatoriamente.
 *
 * Par�metros: int altura: n�mero de linhas do tabuleiro.
 *             int largura: n�mero de colunas do tabuleiro.
 *             int n_pocos_lava: n�mero de po�os de lava.
 *             int random_seed: semente para o gerador de n�meros aleat�rios.
 *
 * Valor de Retorno: um ponteiro para uma struct Caverna alocada, NULL se algo falhou. */

Caverna* geraCaverna (int altura, int largura, int n_pocos_lava, int random_seed)
{
    int i, j;
    Caverna* caverna;

    /* Antes de tudo: o tabuleiro precisa ter pelo menos 4 posi��es livres na entrada, e mais 1 posi��o para a po�a d'�gua.
       Al�m disso, pelo menos metade das posi��es restantes precisa estar livre.
       O tabuleiro tamb�m precisa ter pelo menos 4x4 casas. */
    if (n_pocos_lava > (altura*largura-5)/2 ||
        altura < 4 ||
        largura < 4)
        return (NULL);

    /* Aloca. */
    caverna = (Caverna*) malloc (sizeof (Caverna));
    if (!caverna)
        return (NULL);

    caverna->altura = altura;
    caverna->largura = largura;
    caverna->tabuleiro = (int**) malloc (sizeof (int*) * altura);
    if (!caverna->tabuleiro)
        return (NULL);

    for (i = 0; i < altura; i++)
    {
        caverna->tabuleiro [i] = (int*) malloc (sizeof (int) * largura);
        if (!(caverna->tabuleiro [i]))
        {
            destroiCaverna (caverna);
            return (NULL);
        }
    }

    /* Agora, repete at� conseguir gerar uma caverna v�lida.
       Gerar e testar � uma estrat�gia meio "burra", mas � estruturalmente mais simples do que tentar garantir que qualquer caverna gerada ser� v�lida.
       O problema � que a gera��o pode ficar lenta se houver muitos po�os de lava - no limite, o programa pode at� congelar! */
    srand (random_seed);
    do
    {
        /* Inicializa com 0s. */
        for (i = 0; i < altura; i++)
            for (j = 0; j < largura; j++)
                caverna->tabuleiro [i][j] = 0;

        /* Preenche. */
        preencheCaverna (caverna, n_pocos_lava);

    } while (!cavernaValida (caverna));

    return (caverna);
}

/*----------------------------------------------------------------------------*/
/** Fun��o auxiliar chamada pela geraCaverna para preencher o tabuleiro.
 *
 * Par�metros: Caverna* caverna: caverna a preencher.
 *             int n_pocos_lava: n�mero de po�os de lava.
 *
 * Valor de Retorno: NENHUM */

void preencheCaverna (Caverna* caverna, int n_pocos_lava)
{
    int i, j;
    Coordenada* casas;
    int n_casas = 0;

    casas = (Coordenada*) malloc (sizeof (Coordenada) * (caverna->altura * caverna->largura - 4));

    /* Coloca na lista de casas todas as casas do tabuleiro (menos as 4 da entrada). */
    /* Usar um vetor aqui � meio lento, mas bem mais simples que inventar uma lista encadeada ou jogar um algoritmo de shuffling. */
    for (i = 0; i < caverna->altura; i++)
        for (j = 0; j < caverna->largura; j++)
        {
            if (i >= 2 || j >= 2)
            {
                casas [n_casas].y = i;
                casas [n_casas].x = j;
                n_casas++;
            }
        }

    /* Seleciona agora n_pocos_lava+1 casas. O +1 � para a po�a d'�gua. */
    n_pocos_lava++;
    while (n_pocos_lava)
    {
        int c = rand () % n_casas; /* Escolhe uma casa... */

        if (n_pocos_lava == 1) /* Po�a d'�gua. */
            caverna->tabuleiro [casas [c].y] [casas [c].x] += POSICAO_COM_AGUA; /* Note que eu incremento, n�o atribuo direto POSICAO_COM_AGUA - precisamos saber o n�mero de vizinhos com lava! */
        else /* Lava. */
        {
            caverna->tabuleiro [casas [c].y] [casas [c].x] = POSICAO_COM_LAVA;
            incrementaVizinhosTabuleiro (caverna, casas [c]);
        }

        /* Remove a casa da lista de casas. */
        for (i = c+1; i < n_casas; i++)
            casas [i-1] = casas [i];
        n_casas--;
        n_pocos_lava--;
    }

    free (casas);
}

/*----------------------------------------------------------------------------*/
/** Fun��o auxiliar chamada pela preencheCaverna para aumentar a contagem de
 * calor ao redor de um po�o de lava.
 *
 * Par�metros: Caverna* caverna: a caverna que est� sendo gerada.
 *             Coordenada c: posi��o do po�o de lava.
 *
 * Valor de Retorno: NENHUM */

void incrementaVizinhosTabuleiro (Caverna* caverna, Coordenada c)
{
    if (c.y - 1 >= 0 && caverna->tabuleiro [c.y-1][c.x] != POSICAO_COM_LAVA) /* Acima */
        caverna->tabuleiro [c.y-1][c.x]++;

    if (c.y + 1 < caverna->altura && caverna->tabuleiro [c.y+1][c.x] != POSICAO_COM_LAVA) /* Abaixo */
        caverna->tabuleiro [c.y+1][c.x]++;

    if (c.x - 1 >= 0 && caverna->tabuleiro [c.y][c.x-1] != POSICAO_COM_LAVA) /* Esquerda */
        caverna->tabuleiro [c.y][c.x-1]++;

    if (c.x + 1 < caverna->largura && caverna->tabuleiro [c.y][c.x+1] != POSICAO_COM_LAVA) /* Direita */
        caverna->tabuleiro [c.y][c.x+1]++;
}

/*----------------------------------------------------------------------------*/
/** Fun��o auxiliar chamada pela geraCaverna para verificar se a caverna �
 * v�lida. Ela ser� v�lida se existir pelo menos um caminho entre a entrada
 * e a po�a d'�gua. Para testar isso, usamos uma estrat�gia baseada em uma
 * pilha: vamos empilhando as casas acess�veis a partir da entrada, at�
 * conseguir encontrar a po�a d'�gua (caverna v�lida) ou a pilha se esvaziar
 * (caverna inv�lida).
 *
 * Par�metros: Caverna* caverna: caverna a testar.
 *
 * Valor de Retorno: 0 se for uma caverna inv�lida, 1 do contr�rio. */

int cavernaValida (Caverna* caverna)
{
    int i, j;
    int achou = 0;
    int pos_pilha = 0;
    Coordenada* pilha; /* Pilha para as casas acess�veis. */
    int** casa_testada; /* Matriz que diz quais casas do tabuleiro j� foram testadas. */

    /* Aloca a pilha e a matriz para casas testadas. */
    casa_testada = (int**) malloc (sizeof (int*) * caverna->altura);
    for (i = 0; i < caverna->altura; i++)
    {
        casa_testada [i] = (int*) malloc (sizeof (int) * caverna->largura);
        for (j = 0; j < caverna->largura; j++)
            casa_testada [i][j] = 0;
    }

    pilha = (Coordenada*) malloc (sizeof (Coordenada) * caverna->altura * caverna->largura);

    /* Come�a com a entrada. */
    pilha [pos_pilha].x = 0;
    pilha [pos_pilha].y = 0;
    pos_pilha++;

    /* Repete at� esvaziar a pilha ou achar um caminho. */
    while (!achou && pos_pilha)
    {
        /* Pop da posi��o no topo da pilha. */
        Coordenada c = pilha [pos_pilha-1];
        pos_pilha--;

        casa_testada [c.y][c.x] = 1;

        /* �gua? */
        if (caverna->tabuleiro [c.y][c.x] >= POSICAO_COM_AGUA)
            achou = 1;
        else
        {
            /* Testa os vizinhos da casa. */
            /* Acima */
            if ((c.y - 1 >= 0) && (!casa_testada [c.y-1][c.x]) && (caverna->tabuleiro [c.y-1][c.x] != POSICAO_COM_LAVA))
            {
                pilha [pos_pilha].x = c.x;
                pilha [pos_pilha].y = c.y-1;
                pos_pilha++;
            }

            /* Abaixo */
            if ((c.y + 1 < caverna->altura) && (!casa_testada [c.y+1][c.x]) && (caverna->tabuleiro [c.y+1][c.x] != POSICAO_COM_LAVA))
            {
                pilha [pos_pilha].x = c.x;
                pilha [pos_pilha].y = c.y+1;
                pos_pilha++;
            }

            /* Esquerda */
            if ((c.x - 1 >= 0) && (!casa_testada [c.y][c.x-1]) && (caverna->tabuleiro [c.y][c.x-1] != POSICAO_COM_LAVA))
            {
                pilha [pos_pilha].x = c.x-1;
                pilha [pos_pilha].y = c.y;
                pos_pilha++;
            }

            /* Direita */
            if ((c.x + 1 < caverna->largura) && (!casa_testada [c.y][c.x+1]) && (caverna->tabuleiro [c.y][c.x+1] != POSICAO_COM_LAVA))
            {
                pilha [pos_pilha].x = c.x+1;
                pilha [pos_pilha].y = c.y;
                pos_pilha++;
            }
        }
    }

    /* Libera tudo. */
    for (i = 0; i < caverna->altura; i++)
        free (casa_testada [i]);
    free (casa_testada);
    free (pilha);

    return (achou);
}

/*----------------------------------------------------------------------------*/
/** Desaloca uma caverna.
 *
 * Par�metros: Caverna* caverna: a caverna a desalocar.
 *
 * Valor de Retornor: NENHUM */

void destroiCaverna (Caverna* caverna)
{
    int i;

    for (i = 0; i < caverna->altura; i++)
    {
        if (caverna->tabuleiro [i])
            free (caverna->tabuleiro [i]);
    }
    free (caverna->tabuleiro);
    free (caverna);
}

/*----------------------------------------------------------------------------*/
/** Mostra na tela uma caverna. Esta fun��o deve ser usada apenas para debug
 * ou para o resultado final - o jogo n�o faz sentido se pudermos visulizar a
 * caverna inteira!!!
 *
 * As casas s�o impressas assim:
 * Entrada: E
 * Casa livre: espa�o vazio.
 * Casa com lava: X
 * Casa com calor: o n�mero de vizinhos com lava.
 * Casa com �gua: A
 * Casa com �gua e calor: A, seguido do n�mero de vizinhos com lava.
 *
 * Par�metros: Caverna* caverna: a caverna a mostrar.
 *
 * Valor de Retorno: NENHUM */

 void mostraCaverna (Caverna* caverna)
 {
    int i, j;

    /* Linha superior - 1 para a linha � esquerda, +4 para cada casa do tabuleiro. */
    for (i = 0; i < caverna->largura*4+1; i++)
        printf ("-");
    printf ("\n");

    /* Tabuleiro. */
    for (i = 0; i < caverna->altura; i++)
    {
        printf ("|");
        for (j = 0; j < caverna->largura; j++)
        {
            if (!i && !j) /* Entrada */
                printf (" E |");
            else if (posicaoLivre (caverna->tabuleiro [i][j]))
                printf ("   |");
            else if (posicaoComLava (caverna->tabuleiro [i][j]))
                printf (" X |");
            else if (posicaoComCalor (caverna->tabuleiro [i][j]))
                printf (" %d |", caverna->tabuleiro [i][j]);
            else if (posicaoComAguaECalor (caverna->tabuleiro [i][j]))
                printf (" A%d|", caverna->tabuleiro [i][j]-POSICAO_COM_AGUA);
            else
                printf (" A |");
        }
        printf ("\n");

        /* Linha inferior - 1 para a linha � esquerda, +4 para cada casa do tabuleiro. */
        for (j = 0; j < caverna->largura*4+1; j++)
            printf ("-");
        printf ("\n");
    }
}

/*----------------------------------------------------------------------------*/
/* Pequenas fun��es para testar o conte�do de uma casa do tabuleiro.
 *
 * Par�metros: int valor_casa: o conte�do de uma casa no tabuleiro.
 *
 * Valor de Retorno: 1 se a posi��o cont�m o que � pedido, 0 do contr�rio. */

int posicaoLivre (int valor_casa) {return (!valor_casa);}
int posicaoComLava (int valor_casa) {return (valor_casa == POSICAO_COM_LAVA);}
int posicaoComCalor (int valor_casa) {return (valor_casa > 0 && valor_casa < POSICAO_COM_AGUA);}
int posicaoComAgua (int valor_casa) {return (valor_casa >= POSICAO_COM_AGUA);}
int posicaoComAguaECalor (int valor_casa) {return (valor_casa > POSICAO_COM_AGUA);}

/*============================================================================*/


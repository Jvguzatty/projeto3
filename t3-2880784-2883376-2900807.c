/*----------------------------------------------------------------------------*/
/* Autores: Rafael Okuma, João Victor Dos Santos, Thiago Macedo               */
/*============================================================================*/
/*  Ra:     2883376,        2883376,            2900807                       */
/*============================================================================*/

#include <stdlib.h>

#include "decisor_aleatorio.h"



/*============================================================================*/
/** Simplesmente aloca um Decisor.
 *
 * Parâmetros: int altura: número de linhas no tabuleiro.
 *             int largura: número de colunas no tabuleiro.
 *
 * Valor de Retorno: um Decisor alocado. */

Decisor* criaDecisor(int altura, int largura)
{
    int i,j;
    Decisor* d = (Decisor*) malloc(sizeof(Decisor));

    d->reconhecer_spawn = 0;
    d->TEM_AGUAA = 0;

    d->mapa = (int**) malloc(altura * sizeof(int*));
    for (i = 0; i < altura; i++)
    {
        d->mapa[i] = (int*) malloc(largura * sizeof(int));
    }

    for(i=0;i<altura;i++){
        for(j=0;j<largura;j++){
            d->mapa[i][j] = 0;
        }
    }


    return d;
}

/*----------------------------------------------------------------------------*/
/** Simplesmente desaloca um Decisor.
 *
 * Parâmetros: Decisor* d: Decisor a destruir.
 *
 * Valor de Retorno: NENHUM */

void destroiDecisor (Decisor* d)
{
    free (d);
}

/*----------------------------------------------------------------------------*/
/** Este decisor não faz absolutamente nada quando é informado sobre o conteúdo
 * da posição atual! Ele simplesmente retorna um movimento aleatório.
 *
 * Parâmetros: Decisor* d: o Decisor.
 *             Coordenada pos: posição atual.
 *             int agua: 1 se a posição atual tiver água, 0 do contrário.
 *             int n_lava: número de poços de lava em casas vizinhas à atual.
 *
 * Valor de Retorno: a direção do próximo movimento: 1 – para cima, 2 – para baixo, 3 – para a esquerda, 4 – para a direita. */

int proximoMovimento (Decisor* d, Coordenada pos, int agua, int n_lava)
{



    if (agua == 1)
    {
        d->TEM_AGUAA = 1; //pq eu fiz uma flag? resposta: a variavel "agua" so diz se APENAS aquela posicao tem agua.
    }
    if (d->TEM_AGUAA == 1)
    {
        return (rand() % 2) ? 3 : 1;
    }else{
        d->mapa[pos.y][pos.x] = 1;
        if (d->reconhecer_spawn == 0)
        {
        if (pos.x == 0 && pos.y == 0) return (4);
        if (pos.x == 1 && pos.y == 0) return (2);
        if (pos.x == 1 && pos.y == 1) return (3);
//              Se a memoria diz que ele AINDA NN terminou o spawn (vale 0)
        if (pos.x == 0 && pos.y == 1)
        {
            d->reconhecer_spawn = 1;
            return (1);
        }
    }
      return (1+(rand ()%4));
    }



//////////////////////////////////////////////////////////
    //reconhecer spawn, pq nao pode ter lava aos redos dele


////////////////////////////////////////////////////////////



}

/*============================================================================*/

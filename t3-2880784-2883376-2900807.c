/*----------------------------------------------------------------------------*/
/* Autores: Rafael Okuma, João Victor Dos Santos, Thiago Macedo               */
/*============================================================================*/
/*  Ra:     2883376,        2883376,            2900807                       */
/*============================================================================*/

#include <stdlib.h>

#include "t3-2883376-2883376-2900807.h"

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

    d->altura = altura;
    d->largura = largura;

    d->inverte = 0;
    d->i = 0;
    d->reconhecer_spawn = 0;
    d->TEM_AGUA = 0;
    d->random = 0;
    d->passo = -1;

    d->ultimo_x = 0;
    d->ultimo_y = 0;

    d->path = (int*) malloc(sizeof(int)*1000);

    d->mapa = (int**) malloc(sizeof(int*)*altura);
    d->peso = (int**) malloc(sizeof(int*)*altura);

    for(i=0;i<altura;i++)
    {
        d->mapa[i]=(int*) malloc(sizeof(int)*largura);
        d->peso[i]=(int*) malloc(sizeof(int)*largura);
    }

    for(i=0;i<altura;i++)
    {
        for(j=0;j<largura;j++)
        {
            d->mapa[i][j]=0;
            d->peso[i][j]=50; // tudo comeca desconhecido
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
    int i;
    
    for(i=0;i<d->altura;i++)
    {
        free(d->mapa[i]);
        free(d->peso[i]);
    }

    free(d->mapa);
    free(d->peso);
    free(d->path);

    free(d);
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
 * Valor de Retorno: a direção do próximo movimento.
 */

int proximoMovimento (Decisor* d, Coordenada pos, int agua, int n_lava)
{
    if(pos.x != d->ultimo_x || pos.y != d->ultimo_y)
    {
        d->path[d->i] = d->random;
        d->i++;

        d->ultimo_x = pos.x;
        d->ultimo_y = pos.y;
    }

    if(n_lava==0)
        d->mapa[pos.y][pos.x] = 1;
    else
        d->mapa[pos.y][pos.x] = 2;

    if(agua==1)
    {
        d->TEM_AGUA=1;
        d->passo=d->i-1;
    }

    if(d->TEM_AGUA==1)
    {
        if(d->passo<0)
            return 1;

        if(d->path[d->passo]==1)
        {
            d->passo--;
            return 2;
        }

        if(d->path[d->passo]==2)
        {
            d->passo--;
            return 1;
        }

        if(d->path[d->passo]==3)
        {
            d->passo--;
            return 4;
        }

        if(d->path[d->passo]==4)
        {
            d->passo--;
            return 3;
        }
    }

    if(d->reconhecer_spawn==0)
    {
        if(pos.x==0 && pos.y==0)
            return 4;

        if(pos.x==1 && pos.y==0)
            return 2;

        if(pos.x==1 && pos.y==1)
            return 3;

        if(pos.x==0 && pos.y==1)
        {
            d->reconhecer_spawn=1;
            return 1;
        }
    }
        d->random = 1 + (rand()%4);

    return d->random;
}

/*============================================================================*/
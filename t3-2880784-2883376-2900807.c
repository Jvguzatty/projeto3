/*----------------------------------------------------------------------------*/
/* Autores: Rafael Okuma, João Victor Dos Santos, Thiago Macedo               */
/*============================================================================*/
/*  Ra:     2880784,        2883376,            2900807                       */
/*============================================================================*/

#include <stdlib.h>
#include <string.h>

#include "t3-2883376-2883376-2900807.h"

int direcaoOposta(int dir)
{
    if(dir == DIR_MOVIMENTO_CIMA)
    {
        return DIR_MOVIMENTO_BAIXO;
    }
    if(dir == DIR_MOVIMENTO_BAIXO)
    {
        return DIR_MOVIMENTO_CIMA;
    }
    if(dir == DIR_MOVIMENTO_ESQUERDA)
    {
        return DIR_MOVIMENTO_DIREITA;
    }
    if(dir == DIR_MOVIMENTO_DIREITA)
    {
        return DIR_MOVIMENTO_ESQUERDA;
    }

    return 0;
}

///////////////////////////////////////////////////////////////////

Decisor* criaDecisor(int altura, int largura)
{
    Decisor* d = (Decisor*) malloc(sizeof(Decisor));

    d->altura = altura;
    d->largura = largura;
    d->topo_historico = 0;
    d->modo_retorno = 0;
    d->ultima_direcao = 0;

    memset(d->visitado, 0, sizeof(d->visitado));
    memset(d->seguro, 0, sizeof(d->seguro));

    d->seguro[0][0] = 1;

    return d;
}

////////////////////////////////////////////////////////////////////////////////////////////

void destroiDecisor(Decisor* d)
{
    free(d);
}

////////////////////////////////////////////////////////////////////////////////////////////
int proximoMovimento(Decisor* d, Coordenada pos, int agua, int n_lava)
{
    int dirs[4] = {DIR_MOVIMENTO_CIMA, DIR_MOVIMENTO_BAIXO, DIR_MOVIMENTO_ESQUERDA, DIR_MOVIMENTO_DIREITA};
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};
    int i;

    d->visitado[pos.y][pos.x]++;
    d->seguro[pos.y][pos.x] = 1;

    if(agua == 1)
    {
        d->modo_retorno = 1;
    }

    if(n_lava == 0)
    {
        if(pos.y - 1 >= 0)
        {
            d->seguro[pos.y - 1][pos.x] = 1;
        }
        if(pos.y + 1 < d->altura)
        {
            d->seguro[pos.y + 1][pos.x] = 1;
        }
        if(pos.x - 1 >= 0)
        {
            d->seguro[pos.y][pos.x - 1] = 1;
        }
        if(pos.x + 1 < d->largura)
        {
            d->seguro[pos.y][pos.x + 1] = 1;
        }
    }
    else
    {
        if(pos.y - 1 >= 0)
        {
            d->seguro[pos.y - 1][pos.x] = 2;
        }
        if(pos.y + 1 < d->altura)
        {
            d->seguro[pos.y + 1][pos.x] = 2;
        }
        if(pos.x - 1 >= 0)
        {
            d->seguro[pos.y][pos.x - 1] = 2;
        }
        if(pos.x + 1 < d->largura)
        {
            d->seguro[pos.y][pos.x + 1] = 2;
        }
    }

    if(d->modo_retorno == 1)
    {
        if(d->topo_historico > 0)
        {
            d->topo_historico--;
            return direcaoOposta(d->historico[d->topo_historico].x);
        }

        return DIR_MOVIMENTO_CIMA;
    }

    {
        int melhor_direcao = -1;
        int melhor_peso = 1000000;

        for(i = 0; i < 4; i++)
        {
            int ny = pos.y + dy[i];
            int nx = pos.x + dx[i];
            int peso = 0;
            int vizinhos_nao_visitados = 0;

            if(ny < 0 || ny >= d->altura || nx < 0 || nx >= d->largura)
            {
                continue;
            }

            if(d->seguro[ny][nx] != 1 || d->visitado[ny][nx] != 0)
            {
                continue;
            }

            if(ny > 0 && d->visitado[ny - 1][nx] == 0 && d->seguro[ny - 1][nx] == 1)
            {
                vizinhos_nao_visitados++;
            }
            if(ny + 1 < d->altura && d->visitado[ny + 1][nx] == 0 && d->seguro[ny + 1][nx] == 1)
            {
                vizinhos_nao_visitados++;
            }
            if(nx > 0 && d->visitado[ny][nx - 1] == 0 && d->seguro[ny][nx - 1] == 1)
            {
                vizinhos_nao_visitados++;
            }
            if(nx + 1 < d->largura && d->visitado[ny][nx + 1] == 0 && d->seguro[ny][nx + 1] == 1)
            {
                vizinhos_nao_visitados++;
            }

            peso += vizinhos_nao_visitados;
            if(d->ultima_direcao != 0 && dirs[i] == direcaoOposta(d->ultima_direcao))
            {
                peso += 2;
            }

            if(peso < melhor_peso)
            {
                melhor_peso = peso;
                melhor_direcao = i;
            }
        }

        if(melhor_direcao >= 0)
        {
            int direcao = dirs[melhor_direcao];

            d->historico[d->topo_historico].x = direcao;
            d->historico[d->topo_historico].y = 0;
            d->topo_historico++;
            d->ultima_direcao = direcao;
            return direcao;
        }
    }

    if(d->topo_historico > 0)
    {
        d->topo_historico--;
        return direcaoOposta(d->historico[d->topo_historico].x);
    }

    for(i = 0; i < 4; i++)
    {
        int ny = pos.y + dy[i];
        int nx = pos.x + dx[i];

        if(ny >= 0 && ny < d->altura && nx >= 0 && nx < d->largura)
        {
            if(d->visitado[ny][nx] == 0)
            {
                int direcao = dirs[i];

                d->historico[d->topo_historico].x = direcao;
                d->historico[d->topo_historico].y = 0;
                d->topo_historico++;
                d->ultima_direcao = direcao;
                return direcao;
            }
        }
    }

    return 1 + (rand() % 4);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
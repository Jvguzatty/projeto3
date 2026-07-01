/*----------------------------------------------------------------------------*/
/* Autores: Rafael Okuma, João Victor Dos Santos, Thiago Macedo               */
/*============================================================================*/
/*  Ra:     2883376,        2883376,            2900807                       */
/*============================================================================*/

#ifndef __DECISOR_ALEATORIO_H
#define __DECISOR_ALEATORIO_H

#include "game_state.h"

#define MAX_DIM 20

typedef struct
{
    int x;
    int y;
} Passo;

typedef struct
{
    int altura;
    int largura;

    int visitado[MAX_DIM][MAX_DIM];
    int seguro[MAX_DIM][MAX_DIM];

    Passo historico[MAX_DIM * MAX_DIM * 4];
    int topo_historico;
    int modo_retorno;
    int ultima_direcao;
} Decisor;

Decisor* criaDecisor (int altura, int largura);
void destroiDecisor (Decisor* d);
int proximoMovimento (Decisor* d, Coordenada pos, int agua, int n_lava);

#endif
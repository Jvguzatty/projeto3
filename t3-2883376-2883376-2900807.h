/*----------------------------------------------------------------------------*/
/* Autores: Rafael Okuma, João Victor Dos Santos, Thiago Macedo               */
/*============================================================================*/
/*  Ra:     2883376,        2883376,            2900807                       */
/*============================================================================*/

#ifndef __DECISOR_ALEATORIO_H
#define __DECISOR_ALEATORIO_H

/*============================================================================*/

#include "game_state.h"

/*============================================================================*/
/** Estrutura do decisor. Este é um decisor muito burro, não tem nada... */

typedef struct{
    int** mapa;
    int reconhecer_spawn;
    int TEM_AGUA;
    int* path;
    int random;
    int i;
    int inverte; 
    int passo;

} Decisor;

/*============================================================================*/
Decisor* criaDecisor (int altura, int largura);
void destroiDecisor (Decisor* d);
int proximoMovimento (Decisor* d, Coordenada pos, int agua, int n_lava);

/*============================================================================*/
#endif /* __DECISOR_ALEATORIO_H */



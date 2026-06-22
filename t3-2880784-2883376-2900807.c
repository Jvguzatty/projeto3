/*============================================================================*/
/* CAVERNA MARCIANA: DECISOR                                                  */
/*----------------------------------------------------------------------------*/
/* Autores:                                                                   */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "game_state.h"
#include "decisor_aleatorio.h"

/*============================================================================*/
/** Cria e inicializa o decisor. */
Decisor* criaDecisor (int altura, int largura)
{
    Decisor* d = (Decisor*) malloc (sizeof (Decisor));
    d->reconhecer_spawn = 0;
    return (d);
}

/*----------------------------------------------------------------------------*/
/** Desaloca o decisor. */
void destroiDecisor (Decisor* d)
{
    free (d);
}

/*----------------------------------------------------------------------------*/
//1  para cima, 2  para baixo, 3  para a esquerda, 4  para a direita.
/** Calcula o próximo movimento do robô. */
int proximoMovimento (Decisor* d, Coordenada pos, int agua, int n_lava)
{
    
//////////////////////////////////////////////////////////
    //reconhecer spawn, pq nao pode ter lava aos redos dele
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
////////////////////////////////////////////////////////////
    return (2);
}

/*============================================================================*/

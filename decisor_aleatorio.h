/*============================================================================*/
/* UM DECISOR MUITO, MUITO SIMPLES PARA O PROBLEMA DA CAVERNA MARCIANA        */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu                                                     */
/*============================================================================*/
/** Um robô muito ruim - ele decide seus movimentos aleatoriamente! */
/*============================================================================*/

#include <stdlib.h>

#include "t3-x-y-z.h"

/*============================================================================*/
/** Simplesmente aloca um Decisor.
 *
 * Parâmetros: int altura: número de linhas no tabuleiro.
 *             int largura: número de colunas no tabuleiro.
 *
 * Valor de Retorno: um Decisor alocado. */

Decisor* criaDecisor (int altura, int largura)
{
    Decisor* d = ((Decisor*) malloc ((altura*largura)*sizeof (Decisor)));
    d->m = (int**)malloc(altura*sizeof(int*));
    for(int i = 0;i<largura;i++){
        d->m[i] = (int*)malloc(largura*sizeof(int));
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

    if(agua == 1){

    }
////////////////////////////////////////////////////////////
    return (2);


}

/*============================================================================*/

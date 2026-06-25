/*============================================================================*/
/* UM DECISOR MUITO, MUITO SIMPLES PARA O PROBLEMA DA CAVERNA MARCIANA        */
/*----------------------------------------------------------------------------*/
/* Autor: Bogdan T. Nassu                                                     */
/*============================================================================*/
/** Um robô muito ruim - ele decide seus movimentos aleatoriamente! */
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

Decisor* criaDecisor (int altura, int largura)
{
    Decisor *b;
    b = (Decisor*) malloc (sizeof (Decisor));
    b->n_jogadas = 0;
    b->v = (int*)malloc(sizeof(int)*20*altura*largura);
    b->achou = 0;

    return b;
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
    int a;


    if(agua){
        d->achou = 1;
    }

    if(d->achou ){
        a = (rand() % 2) ? 3 : 1;
        /*
        if(d->n_jogadas>=0){

            if(d->v[d->n_jogadas] == 1){
                a = 2;
                d->n_jogadas--;
            }else if(d->v[d->n_jogadas] == 2){
                a = 1;
                d->n_jogadas--;
            }else if(d->v[d->n_jogadas] == 3){
                a = 4;
                d->n_jogadas--;
            }else{
                a = 3;
                d->n_jogadas--;
            }


        }else{
            a = (rand() % 2) ? 3 : 1;
        }
            */

    }else{
        d->n_jogadas++;
        a = (1+(rand ()%4));
        d->v[d->n_jogadas]=a;
    }

    //printf("%d %d",pos.x,pos.y);
    //printf("\n");


    return a; // Retorna um valor aleatório entre 1 e 4.
}

/*============================================================================*/
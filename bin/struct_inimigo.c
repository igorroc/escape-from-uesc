#ifndef INIMIGO_C
#define INIMIGO_C

#include <gb/gb.h>

typedef struct Inimigo{
    UINT8 id;
    UINT8 x; //posicao x
    UINT8 y; //posicao y
    UINT8 velocidade_x;
    UINT8 velocidade_y; //velocidade de queda
    INT8 direcao; //indica se esta virado pra esquerda (-1) ou direita (1)
    INT8 passo; //usado para fazer a animacao de movimento
}_Inimigo;

    _Inimigo inimigo;


#endif
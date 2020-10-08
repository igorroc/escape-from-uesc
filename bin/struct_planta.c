#ifndef PLANTA_C
#define PLANTA_C

#include <gb/gb.h>

typedef struct Planta{
    UINT8 id;
    UINT8 x;
    UINT8 y;
    UINT8 direcao; //1 para a direita, 0 para a esquerda
    UINT8 passo;
    UINT8 velocidade_x;
}_Planta;

    _Planta planta[6];

#endif
#ifndef EXPLORER_C
#define EXPLORER_C

#include <gb/gb.h>

typedef struct Explorer{
    UINT8 id;
    UINT8 x; //posicao x
    UINT8 y; //posicao y
    UINT8 passo;
    INT8 velocidade;

}_Explorer;

    _Explorer explorer;


#endif
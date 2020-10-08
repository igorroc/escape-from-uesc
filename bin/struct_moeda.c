#ifndef MOEDA_C
#define MOEDA_C

#include <gb/gb.h>

typedef struct Moeda{
    UINT8 id;
    UINT8 x;
    UINT8 y;
    UINT8 brilho;
    UINT8 giro;
    UINT8 naTela;
    UINT8 contador;
    UINT8 plataforma;
    UINT8 cont_letra;
}_Moeda;

    _Moeda moeda;

#endif
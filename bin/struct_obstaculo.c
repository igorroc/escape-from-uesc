#ifndef OBSTACULO_C
#define OBSTACULO_C

#include <gb/gb.h>

typedef struct Obstaculo{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    UINT8 variacao; // 0 para ";", 1 para moeda, 2 para café
    UINT8 velocidade; //Velocidade que o obstaculo passa na tela
    UINT8 quantidade; //Qauntidade de vezes que o obstaculo passou na tela
}_Obstaculo;

    _Obstaculo obstaculo;


#endif
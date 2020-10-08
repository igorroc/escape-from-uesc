#ifndef OBSTACULO_C
#define OBSTACULO_C

#include <gb/gb.h>

typedef struct Obstaculo{
    UINT8 id;
    UINT8 x; //posicao x
    UINT8 y; //posicao y
    UINT8 variacao; // 0 PARA PONTO E VIRGULA, 1 PARA MOEDA, 2 PARA CAFE
    UINT8 velocidade;
    UINT8 quantidade; // QUANTIDADE DE VEZES QUE ELE JA PASSOU NA TELA
}_Obstaculo;

    _Obstaculo obstaculo;


#endif
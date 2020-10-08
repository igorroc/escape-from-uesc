#ifndef PLANTA_C
#define PLANTA_C

#include <gb/gb.h>

typedef struct Planta{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    UINT8 direcao; //1 para a direita, 0 para a esquerda
    UINT8 passo; //Variavel para controle da animação de andar
    UINT8 velocidade; //Velocidade que a planta passa na tela
}_Planta;

    _Planta planta[6];

#endif
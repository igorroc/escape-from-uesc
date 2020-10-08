#ifndef MOEDA_C
#define MOEDA_C

#include <gb/gb.h>

typedef struct Moeda{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    UINT8 brilho; //Variavel para o controle da passada do brilho
    UINT8 giro; //Variavel para o controle do giro
    UINT8 naTela; //Variavel para o controle da moeda na tela
    UINT8 contador; //Contador para quando a moeda aparece na tela
    UINT8 plataforma; //Variavel para o controle de qual plataforma ela aparecera, na fase do Jorge
    UINT8 cont_letra; //Variavel para o controle de quando virá a letra, na fase do Jorge
}_Moeda;

    _Moeda moeda;

#endif
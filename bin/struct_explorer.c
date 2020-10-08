#ifndef EXPLORER_C
#define EXPLORER_C

#include <gb/gb.h>

typedef struct Explorer{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    UINT8 flutuar; //Variavel para o controle de quando o explorer deve flutuar
}_Explorer;

    _Explorer explorer;


#endif
#ifndef LIVRO_C
#define LIVRO_C

#include <gb/gb.h>

typedef struct Livro{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    UINT8 naTela; //Indica se o livro esta na tela
    UINT8 contador; //Quando chegar em 5, se torna uma caveira
    UINT8 caveira; //Indica se é uma caveira
}_Livro;

    _Livro livro;


#endif
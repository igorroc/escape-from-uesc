#ifndef LIVRO_C
#define LIVRO_C

#include <gb/gb.h>

typedef struct Livro{
    UINT8 id; // INDICA O ID DA SPRITE
    UINT8 x; // INDICA A POSICAO HORIZONTAL
    UINT8 y; // INDICA A POSICAO VERTICAL
    UINT8 naTela; // INDICA SE O LIVRO ESTA NA TELA
    UINT8 contador; // QUANDO CHEGAR EM 5, VIRA UMA CAVEIRA
    UINT8 caveira; // INDICA SE E UMA CAVEIRA
}_Livro;

    _Livro livro;


#endif
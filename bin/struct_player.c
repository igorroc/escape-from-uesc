#ifndef PLAYER_C
#define PLAYER_C

#include <gb/gb.h>

typedef struct Player{
    UINT8 id;
    UINT8 x; //Posicao x (vai de 0 -> 160)
    UINT8 y; //Posicao y (vai de 0 -> 144)
    UINT8 velocidade_x;
    UINT8 velocidade_y; //Velocidade de queda
    INT8 direcao; //Indica se esta virado pra esquerda (-1) ou direita (1)
    INT8 passo; //Usado para fazer a animacao de movimento
    INT8 agachando; //True se estiver pressionado para baixo
    INT8 socando; //True se tiver pressionado A
    INT8 piscando; //Contador para a animacao de piscar, tempo padrao: 100
    INT8 pulando; //True quando estiver no ar
    INT8 CD_pulo; //Cooldown do pulo, tempo padrao: 15
    INT8 pontos;
}_Player;

    _Player player;


#endif
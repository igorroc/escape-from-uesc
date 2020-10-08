#ifndef PLAYER_C
#define PLAYER_C

#include <gb/gb.h>

typedef struct Player{
    UINT8 id;
    UINT8 x; // Posicao x (vai de 0 -> 160)
    UINT8 y; //Posicao y (vai de 0 -> 144)
    UINT8 velocidade_x;
    INT8 velocidade_y; //Velocidade de queda
    INT8 direcao; //Indica se esta virado pra esquerda (-1) ou direita (1)
    INT8 passo; //Usado para fazer a animacao de movimento
    INT8 agachando; //True se estiver pressionado para baixo
    INT8 socando; //True se tiver pressionado A
    INT8 piscando; //Contador para a animacao de piscar, tempo padrao: 100
    INT8 pulando; //True quando estiver no ar
    UINT8 pontos; //Quantidade de pontos nas fases
    UINT8 vidas; //Padrao 3
    UINT8 chao; //Indica quando ele esta no chao
    UINT8 UESC[4]; //Pontos para poder terminar
    UINT8 reais;
    UINT32 contador_RU;
}_Player;

    _Player player;


#endif
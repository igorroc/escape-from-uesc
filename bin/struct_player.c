#ifndef PLAYER_C
#define PLAYER_C

#include <gb/gb.h>

typedef struct Player{
    UINT8 id; //Indica o id da sprite
    UINT8 x; //Indica a posição horizontal
    UINT8 y; //Indica a posição vertical
    INT8 velocidade_y; //Velocidade de queda
    INT8 direcao; //Indica se esta virado pra esquerda (-1) ou direita (1)
    INT8 passo; //Usado para fazer a animacao de movimento
    INT8 agachando; //True se estiver pressionado para baixo
    INT8 piscando; //Contador para a animacao de piscar, tempo padrao: 100
    INT8 pulando; //True quando estiver no ar
    UINT8 pontos; //Quantidade de pontos nas fases
    UINT8 vidas; //Vidas do personagem (padrao = 3)
    UINT8 chao; //Indica quando ele esta no chao
    UINT8 UESC[4]; //Pontos para poder terminar
    UINT8 reais; //Dinheiro para comprar vida
    UINT16 contador_RU; //Timer para o RU abrir
    UINT8 escolha; //Escolha da saida (0 - ILHÉUS, 1 - ITABUNA)
}_Player;

    _Player player;


#endif
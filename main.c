#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gb/drawing.h>

#include "assets/player/mario.c"
#include "assets/player/personagem.c"
#include "assets/inimigo/inimigo.c"
#include "assets/background/muro.c"
#include "assets/background/background_tiles.c"

#define LARGURA 160
#define ALTURA 144
#define TRUE 1
#define FALSE 0
#define FPS 50 // Tempo de delay do jogo, quanto menor mais rapido.


UINT8 GRAVIDADE = -2;
UINT8 CHAO = 109;
int rolagem = 0;

#include "bin/struct_player.c"
#include "bin/struct_inimigo.c"
#include "bin/functions.c"

void main(){
    char nivel[] = "plataforma";
    INT8 inimigo_x = 0;

    iniciar_som();

    player.id = 0;
    player.x = 80;
    player.y = 109;
    player.velocidade_y = 10;
    player.pulando = FALSE;
    player.passo = 1;
    player.direcao = 1;
    player.piscando = 0;
    player.agachando = FALSE;
    player.socando = FALSE;
    player.CD_pulo = 0;

    inimigo.id = 32;
    inimigo.passo = 1;
    inimigo.x = 0;
    inimigo.y = 117;
    
    set_sprite_data(player.id, 32, Personagem);
    set_sprite_tile(player.id, 0); // esquerda superior
    set_sprite_tile(player.id+1, 1); // esquerda inferior
    set_sprite_tile(player.id+2, 2); // direita superior
    set_sprite_tile(player.id+3, 3); // direita inferior

    set_sprite_data(inimigo.id, 4, Goomba);
    set_sprite_tile(inimigo.id, 34);

    set_bkg_data(0, 7, backgroundtiles);
    set_bkg_tiles(0, 0, 40, 18, backgroundmap);

    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;

    
    while(1){
        move_sprite(player.id, player.x, player.y); // esquerda superior
        move_sprite(player.id+1, player.x, player.y+8); // esquerda inferior
        move_sprite(player.id+2, player.x+8, player.y); // direita superior
        move_sprite(player.id+3, player.x+8, player.y+8); // direita inferior

        move_sprite(inimigo.id, inimigo.x, inimigo.y);

        if(detectou_colisao()){
            break;
        }

        //inimigo.x++;

        if(inimigo.passo == 1){
            set_sprite_tile(inimigo.id, 34);
            inimigo.passo = 2;
        }else{
            set_sprite_tile(inimigo.id, 35);
            inimigo.passo = 1;
        }
        
        scroll_bkg(rolagem, 0);

        if(player.CD_pulo < 0){
            player.CD_pulo = 0;
        }else{
            player.CD_pulo--;
        }

        if(player.pulando == TRUE){
            pular();
        }
        
        mover_personagem();

        delay(FPS);
    }
    
    printf("\n\n\n= Voce morreu =");

    delay(999999);
    
}
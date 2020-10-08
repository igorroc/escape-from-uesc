#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <string.h>

#include "assets/player/personagem.c"
#include "assets/background/Mapa_dos_Mapas_QUADRADO.c"
#include "assets/background/Background_Tiles_Cima.c"
#include "assets/fases/biblioteca/Itens.c"
#include "assets/testes/Letras.c"


#define LARGURA 160
#define ALTURA 144
#define TRUE 1
#define FALSE 0
#define FPS 50 // Tempo de delay do jogo, quanto menor mais rapido.


UINT8 GRAVIDADE = -2;
UINT8 CHAO = 109;
int rolagem = 0;

#include "bin/struct_player.c"
#include "bin/struct_livro.c"
#include "bin/struct_background.c"
#include "bin/functions.c"
#include "bin/textos.c"

void main(){
    char nivel[] = "menu";
    iniciar_som();
    delay(100);
    

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
    player.pontos = 0;

    set_sprite_data(player.id, 34, Personagem);
    set_sprite_tile(player.id, 32); // SETA



    set_sprite_data(34, 12, Itens);

    livro.id = 10;
    livro.y = 0;
    livro.naTela = FALSE;
    livro.contador = 0;
    livro.caveira = FALSE;

    set_sprite_tile(livro.id, 34);
    set_sprite_tile(livro.id+1, 35);
    set_sprite_tile(livro.id+2, 36);
    set_sprite_tile(livro.id+3, 37);



    set_sprite_data(46, 26, letras);

    background.x = 40;
    background.y = 100;

    set_bkg_data(0, 8, tilesbackgroundCima);
    set_bkg_tiles(0, 0, 31, 31, mapamenu);
    move_bkg(background.x, background.y);
    
    waitpad(J_START);
    
    DISPLAY_ON;
    SHOW_SPRITES;

    intro();

    waitpad(J_START);
    som_confirmar();

    fadeout(FPS);    
    SHOW_BKG;
    intro_saida();
    fadein(FPS);

    while(1){
        move_sprite(player.id, player.x, player.y); // SETA
        
        mover_personagem_cima();

        if(strcmp(nivel, "plat") == 0){
            printf("plataforma");
            scroll_bkg(rolagem, 0);

            if(player.CD_pulo < 0){
                player.CD_pulo = 0;
            }else{
                player.CD_pulo--;
            }

            if(player.pulando == TRUE){
                pular();
            }

            mover_personagem_lado();

        }else if(joypad() == J_A && ((background.x+player.x) >= 15 && (background.x+player.x) <= 38) && ((background.y+player.y) >= 135 && (background.y+player.y) <= 139)){
            som_confirmar();
            fadeout(100);
            biblioteca();
            HIDE_BKG;
            move_sprite(player.id, 250, 250);
            fadein(100);
            delay(300);
            fadeout(100);
            biblioteca_saida();

            set_sprite_prop(player.id, 0);
            set_sprite_tile(player.id, 42);
            set_sprite_tile(player.id+1, 43);
            set_sprite_tile(player.id+2, 44);
            set_sprite_tile(player.id+3, 45);

            player.x = 80;
            player.y = 109;

            
            
            fadein(FPS);

            while(joypad() != J_START){
                if(livro.naTela == FALSE){
                    livro.naTela = TRUE;
                    livro.y = 0;
                    livro.x = player.x;
                }
                mover_mochila_lado();
                mover_sprites(player.id, player.x, player.y);
                
                if(livro.contador >= 5){
                    set_sprite_tile(livro.id, 38);
                    set_sprite_tile(livro.id+1, 39);
                    set_sprite_tile(livro.id+2, 40);
                    set_sprite_tile(livro.id+3, 41);
                    livro.contador = 0;
                    livro.caveira = TRUE;

                }
                mover_sprites(livro.id, livro.x, livro.y);
                livro.y += 15;
                if(livro.y > 200){
                    livro.naTela = FALSE;
                    if(livro.caveira == TRUE){
                        livro.caveira = FALSE;
                        set_sprite_tile(livro.id, 34);
                        set_sprite_tile(livro.id+1, 35);
                        set_sprite_tile(livro.id+2, 36);
                        set_sprite_tile(livro.id+3, 37);
                    }else{
                        livro.contador++;
                    }

                }
                delay(FPS);
                
            }

            fadeout(FPS);
            som_sair();
            set_sprite_tile(player.id, 32); // SETA
            move_sprite(player.id+1, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+2, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+3, 500, 500); // JOGANDO PARA FORA DA TELA

            mover_sprites(livro.id, 500, 500);
            player.x = 80;
            player.y = 109;
            move_sprite(player.id, player.x, player.y); // SETA

            background.x = 40;
            background.y = 100;
            move_bkg(background.x, background.y);
            SHOW_BKG;

            fadein(FPS);
        }
        
        delay(FPS);
        
    }

    printf("\n\n\n= Voce morreu =");


    display_off();
}

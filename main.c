#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <string.h>
#include <rand.h>


#include "assets/player/personagem.c"
#include "assets/player/vida.c"
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
    player.vidas = 3;
    player.UESC[0] = 0;
    player.UESC[1] = 0;
    player.UESC[2] = 0;
    player.UESC[3] = 0;

    set_sprite_data(player.id, 34, Personagem);
    set_sprite_tile(player.id, 32); // SETA


    set_sprite_data(34, 12, Itens);

    livro[0].id = 10;
    livro[0].y = 0;
    livro[0].naTela = FALSE;
    livro[0].contador = 0;
    livro[0].caveira = FALSE;

    set_sprite_tile(livro[0].id, 34);
    set_sprite_tile(livro[0].id+1, 35);
    set_sprite_tile(livro[0].id+2, 36);
    set_sprite_tile(livro[0].id+3, 37);



    set_sprite_data(46, 37, letras);

    set_sprite_data(83, 1, vida);

    set_sprite_tile(7, 83); // CORACAO 1
    set_sprite_tile(8, 83); // CORACAO 2
    set_sprite_tile(9, 83); // CORACAO 3
    


    background.x = 40;
    background.y = 100;

    set_bkg_data(0, 8, tilesbackgroundCima);
    set_bkg_tiles(0, 0, 31, 31, mapamenu);
    move_bkg(background.x, background.y);
    
    //waitpad(J_START);
    
    DISPLAY_ON;
    SHOW_SPRITES;

    //intro();

    waitpad(J_START);
    som_confirmar();

    fadeout(FPS);    
    SHOW_BKG;
    //intro_saida();
    fadein(FPS);

    move_sprite(7, 142, 20); // CORACAO 1
    move_sprite(8, 150, 20); // CORACAO 2
    move_sprite(9, 158, 20); // CORACAO 3
    while(1){
        move_sprite(player.id, player.x, player.y); // SETA
        verifica_uesc();
        mover_personagem_cima();

        
        if(0){
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

        }
        if(joypad() == J_A && verifica_biblioteca()){
            
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

            mover_sprites(player.id, player.x, player.y);

            fadein(100);

            waitpad(J_A);
            
            pontos();
            while(joypad() != J_START && player.vidas > 0){
                
                if(livro[0].naTela == FALSE){
                    livro[0].naTela = TRUE;
                    livro[0].y = 0;
                    livro[0].x = (rand()%100) + 40;
                }
                mover_mochila_lado();
                mover_sprites(player.id, player.x, player.y);
                
                if(livro[0].contador >= 5){
                    set_sprite_tile(livro[0].id, 38);
                    set_sprite_tile(livro[0].id+1, 39);
                    set_sprite_tile(livro[0].id+2, 40);
                    set_sprite_tile(livro[0].id+3, 41);
                    livro[0].contador = 0;
                    livro[0].caveira = TRUE;

                }
                mover_sprites(livro[0].id, livro[0].x, livro[0].y);
                if(player.pontos <= 15){
                    if(player.pontos < 0){
                        livro[0].y += 5;
                    }else{
                        livro[0].y += 5 + player.pontos;
                    }
                }else{
                    livro[0].y += 20;
                }
                if(livro[0].y > 200){
                    livro[0].naTela = FALSE;
                    if(livro[0].caveira == TRUE){
                        livro[0].caveira = FALSE;
                        set_sprite_tile(livro[0].id, 34);
                        set_sprite_tile(livro[0].id+1, 35);
                        set_sprite_tile(livro[0].id+2, 36);
                        set_sprite_tile(livro[0].id+3, 37);
                    }else{
                        livro[0].contador++;
                    }

                }

                if(colisao_16bits(player.x, player.y, livro[0].x, livro[0].y)){
                    livro[0].y = 250;
                    if(livro[0].caveira == TRUE){
                        player.vidas--;
                        player.pontos--;
                        switch (player.vidas){
                            case 3:
                                move_sprite(7, 142, 20);
                                move_sprite(8, 150, 20);
                                move_sprite(9, 158, 20);
                                break;
                            case 2:
                                move_sprite(7, 142, 20);
                                move_sprite(8, 150, 20);
                                move_sprite(9, 500, 20);
                                break;
                            case 1:
                                move_sprite(7, 142, 20);
                                move_sprite(8, 500, 20);
                                move_sprite(9, 500, 20);
                                break;
                            case 0:
                                move_sprite(7, 500, 20);
                                move_sprite(8, 500, 20);
                                move_sprite(9, 500, 20);
                                break;
                        }
                        
                    }else{
                        player.pontos++;
                    }
                    livro[0].naTela = FALSE;
                }

                if(player.pontos >= 3){
                    som_confirmar();
                    player.UESC[3] = TRUE;
                    break;
                }

                delay(50);
                
            }

            fadeout(100);
            som_sair();
            pontos_saida();
            set_sprite_tile(player.id, 32); // SETA
            move_sprite(player.id+1, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+2, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+3, 500, 500); // JOGANDO PARA FORA DA TELA

            mover_sprites(livro[0].id, 500, 500);
            player.x = 80;
            player.y = 109;
            player.pontos = 0;
            move_sprite(player.id, player.x, player.y); // SETA

            background.x = 40;
            background.y = 100;
            move_bkg(background.x, background.y);
            SHOW_BKG;

            fadein(100);
                    
        }
        
        delay(FPS);
                
    }

    printf("\n\n\n= Voce morreu =");


    display_off();
}

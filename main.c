#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gb/drawing.h>
#include <string.h>
#include <rand.h>
#include <time.h>

#include "assets/player/personagem.c"
#include "assets/player/vida.c"
#include "assets/background/Mapa_dos_Mapas_QUADRADO.c"
#include "assets/background/Background_Tiles.c"
#include "assets/fases/jorge/Mapa.c"
#include "assets/fases/jorge/plantas_chave.c"
#include "assets/fases/biblioteca/Background_biblioteca.c"
#include "assets/fases/biblioteca/Itens.c"
#include "assets/fases/ceu/Mapa_CEU.c"
#include "assets/fases/ceu/Tile_Nave.c"
#include "assets/fases/exatas/Tiles_CIC.c"
#include "assets/testes/umreal.c"
#include "assets/testes/Letras.c"


#define LARGURA 160
#define ALTURA 144
#define TRUE 1
#define FALSE 0
#define FPS 50 // Tempo de delay do jogo, quanto menor mais rapido.
#define delay_rapido 100
#define delay_lento 300

UINT8 GRAVIDADE = -2;
UINT8 CHAO = 152;
int rolagem = 0;
UINT8 inimigo1_x, inimigo1_y, inimigo2_x, inimigo2_y;
UINT8 velocidade;
UINT8 nivel; // 0 É O MENU, 1 É O EXATAS, 2 É O JORGE, 3 É O CEU, 4 É A BIBLIOTECA


#include "bin/struct_player.c"
#include "bin/struct_livro.c"
#include "bin/struct_planta.c"
#include "bin/struct_background.c"
#include "bin/struct_moeda.c"
#include "bin/struct_obstaculo.c"
#include "bin/struct_explorer.c"
#include "bin/functions.c"
#include "bin/textos.c"
#include "bin/fases.c"


void main(){

    

/*  []-------- INICIO DO SETUP --------[] */
    iniciar_som(); // INICIAR OS DRIVERS DE AUDIO
    initrand(time(NULL)); //INICIAR A SEMENTE ALEATÓRIA
   
    // INICIANDO TODOS OS VALORES DA STRUCT PLAYER
    player.id = 0;
    player.x = 80;
    player.y = 109;
    player.velocidade_y = 10;
    player.pulando = FALSE;
    player.passo = 1;
    player.direcao = 1;
    player.piscando = 0;
    player.agachando = FALSE;
    player.chao = TRUE;
    player.socando = FALSE;
    player.pontos = 0;
    player.vidas = 3;
    player.UESC[0] = FALSE;
    player.UESC[1] = FALSE;
    player.UESC[2] = FALSE;
    player.UESC[3] = FALSE;
    player.contador_RU = 0;
    player.reais = 0; 

    // ENVIANDO TILES
    set_sprite_data(player.id, 34, Personagem); // PERSONAGEM 16BITS COM ANIMAÇÕES
    set_sprite_data(34, 12, Itens); // LIVRO, CAVEIRA E MOCHILA
    set_sprite_data(46, 37, letras); // LETRAS DE A ATÉ Z, :, 0 ATÉ 9
    set_sprite_data(83, 1, vida); // SPRITE CORAÇÃO
    set_sprite_data(84, 4, plantas_chave); // PLANTAS INIMIGAS E CHAVE
    set_sprite_data(88, 7, umreal); // SPRITES DE 1 REAL COM ANIMAÇÃO
    set_sprite_data(95, 8, Tile_Nave); //NAVE
    set_sprite_data(103, 9, tiles_CIC); //INTERNET EXPLORER, CAFE, PONTO E VIRGULA
    
    // SETANDO TILES
    set_sprite_tile(player.id, 32); // SETA

    // SETANDO BACKGROUND
    background.x = 40;
    background.y = 100;
    
    
    set_bkg_data(0, 18, tilesbackgroundCima); // TILES DO BACKGROUND
    set_bkg_tiles(0, 0, mapamenuWidth, mapamenuHeight, mapamenu); // INICIANDO O MAPA DA UESC
    move_bkg(background.x, background.y);
/*  []-------- FIM DO SETUP --------[] */

    
    DISPLAY_ON;
    SHOW_SPRITES;
    remover_sprites(0, 39);
    intro(); // ANIMAÇÃO DA LOGO DO JOGO
    waitpad(J_START);
    som_confirmar();
    
    fadeout(delay_rapido);
    remover_sprites(20, 33); // REMOVER INTRO
    SHOW_BKG;
    verifica_vidas();
    verifica_moedas();
    move_sprite(player.id, player.x, player.y);
    fadein(delay_rapido);


    while(player.vidas > 0){

        move_sprite(player.id, player.x, player.y); // SETA
        verifica_uesc(); // VERIFICA QUANTAS LETRAS O JOGADOR JÁ POSSUI
        verifica_vidas(); // VERIFICA QUANTAS VIDAS O JOGADOR AINDA POSSUI
        verifica_moedas(); // VERIFICA QUANTAS MOEDAS O JOGADOR POSSUI
        mover_personagem_topo(); // MOVER O PERSONAGEM NA VISÃO DE CIMA
        nivel = 0;
        
        if(joypad() == J_A && verifica_exatas()){
            nivel = 1; 
            jogar_exatas();
        }
        if(joypad() == J_A && verifica_jorge()){
            nivel = 2;
            jogar_jorge();
        }
        if(joypad() == J_A && verifica_adonias()){
            nivel = 3;
            jogar_adonias();
        }
        if(joypad() == J_A && verifica_biblioteca()){
            nivel = 4;
            jogar_biblioteca();
        }
        if(joypad() == J_A && verifica_ru()){
            
            fadeout(delay_rapido);
            move_sprite(player.id, 250, 250); // JOGANDO PARA FORA DA TELA
            HIDE_BKG;

            fadein(delay_rapido);
            escrever("ru", 20, 80, 85);
            delay(delay_lento);

            fadeout(delay_rapido);
            
            remover_sprites(20, 21); // TEXTO SAIDA
            fadein(delay_rapido);
            if(player.contador_RU > 500){ // COOLDOWN PARA PODER COMPRAR VIDA PASSOU
                confirmar_ru(); // TEXTO 
            }else{
                escrever("aguarde", 20, 60, 77);
                escrever("na fila", 27, 60, 85);
            }
            

            while (joypad() != J_A && joypad() != J_B && joypad() != J_START){
                if(player.contador_RU > 500){ // COOLDOWN PARA PODER COMPRAR VIDA PASSOU
                    confirmar_ru();
                    remover_sprites(11, 17); // REMOVE A FILA
                    while(1){
                        animacao_moeda();
                        delay(FPS);
                        if(joypad() == J_A){ // COMPRAR VIDA
                            if(player.reais >= 1){
                                if(player.vidas < 3){
                                    player.vidas++;
                                    player.reais--;
                                    player.contador_RU = 0;
                                }else{
                                    escrever("vida", 20, 72, 76);
                                    escrever("cheia", 24, 68, 84);
                                    delay(100);
                                    waitpad(J_A);
                                }
                            }else{
                                remover_sprites(20, 33);
                                moeda.x = 250;
                                moeda.y = 250;
                                escrever("sem", 20, 76, 81);
                                escrever("moedas", 23, 64, 89);
                                delay(delay_rapido);
                                waitpad(J_A);
                            }
                            break;
                        }else if(joypad() == J_B || joypad() == J_START){ // CANCELAR COMPRA
                            break;
                        }
                    }
                    
                }else{ // AINDA EM COOLDOWN PARA COMPRAR A VIDA
                    ru_timer();
                    remover_sprites(11, 35);
                }
            }
            
            
            
            fadeout(delay_rapido);
            delay(delay_lento);
            remover_sprites(20, 35); // TEXTO SAIDA
            remover_sprites(11, 17); // REMOVE A FILA
            remover_sprites(0, 0); // REMOVE A SETA
            verifica_vidas();
            verifica_moedas();
            SHOW_BKG;

            
            // VOLTA PARA A TORRE
            player.x = 80;
            player.y = 109;
            move_sprite(player.id, player.x, player.y); // SETA
            background.x = 40;
            background.y = 100;
            move_bkg(background.x, background.y);

            fadein(delay_rapido);
        }
        if(joypad() == J_A && verifica_guarita()){
            fadeout(delay_rapido);
            HIDE_BKG;
            move_sprite(player.id, 250, 250);
            fadein(delay_rapido);
            escrever("guarita", 20, 60, 85);
            delay(delay_lento);
            fadeout(delay_rapido);
            remover_sprites(20, 26);
            fadein(delay_rapido);
            if(player.UESC[0] == TRUE && player.UESC[1] == TRUE && player.UESC[2] == TRUE && player.UESC[3] == TRUE){ // COOLDOWN PARA PODER COMPRAR VIDA PASSOU
                escrever("escolha se", 17, 44, 81);
                escrever("u", 26, 124, 81);
                escrever("destino", 27, 60, 89);
                delay(delay_lento);
                escolher_saida();
            }else{
                escrever("colete", 17, 64, 77);
                escrever("todas as", 23, 56, 85);
                escrever("letras", 30, 64, 93);
                waitpad(J_START);
            }
            
            
            fadeout(delay_rapido);
            SHOW_BKG;
            player.x = 80;
            player.y = 109;
            move_sprite(player.id, player.x, player.y); // SETA
            background.x = 40;
            background.y = 100;
            move_bkg(background.x, background.y);
            remover_sprites(17, 35);
            fadein(delay_rapido);
        }
        if(joypad() == J_A && verifica_arvore_cima()){

            fadeout(delay_rapido);
            HIDE_BKG;
            remover_sprites(0, 0);
            fadein(delay_rapido);
            escrever("bosque", 20, 64, 85);
            delay(delay_lento);
            fadeout(delay_rapido);
            remover_sprites(20, 26);
            fadein(delay_rapido);
            escrever("pacote", 11, 64, 81);
            escrever("encontrado", 17, 48, 89);

            escrever("abrir: a", 27, 56, 100);

            while (joypad() != J_START){
                if(joypad() == J_A){
                    if(player.vidas == 1 && player.reais > 0){
                        player.vidas = 3;
                        player.reais--;
                    }else if(player.vidas < 3 && player.reais > 0){
                        player.vidas++;
                        player.reais--;
                    }else{
                        fadeout(delay_rapido);
                        remover_sprites(11, 33);
                        fadein(delay_rapido);
                        escrever("nada", 11, 74, 81);
                        escrever("aconteceu", 15, 54, 89);
                        delay(delay_lento);
                    }
                    
                    break;
                }else if(joypad() == J_B){
                    break;
                }
            }
            fadeout(delay_rapido);
            remover_sprites(11, 33);
            player.x = 80;
            player.y = 109;
            set_sprite_tile(player.id, 32); // SETA
            move_sprite(player.id, player.x, player.y); // SETA

            background.x = 40;
            background.y = 100;
            set_bkg_tiles(0, 0, 31, 31, mapamenu);
            move_bkg(background.x, background.y);
            SHOW_BKG;
            fadein(delay_rapido);
            
        }
        if(joypad() == J_SELECT && verifica_torre()){
            // easter egg
            
            player.UESC[0] = TRUE;
            player.UESC[1] = TRUE;
            player.UESC[2] = TRUE;
            player.UESC[3] = TRUE;
        
        }
        
        player.contador_RU++;
        delay(FPS);
                
    }
    
    fadeout(delay_rapido);
    
    remover_sprites(0, 40);

    HIDE_BKG;

    fadein(delay_rapido);

    game_over();

    HIDE_BKG;
    HIDE_SPRITES;
    DISPLAY_OFF;
}

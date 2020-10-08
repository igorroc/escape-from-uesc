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
#include "assets/background/Background_Tiles_Cima.c"
#include "assets/fases/jorge/Mapa.c"
#include "assets/fases/jorge/plantas_chave.c"
#include "assets/fases/biblioteca/Background_biblioteca.c"
#include "assets/fases/biblioteca/Itens.c"
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



#include "bin/struct_player.c"
#include "bin/struct_livro.c"
#include "bin/struct_planta.c"
#include "bin/struct_background.c"
#include "bin/struct_moeda.c"
#include "bin/functions.c"
#include "bin/textos.c"


void main(){

    int i;

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
    
    // SETANDO TILES
    set_sprite_tile(player.id, 32); // SETA
    set_sprite_tile(7, 83); // CORACAO 1
    set_sprite_tile(8, 83); // CORACAO 2
    set_sprite_tile(9, 83); // CORACAO 3

    
    // SETANDO BACKGROUND
    background.x = 40;
    background.y = 100;

    set_bkg_data(0, 10, tilesbackgroundCima); // TILES DO BACKGROUND
    set_bkg_tiles(0, 0, 31, 31, mapamenu); // INICIANDO O MAPA DA UESC
    move_bkg(background.x, background.y);
/*  []-------- FIM DO SETUP --------[] */

    DISPLAY_ON;
    SHOW_SPRITES;
    
    intro(); // ANIMAÇÃO DA LOGO DO JOGO
    waitpad(J_START);
    som_confirmar();
   
    fadeout(delay_rapido);
    move_sprite(7, 142, 20); // CORACAO 1
    move_sprite(8, 150, 20); // CORACAO 2
    move_sprite(9, 158, 20); // CORACAO 3
    intro_saida();
    SHOW_BKG;
    fadein(delay_rapido);

    //escrever("testando funcao", 50);
    //waitpad(J_A);

    while(player.vidas > 0){

        move_sprite(player.id, player.x, player.y); // SETA
        verifica_uesc(); // VERIFICA QUANTAS LETRAS O JOGADOR JÁ POSSUI
        verifica_vidas(); // VERIFICA QUANTAS VIDAS O JOGADOR AINDA POSSUI
        verifica_moedas(); // VERIFICA QUANTAS MOEDAS O JOGADOR POSSUI
        mover_personagem_cima(); // MOVER O PERSONAGEM NA VISÃO DE CIMA

        if(joypad() == J_A && verifica_ru()){
            
            fadeout(100);
            move_sprite(player.id, 250, 250); // JOGANDO PARA FORA DA TELA
            HIDE_BKG;
            ru(); // TEXTO

            fadein(100);
            
            delay(300);

            fadeout(100);
            
            ru_saida(); // TEXTO SAIDA
            
            if(player.contador_RU > 500){ // COOLDOWN PARA PODER COMPRAR VIDA PASSOU
                confirmar_ru(); // TEXTO 
            }else{
                ru_fechado();
            }
            fadein(100);

            while (joypad() != J_A && joypad() != J_B && joypad() != J_START){
                if(player.contador_RU > 500){ // COOLDOWN PARA PODER COMPRAR VIDA PASSOU
                    while(1){
                        animacao_moeda();
                        delay(50);
                        if(joypad() == J_A){ // COMPRAR VIDA
                            if(player.reais >= 1){
                                player.vidas++;
                                player.reais--;
                                player.contador_RU = 0;
                            }else{
                                ru_fechado_saida();
                                sem_moedas();
                                delay(100);
                                waitpad(J_A);
                            }
                            break;
                        }else if(joypad() == J_B || joypad() == J_START){ // CANCELAR COMPRA
                            break;
                        }
                    }
                    
                }else{ // AINDA EM COOLDOWN PARA COMPRAR A VIDA
                    ru_timer();
                }
            }
            
            
            
            fadeout(100);
            sem_moedas_saida(); // TEXTO SAIDA
            ru_fechado_saida(); // TEXTO SAIDA
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

            fadein(100);
        }
        if(joypad() == J_A && verifica_biblioteca()){
            
            som_confirmar();
            
            fadeout(delay_rapido);
            
            biblioteca(); // TEXTO
            HIDE_BKG;
            move_sprite(player.id, 250, 250); // MOVE PARA FORA DA TELA A SETA
            
            // INICIANDO AS VARIAVEIS DO LIVRO
            livro.id = 10;
            livro.y = 0;
            livro.naTela = FALSE;
            livro.contador = 0;
            livro.caveira = FALSE;

            set_sprite_tile(livro.id, 34);
            set_sprite_tile(livro.id+1, 35);
            set_sprite_tile(livro.id+2, 36);
            set_sprite_tile(livro.id+3, 37);

            fadein(delay_rapido);

            delay(delay_lento);

            fadeout(delay_rapido);
            
            biblioteca_saida(); // SAI O TEXTO
            
            // ARRUMA E INICIA A SPRITE DA MOCHILA
            set_sprite_prop(player.id, 0);
            set_sprite_prop(player.id+1, 0);
            set_sprite_prop(player.id+2, 0);
            set_sprite_prop(player.id+3, 0);
            set_sprite_tile(player.id, 42);
            set_sprite_tile(player.id+1, 43);
            set_sprite_tile(player.id+2, 44);
            set_sprite_tile(player.id+3, 45);
            
            // INICIA O MAPA DA BIBLIOTECA
            set_bkg_tiles(0, 0, 20, 18, mapa_biblioteca);
            move_bkg(0, 0);
            SHOW_BKG;

            player.x = 80;
            player.y = 109;
            player.pontos = 0;

            mover_sprites(player.id, player.x, player.y);

            fadein(delay_rapido);
            
            
            while(joypad() != J_START && player.vidas > 0){
                
                pontos(); // MOSTRADOR DE PONTOS ATUAIS
                
                

                if(livro.naTela == FALSE){ // SE NÃO EXISTIR LIVRO NA TELA, CRIA UM
                    livro.naTela = TRUE;
                    livro.y = 0;
                    livro.x = sorteio(20, 130); // SORTEIA A POSICAO X DO LIVRO
                }
                mover_mochila_lado();
                mover_sprites(player.id, player.x, player.y); // MOVER MOCHILA
                if(livro.contador >= 5){ // A CADA 5 LIVROS, UMA CAVEIRA
                    set_sprite_tile(livro.id, 38);
                    set_sprite_tile(livro.id+1, 39);
                    set_sprite_tile(livro.id+2, 40);
                    set_sprite_tile(livro.id+3, 41);
                    livro.contador = 0;
                    livro.caveira = TRUE;
                }
                mover_sprites(livro.id, livro.x, livro.y); // CAIR LIVRO
                if(player.pontos <= 0){
                    livro.y += 5;
                }else{
                    livro.y += 5 + 2*player.pontos;
                }
                

                if(livro.y > 200){ // QUANDO O LIVRO ESTÁ FORA DA TELA
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

                if(colisao_16bits(player.x, player.y, livro.x, livro.y)){ // COLISAO COM O LIVRO/CAVEIRA
                    livro.y = 250;
                    livro.contador++;
                    if(livro.caveira == TRUE){
                        player.vidas--;
                        player.pontos--;
                        verifica_vidas();
                    }else{
                        player.pontos++;
                    }
                    livro.naTela = FALSE;
                }

                if(player.pontos == 10){
                    som_confirmar();
                    player.UESC[3] = TRUE; // ADICIONA A LETRA 'C'
                    break;
                }
                
                
                delay(FPS);
                
            }

            fadeout(100);
            som_sair();
            pontos_saida();
            set_sprite_tile(player.id, 32); // SETA
            move_sprite(player.id+1, 250, 250); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+2, 250, 250); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+3, 250, 250); // JOGANDO PARA FORA DA TELA
            mover_sprites(livro.id, 250, 250); // JOGANDO PARA FORA DA TELA

            // VOLTA PARA A TORRE
            player.x = 80;
            player.y = 109;
            player.pontos = 0;
            move_sprite(player.id, player.x, player.y); // SETA
            background.x = 40;
            background.y = 100;
            move_bkg(background.x, background.y);
            set_bkg_tiles(0, 0, 31, 31, mapamenu);

            fadein(100);
                    
        }
        if(joypad() == J_A && verifica_jorge()){
            fadeout(100);

            jorge();
            mover_sprites(player.id, 250, 250);
            HIDE_BKG;
            fadein(100);
            delay(300);
            fadeout(100);
            jorge_saida();
            set_bkg_tiles(0, 0, 20, 18, mapa_jorge);
            move_bkg(0, 0);

            set_sprite_prop(player.id, 0);
            set_sprite_prop(player.id+1, 0);
            set_sprite_prop(player.id+2, 0);
            set_sprite_prop(player.id+3, 0);
            set_sprite_tile(player.id, 0);
            set_sprite_tile(player.id+1, 1);
            set_sprite_tile(player.id+2, 2);
            set_sprite_tile(player.id+3, 3);
            player.pulando = TRUE;
            player.velocidade_y = 0;
            player.x = 80;
            player.y = 120;
            mover_sprites(player.id, player.x, player.y);

            setup_plantas();

            moeda.x = 250;
            moeda.y = 250;
            moeda.giro = 0;
            moeda.id = 24;
            moeda.contador = 100;
            moeda.cont_letra = 0;
            
            SHOW_BKG;
            
            fadein(100);

            while (joypad() != J_START && player.vidas > 0){
                verifica_vidas();
                verifica_borda();
                verifica_moedas();
                mover_personagem_lado();
                mover_sprites(player.id, player.x, player.y);

                if(player.pulando == TRUE){
                    if(player.velocidade_y < 0 && colisao_plataforma(0, 160, 108)){
                        player.pulando = FALSE;
                        player.velocidade_y = 0;
                        player.y = 92;
                        mover_sprites(player.id, player.x, player.y);
                    }else if(player.velocidade_y < 0 && colisao_plataforma(0, 160, 60)){
                        player.pulando = FALSE;
                        player.velocidade_y = 0;
                        player.y = 44;
                        mover_sprites(player.id, player.x, player.y);
                    }else{
                        pular();
                    }
                }

                for(i = 0; i < 6; i++){
                    move_sprite(planta[i].id, planta[i].x, planta[i].y);
                    if(planta[i].direcao == 1){ //VIRADO PRA DIREITA
                        set_sprite_prop(planta[i].id, S_FLIPX);
                        if(planta[i].x < 160){
                            planta[i].x += planta[i].velocidade_x;
                        }else{
                            planta[i].x = 0;
                            planta[i].velocidade_x = sorteio(1, 4);
                        }
                    }else{ //VIRADO PRA ESQUERDA
                        set_sprite_prop(planta[i].id, 0);
                        if(planta[i].x > 0){
                            planta[i].x -= planta[i].velocidade_x;
                        }else{
                            planta[i].x = 160;
                            planta[i].velocidade_x = sorteio(1, 4);
                        }
                    }

                    if(planta[i].passo > 6){
                        planta[i].passo = 0;
                    }else if(planta[i].passo > 4){
                        set_sprite_tile(planta[i].id, 86);
                        planta[i].passo++;
                    }else if(planta[i].passo > 2){
                        set_sprite_tile(planta[i].id, 85);
                        planta[i].passo++;
                    }else{
                        set_sprite_tile(planta[i].id, 84);
                        planta[i].passo++;
                    }
                    
                    if(colisao_8bits(planta[i].x, planta[i].y, player.x, player.y)){
                        player.vidas--;
                        planta[i].x = 170;
                    }
                }
                if(moeda.cont_letra > 5){
                    set_sprite_tile(moeda.id, 66);
                    move_sprite(moeda.id, moeda.x, moeda.y);
                    
                }else{
                    animacao_moeda();
                }
                if(moeda.contador > 75){
                    moeda.contador = 0;
                    moeda.cont_letra++;
                    moeda.plataforma = sorteio(0, 2);
                    switch (moeda.plataforma){
                        case 0:
                            moeda.y = 48;
                            moeda.x = sorteio(16, 144);
                            break;
                        case 1:
                            moeda.y = 96;
                            moeda.x = sorteio(16, 144);
                            break;
                        case 2:
                            moeda.y = 140;
                            moeda.x = sorteio(16, 144);
                            break;
                    }
                }else{
                    moeda.contador++;
                }
                if(colisao_8bits(moeda.x, moeda.y, player.x, player.y)){
                    if(moeda.cont_letra > 5){
                        player.UESC[0] = TRUE;
                        break;
                    }
                    moeda.naTela = FALSE;
                    moeda.x = 250;
                    moeda.y = 250;
                    if(player.reais < 9){
                        player.reais++;
                    }
                }
                
                verifica_vidas();
                delay(FPS);
            }
            fadeout(100);

            set_sprite_tile(player.id, 32); // SETA
            move_sprite(player.id+1, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+2, 500, 500); // JOGANDO PARA FORA DA TELA
            move_sprite(player.id+3, 500, 500); // JOGANDO PARA FORA DA TELA

            remover_plantas();
            move_sprite(moeda.id, 250, 250);

            player.x = 80;
            player.y = 109;
            player.pontos = 0;
            move_sprite(player.id, player.x, player.y); // SETA

            background.x = 40;
            background.y = 100;
            set_bkg_tiles(0, 0, 31, 31, mapamenu);
            move_bkg(background.x, background.y);
            
            fadein(100);
        }
        if(joypad() == J_A && verifica_exatas()){
            HIDE_BKG;
            while (joypad() != J_START){
                
            }
            SHOW_BKG;
            
        }
        if(joypad() == J_A && verifica_adonias()){
            HIDE_BKG;
            while (joypad() != J_START){
                
            }
            SHOW_BKG;
            
        }
        if(joypad() == J_A && verifica_guarita()){
            HIDE_BKG;
            while (joypad() != J_START){
                
            }
            SHOW_BKG;
            
        }
        
        player.contador_RU++;
        delay(FPS);
                
    }
    
    fadeout(200);
    
    move_sprite(player.id, 250, 250);
    move_sprite(4, 250, 250);
    move_sprite(5, 250, 250);
    move_sprite(66, 250, 250);
    move_sprite(67, 250, 250);
    move_sprite(68, 250, 250);
    move_sprite(69, 250, 250);

    verifica_uesc_saida();

    HIDE_BKG;

    fadein(200);

    game_over();
    
    
    
    



    display_off();
}

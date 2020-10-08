#ifndef FASES_C
#define FASES_C

#include <gb/gb.h>

#define LARGURA 160
#define ALTURA 144
#define TRUE 1
#define FALSE 0
#define FPS 50 // Tempo de delay do jogo, quanto menor mais rapido.
#define delay_rapido 100
#define delay_lento 300

void onibus(){
    CHAO = 124;
    while(joypad() != J_START){
        mover_sprites(player.id, player.x, player.y);
        mover_personagem_lado();
        if(player.pulando == TRUE){
            pular();
        }
        delay(FPS);
    }
    HIDE_BKG;
}

void jogar_exatas(){
    fadeout(delay_rapido);
    HIDE_BKG;
    move_sprite(player.id, 250, 250);
    fadein(delay_rapido);
    escrever("exatas", 20, 64, 85);
    delay(delay_lento);
    fadeout(delay_rapido);
    remover_sprites(20, 25);
    SHOW_BKG;
    set_bkg_tiles(0, 0, mapa_bibliotecaWidth, mapa_bibliotecaHeight, mapa_biblioteca);
    move_bkg(0, 0);
    set_sprite_tile(player.id, 0);
    set_sprite_tile(player.id+1, 1);
    set_sprite_tile(player.id+2, 2);
    set_sprite_tile(player.id+3, 3);
    reset_sprites(player.id, 4);
    player.x = 80;
    player.y = 109;
    player.passo = 1;
    mover_sprites(player.id, player.x, player.y);

    CHAO = 124;

    obstaculo.id = 15;
    obstaculo.variacao = 0;
    obstaculo.x = 200;
    obstaculo.y = 116;
    obstaculo.velocidade = 2;
    obstaculo.quantidade = 0;
    reset_sprites(11, 19);
    set_sprite_tile(obstaculo.id, 111); // OBSTACULO
    move_sprite(obstaculo.id, obstaculo.x, obstaculo.y);

    explorer.id = 20;
    explorer.x = 0;
    explorer.y = 100;
    explorer.passo = 0;

    set_sprite_tile(explorer.id, 107);
    set_sprite_tile(explorer.id+1, 108);
    set_sprite_tile(explorer.id+2, 109);
    set_sprite_tile(explorer.id+3, 110);

    fadein(delay_rapido);
    while (joypad() != J_START && player.vidas > 0){
        if((obstaculo.quantidade)%26 == 25 || obstaculo.variacao == 2){
            obstaculo.variacao = 2;
            obstaculo.y = 108;
            set_sprite_tile(obstaculo.id, 103); // CAFE
            set_sprite_tile(obstaculo.id+1, 104); // CAFE
            set_sprite_tile(obstaculo.id+2, 105); // CAFE
            set_sprite_tile(obstaculo.id+3, 106); // CAFE
            mover_sprites(obstaculo.id, obstaculo.x, obstaculo.y);
        }else if((obstaculo.quantidade)%5 == 4){
            if(obstaculo.variacao != 2){
                obstaculo.y = 116;
                obstaculo.variacao = 1;
                remover_sprites(obstaculo.id+1, obstaculo.id+3);
                moeda.id = obstaculo.id;
                moeda.x = obstaculo.x;
                moeda.y = obstaculo.y;
                animacao_moeda();
            }
        }else{
            if(obstaculo.variacao != 2){
                obstaculo.variacao = 0;
                obstaculo.y = 116;
                remover_sprites(obstaculo.id+1, obstaculo.id+3);
                set_sprite_tile(obstaculo.id, 111); // OBSTACULO
                move_sprite(obstaculo.id, obstaculo.x, obstaculo.y);
            }
        }

        mover_sprites(player.id, player.x, player.y);
        mover_sprites(explorer.id, explorer.x, explorer.y);
        mover_personagem_lado();
        verifica_vidas();
        verifica_moedas();
        verifica_borda();

        

        if(explorer.passo%3 == 0){
            if(player.x > explorer.x){
                explorer.x++;
            }else if(player.x < explorer.x){
                explorer.x--;
            }
            explorer.passo++;
        }else{
            explorer.passo++;
        }

        switch (explorer.passo){
            case 22:
                explorer.passo = 0;
            case 0:
                explorer.y -= 11;
                break;
            case 1:
            case 21:
                explorer.y -= 9;
                break;
            case 2:
            case 20:
                explorer.y -= 7;
                break;
            case 3:
            case 19:
                explorer.y -= 5;
                break;
            case 4:
            case 18:
                explorer.y -= 3;
                break;
            case 5:
            case 17:
                explorer.y -= 1;
                break;
            case 6:
            case 16:
                explorer.y += 1;
                break;
            case 7:
            case 15:
                explorer.y += 3;
                break;
            case 8:
            case 14:
                explorer.y += 5;
                break;
            case 9:
            case 13:
                explorer.y += 7;
                break;
            case 10:
            case 12:
                explorer.y += 9;
                break;
            case 11:
                explorer.y += 11;
                break;
        }

        if(colisao_16bits(player.x, player.y, explorer.x, explorer.y)){
            player.vidas--;
            explorer.x = 0;
        }

        obstaculo.x -= 5;
        if(player.pulando == TRUE){
            pular();
        }
        if(obstaculo.x <= 8){
            obstaculo.quantidade++;
            obstaculo.velocidade++;
            obstaculo.x = 200;
            if(obstaculo.variacao == 2){
                obstaculo.variacao = 0;
            }
        }
        
        if(obstaculo.variacao == 2){
            if(colisao_16bits(obstaculo.x, obstaculo.y, player.x, player.y)){
                player.UESC[1] = TRUE;
                som_confirmar();
                obstaculo.x = 200;
                break;
            }
        }else{
            if(colisao_8bits(obstaculo.x, obstaculo.y, player.x, player.y)){
                if(obstaculo.variacao == 0){
                    player.vidas--;
                    obstaculo.x = 200;
                    if(obstaculo.velocidade >= 3){
                        obstaculo.velocidade -= 3;
                    }
                }else if(obstaculo.variacao == 1){
                    if(player.reais < 9){
                        player.reais++;
                    }
                    obstaculo.x = 200;
                    obstaculo.quantidade++;
                    obstaculo.variacao = 0;
                } 
            }
        }
        

        scroll_bkg(1, 0);
        
        delay(FPS);
    }
    
    fadeout(delay_rapido);

    CHAO = 152;
    player.x = 80;
    player.y = 109;
    remover_sprites(0, 3);
    remover_sprites(11, 23);
    set_sprite_tile(player.id, 32); // SETA
    move_sprite(player.id, player.x, player.y); // SETA

    background.x = 40;
    background.y = 100;
    set_bkg_tiles(0, 0, 31, 31, mapamenu);
    move_bkg(background.x, background.y);

    fadein(delay_rapido);
}

void jogar_biblioteca(){
    
    som_confirmar();
    
    fadeout(delay_rapido);
    HIDE_BKG;
    move_sprite(player.id, 250, 250); // MOVE PARA FORA DA TELA A SETA
    fadein(delay_rapido);
    escrever("biblioteca", 20, 44, 85);
    delay(delay_lento);
    fadeout(delay_rapido);

    remover_sprites(20, 29); // SAIDA DO TEXTO
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
    
    
    
    // ARRUMA E INICIA A SPRITE DA MOCHILA
    reset_sprites(player.id, 4);
    set_sprite_tile(player.id, 42);
    set_sprite_tile(player.id+1, 43);
    set_sprite_tile(player.id+2, 44);
    set_sprite_tile(player.id+3, 45);
    
    // INICIA O MAPA DA BIBLIOTECA
    set_bkg_tiles(0, 0, mapa_bibliotecaWidth, mapa_bibliotecaHeight, mapa_biblioteca);
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
                som_sair();
            }else{
                som_confirmar();
                player.pontos++;
            }
            livro.naTela = FALSE;
        }

        if(player.pontos == 10){
            som_confirmar();
            player.UESC[3] = TRUE; // ADICIONA A LETRA 'C'
            player.reais++;
            break;
        }
        
        
        delay(FPS);
        
    }

    fadeout(100);
    som_sair();
    remover_sprites(20, 27); // REMOVER TEXTO PONTOS
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

void jogar_jorge(){
    int i;

    fadeout(100);
    mover_sprites(player.id, 250, 250); // TIRA A SETA
    HIDE_BKG;
    fadein(delay_rapido);
    escrever("pavilhao", 17, 56, 77);
    escrever("jorge", 25, 68, 85);
    escrever("amado", 30, 68, 93);
    delay(delay_lento);
    fadeout(delay_rapido);
    remover_sprites(17, 34); // REMOVE AS LETRAS
    
    set_bkg_tiles(0, 0, 20, 18, mapa_jorge);
    move_bkg(0, 0);

    reset_sprites(player.id, 4); // RESETA AS PROPRIEDADES DAS SPRITES DO PLAYER
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
    moeda.contador = 0;
    moeda.cont_letra = 0;
    
    SHOW_BKG;
    fadein(delay_rapido);

    while (joypad() != J_START && player.vidas > 0){
        verifica_vidas();
        verifica_borda();
        verifica_moedas();
        mover_personagem_lado();
        mover_sprites(player.id, player.x, player.y);

        if(player.pulando == TRUE){
            if(player.velocidade_y < 0 && colisao_plataforma(0, 160, 108)){ // COLISAO DA PLATAFORMA MAIS PROXIMA DO CHAO
                player.pulando = FALSE;
                player.velocidade_y = 0;
                player.y = 92;
                mover_sprites(player.id, player.x, player.y);
            }else if(player.velocidade_y < 0 && colisao_plataforma(0, 160, 60)){ // COLISAO DA PLATAFORMA MAIS PROXIMA DO TETO
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

            if(planta[i].passo > 6){ // ANIMACAO DAS PLANTAS
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
                som_sair();
                planta[i].x = 170;
            }
        }

        if(moeda.cont_letra%8 == 7){ // QUANTIDADE DE MOEDAS PARA APARECER A LETRA
            set_sprite_tile(moeda.id, 66);
            move_sprite(moeda.id, moeda.x, moeda.y);
        }else{
            animacao_moeda();
        }

        if(moeda.contador > 80){ // TIMER PARA APARECER A MOEDA
            moeda.contador = 0;
            moeda.cont_letra++;
            moeda.plataforma = sorteio(0, 2); // SORTEIA QUAL DAS PLATAFORMAS A MOEDA APARECERA
            switch (moeda.plataforma){
                case 0:
                    moeda.y = 48;
                    moeda.x = sorteio(16, 144); // SORTEIA A POSICAO DA MOEDA
                    break;
                case 1:
                    moeda.y = 96;
                    moeda.x = sorteio(16, 144); // SORTEIA A POSICAO DA MOEDA
                    break;
                case 2:
                    moeda.y = 140;
                    moeda.x = sorteio(16, 144); // SORTEIA A POSICAO DA MOEDA
                    break;
            }
        }else{
            moeda.contador++;
        }

        if(colisao_8bits(moeda.x, moeda.y, player.x, player.y)){ // COLISAO COM A MOEDA
            som_confirmar();
            if(moeda.cont_letra%8 == 7){ // QUANTIDADE DE MOEDAS PARA APARECER A LETRA
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
    fadeout(delay_rapido);

    remover_sprites(player.id, player.id+3); // REMOVE O PLAYER
    remover_sprites(planta[0].id, planta[5].id); // REMOVE AS PLANTAS
    move_sprite(moeda.id, 250, 250); // REMOVE A MOEDA

    player.x = 80;
    player.y = 109;
    player.pontos = 0;
    set_sprite_tile(player.id, 32); // SETA
    move_sprite(player.id, player.x, player.y); // SETA

    background.x = 40;
    background.y = 100;
    set_bkg_tiles(0, 0, 31, 31, mapamenu);
    move_bkg(background.x, background.y);
    
    fadein(delay_rapido);
}

void jogar_adonias(){
    fadeout(delay_rapido);
    mover_sprites(player.id, 250, 250);
    HIDE_BKG;
    fadein(delay_rapido);
    escrever("ceu", 20, 76, 85);
    delay(delay_lento);
    fadeout(delay_rapido);
    remover_sprites(17, 29);
    set_bkg_tiles(0, 0, 32, 18, Mapa_CEU);
    move_bkg(0, 0);
    
    reset_sprites(player.id, 4);
    set_sprite_tile(player.id, 95);
    set_sprite_tile(player.id+1, 96);
    set_sprite_tile(player.id+2, 97);
    set_sprite_tile(player.id+3, 98);
    
    player.x = 30;
    player.y = 80;
    player.pontos = 0;
    velocidade = 0;

    mover_sprites(player.id, player.x, player.y);

    inimigo1_x = 160;
    inimigo1_y = sorteio(35, 100);
    set_sprite_tile(11, 99);
    set_sprite_tile(12, 100);
    set_sprite_tile(13, 101);
    set_sprite_tile(14, 102);
    reset_sprites(11, 4);

    inimigo2_x = 160;
    inimigo2_y = sorteio(35, 100);
    set_sprite_tile(15, 99);
    set_sprite_tile(16, 100);
    set_sprite_tile(17, 101);
    set_sprite_tile(18, 102);
    reset_sprites(15, 4);
    mover_sprites(15, inimigo1_x, inimigo1_y);
    
    SHOW_BKG;
    fadein(100);
    
    while (joypad() != J_START && player.vidas > 0 && player.pontos < 10){
        verifica_vidas();
        pontos();
        mover_sprites(player.id, player.x, player.y);
        mover_sprites(11, inimigo1_x, inimigo1_y);
        mover_sprites(15, inimigo2_x, inimigo2_y);
        mover_personagem_cima_baixo();
        mover_inimigo_cima_baixo();
        
        if(colisao_12bits(player.x, player.y, inimigo1_x, inimigo1_y)){
            player.vidas--;
            som_sair();
            if(player.pontos > 0){
                player.pontos--;
            }
            inimigo1_x = 160;
            inimigo1_y = sorteio(35, 100);
        }
        if(colisao_12bits(player.x, player.y, inimigo2_x, inimigo2_y)){
            player.vidas--;
            som_sair();
            if(player.pontos > 0){
                player.pontos--;
            }
            inimigo2_x = 160;
            inimigo2_y = sorteio(35, 100);
        }

        
        if(velocidade < 20){
            scroll_bkg(1, 0);
            inimigo1_x -= 3;
            inimigo2_x -= 3;
            velocidade++;
        }else if(velocidade < 40){
            scroll_bkg(2, 0);
            inimigo1_x -= 4;
            inimigo2_x -= 4;
            velocidade++;
        }else if(velocidade < 60){
            scroll_bkg(3, 0);
            inimigo1_x -= 5;
            inimigo2_x -= 5;
            velocidade++;
        }else if(velocidade < 80){
            scroll_bkg(4, 0);
            inimigo1_x -= 6;
            inimigo2_x -= 6;
            velocidade++;
        }else{
            scroll_bkg(5, 0);
            inimigo1_x -= 7;
            inimigo2_x -= 7;
        }
        
        delay(FPS);
    }
    
    fadeout(100);

    if(player.pontos == 10){
        player.UESC[2] = TRUE;
        player.reais++;
    }

    remover_sprites(0, 3);
    remover_sprites(11, 32);
    player.x = 80;
    player.y = 109;
    set_sprite_tile(player.id, 32); // SETA
    move_sprite(player.id, player.x, player.y); // SETA

    background.x = 40;
    background.y = 100;
    set_bkg_tiles(0, 0, 31, 31, mapamenu);
    move_bkg(background.x, background.y);
    
    fadein(100);
    
}

void escolher_saida(){
    fadeout(delay_rapido);
    remover_sprites(0, 39);
    delay(delay_lento);

    player.x = 46;
    player.y = 85;
    set_sprite_tile(5, 33); // SETA
    
    fadein(delay_rapido);
    
    escrever("ilheus", 10, 58, 69);
    escrever("itabuna", 16, 58, 85);
    escrever("hellzinho", 23, 60, 101);

    move_sprite(5, player.x, player.y);
    
    while (joypad() != J_START){
        move_sprite(5, player.x, player.y); // ESCOLHA
        switch (joypad()){
            case J_UP:
                if(player.y == 69){
                    player.y = 101;
                }else if(player.y == 85){
                    player.y = 69;
                }else if(player.y == 101){
                    player.y = 85;
                }
                break;
            case J_DOWN:
                if(player.y == 69){
                    player.y = 85;
                }else if(player.y == 85){
                    player.y = 101;
                }else if(player.y == 101){
                    player.y = 69;
                }
                break;
            case J_A:
                fadeout(delay_rapido);
                remover_sprites(0, 39);
                fadein(delay_rapido);
                if(player.y == 69){ //INDO PRA ILHEUS
                    escrever("parabens", 20, 58, 81);
                    escrever("voce ganhou", 28, 46, 89);
                    escrever("u", 37, 126, 89);
                    waitpad(J_START);
                    /*
                    reset_sprites(player.id, 4);
                    set_sprite_tile(player.id, 42);
                    set_sprite_tile(player.id+1, 43);
                    set_sprite_tile(player.id+2, 44);
                    set_sprite_tile(player.id+3, 45);
                    player.x = 30;
                    player.pulando = TRUE;
                    
                    // INICIA O MAPA DA BIBLIOTECA
                    set_bkg_tiles(0, 0, mapa_bibliotecaWidth, mapa_bibliotecaHeight, mapa_biblioteca);
                    move_bkg(0, 0);
                    mover_sprites(player.id, player.x, player.y);
                    SHOW_BKG;
                    onibus();
                    */
                }else if(player.y == 85){ //INDO PRA ITABUNA
                    escrever("parabens", 20, 58, 81);
                    escrever("voce ganhou", 28, 46, 89);
                    escrever("u", 37, 126, 89);
                    waitpad(J_START);
                    /*
                    onibus();
                    */
                }else if(player.y == 101){ //INDO PRO INFERNINHO
                    escrever("aperte: a", 20, 52, 81);
                    escrever("para beber", 28, 48, 89);
                    while (joypad() != J_START){
                        if(joypad() == J_A){
                            remover_sprites(20, 39);
                            game_over();
                        }
                    }
                    remover_sprites(20, 39);
                    escrever("escolha", 20, 60, 81);
                    escrever("esperta", 27, 60, 89);
                }
                delay(delay_lento);
                remover_sprites(0, 33);
                player.x = 46;
                player.y = 85;
                escrever("ilheus", 10, 58, 69);
                escrever("itabuna", 16, 58, 85);
                escrever("hellzinho", 23, 60, 101);
                break;
            default:
                break;
        }

        delay(FPS);
    }
    remover_sprites(0, 39);
}

#endif
#ifndef FUNCTIONS_C
#define FUNCTIONS_C

#include <gb/gb.h>
#include "textos.c"

#include "struct_player.c"


// --------------- FUNCOES DE TELA ---------------

void fadeout(UINT8 tempo);
void fadein(UINT8 tempo);

// --------------- FUNCOES DE SOM ---------------

void iniciar_som();
void som_pulo();
void som_soco();
void som_confirmar();
void som_sair();

// ------------ FUNCOES DE MOVIMENTO ------------

int colisao_chao(UINT8);
UINT8 colisao_plataforma(UINT8, UINT8, UINT8);
int colisao_16bits(UINT8, UINT8, UINT8, UINT8);//RETORNA 1 SE COLIDIU, 0 SE NAO
int colisao_8bits(UINT8, UINT8, UINT8, UINT8);
void pular();
void mover_personagem_topo();
void mover_personagem_lado();
void mover_personagem_cima_baixo();
void mover_inimigo_cima_baixo();
void mover_mochila_lado();
void mover_sprites(UINT8 id, UINT8 x, UINT8 y);
void setup_plantas();
void remover_plantas();
void animacao_moeda();
void reset_sprites(UINT8 id, UINT8 qtd);

// ------------ FUNCOES DE VERIFICACAO ------------

UINT8 verifica_guarita();
UINT8 verifica_biblioteca();
UINT8 verifica_jorge();
UINT8 verifica_exatas();
UINT8 verifica_adonias();
UINT8 verifica_arvore_cima();
UINT8 verifica_arvore_baixo();
UINT8 verifica_ru();
void verifica_borda();
void verifica_vidas();
UINT8 sorteio(UINT8, UINT8);



// -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-


// --------------- FUNCOES DE TELA ---------------

void fadeout(UINT8 tempo){
    int i;
    for(i = 0; i < 4; i++){
        switch (i){
            case 0:
                BGP_REG = 0xE4; // TELA NORMAL
                break;
            case 1:
                BGP_REG = 0xF9; // TELA MAIS ESCURA
                break;
            case 2:
                BGP_REG = 0xFE; // TELA MAIS MAIS ESCURA
                break;
            case 3:
                BGP_REG = 0xFF; // TELA PRETA
                break;
        }
        delay(tempo);
    }
}

void fadein(UINT8 tempo){
    int i;
    for(i = 0; i < 3; i++){
        switch (i){
            case 0:
                BGP_REG = 0xFE; // TELA PRETA
                break;
            case 1:
                BGP_REG = 0xF9; // TELA MAIS CLARA
                break;
            case 2:
                BGP_REG = 0xE4; // TELA NORMAL
                break;
        }
        delay(tempo);
    }
}

// --------------- FUNCOES DE SOM ---------------

void iniciar_som(){

    // these registers must be in this specific order!
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels

}

void som_pulo(){
    // see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
    // chanel 1 register 0, Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    // 0001 0110 is 0x16, sweet time 1, sweep direction increase, shift ammount per step 110 (6 decimal)
    NR10_REG = 0x16;

    // chanel 1 register 1: Wave pattern duty and sound length
    // Channels 1 2 and 4
    // 7-6	Wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular  wave is "on" vs "of" so 50% (2) is both equal.
    // 5-0 sound length (higher the number shorter the sound)
    // 01000000 is 0x40, duty cycle 1 (25%), wave length 0 (long)
    NR11_REG = 0x40;

    // chanel 1 register 2: Volume Envelope (Makes the volume get louder or quieter each "tick")
    // On Channels 1 2 and 4
    // 7-4	(Initial) Channel Volume
    // 3	Volume sweep direction (0: down; 1: up)
    // 2-0	Length of each step in sweep (if 0, sweeping is off)
    // NOTE: each step is n/64 seconds long, where n is 1-7
    // 0111 0011 is 0x73, volume 7, sweep down, step length 3
    NR12_REG = 0x73;

    // chanel 1 register 3: Frequency LSbs (Least Significant bits) and noise options
    // for Channels 1 2 and 3
    // 7-0	8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)
    NR13_REG = 0x00;

    // chanel 1 register 4: Playback and frequency MSbs
    // Channels 1 2 3 and 4
    // 7	Initialize (trigger channel start, AKA channel INIT) (Write only)
    // 6	Consecutive select/length counter enable (Read/Write). When "0", regardless of the length of data on the NR11 register, sound can be produced consecutively.  When "1", sound is generated during the time period set by the length data contained in register NR11.  After the sound is ouput, the Sound 1 ON flag, at bit 0 of register NR52 is reset.
    // 5-3	Unused
    // 2-0	3 Most Significant bits of frequency
    // 1100 0011 is 0xC3, initialize, no consecutive, frequency = MSB + LSB = 011 0000 0000 = 0x300
    NR14_REG = 0xC3;
}

void som_soco(){
    
    NR10_REG = 0x2F;

    NR11_REG = 0x48;

    NR12_REG = 0x73;

    NR13_REG = 0x00;

    NR14_REG = 0xC3;
}

void som_confirmar(){
    
    NR10_REG = 0x2F;

    NR11_REG = 0x01;

    NR12_REG = 0xF3;

    NR13_REG = 0x00;

    NR14_REG = 0x87;
}

void som_sair(){
    
    NR10_REG = 0x1B;

    NR11_REG = 0x01;

    NR12_REG = 0xF3;

    NR13_REG = 0x00;

    NR14_REG = 0x87;
}

// ------------ FUNCOES DE MOVIMENTO ------------

int colisao_chao(UINT8 y){
    if(y+16 >= CHAO){
        return 1;
    }
    return 0;
}

UINT8 colisao_plataforma(UINT8 x_min, UINT8 x_max, UINT8 y){
    if(player.x > x_min && player.x < x_max && ((player.y+16) > y && (player.y+16) < y+16)){
        return TRUE;
    }
    return FALSE;
}

int colisao_16bits(UINT8 x1, UINT8 y1, UINT8 x2, UINT8 y2){
    if(x1 > x2 - 16 && x1 < x2 + 16){
        if(y1 > y2 - 16 && y1 < y2 + 16){
            return 1;
        }
    }
    return 0;
}

int colisao_8bits(UINT8 x1, UINT8 y1, UINT8 x2, UINT8 y2){ //X1 E Y1 É DA PLANTA, X2 E Y2 É DO PLAYER
    if(x1 > x2 - 8 && x1 < x2 + 16){
        if(y1 > y2 - 8 && y1 < y2 + 16){
            return 1;
        }
    }
    return 0;
}

int colisao_12bits(UINT8 x1, UINT8 y1, UINT8 x2, UINT8 y2){
    if(x1 > x2 - 12 && x1 < x2 + 12){
        if(y1 > y2 - 12 && y1 < y2 + 12){
            return 1;
        }
    }
    return 0;
}

void pular(){

    if(player.pulando == FALSE){
        player.pulando = TRUE;
    }


    if(player.direcao == 1){
        set_sprite_tile(player.id, 20);
        set_sprite_tile(player.id+1, 21);
        set_sprite_tile(player.id+2, 22);
        set_sprite_tile(player.id+3, 23);
    }else{
        set_sprite_tile(player.id, 22);
        set_sprite_tile(player.id+1, 23);
        set_sprite_tile(player.id+2, 20);
        set_sprite_tile(player.id+3, 21);
    }

    player.velocidade_y += GRAVIDADE;
    player.y -= player.velocidade_y;

    
    if(colisao_chao(player.y)){
        player.pulando = FALSE;
        player.y = CHAO-16;
        player.chao = TRUE;
    }else{
        player.chao = FALSE;
    }
}

void mover_personagem_lado(){
    switch (joypad()){
        case J_UP:
            if(player.pulando == FALSE){
                player.velocidade_y = 11;
                pular();
                som_pulo();
            }
            break;

        case J_DOWN:
            if(player.agachando == FALSE){
                player.agachando = TRUE;
                if(player.chao == FALSE){
                    player.pulando = TRUE;
                    player.y += 16;
                    som_sair();
                }
            }
            
            
            if(player.direcao == 1){
                set_sprite_tile(player.id, 28);
                set_sprite_tile(player.id+1, 29);
                set_sprite_tile(player.id+2, 30);
                set_sprite_tile(player.id+3, 31);
            }else{
                set_sprite_tile(player.id, 30);
                set_sprite_tile(player.id+1, 31);
                set_sprite_tile(player.id+2, 28);
                set_sprite_tile(player.id+3, 29);
            }
            break;

        case J_LEFT:
            if(nivel == 1){
                player.x -= 6;
            }else{
                player.x -= 3;
            }
            
            if(player.direcao == 1){
                set_sprite_prop(player.id, S_FLIPX);
                set_sprite_prop(player.id+1, S_FLIPX);
                set_sprite_prop(player.id+2, S_FLIPX);
                set_sprite_prop(player.id+3, S_FLIPX);
                player.direcao = -1;
            }
            rolagem = -1;

            if(player.passo == 1){
                set_sprite_tile(player.id, 14);
                set_sprite_tile(player.id+1, 15);
                set_sprite_tile(player.id+2, 12);
                set_sprite_tile(player.id+3, 13);
                player.passo = 2;
            }else{
                set_sprite_tile(player.id, 18);
                set_sprite_tile(player.id+1, 19);
                set_sprite_tile(player.id+2, 16);
                set_sprite_tile(player.id+3, 17);
                player.passo = 1;
            }

            break;

        case J_RIGHT:
            player.x += 3;
            if(player.direcao == -1){
                set_sprite_prop(player.id, 1);
                set_sprite_prop(player.id+1, 1);
                set_sprite_prop(player.id+2, 1);
                set_sprite_prop(player.id+3, 1);
                player.direcao = 1;
            }
            rolagem = 1;

            if(player.passo == 1){
                set_sprite_tile(player.id, 12);
                set_sprite_tile(player.id+1, 13);
                set_sprite_tile(player.id+2, 14);
                set_sprite_tile(player.id+3, 15);
                player.passo = 2;
            }else{
                set_sprite_tile(player.id, 16);
                set_sprite_tile(player.id+1, 17);
                set_sprite_tile(player.id+2, 18);
                set_sprite_tile(player.id+3, 19);
                player.passo = 1;
            }
            break;

        case J_A:
            if(player.pulando == FALSE){
                player.velocidade_y = 17;
                pular();
                som_pulo();
            }
            break;
        default:
            rolagem = 0;
            player.piscando++;
            player.agachando = FALSE;
            if(player.pulando == FALSE){
                if(player.direcao == 1){
                    if(player.piscando == 100){
                        player.piscando = 0;
                        set_sprite_tile(player.id, 8);
                        set_sprite_tile(player.id+1, 9);
                        set_sprite_tile(player.id+2, 10);
                        set_sprite_tile(player.id+3, 11);
                    }else if(player.piscando >= 97){
                        set_sprite_tile(player.id, 4);
                        set_sprite_tile(player.id+1, 5);
                        set_sprite_tile(player.id+2, 6);
                        set_sprite_tile(player.id+3, 7);
                    }else{
                        set_sprite_tile(player.id, 0);
                        set_sprite_tile(player.id+1, 1);
                        set_sprite_tile(player.id+2, 2);
                        set_sprite_tile(player.id+3, 3);
                    }
                }else{
                    if(player.piscando == 20){
                        player.piscando = 0;
                        set_sprite_tile(player.id, 10);
                        set_sprite_tile(player.id+1, 11);
                        set_sprite_tile(player.id+2, 8);
                        set_sprite_tile(player.id+3, 9);
                    }else if(player.piscando >= 17){
                        set_sprite_tile(player.id, 6);
                        set_sprite_tile(player.id+1, 7);
                        set_sprite_tile(player.id+2, 4);
                        set_sprite_tile(player.id+3, 5);
                    }else{
                        set_sprite_tile(player.id, 2);
                        set_sprite_tile(player.id+1, 3);
                        set_sprite_tile(player.id+2, 0);
                        set_sprite_tile(player.id+3, 1);
                    }
                }
            }
            if(nivel == 1){
                player.x -= 3;
            }
    }
}

void mover_personagem_cima_baixo(){
    switch (joypad()){
        case J_UP:
            if(player.y > 35){
                player.y -= 4;
            }
            break;
        case J_DOWN:
            if(player.y < 133){
                player.y += 4;
            }
            break;
        case J_RIGHT:
            if(player.x < 150){
                player.x += 6;
            }
            break;
        case J_LEFT:
            if(player.x > 12){
                player.x -= 6;
            }
            break;
        default:
            break;
    }
}

void mover_inimigo_cima_baixo(){
    if(inimigo1_y < player.y){
        set_sprite_tile(30, K);
        inimigo1_y++;
    }else if(inimigo1_y > player.y){
        set_sprite_tile(30, J);
        inimigo1_y--;
    }
    if(inimigo2_y < player.y){
        inimigo2_y++;
    }else if(inimigo2_y > player.y){
        inimigo2_y--;
    }

    if(inimigo1_x <= 8){
        som_confirmar();
        player.pontos++;
        inimigo1_x = 165;
        inimigo1_y = sorteio(35, 100);
    }
    if(inimigo2_x <= 8){
        inimigo2_x = 165;
        inimigo2_y = sorteio(35, 100);
    }
}

void mover_personagem_topo(){
    switch (joypad()){
        case J_UP: 
            set_sprite_tile(player.id, 32);
            set_sprite_prop(player.id, 0);
            if(player.y + background.y >= 20){
                if(player.y >= 18){
                    player.y -= 3;
                }
            }
            if(background.y > 3){
                background.y -= 3;
                move_bkg(background.x, background.y);
            }
            break;
        
        case J_DOWN: 
            set_sprite_tile(player.id, 32);
            set_sprite_prop(player.id, 0);
            set_sprite_prop(player.id, S_FLIPY);
            if(player.y + background.y <= 255){
                if(player.y <= 151){
                    player.y += 3;
                }
            }
            if(background.y < 103){
                background.y += 3;
                move_bkg(background.x, background.y);
            }
            break;

        case J_LEFT:
            set_sprite_tile(player.id, 33);
            set_sprite_prop(player.id, S_FLIPX);
            if(player.x + background.x >= 8){
                if(player.x >= 9){
                    player.x -= 3;
                }
            }
            if(background.x > 3){
                background.x -= 3;
                move_bkg(background.x, background.y);
            }
            break;

        case J_RIGHT:
            set_sprite_tile(player.id, 33);
            set_sprite_prop(player.id, 0);
            if(player.x + background.x <= 250){
                if(player.x <= 158){
                    player.x += 3;
                }
            }
            if(background.x < 88){
                background.x += 3;
                move_bkg(background.x, background.y);
            }
            break;

    }
}

void mover_mochila_lado(){
    switch (joypad()){
        case J_LEFT:
            if(player.x >= 16){
                player.x -= 3 + player.pontos;
            }
            break;

        case J_RIGHT:
            if(player.x <= 145){
                player.x += 3 + player.pontos;
            }
            break;

    }
}

void mover_sprites(UINT8 id, UINT8 x, UINT8 y){
    move_sprite(id, x, y); // ESQUERDA SUPERIOR
    move_sprite(id+1, x, y+8); // ESQUERDA INFERIOR
    move_sprite(id+2, x+8, y); // DIREITA SUPERIOR
    move_sprite(id+3, x+8, y+8); // DIREITA INFERIOR
}

void setup_plantas(){
    planta[0].id = 16; //TOPO ESQUERDA PRA DIREITA
    planta[0].x = 0;
    planta[0].y = 52;
    planta[0].direcao = 1;
    planta[0].velocidade = sorteio(1, 4);
    planta[0].passo = 0;
    set_sprite_tile(planta[0].id, 84);

    planta[1].id = 17; //TOPO DIREITA PRA ESQUERDA
    planta[1].x = 160;
    planta[1].y = 52;
    planta[1].direcao = 0;
    planta[1].velocidade = sorteio(1, 4);
    planta[1].passo = 0;
    set_sprite_tile(planta[1].id, 84);

    planta[2].id = 18; //MEIO ESQUERDA PRA DIREITA
    planta[2].x = 8;
    planta[2].y = 100;
    planta[2].direcao = 1;
    planta[2].velocidade = sorteio(1, 4);
    planta[2].passo = 0;
    set_sprite_tile(planta[2].id, 84);

    planta[3].id = 19; //MEIO DIREITA PRA ESQUERDA
    planta[3].x = 160;
    planta[3].y = 100;
    planta[3].direcao = 0;
    planta[3].velocidade = sorteio(1, 4);
    planta[3].passo = 0;
    set_sprite_tile(planta[3].id, 84);

    planta[4].id = 20; //CHAO ESQUERDA PRA DIREITA
    planta[4].x = 8;
    planta[4].y = 144;
    planta[4].direcao = 1;
    planta[4].velocidade = sorteio(1, 4);
    planta[4].passo = 0;
    set_sprite_tile(planta[4].id, 84);

    planta[5].id = 21; //CHAO DIREITA PRA ESQUERDA
    planta[5].x = 160;
    planta[5].y = 144;
    planta[5].direcao = 0;
    planta[5].velocidade = sorteio(1, 4);
    planta[5].passo = 0;
    set_sprite_tile(planta[5].id, 84);
}

void animacao_moeda(){
    if(moeda.brilho == 2){
        if(moeda.giro > 11){
            moeda.giro = 0;
            moeda.brilho = 0;
        }else if(moeda.giro > 8){
            set_sprite_tile(moeda.id, 92);
            moeda.giro++;
        }else if(moeda.giro > 5){
            set_sprite_tile(moeda.id, 93);
            moeda.giro++;
        }else if(moeda.giro > 2){
            set_sprite_tile(moeda.id, 92);
            moeda.giro++;
        }else{
            set_sprite_tile(moeda.id, 91);
            set_sprite_prop(moeda.id, 0);
            moeda.giro++;
        }
    }else{
        if(moeda.giro > 11){
            moeda.giro = 0;
            moeda.brilho++;
        }else if(moeda.giro > 8){
            set_sprite_tile(moeda.id, 89);
            set_sprite_prop(moeda.id, S_FLIPX);
            moeda.giro++;
            moeda.y++;
        }else if(moeda.giro > 5){
            set_sprite_tile(moeda.id, 90);
            moeda.giro++;
            moeda.y++;
        }else if(moeda.giro > 2){
            set_sprite_tile(moeda.id, 89);
            moeda.giro++;
            moeda.y--;
        }else{
            set_sprite_tile(moeda.id, 88);
            set_sprite_prop(moeda.id, 0);
            moeda.giro++;
            moeda.y--;
        }
    }
    move_sprite(moeda.id, moeda.x, moeda.y);
}

void reset_sprites(UINT8 id, UINT8 qtd){
    int i;
    for(i = 0; i < qtd; i++){
        set_sprite_prop(id+i, 0);
    }
}

// ------------ FUNCOES DE VERIFICACAO ------------

UINT8 verifica_guarita(){
    if((background.x+player.x) >= 94 && (background.x+player.x) <= 142 && (background.y+player.y) <= 24){
        return 1;
    }
    return 0;
}

UINT8 verifica_biblioteca(){
    if((background.x+player.x) >= 15 && (background.x+player.x) <= 38 && (background.y+player.y) >= 35 && (background.y+player.y) <= 70){
        return 1;
    }
    return 0;
}

UINT8 verifica_jorge(){
    if((background.x+player.x) >= 46 && (background.x+player.x) <= 62 && (background.y+player.y) >= 138 && (background.y+player.y) <= 154){
        return 1;
    }
    return 0;
}

UINT8 verifica_exatas(){
    if((background.x+player.x) >= 70 && (background.x+player.x) <= 86 && (background.y+player.y) >= 218 && (background.y+player.y) <= 234){
        return 1;
    }
    return 0;
}

UINT8 verifica_adonias(){
    if((background.x+player.x) >= 180 && (background.x+player.x) <= 194 && (background.y+player.y) >= 134 && (background.y+player.y) <= 158){
        return 1;
    }
    return 0;
}

UINT8 verifica_arvore_cima(){
    if((background.x+player.x) >= 78 && (background.x+player.x) <= 86 && (background.y+player.y) >= 62 && (background.y+player.y) <= 78){
        return 1;
    }
    return 0;
}

UINT8 verifica_torre(){
    if((background.x+player.x) >= 94 && (background.x+player.x) <= 150 && (background.y+player.y) >= 162 && (background.y+player.y) <= 218){
        return 1;
    }
    return 0;
}

UINT8 verifica_ru(){
    if((background.x+player.x) >= 220 && (background.y+player.y) >= 170 && (background.y+player.y) <= 190){
        return 1;
    }
    return 0;
}

void verifica_borda(){
    if(player.x <= 8){
        player.x = 8;
    }else if(player.x >= 152){
        player.x = 152;
    }else if(player.y <= 8){
        player.y = 8;
        player.velocidade_y = 0;
    }
}

void verifica_vidas(){
    set_sprite_tile(7, 83);
    set_sprite_tile(8, 83);
    set_sprite_tile(9, 83);
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
        default:
            player.vidas = 0;
        case 0:
            move_sprite(7, 500, 20);
            move_sprite(8, 500, 20);
            move_sprite(9, 500, 20);
            break;
    }
}

UINT8 sorteio(UINT8 min, UINT8 max){
    UINT8 valor = abs(rand()%max+1)+min;
    
    return valor;
}

// ------------ FUNCOES DAS FASES ------------



#endif
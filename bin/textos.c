#ifndef TEXTOS_C
#define TEXTOS_C

#include <gb/gb.h>

#define A 46
#define B 47
#define C 48
#define D 49
#define E 50
#define F 51
#define G 52
#define H 53
#define I 54
#define J 55
#define K 56
#define L 57
#define M 58
#define N 59
#define O 60
#define P 61
#define Q 62
#define R 63
#define S 64
#define T 65
#define U 66
#define V 67
#define W 68
#define X 69
#define Y 70
#define Z 71
#define ponto 72
#define zero 73
#define um 74
#define dois 75
#define tres 76
#define quatro 77
#define cinco 78
#define seis 79
#define sete 80
#define oito 81
#define nove 82

void intro();
void biblioteca();
void jorge();
void ru();
void pontos();
void verifica_uesc();
void game_over();
void ru_fechado();
void confirmar_ru();
void sem_moedas();
void ru_timer();
void remover_sprites(UINT8, UINT8);

void escrever(char*, UINT8, UINT8, UINT8);
void limpar();



void intro(){
    int x = 200;
    set_sprite_tile(20, E);
    set_sprite_tile(21, S);
    set_sprite_tile(22, C);
    set_sprite_tile(23, A);
    set_sprite_tile(24, P);
    set_sprite_tile(25, E);
    while(x >= 40){
        move_sprite(20, x, 68);
        move_sprite(21, x+8, 68);
        move_sprite(22, x+16, 68);
        move_sprite(23, x+24, 68);
        move_sprite(24, x+32, 68);
        move_sprite(25, x+40, 68);
        x -= 17;
        if(joypad() == J_START){
            return;
        }
        delay(FPS);
    }
    
    if(joypad() == J_START){
        return;
    }
    delay(50);
    set_sprite_tile(26, F);
    set_sprite_tile(27, R);
    set_sprite_tile(28, O);
    set_sprite_tile(29, M);
    x = 0;
    while(x <= 75){
        move_sprite(26, x, 80);
        move_sprite(27, x+8, 80);
        move_sprite(28, x+16, 80);
        move_sprite(29, x+24, 80);
        x += 17;
        if(joypad() == J_START){
            return;
        }
        delay(FPS);
    }

    

    set_sprite_tile(30, U);
    set_sprite_tile(31, E);
    set_sprite_tile(32, S);
    set_sprite_tile(33, C);
    
    x = 252;
    while(x >= 92){
        move_sprite(30, 90, x);
        x -= 10;

        if(joypad() == J_START){
            return;
        }

        delay(40);
    }
    if(joypad() == J_START){
        return;
    }
    
    x = 252;
    while(x >= 92){
        move_sprite(31, 90+8, x);
        x -= 10;
        if(joypad() == J_START){
            return;
        }
        delay(30);
    }
    if(joypad() == J_START){
        return;
    }
    
    x = 252;
    while(x >= 92){
        move_sprite(32, 90+16, x);
        x -= 10;
        if(joypad() == J_START){
            return;
        }
        delay(20);
    }
    if(joypad() == J_START){
        return;
    }

    x = 252;
    while(x >= 92){
        move_sprite(33, 90+24, x);
        x -= 10;
        if(joypad() == J_START){
            return;
        }
        delay(10);
    }
    if(joypad() == J_START){
        return;
    }

}

void biblioteca(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);
    set_sprite_prop(27, 0);
    set_sprite_prop(28, 0);
    set_sprite_prop(29, 0);

    set_sprite_tile(20, B);
    set_sprite_tile(21, I);
    set_sprite_tile(22, B);
    set_sprite_tile(23, L);
    set_sprite_tile(24, I);
    set_sprite_tile(25, O);
    set_sprite_tile(26, T);
    set_sprite_tile(27, E);
    set_sprite_tile(28, C);
    set_sprite_tile(29, A);
    
    move_sprite(20, 44, 85);
    move_sprite(21, 44+8, 85);
    move_sprite(22, 44+16, 85);
    move_sprite(23, 44+24, 85);
    move_sprite(24, 44+32, 85);
    move_sprite(25, 44+40, 85);
    move_sprite(26, 44+48, 85);
    move_sprite(27, 44+56, 85);
    move_sprite(28, 44+64, 85);
    move_sprite(29, 44+72, 85);
}

void jorge(){
    set_sprite_prop(17, 0);
    set_sprite_prop(18, 0);
    set_sprite_prop(19, 0);
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);
    set_sprite_prop(27, 0);
    set_sprite_prop(28, 0);
    set_sprite_prop(29, 0);

    set_sprite_tile(17, P);
    set_sprite_tile(18, A);
    set_sprite_tile(19, V);

    set_sprite_tile(20, J);
    set_sprite_tile(21, O);
    set_sprite_tile(22, R);
    set_sprite_tile(23, G);
    set_sprite_tile(24, E);

    set_sprite_tile(25, A);
    set_sprite_tile(26, M);
    set_sprite_tile(27, A);
    set_sprite_tile(28, D);
    set_sprite_tile(29, O);
    
    move_sprite(17, 76, 77);
    move_sprite(18, 76+8, 77);
    move_sprite(19, 76+16, 77);

    move_sprite(20, 68, 85);
    move_sprite(21, 68+8, 85);
    move_sprite(22, 68+16, 85);
    move_sprite(23, 68+24, 85);
    move_sprite(24, 68+32, 85);

    move_sprite(25, 68, 93);
    move_sprite(26, 68+8, 93);
    move_sprite(27, 68+16, 93);
    move_sprite(28, 68+24, 93);
    move_sprite(29, 68+32, 93);
}

void ru(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);

    set_sprite_tile(20, R);
    set_sprite_tile(21, U);
    
    move_sprite(20, 80, 85);
    move_sprite(21, 80+8, 85);
}

void pontos(){
    int tile;
    if(player.pontos == abs(player.pontos)){
        tile = zero + player.pontos;
    }else{
        tile = zero;
    }
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);
    set_sprite_prop(27, 0);

    set_sprite_tile(20, P);
    set_sprite_tile(21, O);
    set_sprite_tile(22, N);
    set_sprite_tile(23, T);
    set_sprite_tile(24, O);
    set_sprite_tile(25, S);
    set_sprite_tile(26, ponto);
    set_sprite_tile(27, tile);

    move_sprite(20, 10, 150);
    move_sprite(21, 10+8, 150);
    move_sprite(22, 10+16, 150);
    move_sprite(23, 10+24, 150);
    move_sprite(24, 10+32, 150);
    move_sprite(25, 10+40, 150);
    move_sprite(26, 10+48, 150);
    move_sprite(27, 10+56, 150);
}

void verifica_uesc(){
    if(player.UESC[0] == TRUE){
        set_sprite_tile(36, U);
        move_sprite(36, 72, 20);
    }else if(player.UESC[0] == FALSE){
        move_sprite(36, 250, 250);
    }

    if(player.UESC[1] == TRUE){
        set_sprite_tile(37, E);
        move_sprite(37, 72+8, 20);
    }else if(player.UESC[1] == FALSE){
        move_sprite(37, 250, 250);
    }

    if(player.UESC[2] == TRUE){
        set_sprite_tile(38, S);
        move_sprite(38, 72+16, 20);
    }else if(player.UESC[2] == FALSE){
        move_sprite(38, 250, 250);
    }

    if(player.UESC[3] == TRUE){
        set_sprite_tile(39, C);
        move_sprite(39, 72+24, 20);
    }else if(player.UESC[3] == FALSE){
        move_sprite(39, 250, 250);
    }
}

void verifica_moedas(){
    int tile = zero + player.reais;
    set_sprite_tile(4, tile);
    set_sprite_tile(5, 88);

    move_sprite(4, 10, 19);
    move_sprite(5, 10+10, 19);
}

void game_over(){
    UINT8 y = 0;
    UINT8 velocidade = 0;

    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);

    set_sprite_tile(20, G);
    set_sprite_tile(21, A);
    set_sprite_tile(22, M);
    set_sprite_tile(23, E);
    set_sprite_tile(24, O);
    set_sprite_tile(25, V);
    set_sprite_tile(26, E);
    set_sprite_tile(27, R);

    while (y <= 74){
        move_sprite(20, 72, y);
        move_sprite(21, 72+8, y);
        move_sprite(22, 72+16, y);
        move_sprite(23, 72+24, y);
        velocidade += 2;
        y += velocidade;
        if(joypad() == J_A || joypad() == J_B || joypad() == J_DOWN || joypad() == J_UP || joypad() == J_LEFT || joypad() == J_RIGHT || joypad() == J_SELECT){
            return;
        }else if(joypad() == J_START){
            remover_sprites(20, 27);
            reset();
        }
        delay(FPS);
    }
    
    y = 200;
    velocidade = 0;
    while (y >= 86){
        move_sprite(24, 72, y);
        move_sprite(25, 72+8, y);
        move_sprite(26, 72+16, y);
        move_sprite(27, 72+24, y);
        velocidade += 2;
        y -= velocidade;
        if(joypad() == J_A || joypad() == J_B || joypad() == J_DOWN || joypad() == J_UP || joypad() == J_LEFT || joypad() == J_RIGHT || joypad() == J_SELECT){
            return;
        }else if(joypad() == J_START){
            remover_sprites(20, 27);
            reset();
        }
        delay(FPS);
    }
    
    move_sprite(20, 72, 76);
    move_sprite(21, 72+8, 76);
    move_sprite(22, 72+16, 76);
    move_sprite(23, 72+24, 76);
    move_sprite(24, 72, 84);
    move_sprite(25, 72+8, 84);
    move_sprite(26, 72+16, 84);
    move_sprite(27, 72+24, 84);
    
    delay(100);

    while(1){
        if(joypad() == J_A || joypad() == J_B || joypad() == J_DOWN || joypad() == J_UP || joypad() == J_LEFT || joypad() == J_RIGHT || joypad() == J_SELECT){
            return;
        }else if(joypad() == J_START){
            remover_sprites(20, 27);
            reset();
        }
    }

}

void ru_fechado(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);

    set_sprite_tile(20, F);
    set_sprite_tile(21, E);
    set_sprite_tile(22, C);
    set_sprite_tile(23, H);
    set_sprite_tile(24, A);
    set_sprite_tile(25, D);
    set_sprite_tile(26, O);

    move_sprite(20, 60, 85);
    move_sprite(21, 60+8, 85);
    move_sprite(22, 60+16, 85);
    move_sprite(23, 60+24, 85);
    move_sprite(24, 60+32, 85);
    move_sprite(25, 60+40, 85);
    move_sprite(26, 60+48, 85);

}

void confirmar_ru(){
    set_sprite_tile(20, 83);
    set_sprite_tile(21, ponto);
    set_sprite_tile(22, ponto);
    set_sprite_tile(23, ponto);

    

    move_sprite(20, 68, 76);
    move_sprite(21, 68+14, 76);
    move_sprite(22, 68+16, 76);
    move_sprite(23, 68+18, 76);
    moeda.x = 68+32;
    moeda.y = 76;
    moeda.id = 24;

}

void confirmar_saida(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);

    set_sprite_tile(20, S);
    set_sprite_tile(21, A);
    set_sprite_tile(22, I);
    set_sprite_tile(23, N);
    set_sprite_tile(24, D);
    set_sprite_tile(25, O);

    move_sprite(20, 64, 85);
    move_sprite(21, 64+8, 85);
    move_sprite(22, 64+16, 85);
    move_sprite(23, 64+24, 85);
    move_sprite(24, 64+32, 85);
    move_sprite(25, 64+40, 85);
}

void sem_moedas(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);
    set_sprite_prop(22, 0);
    set_sprite_prop(23, 0);
    set_sprite_prop(24, 0);
    set_sprite_prop(25, 0);
    set_sprite_prop(26, 0);
    set_sprite_prop(27, 0);
    set_sprite_prop(28, 0);

    set_sprite_tile(20, S);
    set_sprite_tile(21, E);
    set_sprite_tile(22, M);

    set_sprite_tile(23, M);
    set_sprite_tile(24, O);
    set_sprite_tile(25, E);
    set_sprite_tile(26, D);
    set_sprite_tile(27, A);
    set_sprite_tile(28, S);

    move_sprite(20, 76, 81);
    move_sprite(21, 76+8, 81);
    move_sprite(22, 76+16, 81);

    move_sprite(23, 64, 89);
    move_sprite(24, 64+8, 89);
    move_sprite(25, 64+16, 89);
    move_sprite(26, 64+24, 89);
    move_sprite(27, 64+32, 89);
    move_sprite(28, 64+40, 89);
}

void ru_timer(){

    while (joypad() != J_A && joypad() != J_B && joypad() != J_START && player.contador_RU <= 500){
        
        if(player.contador_RU > 426){
            set_sprite_tile(33, 33); // SETA
            set_sprite_tile(32, ponto);
            move_sprite(33, 52+48, 93);
        }else if(player.contador_RU > 355){
            set_sprite_tile(32, 33); // SETA
            set_sprite_tile(31, ponto);
            move_sprite(32, 52+40, 93);
        }else if(player.contador_RU > 284){
            set_sprite_tile(31, 33); // SETA
            set_sprite_tile(30, ponto);
            move_sprite(31, 52+32, 93);
        }else if(player.contador_RU > 213){
            set_sprite_tile(30, 33); // SETA
            set_sprite_tile(29, ponto);
            move_sprite(30, 52+24, 93);
        }else if(player.contador_RU > 142){
            set_sprite_tile(29, 33); // SETA
            set_sprite_tile(28, ponto);
            move_sprite(29, 52+16, 93);
        }else if(player.contador_RU > 71){
            set_sprite_tile(28, 33);
            set_sprite_tile(27, ponto);
            move_sprite(28, 52+8, 93); 
        }else if(player.contador_RU >= 0){
            set_sprite_tile(27, 33); // SETA
            move_sprite(27, 52, 93);
        }
        

        
        
        player.contador_RU++;
        if(player.contador_RU > 500){
            break;
        }
        delay(FPS);
    }
    
}

void remover_sprites(UINT8 inicio, UINT8 fim){
    int i;
    for(i = inicio; i <= fim; i++){
        move_sprite(i, 250, 250);
    }
}


void escrever(char* frase, UINT8 altura, UINT8 tile, UINT8 topo){
    UINT16 i = 0;
    UINT16 len = strlen(frase);
    
    if(tile >= 40){
        waitpad(J_A);
        escrever(frase, topo, 0, topo);
    }
    while(i <= 10){
        
        if(frase[i] == '\0'){
            break;
        }

        if(tile >= 40){
            break;
        }

        if(frase[i] != ' '){
            if(frase[i] >= 'a' && frase[i] <= 'z'){
                set_sprite_tile(tile, A+(frase[i]-'a'));
            }else if(frase[i] >= 'A' && frase[i] <= 'Z'){
                set_sprite_tile(tile, A+(frase[i]-'A'));
            }else if(frase[i] >= '0' && frase[i] <= '9'){
                set_sprite_tile(tile, zero+(frase[i]-'0'));
            }else if(frase[i] == ':'){
                set_sprite_tile(tile, ponto);
            }
            set_sprite_prop(tile, 0);
            move_sprite(tile, 20+8*i, altura);
            tile++;
        }
        

        i++;
        delay(FPS);
    }

    if(frase[i] != '\0'){
        escrever(frase+i, altura+8, tile, topo);
    }else{
        remover_sprites(tile, 39);
    }
}

#endif
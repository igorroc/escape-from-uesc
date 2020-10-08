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
void intro_saida();
void biblioteca();
void biblioteca_saida();
void jorge();
void jorge_saida();
void ru();
void ru_saida();
void pontos();
void pontos_saida();
void verifica_uesc();
void game_over();
void ru_fechado();
void ru_fechado_saida();
void confirmar_ru();
void sem_moedas();
void sem_moedas_saida();
void ru_timer();

void escrever(char*, UINT8);
void limpar();

void intro(){
    int x = 200;
    set_sprite_tile(20, E);
    set_sprite_tile(21, S);
    set_sprite_tile(22, C);
    set_sprite_tile(23, A);
    set_sprite_tile(24, P);
    set_sprite_tile(25, E);
    while(x >= 59){
        move_sprite(20, x, 60);
        move_sprite(21, x+8, 60);
        move_sprite(22, x+16, 60);
        move_sprite(23, x+24, 60);
        move_sprite(24, x+32, 60);
        move_sprite(25, x+40, 60);
        x -= 17;
        if(joypad() == J_START){
            return;
        }
        delay(70);
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
        move_sprite(26, x, 70);
        move_sprite(27, x+8, 70);
        move_sprite(28, x+16, 70);
        move_sprite(29, x+24, 70);
        x += 10;
        
        if(joypad() == J_START){
            return;
        }
        delay(70);
    }

    

    set_sprite_tile(30, U);
    set_sprite_tile(31, E);
    set_sprite_tile(32, S);
    set_sprite_tile(33, C);
    
    x = 250;
    while(x >= 85){
        move_sprite(30, 70, x);
        x -= 10;

        if(joypad() == J_START){
            return;
        }

        delay(40);
    }

    if(joypad() == J_START){
        return;
    }
    x = 250;
    while(x >= 85){
        move_sprite(31, 70+8, x);
        x -= 10;
        if(joypad() == J_START){
            return;
        }
        delay(30);
    }
    if(joypad() == J_START){
        return;
    }
    x = 250;
    while(x >= 85){
        move_sprite(32, 70+16, x);
        x -= 10;
        if(joypad() == J_START){
            return;
        }
        delay(20);
    }
    if(joypad() == J_START){
        return;
    }
    x = 250;
    while(x >= 85){
        move_sprite(33, 70+24, x);
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

void intro_saida(){
    move_sprite(20, 250, 60);
    move_sprite(21, 250, 60);
    move_sprite(22, 250, 60);
    move_sprite(23, 250, 60);
    move_sprite(24, 250, 60);
    move_sprite(25, 250, 60);
    move_sprite(26, 250, 60);
    move_sprite(27, 250, 60);
    move_sprite(28, 250, 60);
    move_sprite(29, 250, 60);
    move_sprite(30, 250, 60);
    move_sprite(31, 250, 60);
    move_sprite(32, 250, 60);
    move_sprite(33, 250, 60);
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

void biblioteca_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
    move_sprite(22, 250, 250);
    move_sprite(23, 250, 250);
    move_sprite(24, 250, 250);
    move_sprite(25, 250, 250);
    move_sprite(26, 250, 250);
    move_sprite(27, 250, 250);
    move_sprite(28, 250, 250);
    move_sprite(29, 250, 250);
}

void jorge(){
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
    set_sprite_prop(30, 0);
    set_sprite_prop(31, 0);
    set_sprite_prop(32, 0);

    set_sprite_tile(20, P);
    set_sprite_tile(21, A);
    set_sprite_tile(22, V);

    set_sprite_tile(23, J);
    set_sprite_tile(24, O);
    set_sprite_tile(25, R);
    set_sprite_tile(26, G);
    set_sprite_tile(27, E);

    set_sprite_tile(28, A);
    set_sprite_tile(29, M);
    set_sprite_tile(30, A);
    set_sprite_tile(31, D);
    set_sprite_tile(32, O);
    
    move_sprite(20, 76, 77);
    move_sprite(21, 76+8, 77);
    move_sprite(22, 76+16, 77);

    move_sprite(23, 68, 85);
    move_sprite(24, 68+8, 85);
    move_sprite(25, 68+16, 85);
    move_sprite(26, 68+24, 85);
    move_sprite(27, 68+32, 85);

    move_sprite(28, 68, 93);
    move_sprite(29, 68+8, 93);
    move_sprite(30, 68+16, 93);
    move_sprite(31, 68+24, 93);
    move_sprite(32, 68+32, 93);
}

void jorge_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
    move_sprite(22, 250, 250);
    move_sprite(23, 250, 250);
    move_sprite(24, 250, 250);
    move_sprite(25, 250, 250);
    move_sprite(26, 250, 250);
    move_sprite(27, 250, 250);
    move_sprite(28, 250, 250);
    move_sprite(29, 250, 250);
    move_sprite(30, 250, 250);
    move_sprite(31, 250, 250);
    move_sprite(32, 250, 250);
}

void ru(){
    set_sprite_prop(20, 0);
    set_sprite_prop(21, 0);

    set_sprite_tile(20, R);
    set_sprite_tile(21, U);
    
    move_sprite(20, 80, 85);
    move_sprite(21, 80+8, 85);
}

void ru_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
}

void pontos(){
    int tile = 73 + player.pontos;
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

void pontos_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
    move_sprite(22, 250, 250);
    move_sprite(23, 250, 250);
    move_sprite(24, 250, 250);
    move_sprite(25, 250, 250);
    move_sprite(26, 250, 250);
    move_sprite(27, 250, 250);
}

void verifica_uesc(){
    if(player.UESC[0] == TRUE){
        set_sprite_tile(30, U);
        move_sprite(30, 72, 20);
    }

    if(player.UESC[1] == TRUE){
        set_sprite_tile(31, E);
        move_sprite(31, 72+8, 20);
    }

    if(player.UESC[2] == TRUE){
        set_sprite_tile(32, S);
        move_sprite(32, 72+16, 20);
    }

    if(player.UESC[3] == TRUE){
        set_sprite_tile(33, C);
        move_sprite(33, 72+24, 20);
    }
}

void verifica_uesc_saida(){
    
    move_sprite(30, 250, 250);
    move_sprite(31, 250, 250);
    move_sprite(32, 250, 250);
    move_sprite(33, 250, 250);
}

void verifica_moedas(){
    int tile = 73 + player.reais;
    set_sprite_tile(4, tile);
    set_sprite_tile(5, 88);

    move_sprite(4, 10, 20);
    move_sprite(5, 10+10, 19);
}

void game_over(){
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
            break;
        }else if(joypad() == J_START){
            move_sprite(20, 250, 250);
            move_sprite(21, 250, 250);
            move_sprite(22, 250, 250);
            move_sprite(23, 250, 250);
            move_sprite(24, 250, 250);
            move_sprite(25, 250, 250);
            move_sprite(26, 250, 250);
            move_sprite(27, 250, 250);
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

void ru_fechado_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
    move_sprite(22, 250, 250);
    move_sprite(23, 250, 250);
    move_sprite(24, 250, 250);
    move_sprite(25, 250, 250);
    move_sprite(26, 250, 250);
    move_sprite(27, 250, 250);
    move_sprite(28, 250, 250);
    move_sprite(29, 250, 250);
    move_sprite(30, 250, 250);
    move_sprite(31, 250, 250);
    move_sprite(32, 250, 250);
    moeda.x = 250;
    moeda.y = 250;
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

void sem_moedas_saida(){
    move_sprite(20, 250, 250);
    move_sprite(21, 250, 250);
    move_sprite(22, 250, 250);
    move_sprite(23, 250, 250);
    move_sprite(24, 250, 250);
    move_sprite(25, 250, 250);
    move_sprite(26, 250, 250);
    move_sprite(27, 250, 250);
    move_sprite(28, 250, 250);
}

void ru_timer(){
    UINT8 digitos[3] = {0, 0, 0};
    int aux = player.contador_RU;
    int x = 76;
    while (joypad() != J_A && joypad() != J_B && joypad() != J_START && player.contador_RU < 500){
        aux = 500-player.contador_RU;

        digitos[2] = aux%10;
        aux /= 10;
        digitos[1] = aux%10;
        aux /= 10;
        digitos[0] = aux;

        set_sprite_tile(27, zero+digitos[0]);
        set_sprite_tile(28, zero+digitos[1]);
        set_sprite_tile(29, zero+digitos[2]);
        
        move_sprite(27, x, 93);
        move_sprite(28, x+8, 93);
        move_sprite(29, x+16, 93);
        x++;
        player.contador_RU++;
        delay(FPS);
    }
    
}


void escrever(char* frase, UINT8 altura){
    int tile = 0;
    UINT16 i = 0;
    UINT16 len = strlen(frase);

    while(i <= 15){
        
        if(frase[i] != ' '){
            set_sprite_tile(tile, A+(frase[i]-'a'));
            move_sprite(tile, 20+8*i, altura);
            tile++;
        }
        if(frase[i] == '\0'){
            break;
        }

        i++;
        waitpad(J_A);
        delay(100);
    }

    if(frase[i] != '\0'){
        escrever(frase+i, altura+8);
    }
}

void limpar(){
    int tile = 0;
    for(tile = 0; tile < 40; tile++){
        move_sprite(tile, 250, 250);
    }
}

#endif
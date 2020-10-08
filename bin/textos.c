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

void intro();
void intro_saida();
void biblioteca();
void biblioteca_saida();

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
        
        delay(70);
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
        
        delay(40);
    }
    x = 250;
    while(x >= 85){
        move_sprite(31, 70+8, x);
        x -= 10;
        
        delay(30);
    }
    x = 250;
    while(x >= 85){
        move_sprite(32, 70+16, x);
        x -= 10;
        
        delay(20);
    }
    x = 250;
    while(x >= 85){
        move_sprite(33, 70+24, x);
        x -= 10;
        
        delay(10);
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

#endif
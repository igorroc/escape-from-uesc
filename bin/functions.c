#ifndef FUNCTIONS_C
#define FUNCTIONS_C

#include <gb/gb.h>

#include "struct_player.c"

int colisao_chao(UINT8);
void pular();
void iniciar_som();
void som_pulo();
void som_agachar();
void som_soco();
void mover_personagem();
int detectou_colisao();

int colisao_chao(UINT8 y){
    if(y >= CHAO){
        return CHAO;
    }
    return -1;
}


void pular(){
    INT8 possivel_y;

    if(player.pulando == FALSE){
        player.pulando = TRUE;
        player.velocidade_y = 15;
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
    
    possivel_y = (INT8)colisao_chao(player.y);

    
    if(possivel_y != -1){
        player.pulando = FALSE;
    }
}

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

void som_agachar(){
    // see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
    // chanel 1 register 0, Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    // 0001 0110 is 0x16, sweet time 1, sweep direction increase, shift ammount per step 110 (6 decimal)
    NR10_REG = 0x1E; 

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
    // see https://github.com/bwhitman/pushpin/blob/master/src/gbsound.txt
    // chanel 1 register 0, Frequency sweep settings
    // 7	Unused
    // 6-4	Sweep time(update rate) (if 0, sweeping is off)
    // 3	Sweep Direction (1: decrease, 0: increase)
    // 2-0	Sweep RtShift amount (if 0, sweeping is off)
    // 0010 1111 is 0x16, sweet time 1, sweep direction increase, shift ammount per step 110 (6 decimal)
    NR10_REG = 0x2F;

    // chanel 1 register 1: Wave pattern duty and sound length
    // Channels 1 2 and 4
    // 7-6	Wave pattern duty cycle 0-3 (12.5%, 25%, 50%, 75%), duty cycle is how long a quadrangular  wave is "on" vs "of" so 50% (2) is both equal.
    // 5-0 sound length (higher the number shorter the sound)
    // 0100 1000 is 0x40, duty cycle 1 (25%), wave length 0 (long)
    NR11_REG = 0x48;

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

void mover_personagem(){
    switch (joypad()){
        case J_UP:
            if(player.pulando == FALSE && player.CD_pulo == 0){
                som_pulo();
                pular();
                player.CD_pulo = 15;
            }
            break;

        case J_DOWN:
            if(player.agachando == FALSE){
                som_agachar();
                player.agachando = TRUE;
            }
            set_sprite_tile(player.id, 28);
            set_sprite_tile(player.id+1, 29);
            set_sprite_tile(player.id+2, 30);
            set_sprite_tile(player.id+3, 31);
            break;

        case J_LEFT:
            player.x--;
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
            player.x++;
            if(player.direcao == -1){
                set_sprite_prop(player.id, S_FLIPX);
                set_sprite_prop(player.id+1, S_FLIPX);
                set_sprite_prop(player.id+2, S_FLIPX);
                set_sprite_prop(player.id+3, S_FLIPX);
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
            set_sprite_tile(player.id, 10+player.direcao);
            if(player.socando == FALSE){
                som_soco();
                player.socando = TRUE;
            }
            break;

        case J_B:
            if(player.direcao == 1){
                set_sprite_tile(player.id, 24);
                set_sprite_tile(player.id+1, 25);
                set_sprite_tile(player.id+2, 26);
                set_sprite_tile(player.id+3, 27);
            }else{
                set_sprite_tile(player.id, 26);
                set_sprite_tile(player.id+1, 27);
                set_sprite_tile(player.id+2, 24);
                set_sprite_tile(player.id+3, 25);
            }
            
            break;
            
        default:
            rolagem = 0;
            player.piscando++;
            player.agachando = FALSE;
            player.socando = FALSE;
            if(player.pulando == 0){
                if(player.direcao == 1){
                    if(player.piscando == 20){
                        player.piscando = 0;
                        set_sprite_tile(player.id, 8);
                        set_sprite_tile(player.id+1, 9);
                        set_sprite_tile(player.id+2, 10);
                        set_sprite_tile(player.id+3, 11);
                    }else if(player.piscando >= 17){
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
    }
}

int detectou_colisao(){
    if(player.x <= inimigo.x + 8 && player.x +8 >= inimigo.x){
        if(player.y <= inimigo.y +  8 && player.y + 8>= inimigo.y){
            return 1;
        }
    }
    return 0;
}

#endif
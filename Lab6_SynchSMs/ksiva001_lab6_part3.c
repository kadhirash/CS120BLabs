/*  Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *  Lab Section: 021
 *  Assignment: Lab # 6  Exercise # 3
 *  Exercise Description: 
 *      previous lab extension
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "timer.h"
enum States {Start, Init, Inc, Dec, Wait, Reset} state;


#define A0 (~PINA & 0x01)
#define A1 (~PINA & 0x02)
#define B PORTB
unsigned char timer = 0;

// Inc/Dec as you're holding the state 
void Tick() {
    switch(state) { 
        case Start:
            state = Init; break;
        case Init:
            if (A0 && !A1){
                state = Inc;
            }
            else if (A1 && !A0){
                state = Dec;
            }
            else if (A0 && A1){
                state = Reset;
            }
            else{
                state = Init;
            }
            break;
        case Inc:
            if(A1){
                state = Reset;
            }
            if(!A0){
                state = Wait;
            }
            break;
        case Dec:
            if(A0){
                state = Reset;
            }
            if(!A1){
                state = Wait;
            }
            break;
        case Wait:
            if(A0){
                state = Inc;
            }
            else if (A1){
                state = Dec;
            }else if (A0 && A1){
                state = Reset;
            }
            else{
                state = Wait;
            }
            break;
        case Reset:
            if(!A0 && !A1){
                state = Init;
            }
            else {
                state = Reset;
            }
            break;
        default: 
        state = Start; break;
    }
    switch(state) { 
        case Start:
            break;
        case Init:
            timer = 0; break;
        case Inc:
            if(timer == 0x00 && B < 0x09){
                timer++;
                B++;
            }else if (B >= 0x09){
                timer++;
                B = 0x09;
            }
            timer++;
            if(timer == 100){
                if(B < 0x09){
                    timer = 1;
                    B++;
                }
            }
            break;
        case Dec:
            if(timer == 0x00 && B > 0x00){
                timer ++;
                B --;
            }else if(B <= 0x00){
                B = 0x00;
                timer++;
            }
            timer++;
            if(timer == 100){
                if(B > 0x00){
                    timer = 1;
                    B --;
                }
            }
            break;
        case Wait:
            timer = 0; break;
        case Reset:
            B = 0x00; timer = 0x00; break;
        default: 
            state = Start; break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x07; 

    TimerSet(100);
    TimerOn();
    state = Start;
    //PORTB = 0x07;
    /* Insert your solution below */
    while (1) {
    Tick();
    while (!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
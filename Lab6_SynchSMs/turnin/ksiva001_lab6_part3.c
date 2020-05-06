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
enum States {Init, Start, LED1, Inc , Dec, Wait, Restart} state;


unsigned char A = 0x00;

void Tick() {
    A = ~PINA & 0x03;
    switch(state) { 
        case Init:
            state = Start; break;
        case Start:
            state = LED1; break;
        case LED1:
            if (A  == 0x01)
                state = Inc;
            else if (A == 0x02)
                state = Dec;
            else if (A  == 0x03)
                state = Restart;
            else
                state = LED1;
            break;
        case Inc:
        case Dec:
            state = Wait;
            break;
        case Wait:
            if(A == 0x01)
                state = Inc;
            else if (A == 0x02)
                state = Dec;
            else if (A == 0x03)
                state = Restart;
            else if (A  == 0x00)
                state = LED1;
            else
                state = Wait;
            break;
        case Restart:
            if(A == 0x00){
                state = LED1;
            }
            else {
                state = Restart;
            }
        default: break;
    }
    switch(state) { 
        case Init:
        PORTB = 0x07; break;
        case Start:
        case LED1:
        case Wait:
            break;
        case Inc:
                if (PORTB < 9) PORTB++;
                break;
        case Dec:
                if (PORTB > 0) PORTB--;
                break;
        case Restart:
                PORTB = 0x00;
            break;
        default: break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00; 


    TimerSet(100);
    TimerOn();
    state = Start;
    PORTB = 0x07;
    /* Insert your solution below */
    while (1) {
    Tick();
    while (!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
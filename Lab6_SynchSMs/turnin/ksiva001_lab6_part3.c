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
enum States {Start, Init, Inc, Dec, Work} state;


#define A1 (~PINA & 0x01)
#define A2 (~PINA & 0x02)
#define A3 (~PINA & 0x03)
#define B PORTB
unsigned char timer = 0;

// Inc/Dec as you're holding the state 
void Tick() {
    switch(state) { 
        case Start:
            state = Init; break;
        case Init:
            B = 0x07; state = Work; break;
        case Work:
        	if(A1 == 0x01){ // inc
        		if(B < 0x09){
        			B ++;
        			timer = 0;
        			state = Inc;
        		}
        	}else if (A2 == 0x02){ //dec
        		if(B > 0x00){
        			B --;
        			timer = 0;
        			state = Dec;
        		}
        	}else if (A3 == 0x03){
        		B = 0x00; //reset
        	}
        	else{
        		state = Work;
        	}
        	break;
        case Inc:
        	if(A1 == 0x01){
        		timer ++;
        		if(B < 0x09 && ( (timer % 10) == 0)){
        			B ++;
        			timer = 0;
        		}
        	}
        	else {
        		state = Work;
        	}
           	break;
        case Dec:
        	if(A2 == 0x02){
        		timer ++;
        		if(B > 0x00 && ( (timer % 10) == 0)){
        			B --;
        			timer = 0;
        		}
        	}
        	else {
        		state = Work;
        	}
           	break;
        default: 
            state = Init; break;
    }
    switch(state) { 
        case Start:
        case Init:
        case Inc:
        case Dec:
        	break;
        default: 
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00; 

    TimerSet(100);
    TimerOn();
    state = Init;
    /* Insert your solution below */
    while (1) {
    Tick();
    while (!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}
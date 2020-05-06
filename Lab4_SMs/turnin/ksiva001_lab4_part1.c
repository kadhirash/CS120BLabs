/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 4 Exercise # 1
 *	Exercise Description: PB0 & PB1 LED
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Off, Wait_One, On, Wait_Two} state;

void Tick(){
	// State Transitions
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if((PINA & 0x01) == 0x01){
				state = Off;
				break;
			}else{
				state = Init;
				break;
			}
		case Off:
			if((PINA & 0x01) == 0x00){
				state = Wait_One;
				break;
			}else{
				state = Off;
				break;
			}
		case Wait_One:
			if((PINA & 0x01) == 0x01){
				state = On;
				break;
			}else{
				state = Wait_One;
				break;
			}
		case On:
			if((PINA & 0x01) == 0x00){
				state = Wait_Two;
				break;
			}else{
				state = On;
				break;
			}
		case Wait_Two:
			if((PINA & 0x01) == 0x01){
				state = Off;
				break;
			}else{
				state = Wait_Two;
				break;
			}
		default:
			break;
		
	};
	// State Actions
	switch(state){
		case Init:
			PORTB = 0x01;
			break;
		case Off:
			PORTB = 0x02;
			break;
		case Wait_One:
			break;
		case On:
			PORTB = 0x01;
			break;
		case Wait_Two:
			break;
		default:
			break;
	};

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs, intialize to 1s
	DDRB = 0xFF; PORTB = 0x00;	// Configue port B's 8 pins as outputs, initialize to 0s
	state = Start;
    /* Insert your solution below */
    while (1) {
	Tick();	
    }
    return 1;
}

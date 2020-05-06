/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 6  Exercise # 1
 *	Exercise Description: 
 *		syncSM to blink 3 LEDs 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "timer.h"

enum States {Init, Start, LED1, LED2, LED3} state;
void Tick(){
	switch(state){
		case Init:
			state = Start;
			break;
		case Start:
			state = LED1;
			break;
		case LED1:
			state = LED2;
			break;
		case LED2:
			state = LED3;
			break;
		case LED3:
			state = LED1;
			break;
		default:
			state = Start;
			break;
	
	}
	switch(state){
		case Init:
		case Start:
			break;
		case LED1:
			PORTB = 0x01; break;
		case LED2:
			PORTB = 0x02; break;
		case LED3:
			PORTB = 0x04; break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();
	unsigned char tmpB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	tmpB = ~tmpB;
	PORTB = tmpB;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 6  Exercise # 2
 *	Exercise Description: 
 *		syncSM to blink 3 LEDs with button press
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "timer.h"

enum States {Start, Init, Wait_Press, Wait_Release, Wait_Reset, Reset} state;

#define A0 (~PINA & 0x01)
#define B PORTB

unsigned char i;

void Tick(){
	switch(state){
		case Start:
			i = 0; 
			state = Init; break;
		case Init:
			B = 0x01;
			if(!A0){
				state = Init;
			}else{
				state = Wait_Press;
			}
			break;
		case Wait_Press:
			if(A0){
				state = Wait_Press;
			}else{
				state = Wait_Release;
			}
			break;
		case Wait_Release:
			if(A0){
				state = Wait_Reset;
			}else{
				state = Wait_Release;
			}
			break;
		case Wait_Reset:
			if(!A0){
				state = Reset;
			}else{
				state = Wait_Reset;
			}
			break;
		case Reset:
			//i = 0; 
			//B = 0x01; 
			state = Init; 
			break;
		default:
			state = Start; break;
	}
	switch(state){
		case Start:
			break;
		case Init: // LED bouncing
			if(i == 0){
					i ++;
					B = 0x01;
			}
			if(i == 1){
				i ++;
				B = 0x02;
			}
			if(i == 2){
				i ++;
				B = 0x04;
			}
			if(i == 3){
				i = 0;
				B = 0x02;
			}
			break;
		case Wait_Press:
			if(i == 0){
					i ++;
					B = 0x01;
			}
			if(i == 1){
				i ++;
				B = 0x02;
			}
			if(i == 2){
				i ++;
				B = 0x04;
			}
			if(i == 3){
				i = 0;
				B = 0x02;
			}
			break;
		case Wait_Release:
			break;
		case Wait_Reset:
			//i = 0;
			break;
		case Reset:
			i = 0; //B = 0x01;
			break;
		default:
		 state = Start; break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	state = Init;
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

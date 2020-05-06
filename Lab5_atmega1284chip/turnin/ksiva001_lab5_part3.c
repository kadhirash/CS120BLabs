/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section:
 *	Assignment: Lab # 5 Exercise # 3
 *	Exercise Description: LED lights
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo Link: https://drive.google.com/file/d/1Z8HILmEcvz5XK8XToQLEr3rBpPsfhb13/view?usp=sharing 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {Start, Init, Wait, Next_100, Next_100_Wait, Next_200, Next_200_Wait, Next_All, Final_Wait} state;

void Tick(){
	unsigned char temp = ~PINA & 0x01;
	switch(state){
		case Start:
			state = Init; break;
		case Init:
			if(temp){
				state = Wait; break;
			}else{
				state = Init; break;
			}
		case Wait:
			if(!temp){
				state = Next_100; break;
			}else{
				state = Wait; break;
			}
		case Next_100:
			if(temp){
				state = Next_100_Wait; break;
			}else{
				state = Next_100; break;
			}
		case Next_100_Wait:
			if(!temp){
				state = Next_200; break;
			}else{
				state = Next_100_Wait; break;
			}
		case Next_200:
			if(temp){
				state = Next_200_Wait; break;
			}else{
				state = Next_200; break;
			}
		case Next_200_Wait:
			if(!temp){
				state = Next_All; break;
			}else{
				state = Next_200_Wait; break;
			}
		case Next_All:
			if(temp){
				state = Final_Wait; break;
			}else{
				state = Next_All; break;
			}
		case Final_Wait:
			if(!temp){
				state = Init; break;
			}else{
				state = Final_Wait; break;
			}
	};

	switch(state){
		case Start:
			break;
		case Init:
			PORTC = 0x03;	// 3
			break;
		case Wait:
			break;
		case Next_100:
			PORTC = 0x64; break; // 100
		case Next_100_Wait:
			break;
		case Next_200:
			PORTC = 0xC8; break; // 200
		case Next_200_Wait:
			break;
		case Next_All:
			PORTC = 0xFF; break; // ALL
		case Final_Wait:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	state = Start;
	PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}

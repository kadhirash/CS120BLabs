/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 4 Exercise # 3
 *	Exercise Description: House
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Wait, Pound, Y, Lock, Pause} state;
void Tick(){
	// State Transitions
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if((PINA & 0x04) == 0x04){
				state = Pound;
				break;
			}else if ((PINA & 0x80) == 0x80){
				state = Lock;
				break;
			}else{
				state = Init;
				break;
			}
		case Wait:
			if((PINA & 0x02) == 0x02){
				state = Y;
				break;
			}
			/*else if ((PINB & 0x01) == 0x01){
			
				if((PINA & 0x02) == 0x02){
					state = Lock;
					break;
				}else{
					state = Wait;
					break;
				}
				break;
			}*/
			else if ((PINA & 0x80) == 0x80){
				state = Lock;
				break;
			}else if ((PINA & 0x01) == 0x01){
				state = Init;
				break;
			}else{
				state = Wait;
				break;
			}
		case Pound:
			if(PINA == 0x00){
				state = Pound;
				break;
			}
			state = Wait;
			break;
		case Y:
			state = Pause;
			break;
		case Lock:
			if((PINA & 0x00 ) == 0x00 ){
				state = Init;
				break;
			}else{
				state = Lock;
				break;
			}
		case Pause:
			if((PINA & 0x87) == 0x00){
				state = Init;
				break;
			}else{
				state = Pause;
				break;
			}
		default:
			break;
		
	};
	// State Actions
	switch(state){
		case Start:
			PORTB = 0x00;
			PORTC = 0x00;
			break;
		case Init:
			PORTC = 0x01;
			break;
		case Wait:
			PORTC = 0x03;	
			break;
		case Pound:
			PORTC = 0x02;
			break;
		case Y:
			PORTB = 0x01;
			PORTC = 0x04;
			break;
		case Lock:
			PORTB = 0x00;
			PORTC = 0x06;
			break;
		case Pause:
			PORTC = 0x05;
			break;
		default:
			break;
	};

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs, intialize to 1s
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}

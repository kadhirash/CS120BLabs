/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 4 Exercise # 2
 *	Exercise Description: House
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Init, Inc, Dec, Reset} state;
unsigned char cnt = 0x00;
void Tick(){
	// State Transitions
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if((PINA & 0x03) == 0x01){
				state = Inc;
				break;
			}else if ((PINA & 0x3) == 0x02){
				state = Dec;
				break;
			}else if ((PINA & 0x03) == 0x03){
				state = Reset;
				break;
			}else{
				state = Init;
				break;
			}
		case Inc:
			state = Init;
			break;
		case Dec:
			state = Init;
			break;
		/*case Wait:	
			if ((PINA & 0x03) == 0x01){
				state = Inc;
				break;
			}
			else if ((PINA & 0x03) == 0x02){
				state = Dec;
				break;
			}else if ((PINA & 0x03) == 0x03){
				state = Reset;
				break;
			}else{
				state = Wait;
				break;
			}*/
		case Reset:
			if((PINA & 0x03) == 0x03){
				state = Reset;
				break;
			}else{
				state = Init;
				break;
			}
		default:
			break;
		
	};
	// State Actions
	switch(state){
		case Init:
			break;
		case Inc:
			if(cnt>= 0x09){
				cnt = 0x09;
				break;
			}else{
				cnt += 0x01;
				break;
			}
		case Dec:
			if(cnt <= 0x00){
				cnt = 0x00;
			}else{
				cnt -= 0x01;
				break;
			}
//		case Wait:
//			break;
		case Reset:
			cnt = 0x00;
			break;
		default:
			break;
	};

}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs, intialize to 1s
	DDRC = 0xFF; PORTC = 0x00;
	state = Start;
	cnt = 0x07;
    /* Insert your solution below */
    while (1) {
	Tick();
	PORTC = cnt;
    }
    return 1;
}

/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section:
 *	Assignment: Lab # 5 Exercise # 2
 *	Exercise Description: Lab 4, exercise 2 extension
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo Link: https://drive.google.com/file/d/168i68_innIKfphPoQsWcI_cMlz-pawqc/view?usp=sharing

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


// Had help from housemates
// Reset each state
enum States{Start, Inc_d, Inc_p, Dec_d, Dec_p} state;

void Tick(){
	unsigned char temp = ~PINA & 0x03;

	switch(state){
		case Start:
			state = Inc_d; break;
		case Inc_d:
			if(temp == 0x01){
				state = Inc_p;
				if(PORTC >= 0x09){
					PORTC = 0x09; break;
				}else{
					PORTC += 0x01; break;
				}
			}else if (temp == 0x02){
				state = Dec_p;
				if(PORTC <= 0x00){
					PORTC = 0x00; break;
				}else{
					PORTC -= 0x01; break;
				}
			}else if(temp == 0x03){
				state = Inc_d; PORTC = 0x00; break;
			} else{
				state = Inc_d; break;
			}
		case Inc_p:
			if(temp == 0x00){
				state = Inc_d; break;
			}else if(temp == 0x03){
				state = Inc_p; PORTC = 0x00; break;
			}else{
				state = Inc_p; break;
			}
		case Dec_d:
			if(temp == 0x01){
				state = Inc_p;
				if(PORTC >= 0x09){
					PORTC = 0x09; break;
				}else{
					PORTC += 0x01; break;
				}
			}else if (temp == 0x02){
				state = Dec_p;
				if(PORTC <= 0x00){
					PORTC = 0x00; break;
				}else{
					PORTC -= 0x01; break;
				}
			}else if (temp == 0x03){
				state = Dec_d; PORTC = 0x00; break;
			}else{
				state= Dec_d; break;
			}
		case Dec_p:
			if(temp == 0x00){
				state = Dec_d; break;
			}
			else if(temp == 0x03){
				state = Dec_p; PORTC = 0x00; break;
			}else{
				state = Dec_p; break;
			}
		default:
			state = Start;
			break;	
	};

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	PORTC = 0x00;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}

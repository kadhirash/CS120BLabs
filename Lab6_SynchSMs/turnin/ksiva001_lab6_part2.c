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

enum States {Init, LED1, LED2, LED3} state;

#define A0 (~PINA & 0x01)
#define B PORTB
unsigned char i = 0; // counter variable between LED lights
unsigned char reset = 0; // reset variable 

void Tick(){
	switch(state){
		case Init:
				i = 1;
				B = 0x01; 
				state = LED1; 
			break;

		case LED1:
				if(!A0 && i == 1){ // not pressed (game start)
					i = 2;
					B = 0x02;
					state = LED2;
				}
				else if(A0 && i == 1){ // button pressed (led stops)
					i++;	// increment i counter 
					B = 0x01;	// maintain position
					state = LED1;
				}
				else if(A0 && i > 1){	// button hold (led still stopped)
					i++;
					B = 0x01;
					state = LED1;
				}
				else if(!A0 && i > 1 && reset == 0){ // release after held/reset (led still stopped, but i = 2)
					i = 2;
					B = 0x01;
					state = LED1;
				}
				else if(A0 && i == 2){ // pressed again to reset (Bouncing starts)
					i = 1;
					reset = 1; // set reset
					B = 0x01;
					state = LED1;
				}
				else if(A0 && i >= 2 && reset == 1){ // pressed and held after reset
						i = 12;
						B = 0x01;
						state = LED1;
				}
				else if(A0 && i == 11){
					i == 12;
					reset = 0;
					B = 0x01;
					state = LED2;
				}
				else{
					i = 1;
					B = 0x01;
					state = LED1;
				}
			break;

		case LED2:
				if(!A0 && i == 2){ // not pressed (game start) from LED 1 --> LED 2
					i = 3;
					B = 0x04;
					state = LED3;
				}
				else if(A0 && i == 2){ // button pressed (led stops)
					i++;	// increment i counter
					B = 0x02;	// maintain position
					state = LED2;
				}

				else if(!A0 && i == 22){ // from LED 3 --> LED 2
					i = 1;
					B = 0x01;
					state = LED1;
				}

				else if(A0 && i > 2){ // button hold (led still stopped)
					i++;	// increment i counter
					B = 0x02;	// maintain position
					state = LED2;
				}
				else if(!A0 && i > 1 &&  reset == 0){ // release after held/reset (led still stopped, but i = 3)
					i = 3;
					B = 0x02;
					state = LED2;
				}
				else if(A0 && i == 3){ // pressed again to reset (Bouncing starts)
					i = 1;
					reset = 1;
					B = 0x01;
					state = LED1;
				}
				else if(A0 && i == 12){ // pressed and held after reset
						i = 13;
						B = 0x04;
						state = LED3;
				}
				else if(A0 && i == 22){
					i == 11;
					B = 0x01;
					state = LED1;

				}
				else{
					i = 2;
					B = 0x04;
					state = LED2;
				}
			break;

		case LED3:
			if(!A0 && i == 3){ // not pressed (game start) from LED 2 --> LED 3
				i = 22; // go back to LED 2
				B = 0x02;
				state = LED2;
			}
			else if(A0 && i == 3){ // button pressed (led stops)
				i++;	// increment i counter
				B = 0x04;	// maintain position
				state = LED3;
			}
			else if(A0 && i > 3){  // button hold (led still stopped)
					i ++;
					B = 0x04;
					state = LED3;
			}
			else if(!A0 && i > 1 && reset == 0){  // release after held (led still stopped, but i = 3)
				i = 22;
				B = 0x04;
				state = LED3;
			}
			else if(A0 &&  i == 4){ // pressed again to reset (Bouncing starts)
				i = 1;
				reset = 1;
				B = 0x01;
				state = LED1;
			}
			else if(A0 && i == 13){
				i = 22;
				B = 0x02;
				state = LED2;
				break;
			}
			else{
				i = 3;
				B = 0x04;
				state = LED3;
			}
			break;
		default:
			state = Init; break;
	}
	switch(state){
		case Init:
			B = 0x00; break;
		case LED1:
		case LED2:
		case LED3:
			 break;
		default:
			state = Init;	break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	//unsigned char tmpB = 0x00;
	state = Init;
    /* Insert your solution below */
    while (1) {
	//tmpB = ~tmpB;
	//PORTB = tmpB;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

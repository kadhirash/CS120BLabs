/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 9  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	PWM, 3 buttons to select different tones
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency){
	static double current_frequency;

	if(frequency != current_frequency){
		if(!frequency) { TCCR3B &= 0x08;}
		else{ TCCR3B |= 0x03; }

		if(frequency < 0.954) { OCR3A = 0xFFFF;}

		else if (frequency > 31250) {OCR3A = 0x0000;}

		else { OCR3A = (short) (8000000 / (128 * frequency)) - 1;}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);

	set_PWM(0);
}


void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

enum States{Start, Init, On, Off} state;

#define A (~PINA & 0x07)

void Tick(){
	switch(state){
		case Start:
			state = Init;
			break;
		case Init:
			if(A != 0x00){
				state = On;
			}else{
				state = Init;
			}
			break;
		case On:
			if(A != 0x00){
				state = On;
			}else{
				state = Off;		
			}
			break;
		case Off:
			state = Init;
			break;
		default:
			break;
	}
	switch(state){
		case Start:
			break;
		case Init:
			set_PWM(0);
			break;
		case On:
			if(A == 0x01){
				set_PWM(261.63);
				
			}else if (A == 0x02){
				set_PWM(293.66);
			}else if (A == 0x04){
				set_PWM(329.63);
			}else if (A == 0x03 || A == 0x05 || A == 0x06 || A == 0x07){
				set_PWM(0);
			}
			break;
		case Off:
			set_PWM(0);
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = Start;
	PWM_on();
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}

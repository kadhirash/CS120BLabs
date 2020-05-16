/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 9  Exercise # 2 
 *	Exercise Description: [optional - include for your own benefit]
 *	PWM, 3 buttons and scale up and down sounds
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

enum States{Start, Init, Inc, Dec, Switch, Wait} state;

#define A (~PINA & 0x07)

unsigned short	scale[9] = {	261.63,	// C4
				293.66,	// D4
				329.63, // E4
				349.23, // F4
				392.00, // G4
				440.00, // A4
				493.88, // B4
				523.25 // C5
				}; // the notes
unsigned char turnt = 1; // when switched on or off
unsigned char pos = 0x00; // keep track
unsigned char tempPos = 0x00; // keep track when on/off
void Tick(){
	switch(state){
		case Start:
			state = Init; break;
		case Init:
			if(A == 0x01){
				state = Inc;
			}else if (A == 0x02){
				state = Dec;
			}else if (A == 0x04){
				state = Switch;
			}else{
				state = Init;
			}
			break;
		case Inc:
		case Dec:
		case Switch:
			state = Wait; break;
		case Wait:
			if(!A){
				state = Init;
			}else{
				state = Wait;
			}
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
		case Inc:
			if(pos < 0x07){
				pos++;
			}
			break;
		case Dec:
			if(pos > 0x00){
				pos--;
			}
			break;
		case Switch:
			if(turnt){
				PWM_on();
				pos = tempPos;
			}else{
				PWM_off();
				tempPos = pos;
			}
			turnt = !turnt;
			break;
		case Wait:
			set_PWM(scale[pos]);
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

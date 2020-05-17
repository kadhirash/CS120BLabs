/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 9  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	PWM, 3 buttons and scale up and down sounds
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://drive.google.com/open?id=1b2iNaVUvxpPwRjsxO5hAPqMfVOqR3blz
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"
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

enum States{Start, Init, Play, Wait} state;

#define A (~PINA & 0x07)

unsigned short	scale[26] = {	261.63,	// C4 - mi 
				293.66,	// D4 - re
				329.63, // E4 - do
				293.66, // D4 - re
				261.63, // C4 - me
				261.63,
				261.63,
				293.66,
				293.66,
				293.66,
				261.63,
				349.23,
				349.23,
				261.63,
				293.66,
				329.63,
				293.66,
				261.63,
				261.63,
				261.63,
				261.63,
				293.66,
				293.66,
				261.63,
				293.66,
				329.63
				}; // the notes
unsigned short time[26] = {500, 500, 250, 250, 700, 500, 400, 500, 700,
				500, 500, 250, 250, 700, 400, 300, 200,
				350, 400, 200, 400, 700, 230, 240, 250,
				700};
unsigned char turnt = 1; // when switched on or off
unsigned char pos = 0x00; // keep track
unsigned char tempPos = 0x00; // keep track when on/off
void Tick(){
	switch(state){
		case Start:
			state = Init; break;
		case Init:
			if(A == 0x01){
				state = Play;
			}
			break;
		case Play:
			if(pos == 25 && A){
				state = Wait;
			}else{
				state = Play;
				if(pos == 26){
					set_PWM(0);
					state = Init;
				}
			}
			break;
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
		case Play:
			set_PWM(scale[pos]);
			pos = (pos + 1) % 28;
			break;
		case Wait:
			pos = 0;
			set_PWM(0);
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
	TimerOn();
    /* Insert your solution below */
    while (1) {
	TimerSet(time[pos]);
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

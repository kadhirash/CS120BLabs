/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 10  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	Blinking and 3 LED's, but periods are different now and speaker.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"


enum ThreeLEDsSM{ThreeLEDsStart, ThreeLEDsInit} ThreeLEDsState;
unsigned char threeLEDs = 0x00; // shared variable

void ThreeLEDsSM_Tick(){
	switch(ThreeLEDsState){
		case ThreeLEDsStart:
			ThreeLEDsState = ThreeLEDsInit; break;
		case ThreeLEDsInit:
			break;
		default:
			break;
	}
	switch(ThreeLEDsState){
		case ThreeLEDsStart:
			break;
		case ThreeLEDsInit:
			if(threeLEDs == 0x00){
				threeLEDs = 0x01;
			}else if (threeLEDs == 0x01){
				threeLEDs = 0x02;
			}else if (threeLEDs == 0x02){
				threeLEDs = 0x04;
			}else if (threeLEDs == 0x04){
				threeLEDs = 0x01; 
			}
			break;
		default: 
			break;
	}
}

enum BlinkingLEDSM{BlinkingLEDStart, BlinkingLEDInit} BlinkingLEDState;
unsigned char blinkingLED = 0x01;

void BlinkingLEDSM_Tick(){
	switch(BlinkingLEDState){
		case BlinkingLEDStart:
			BlinkingLEDState = BlinkingLEDInit;
			break;
		case BlinkingLEDInit:
			break;
		default:
			break;
	}
	switch(BlinkingLEDState){
		case BlinkingLEDStart:
			break;
		case BlinkingLEDInit:
			blinkingLED = !blinkingLED; 
			break;
	}
}

enum SpeakerSM{SpeakerStart, SpeakerInit, SpeakerOn, SpeakerOff} SpeakerState;
unsigned char speaker = 0x00;
#define A2 (~PINA & 0x04)

void SpeakerSM_Tick(){
	switch(SpeakerState){
		case SpeakerStart:
			SpeakerState = SpeakerInit; break;
		case SpeakerInit:
			SpeakerState = SpeakerOn; break;
		case SpeakerOff:
			if(A2 == 0x04){
				SpeakerState = SpeakerOn;
			}
			break;
		case SpeakerOn:
			if(A2 != 0x00){
				SpeakerState = SpeakerOff;
			}
			break;
		default:
			break;
	}
	switch(SpeakerState){
		case SpeakerStart:
		case SpeakerInit:
		case SpeakerOff:
			speaker = 0x00; break;
		case SpeakerOn:
			speaker = 0x01; break;
		default:
			break;
	}
}



enum CombineLEDsSM{CombineLEDStart} CombineLEDState;

void CombineLEDsSM_Tick(){
	switch(CombineLEDState){
		case CombineLEDStart:
			break;
		default:
			break;
	}
	switch(CombineLEDState){
		case CombineLEDStart:
			PORTB = threeLEDs | (blinkingLED << 3) | (speaker << 4);
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;
	DDRA = 0x00;	PORTA = 0xFF;
	unsigned short ThreeLEDs_Time = 0;
	unsigned short BlinkingLED_Time = 0;
	unsigned short Speaker_Time = 0;
	const unsigned short period = 2; 


	ThreeLEDsState = ThreeLEDsStart;
	BlinkingLEDState = BlinkingLEDStart;
	CombineLEDState = CombineLEDStart;
	

	TimerSet(2);
	TimerOn();
    /* Insert your solution below */
    while (1) {
	if(ThreeLEDs_Time >= 300){
		ThreeLEDsSM_Tick();
		ThreeLEDs_Time = 0; // reset time 
	}
	if(BlinkingLED_Time >= 1000){
		BlinkingLEDSM_Tick();
		BlinkingLED_Time = 0;
	}
	if(Speaker_Time >= 2){
		SpeakerSM_Tick();
		Speaker_Time = 0;
	}


	CombineLEDsSM_Tick();
		
	while(!TimerFlag);
	TimerFlag = 0;
	ThreeLEDs_Time += period;
	BlinkingLED_Time += period;
	Speaker_Time += period;
    }
    return 1;
}

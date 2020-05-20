/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 10  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	Blinking and 3 LED's, but periods are different now
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
			PORTB = threeLEDs | (blinkingLED << 3);
			break;
		default:
			break;
	}
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;

	unsigned short ThreeLEDs_Time = 0;
	unsigned short BlinkingLED_Time = 0;
	const unsigned short period = 100; // common gcd between 300, 1000


	ThreeLEDsState = ThreeLEDsStart;
	BlinkingLEDState = BlinkingLEDStart;
	CombineLEDState = CombineLEDStart;

	TimerSet(100);
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
	CombineLEDsSM_Tick();
	
	while(!TimerFlag);
	TimerFlag = 0;
	ThreeLEDs_Time += period;
	BlinkingLED_Time += period;
    }
    return 1;
}

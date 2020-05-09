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

enum States {Start, Init, Led_Stop, Led_Bounce, Pause, Restart} state;

#define A0 (~PINA & 0x01)
#define B PORTB

unsigned char press_count; // keep track of presses
unsigned char led_count; // keep track of led

void Tick(){
	switch(state){
		case Start:
			state = Init; break;
		case Init:
			led_count = 1; press_count = 0; B = 0x01; state = Led_Stop; break;
		case Led_Stop:
			if(!A0){
				press_count ++; // when not pressing A0, increment presses
			}
			if (A0 && press_count >= 1){ // only if press count >= 1, go to Pause
				state = Pause;
			}
			else if (led_count == 0){
				B = 0x01; state = Led_Stop; 
			}
			else if (led_count == 1){
				B = 0x02; state = Led_Stop;
			}
			else if (led_count == 2){
				B = 0x04; state = Led_Bounce;
			}
			led_count++; // increment led
			break;
		case Led_Bounce:
			if(!A0){
				press_count ++;
			}
			if (A0 && press_count >= 1){
				state = Pause;
			}
			else if (led_count == 3){
				B = 0x02; state = Led_Bounce; 
			}
			else if (led_count == 4){
				led_count = 0; B = 0x01; state = Led_Stop;  // reset led count back to 0
			} 
			led_count++;
			break;
		case Pause:
			if(A0){
				state = Pause;
			}else {
				state = Restart;
			}
			break;
		case Restart:
			if(A0){
				led_count = 1; press_count = 0; B = 0x01; state = Led_Stop;
			}
			break;
		default:
			state = Start; break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(300);
	TimerOn();
	state = Init;
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

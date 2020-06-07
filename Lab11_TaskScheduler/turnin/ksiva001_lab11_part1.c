/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 11  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	Task scheduler
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "bit.h"
#include "io.c"

#include "io.h"
#include "keypad.h"
#include "scheduler.h"
#include "timer.h"

//------Shared Variables----------
unsigned char key;
//------End Shared Variables------


// Enumeration of states.
enum DisplaySM_States {DisplaySM_output} state;


int DisplaySMTick(int state){
	// Local Variables
	key = GetKeypadKey();
	switch(state){ //State machine transition
		case DisplaySM_output:
			switch(key){
				case '\0': PORTB = 0x1F; 
				case '1': PORTB = 0x01; 
				case '2': PORTB = 0x02;
				case '3': PORTB = 0x03;
				case '4': PORTB = 0x04;
				case '5': PORTB = 0x05;
				case '6': PORTB = 0x06;
				case '7': PORTB = 0x07;
				case '8': PORTB = 0x08;
				case '9': PORTB = 0x09;
				case 'A': PORTB = 0x0A;
				case 'B': PORTB = 0x0B;
				case 'C': PORTB = 0x0C;
				case 'D': PORTB = 0x0D;
				case '*': PORTB = 0x0E;
				case '0': PORTB = 0x00;
				case '#': PORTB = 0x0F;
				default: PORTB = 0x1B; 
			}
			state = DisplaySM_output;
			break;
	}
	return state; 
}


// Implement scheduler code from PES.
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	

	unsigned long int DisplaySMTick_taskCalc = 100; 


	unsigned long int GCD = 2; 

	unsigned long int DisplaySMTick_period = DisplaySMTick_taskCalc;
	

	// Declare an array of tasks
	static task task1;
	task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	
	// Task 1 
	task1.state = 0; // Task initial state.
	task1.period = DisplaySMTick_period; // Task Period.
	task1.elapsedTime = DisplaySMTick_period; // Task current elasped time.
	task1.TickFct = &DisplaySMTick; // Function pointer for the tick.

	
	// Set the timer and turn it on
	TimerSet(GCD);
	TimerOn();

	unsigned short i; // Scheduler for-loop iterator

    /* Insert your solution below */
    while (1) {
	for(i = 0; i < numTasks; i++){ // Scheduler code
		if(tasks[i]->elapsedTime == tasks[i]->period){ // Task is ready to tick
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state); // Set next state
			tasks[i]->elapsedTime = 0; // Reset the elapsed ttime for next tick
		}
		tasks[i]->elapsedTime += 1;
	}
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 0; // Error: Program should not exit!
}

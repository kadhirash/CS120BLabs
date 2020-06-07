/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 11  Exercise # 2
 *	Exercise Description: [optional - include for your own benefit]
 *	Task scheduler with LCD
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
const unsigned char astring[45] = {' ',' ', 'C', 'S', '1', '2', '0', 'B', ' ', 'i', 's',  ' ', 'L', 'e', 'g', 'e', 'n', 'd', '.', '.', '.', ' ','w', 'a', 'i', 't', ' ', 'f', 'o', 'r', ' ', 'i', 't', ' ', 'D', 'A', 'R', 'Y', '!', ' ', ' ', ' ', ' ', ' ', ' '};
unsigned char counter = 1;
//------End Shared Variables------


// Enumeration of states.
enum DisplaySM_States {DisplaySM_output} state;


int DisplaySMTick(int state){
	// Local Variables
	int i = 0;
	switch(state){ //State machine transition
		case DisplaySM_output:
			for(i = 1; i <= 16; i++){
				LCD_Cursor(i);
				LCD_WriteData(astring[counter + i - 2]);
				if(counter + i + 1 == 47){
					counter = 1;
				}
			}
		counter++;
	}		
	return state; 
}


// Implement scheduler code from PES.
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xF0; PORTA = 0x0F;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

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
	LCD_init();
	LCD_ClearScreen();
	unsigned short i; // Scheduler for-loop iterator
    /* Insert your solution below */
    while (1) {
	for(i = 0; i < numTasks; i++){ // Scheduler code
		if(tasks[i]->elapsedTime >= tasks[i]->period){ // Task is ready to tick
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

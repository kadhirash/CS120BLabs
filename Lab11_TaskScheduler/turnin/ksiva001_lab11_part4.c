/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 11  Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	Task scheduler with LCD & Keypad and no refresh
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://drive.google.com/file/d/1ALUjIp30M8cSmzqaSO-VVxtIHicwMzDH/view?usp=sharing
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
unsigned char tempB = 0x00;
unsigned char counter = 1;
//------End Shared Variables------


// Enumeration of states.
enum DisplaySM_States {DisplaySM_output} state;


int DisplaySMTick(int state){
	// Local Variables
	key = GetKeypadKey();
	switch(state){ //State machine transition
		case DisplaySM_output:
			switch(key){
				case '\0': break;
				case '1': tempB = 0x01; 
					  LCD_Cursor(counter);
					  LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '2': tempB = 0x02;
					  LCD_Cursor(counter);
					  LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '3': tempB = 0x03;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '4': tempB = 0x04;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '5': tempB = 0x05;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '6': tempB = 0x06;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '7': tempB = 0x07;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '8': tempB = 0x08;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '9': tempB = 0x09;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case 'A': tempB = 0x0A;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x37); 
					  counter++;
					  break;
				case 'B': tempB = 0x0B;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x37); 
					  counter++;
					  break;
				case 'C': tempB = 0x0C;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x37); 
					  counter++;
					  break;
				case 'D': tempB = 0x0D;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x37); 
					  counter++;
					  break;
				case '*': tempB = 0x0E;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x1C); 
					  counter++;
					  break;
				case '0': tempB = 0x00;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + '0'); 
					  counter++;
					  break;
				case '#': tempB = 0x0F;
					  LCD_Cursor(counter);
                                          LCD_WriteData(tempB + 0x14); 
					  counter++;
					  break;
				default:  tempB = 0x1B; break;
			}
			if(counter == 17){ // counter = Screen length
				counter = 1;
			}
			state = DisplaySM_output;
			PORTB = tempB;
			break;
	}
	return state; 
}


// Implement scheduler code from PES.
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F; // keypad
	DDRD = 0xFF; PORTD = 0x00;	

	unsigned long int DisplaySMTick_taskCalc = 200; 

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
	LCD_DisplayString(1,"Congratulations!");

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

/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 3 Exercise # 5
 *	Exercise Description: Car passenger ports (9 bits)
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0x00; PORTD = 0xFF;	// Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFE; PORTB = 0x01;	// Configure port B's 7 pins outputs and 1 input, initialize to 0s and 1
	unsigned short weight = 0x0000; 	// weight variable (use short since 9 bits and char only holds 8) 
    /* Insert your solution below */
 	while (1){
		weight = (PIND << 1) | (PINB & 0x01); // Shift PIND by 1 since now can compare 8 bits of D and OR it with 1 bit of PINB --> actual weight
		if(weight >= 0x46){
			PORTB = 0x02;	// PB1 = 1
		}
		else if ((weight > 0x05) && (weight <  0x46)){
			PORTB = 0x04;	// PB2 = 1
		}
		else{PORTB = 0x00;}
		weight = 0x0000; 		// reset weight variable
    	}	
	return 1;
}

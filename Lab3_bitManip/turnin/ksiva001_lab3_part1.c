/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 3 Exercise # 1
 *	Exercise Description: Count # of 1's on ports A and B and output to C
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

// Taken from zybooks, section 2.7
// x: 8-bit value, k: bit position to set, range is 0-7.
unsigned char GetBit(unsigned char x, unsigned char k){
	return ((x & (0x01 << k)) != 0);	// Mask with 1 in kth position, then bitwise AND to pass kth bit of x 
						// Returns 1 if kth bit is 1 
 }

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0x00; PORTB = 0xFF;	// Configure port B's 8 pins as inputs, initialize to 1s
	DDRC = 0xFF; PORTC = 0x00;	// Configure port C's 8 pins as outputs, initialize to 0s
	
	unsigned char i = 0x00;
	unsigned char counter_one = 0x00;	// Use a "count" variable to keep track of number of 1s
    /* Insert your solution below */
 	while (1){
		for(i = 0; i < 8; i++){
			counter_one += GetBit(PINA, i) + GetBit(PINB, i); 
		}
		PORTC = counter_one;	// set PORTC to counter_one
		counter_one = 0;	// reset counter_one
    }
    return 1;
}

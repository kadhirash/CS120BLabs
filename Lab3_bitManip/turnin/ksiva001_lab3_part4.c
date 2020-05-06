/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 3 Exercise # 4
 *	Exercise Description: 8 bit value and write to specific ports.
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
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs, initialize to 1s
	DDRB = 0xFF; PORTB = 0x00;	// Configure port B's 8 pins as outputs, initialize to 0s
	DDRC = 0xFF; PORTC = 0x00;	// Configure port C's 8 pins as outputs, intitialize to 0s
    /* Insert your solution below */
 	while (1){
		PORTB = (PINA & 0xF0) >> 4;	// Upper to Lower shift, e.g. 1010 0000 => 0000 1010
		PORTC = (PINA & 0x0F) << 4;	// Lower to Upper shift, e.g. 0000 1100 => 1100 0000	
						// Overall shift, e.g. 1010 1100 => 1100 1010
    	}	
	return 1;
}

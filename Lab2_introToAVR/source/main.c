/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 2  Exercise # 4
 *	Exercise Description: Challenge activity, amusement park.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <stdlib.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF;	// Configure port B's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF;	// Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00;	// Configure port D's 8 pins as outputs
					// Initialize output on PORTC to 0x00
	
	unsigned char actual = 0x00;	// keep track of actual weight
	unsigned char temp = 0x00;
    /* Insert your solution below */
    while (1) {
	actual = PINA+PINB+PINC;
	
	if (actual > 0x8C)  temp |= 0x01;
	if (abs(PINA-PINC) > 0x50) temp |= 0x02;
	
	actual = actual & 0xFC;		// Can bit mask with 1111 1100 so only uses ports D2-D7
	PORTD = actual + temp;
	temp = 0x00;
    }
    return 1;
}

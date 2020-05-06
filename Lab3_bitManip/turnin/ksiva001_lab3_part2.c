/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 3 Exercise # 2
 *	Exercise Description: Car fuel-sensor
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
	DDRC = 0xFF; PORTC = 0x00;	// Configure port C's 8 pins as outputs, initialize to 0s

    /* Insert your solution below */
 	while (1){
		switch(PINA){
			case 0x01 ... 0x02:	// 1 - 2
				PORTC = 0x60;	// 0100 0000
				break;	

			case 0x03 ... 0x04:	// 3 - 4
				PORTC = 0x70;	// 0111 0000
				break; 

			case 0x05 ... 0x06:	// 5 - 6
				PORTC = 0x38;	// 0011 1000
				break;

			case 0x07 ... 0x09:	// 7 - 9
				PORTC = 0x3C;	// 0011 1100
				break;	

			case 0x0A ... 0x0C:	// 10 - 12
				PORTC = 0x3E;	// 0011 1110
				break;				
			
			case 0x0D ... 0x0F:	// 13 - 15
				PORTC = 0x3F;	// 0011 1111
				break;	
			default:
				PORTC = 0x40;
				break;
		}
		
    	}
    return 1;
}

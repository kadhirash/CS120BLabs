/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 2  Exercise # 3
 *	Exercise Description: Challenge activity, amusement park.
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
	DDRA = 0x00; PORTA = 0xFF;	// Configure port A's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00;	// Configure port C's 8 pins as outputs
					// Initialize output on PORTC to 0x00
	
	unsigned char A0 = 0x00; // PC0
	unsigned char A1 = 0x00; // PC1
	unsigned char A2 = 0x00; // PC2
	unsigned char A3 = 0x00; // PC3
	unsigned char cntavail = 4; // count available
    /* Insert your solution below */
    while (1) {
	A0 = PINA & 0x01; // 0000 0001
	A1 = PINA & 0x02; // 0000 0010
	A2 = PINA & 0x04; // 0000 0100
	A3 = PINA & 0x08; // 0000 1000

	
	if( (A0 == 0x01) ){
		cntavail--;
	}
	if( (A1 == 0x02) ){
		cntavail--;
	}
	if( (A2 == 0x04) ){
		cntavail--;
	}
	if( (A3 == 0x08) ){
		cntavail--;
	}
	
	if(cntavail == 0){
		cntavail = 0x80; // 1000 0000
	}
	PORTC = cntavail;
	cntavail = 4; // reset count available variable 
    }
    return 1;
}

/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section:
 *	Assignment: Lab # 5 Exercise # 1
 *	Exercise Description: Lab 3, exercise 2 extension
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
// Demo Link: https://drive.google.com/file/d/1M7Gi1zvruHv9PKZZDhwG6bTmylXqPS4W/view?usp=sharing
//
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

    /* Insert your solution below */
    while (1) {
	switch(~PINA & 0x0F){
		case 0x01 ... 0x02:
			PORTC = 0x60;
			break;
		case 0x03 ... 0x04:
			PORTC = 0x70;
			break;
		case 0x05 ... 0x06:
			PORTC = 0x38;
			break;
		case 0x07 ... 0x09:
			PORTC = 0x3C;
			break;
		case 0x0A ... 0x0C:
			PORTC = 0x3E;
			break;
		case 0x0D ... 0x0F:
			PORTC = 0x3F;
			break;
		default:
			PORTC = 0x40;
			break;
	}	
    }
    return 1;
}

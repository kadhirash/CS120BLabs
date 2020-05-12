/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 8  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
 *	ADC 10 LED
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://drive.google.com/open?id=1vH8Sgf62MOh-WM-uuVmOmLOYfhaJ6ehg
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
	// ADEN: setting this bit enables analog-to-digital conversion.
	// ADSC: setting this bit starts the first conversion.
	// ADATE: setting this bit eneabels auto-triggering. Since we are
	// 		in Free Running Mode, a new conversion will trigger whenever
	// 		the previous conversion completes.
}

unsigned short my_short = 0x00;

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	my_short = ADC; //value of ADC register is now in my_short
	PORTB = (char)my_short;
	PORTD = (char)(my_short >> 8);
    }
    return 1;
}

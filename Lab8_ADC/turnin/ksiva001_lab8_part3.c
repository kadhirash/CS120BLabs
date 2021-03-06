/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 8  Exercise # 3
 *	Exercise Description: [optional - include for your own benefit]
 *	ADC 10 LED photoresister light up only if enough light
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

// Demo: https://drive.google.com/open?id=1lEfFryiF0IWmL5bsvWJNG1gj2K3vcDCd
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
unsigned short MAX = 0x00; // the highest ADC value observed from part 2

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	my_short = ADC; //value of ADC register is now in my_short
	if(my_short > MAX){ // if lowest value > highest
		MAX = my_short; // set real highest value to old highest
	}
	if(my_short >= MAX/2){
		PORTB = 0x01;
	}
	if (my_short < MAX/2){
		PORTB = 0x00;
	}
    }
    return 1;
}

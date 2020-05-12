/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 8  Exercise # 4
 *	Exercise Description: [optional - include for your own benefit]
 *	ADC 8 LED photoresistor light up based on intensity of light
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
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
unsigned short tempB = 0x00; 
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	ADC_init();
    /* Insert your solution below */
    while (1) {
	my_short = ADC; //value of ADC register is now in my_short
	
	if(my_short > MAX){ // if lowest value > highest
		MAX = my_short; // set real highest value to old highest
		tempB = MAX/8; // Divide MAX ADC value by 8 for each LED threshold
	}
	else if(my_short <= tempB){
		PORTB = 0x00;	// none
	}
	else if(my_short <= 2*tempB){
		PORTB = 0x01; // one
	}
	else if (my_short <= 3*tempB){
		PORTB = 0x03; // two
	}
	else if(my_short <= 4*tempB){
		PORTB = 0x07; // three 
	}
	else if(my_short <= 5*tempB){
		PORTB = 0x0F; // four
	}
	else if(my_short <= 6*tempB){
		PORTB = 0x1F; // five
	}
	else if (my_short <= 7*tempB){
		PORTB = 0x3F; // six
	}
	else if (my_short <= 8*tempB){
		PORTB = 0x7F; // seven
	}else {
		PORTB = 0xFF; // all
	}
    }
    return 1;
}

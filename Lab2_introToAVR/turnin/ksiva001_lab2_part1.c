/*	Author: ksiva001
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 21
 *	Assignment: Lab # 2  Exercise # 1
 *	Exercise Description: [optional - include for your own benefit]
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
	DDRB = 0xFF; PORTB = 0x00;	// Configure port B's 8 pins as outputs
					// Initialize output on PORTB to 0x00
	
	unsigned char garage_door_sensor = 0x00; // PA0
	unsigned char light_sensor = 0x00; // PA1
	unsigned char LED = 0x00; // PB0
    /* Insert your solution below */
    while (1) {
	garage_door_sensor = PINA & 0x01;
	light_sensor = PINA & 0x02;
	if((garage_door_sensor == 0x01) && (light_sensor == 0x00)){
		LED = 0x01;
	}else{
		LED = 0x00;
	}
	PORTB = LED;
    }
    return 1;
}

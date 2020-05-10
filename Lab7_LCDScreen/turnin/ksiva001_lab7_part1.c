/*  Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *  Lab Section: 021
 *  Assignment: Lab # 7  Exercise # 1
 *  Exercise Description: 
 *      previous lab extension
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */

// Demo: 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "io.h"
#include "timer.h"
enum States {Start, Init, Inc, Dec, Work} state;

#define A1 (~PINA & 0x01)
#define A2 (~PINA & 0x02)
#define A3 (~PINA & 0x03)
unsigned char timer = 0;
unsigned char counter = 0; // keep track of cursor number
// Inc/Dec as you're holding the state 
void Tick() {
    switch(state) { 
        case Start:
            state = Init; break;
        case Init:
            LCD_Cursor(1);
	    LCD_WriteData('0');
	    state = Work; break;
        case Work:
        	if(A3 == 0x03){ // reset
			counter = 0x00;
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');	
		}
	    	else if(A1 == 0x01){ // inc
        		if(counter < 0x09){
        			counter ++;
        			timer = 0;
        			state = Inc;
        		}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
        	}else if (A2 == 0x02){ //dec
        		if(counter > 0x00){
        			counter --;
        			timer = 0;
        			state = Dec;
        		}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
        	}
        	else{
        		state = Work;
        	}
        	break;
        case Inc:
        	if(A1 == 0x01){
        		timer ++;
        		if(counter < 0x09 && ( (timer % 10) == 0)){
        			counter ++;
        			timer = 0;
        		}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
        	}
        	else {
        		state = Work;
        	}
           	break;
        case Dec:
        	if(A2 == 0x02){
        		timer ++;
        		if(counter > 0x00 && ( (timer % 10) == 0)){
        			counter --;
        			timer = 0;
        		}
			LCD_Cursor(1);
			LCD_WriteData(counter + '0');
        	}
        	else {
        		state = Work;
        	}
           	break;
        default: 
            state = Init; break;
    }
    switch(state) { 
        case Start:
        case Init:
        case Inc:
        case Dec:
	case Work:
        	break;
        default: 
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00; // LCD data lines
    DDRD = 0xFF; PORTD = 0x00; // LCD control lines

    // Initializes the LCD display
    LCD_init();

    TimerSet(100);
    TimerOn();
    /* Insert your solution below */
    while (1) {
    Tick();
    while (!TimerFlag);
    TimerFlag = 0;
    }
    return 1;
}

/*	Author: lab
 *  Partner(s) Name: Kadhirash Sivakumar
 *	Lab Section: 021
 *	Assignment: Lab # 7  Exercise # 2
 *	Exercise Description: 
 *		syncSM to blink 3 LEDs with button press extension with LCD
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
// Demo: 
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include "io.h"
#include "timer.h"

enum States {Start, Init, Led_Stop, Led_Bounce, Pause, Restart} state;

#define A0 (~PINA & 0x01)
#define B PORTB

unsigned char press_count; // keep track of presses
unsigned char led_count; // keep track of led
unsigned char counter = 0;
unsigned char messg[8] = "Winner!!";

void Tick(){
	switch(state){
		case Start:
			state = Init; break;
		case Init:
			led_count = 1; 
			press_count = 0; 
			counter = 5;
			B = 0x01; 
			LCD_Cursor(1);
			LCD_WriteData('5'); // Initial score of 5
			state = Led_Stop; break;
		case Led_Stop:
			if(!A0){
				press_count ++; // when not pressing A0, increment presses
			}
			if (A0 && press_count >= 1){ // only if press count >= 1, go to Pause
				if(B == 0x01 || B == 0x04){
					-- counter ;
					LCD_Cursor(1);
					LCD_WriteData(counter + '0');
				}
				if(B == 0x02){
					++ counter;
					if(counter >= 9){
						LCD_Cursor(1);
						LCD_ClearScreen();
						LCD_DisplayString(1, messg);
					}else{
						LCD_Cursor(1);
						LCD_WriteData(counter + '0');
					}
				}
				state = Pause;
			}
			else if (led_count == 0){
				B = 0x00;	
				state = Led_Stop; 
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
			else if (led_count == 1){
				B = 0x02; 
				state = Led_Stop;
				if(counter >= 9){
					LCD_Cursor(1);
					LCD_ClearScreen();
					LCD_DisplayString(1, messg);	
				}
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
			}
			else if (led_count == 2){
				LCD_Cursor(1);
				LCD_WriteData(counter + '0');
				B = 0x04; 
				state = Led_Bounce;

			}
			led_count++; // increment led
			break;
		case Led_Bounce:
			if(!A0){
				press_count ++;
			}
			if (A0 && press_count >= 1){
				if(B == 0x01 || B == 0x04){
					-- counter;
					LCD_Cursor(1);
					LCD_WriteData(counter + '0');
				}
				if(B == 0x02){
					++ counter;
					if(counter >= 9){
						LCD_Cursor(1);
						LCD_ClearScreen();
						LCD_DisplayString(1, messg);
						break;
					}else{
						LCD_Cursor(1);
						LCD_WriteData(counter + '0');
					}
					
				}
				state = Pause;

			}
			else if (led_count == 3){
				B = 0x02; 
				state = Led_Bounce; 
				 if(counter >= 9){
                                        LCD_Cursor(1);
                                        LCD_ClearScreen();
                                        LCD_DisplayString(1, messg);
                                }
			}
			else if (led_count == 4){
				led_count = 0; 
				B = 0x01; 
				state = Led_Stop;  // reset led count back to 0
			} 
			led_count++;
			break;
		case Pause:
			if(A0){
				state = Pause;
			}
			else {
				state = Restart;
			}
			break;
		case Restart:
			if(A0){
				if (counter >= 9){
					led_count = 1; 
					press_count = 0; 
					B = 0x01; 
					counter = 5;
					LCD_ClearScreen();
					LCD_Cursor(1);
					LCD_WriteData('5');
					state = Led_Stop;
				}
				
				if(counter != 9){
					led_count = 1;
					press_count = 0;
					B = 0x01;
					LCD_Cursor(1);
					LCD_WriteData(counter + '0');
					state = Led_Stop;
				}
			}
			break;
		default:
			state = Start; break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00; // LCD data lines
	DDRD = 0xFF; PORTC = 0x00; // LCD control lines
	// Initializes the data display
	LCD_init();
	TimerSet(300);
	TimerOn();
	//state = Init;
    /* Insert your solution below */
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

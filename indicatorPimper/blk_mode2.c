/*
 * blk_mode1.c
 *
 * Start Development:	24.09.2016 14:13:49
 * Author :		Tropea Salvatore
 * Version:		V a1.00.00
 * Description:		Application to modify the flashing mode of Indicator Lamps in cars.
 *			Blinking_mode 2 provides a dimmable LED to dimm up & down in different modes.
 */

#include "HardwareDef.h"

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Dimm LEDs on and off (Ramp)
int dutyCycle = 0;		    //PWM Value 0-0xff Comparisionvalue
int cycles = 0;			    //Interval in prog. cycles for slow dimm up and down
char direction = 0;		    //Direction of Dimm. 0->up 1->down
char state = 0;			    //State of function
unsigned int interval = 200;	    //interval value (for cycles) default-> ??
unsigned int speed = 5;		    //Speed up value (for dutyCylce increment or decrement) default-> ??

void blk_mode2(){
	TCCR5A = (1 << COM5A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK5 = (1 << TOIE5);
	
	OCR5AL = dutyCycle;
	
	state = 1;
	sei();
	TCCR5B = (1 << CS00);
	OUTPUT = 0x00;
}

//-Interrupt Service Routine for TIM5 Overflow
ISR(TIMER5_OVF_vect)
{
	if (state == 1) //Is blinking active?
	{
		if (cycles < interval) //Wait for cycles as an interval
		{
			cycles++;
		} 
		else
		{
			switch (direction) //Dimm up or down
			{
				case 0: //Dimm up and revert direction when reached max
				dutyCycle = dutyCycle + speed;
				if (dutyCycle >= 255)
				{
					direction = 1;
				}
				break;
			
				case 1: //Dimm down and revert direction when reached min and end ISR
				dutyCycle = dutyCycle - speed;
				if (dutyCycle <= 0)
				{
					direction = 0;
					state = 0;
					dutyCycle = 0;
					cli();
				
				}
				break;
			
				default:
				//Nothing
				break;
			}
			cycles = 0; //Reset interval to 0
		}
		OCR5AL = dutyCycle; //write actual dutyCycle to HW-Register
	}	
	
}
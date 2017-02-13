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
unsigned int interval = 1000;	    //interval value (for cycles) default-> ??
unsigned int speed = 5;		    //Speed up value (for dutyCylce increment or decrement) default-> ??

void blk_mode2(){
	TCCR0 = (1 << WGM00) | (1 << COM01) | (1 << COM00) | (1 << WGM01) | (1 << CS00);
	
	TIMSK = (1 << TOIE0);
	TIFR = (1 << TOV0);
	
	OCR0 = dutyCycle;
	
	
	
	state = 1;
	sei();
	//OUTPUT = 0x00;
}

//-Interrupt Service Routine for TIM5 Overflow
ISR(TIMER0_OVF_vect)
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
				dutyCycle = dutyCycle - speed;
				if (dutyCycle <= 0)
				{
					direction = 1;
				}
				break;
			
				case 1: //Dimm down and revert direction when reached min and end ISR
				dutyCycle = dutyCycle + speed;
				if (dutyCycle > 254)
				{
					direction = 0;
					state = 0;
					dutyCycle = 255;
					cli();
				
				}
				break;
			
				default:
				//Nothing
				break;
			}
			cycles = 0; //Reset interval to 0
		}
		OCR0 = dutyCycle; //write actual dutyCycle to HW-Register
	}	
	
}
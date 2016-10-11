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
int dutyCycle = 0;
int cycles = 0;
void blk_mode2(){
	TCCR5A = (1 << COM5A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK5 = (1 << TOIE5);
	
	OCR5AL = dutyCycle;
	//OCR5AH = ;
	
	sei();
	
	TCCR5B = (1 << CS00);
	
	OUTPUT = 0x01;
	
	while (1)
	{
		
	}
	
}

ISR(TIMER5_OVF_vect)
{
	if (cycles < 150)
	{
		cycles++;
	} 
	else
	{
		dutyCycle = dutyCycle + 5;
		cycles = 0;
	}
	
	OCR5AL = dutyCycle;
}

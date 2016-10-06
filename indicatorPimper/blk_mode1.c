/*
 * blk_mode1.c
 *
 * Start Development:	24.09.2016 14:13:49
 * Author :		Tropea Salvatore
 * Version:		V a1.00.00
 * Description:		Application to modify the flashing mode of Indicator Lamps in cars.
 *			Blinking_mode 1 runs a ProgressBar with 8 LEDs
 */

#include "HardwareDef.h"

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>



void blk_mode1 (){
	
	int pause = 83;
	unsigned char blkSteps [] =  {0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff};
	
	for (unsigned int i = 0; i < sizeof(blkSteps); i++)
	{
		OUTPUT = blkSteps[i];
		_delay_ms(pause);
	}
}

void blk_mode11 (){
	
	int pause = 83*4;
	unsigned char blkSteps [] =  {0x00, 0x0f, 0xff};
	
	for (unsigned int i = 0; i < sizeof(blkSteps); i++)
	{
		OUTPUT = blkSteps[i];
		_delay_ms(pause);
	}
}
//Dimm LEDs on and off (Ramp)
double dutyCycle = 0;

void blk_mode2(){
	TCCR5A = (1 << COM5A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK5 = (1 << TOIE5);
	
	OCR5A = (dutyCycle/100)*255;
	
	sei();
	
	TCCR5B = (1 << CS00);
	
	OUTPUT = 0x01;
	
	while (dutyCycle < 100)
	{
		_delay_ms(100);
		dutyCycle += 10;
	}
	
}

ISR(TIMER5_OVF_vect)
{
	OCR5A = (dutyCycle/100)*255;
}


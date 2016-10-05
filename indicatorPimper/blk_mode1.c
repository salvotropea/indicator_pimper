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

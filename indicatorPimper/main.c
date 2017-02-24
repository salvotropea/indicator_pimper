/*
 * indicatorPimper.c
 *
 * Start Development:	01.03.2017 14:13:49
 * Author :				Tropea Salvatore
 * Version:				V c1.00.00
 * Description:			Application to modify the flashing mode of Indicator Lamps in cars.
 */ 


#include "HardwareDef.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


//--Prototypes declaration
void blk_mode1 ();
void blk_mode11 ();
void blk_mode12 ();
void blk_mode2 ();

//This function initializes the Direction and Value at Startup of the Hardware. 
void initPorts () {
	//--Direction--//
	DDRB = 0xff;	//PortL Output LEDs
	SEL = 0x00;	//PortH Input DIP-Switches
	INPUT = 0x00;	//PortK Input Button1/2/3 & Joystick
	
	//--Startup value--//
	OUTPUT = 0x00;	//All LEDs off
	//PORTK = 0xff;
}

//Release Detection of Blinking state
unsigned char release_detection (char Input){
	if ((Input & 0x04) == 0x04) {
		return 0x01;
	}else
	{
		return 0x00;
	}
}

void (*blink) () = blk_mode1;
void blk_selection () {
	//Untere 4  Bits ausmaskieren
	unsigned char _sel = SEL & 0x0F;
	
	switch (_sel)
	{
		case 0x01:
		blink = blk_mode1;
		break;
		case 0x02:
		blink = blk_mode11;
		break;
		case 0x03:
		blink = blk_mode12;
		break;
		case 0x04:
		blink = blk_mode2;
		break;
		default:
		blink = blk_mode1;
		break;
	}
}

int main(void)
{
	initPorts();
	blk_selection();
	while(1) {
		//Copy Input to have a save State in the next Execution.
		char _input = INPUT;
		
		
		
		if (release_detection(_input) == 0x01)
		{
			blink();
		}else {
			OUTPUT = 0x00;
		}
	}
		
}


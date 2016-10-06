/*
 * indicatorPimper.c
 *
 * Start Development:	24.09.2016 14:13:49
 * Author :		Tropea Salvatore
 * Version:		V a1.00.00
 * Description:		Application to modify the flashing mode of Indicator Lamps in cars.
 */ 


#include "HardwareDef.h"
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


//--Prototypes declaration
void blk_mode1 ();
void blk_mode11 ();
void blk_mode2();

//This function initializes the Direction and Value at Startup of the Hardware. 
void initPorts () {
	//--Direction--//
	DDRL = 0xff;	//PortL Output LEDs
	DDRH = 0x00;	//PortH Input DIP-Switches
	DDRK = 0x00;	//PortK Input Button1/2/3 & Joystick
	
	//--Startup value--//
	PORTL = 0x00;	//All LEDs off
	PORTK = 0xff;
}

//Release Detection of Blinking state
unsigned char release_detection (char Input){
	if ((Input & 0x01) == 0x00) {
		return 0x01;
	}else
	{
		return 0x00;
	}
}

void (*blink) () = blk_mode1;
void blk_selection () {
	switch (SEL)
	{
		case 0x01:
		blink = blk_mode1;
		break;
		case 0x02:
		blink = blk_mode11;
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
			//blink();
			blk_mode2();
		}else {
			OUTPUT = 0x00;
		}
	}
		
}


/*
 * indicatorPimper.c
 *
 * Start Development:	24.09.2016 14:13:49
 * Author :		Tropea Salvatore
 * Version:		V a1.00.00
 * Description:		Application to modify the flashing mode of Indicator Lamps in cars.
 */ 

#define F_CPU 16000000UL
#define led PORTL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

//This function initialiases the Direction and Value at Startup of the Hardware. 
void initPorts () {
	//--Direction--//
	DDRL = 0xff;	//PortL Output LEDs
	DDRH = 0x00;	//PortH Input DIP-Switches
	DDRK = 0x00;	//PortK Input Button1/2/3 & Joystick
	
	//--Startup value--//
	PORTL = 0x00;	//All LEDs off
}

int main(void)
{
	initPorts();
	while(1) {
		led = 0x01;
		_delay_ms(150);
		led = 0x00;	
		_delay_ms(150);
	}
	
}


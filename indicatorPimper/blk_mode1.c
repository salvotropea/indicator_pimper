/*
 * blk_mode1.c
 *
 * Created: 28.09.2016 21:36:42
 *  Author: Tropea
 */ 

#define F_CPU 16000000UL

#define output PORTL

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>



void blk_mode1 (){
	
	int pause = 100;
	
	output = 0x01;
	_delay_ms(pause);
	output = 0x03;
	_delay_ms(pause);
	output = 0x07;
	_delay_ms(pause);
	output = 0x0F;
	_delay_ms(pause);
	output = 0x1F;
	_delay_ms(pause);
	output = 0x3F;
	_delay_ms(pause);
	output = 0x7F;
	_delay_ms(pause);
	output = 0xFF;
	_delay_ms(pause);
}

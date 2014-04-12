#include <stdint.h>

#include "reg24lu1.h"
#include "nrfutils.h"

// this is an example of INT0

// For this to work you have to short P0.2 and P0.3
// A falling edge on P0.2 will cause the ISR to be called.
// This, in turn, will call the ISR which causes a transition on P0.0

// ISR for interrupt on P0.3
void ISR_EXT_INT0(void) __interrupt INTERRUPT_EXT_INT0
{
	// toggle P0.0
	P00 = P00 ? 0 : 1;
}

void main()
{
	P0DIR = 0x08;	// all out except P0.3
	
	P0EXP = 0x00;	// P0.3 INT0
	P0ALT = 0x08;
	
	TCON |= 0x01;	// fire interrupt on falling edge
	IEN0  = 0x81;	// enable interrupts, enable P0.3 interrupt
	
	while (1)
	{
		P02 = 0;
		delay_ms(100);
		P02 = 1;
		delay_ms(100);
	}
}

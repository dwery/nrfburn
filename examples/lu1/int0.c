#include "reg24lu1.h"
#include "utils.h"

// for this to work you have to short P0.2 and P0.3
// a falling edge on P0.2 will cause the ISR to be called
// this will cause a transition on P0.0

// ISR for interrupt on P0.3
void EXT_INT0_ISR(void) __interrupt 0
{
	if (P00 == 0)
		P00 = 1;
	else
		P00 = 0;
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

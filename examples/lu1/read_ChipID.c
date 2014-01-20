#include <stdint.h>

#include "reg24lu1.h"

void delay_us(uint16_t us)
{
	do {
		__asm
		nop
		nop
		nop
		nop
		nop
		__endasm;
	} while (--us);
}

void delay_ms(uint16_t ms)
{
	do {
		delay_us(1000);
	} while (--ms);
}

__xdata volatile uint8_t* pChipID = (__xdata void*) 0x000B;

/*
my CHIPID (large)    = 0x2ADF32E602
my CHIPID (small)    = 0x189E9772D3
my CHIPID (SparkFun) = 0x500737F4C6

0x20 = 0xff number of unprotected pages
0x21 = 0xb0 enable flash data memory (0xff -> no data memory)
0x22 = 0x00 readback blocking byte for InfoPage
			(0xff -> RDISIP=0, any other value RDISIP=1)
0x23 = 0x80 readback blocking byte for MainBlock
			(0xff -> RDISMB=0, any other value RDISMB=1)
0x24 = 0x21 enable debug
			(0xff -> DBG=0, Other value: FSR.DBG=1 if FSR.RDISMB=0, enables HW debug.)
*/

void main()
{
	P0ALT = 0b00000111;	// for master SPI
	P0EXP = 0b00000001;	// for master SPI

	P0DIR = 0x00;		// all out; LED is on P03

	// configure SPI
	SMCTL  = 0x16;	// enable, 1/64 prescaler
	INTEXP = 0x02;
	SPIF = 0;
	I3FR = 1;	// SPIF interrupt does not work without this :)

	for (;;)
	{
		int i;

		// clock it out through SPI
		P03 = 0;
		for (i = 0; i < 5; i++)
		{
			SPIF = 0;
			INFEN = 1;	// activate the info page
			SMDAT = pChipID[i];
			INFEN = 0;	// deactivate the info page
			while (SPIF == 0)
				;
		}
		P03 = 1;

		delay_ms(100);
	}
}

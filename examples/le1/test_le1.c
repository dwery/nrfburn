#include <stdint.h>
#include <stdio.h>

#include "reg24le1.h"
#include "utils.h"

#define BAUD_57K6   1015  // = Round(1024 - (2*16e6)/(64*57600))
#define BAUD_38K4   1011  // = Round(1024 - (2*16e6)/(64*38400))
#define BAUD_19K2    998  // = Round(1024 - (2*16e6)/(64*19200))
#define BAUD_9K6     972  // = Round(1024 - (2*16e6)/(64*9600))

void uart_init(void)
{
	uint16_t temp;

	ES0 = 0;			// Disable UART0 interrupt while initializing
	REN0 = 1;			// Enable receiver
	SM0 = 0;			// Mode 1..
	SM1 = 1;			// ..8 bit variable baud rate
	PCON |= 0x80; 		// SMOD = 1
	ADCON |= 0x80;		// Select internal baud rate generator
	temp = BAUD_57K6;
	//temp = BAUD_38K4;
	//temp = BAUD_9K6;
	//temp = BAUD_19K2;
	S0RELL = (uint8_t)temp;
	S0RELH = (uint8_t)(temp >> 8);
	TI0 = 0;
	//ES0 = 1;			// Enable UART0 interrupt
}

void putchar(char c)
{
	while (TI0 == 0)
		;
    TI0 = 0;
    S0BUF = c;
}

void main()
{
	P0DIR = 0x00;

	//uart_init();
	
	while (1)
	{
		P05 = 1;
		delay_us(500);
		
		P05 = 0;
		delay_us(100);
		
		//printf("asd %i\n", 12);
	}
}

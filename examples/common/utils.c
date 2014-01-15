#include "utils.h"

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

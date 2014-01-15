#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#include "nRF24L.h"
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
	WDCON |= 0x80;		// Select internal baud rate generator
	temp = BAUD_57K6;
	//temp = BAUD_38K4;
	//temp = BAUD_9K6;
	//temp = BAUD_19K2;
	S0RELL = (uint8_t)temp;
	S0RELH = (uint8_t)(temp >> 8);
	P0ALT |= 0x06;		// Select alternate functions on P01 and P02
	P0EXP &= 0xf0;		// Select RxD on P01 and TxD on P02
	P0DIR |= 0x02;		// P01 (RxD) is input
	TI0 = 1;		
	//ES0 = 1;			// Enable UART0 interrupt
}

void putchar(char c)
{
	while (TI0 == 0)
		;
    TI0 = 0;
    S0BUF = c;
}

/*
void main()
{
	// receiver address
	__xdata uint8_t RxAddr[] = {0x34, 0x43, 0x10, 0x10, 0x01};
	
	P0DIR = 0x00;	// all out; LED is on P03

	uart_init();
	printf("here, here");
	P03 = 1;
	
	nRF_Init();

	P03 = 0;
	
	// init the receiver
	nRF_FlushRX();
	nRF_WriteAddrReg(RX_ADDR_P0, RxAddr, 5);
	nRF_WriteReg(RF_SETUP, vRF_DR_250KBPS);	// data rate
	nRF_WriteReg(RX_PW_P0, 7);				// RX payload length
	nRF_WriteReg(EN_RXADDR, vERX_P0);		// enable address
	nRF_WriteReg(RF_CH, 30);				// receiver channel
	nRF_WriteReg(STATUS, vRX_DR | vTX_DS | vMAX_RT);	// reset the IRQ flags
	nRF_WriteReg(CONFIG, vEN_CRC | vCRCO | vPWR_UP | vPRIM_RX);

	P03 = 1;

	// enable the receiver
	nRF_CE_hi();

	P03 = 0;
	while (1)
	{
		if (RFIRQ)
		{
			nRF_ReadRxPayload(7);
			nRF_WriteReg(STATUS, vRX_DR);
			RFIRQ = 0;
			printf("pl=0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", nRF_data[1], nRF_data[2], nRF_data[3], nRF_data[4], nRF_data[5], nRF_data[6], nRF_data[7]);
			P03 = 1;
		} else {
			P00 = (P00 == 1 ? 0 : 1);
		}
	}
}
*/

void main()
{
	P0DIR = 0x00;	// all out; LED is on P03
	
	//uart_init();

	while (1)
	{
		P03 = 1;
		//delay_us(300);

		P03 = 0;
		//delay_us(300);
	}
}

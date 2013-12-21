#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hw_setup.h"
#include "avr_serial.h"
#include "utils.h"
#include "prg_spi.h"
#include "prg_parse.h"
#include "usbdrv.h"

void init_hw(void)
{
	// the LEDs
	SetBit(DDR(LED1_PORT), LED1_BIT);
	ClrBit(PORT(LED1_PORT), LED1_BIT);

	SetBit(DDR(LED2_PORT), LED2_BIT);
	ClrBit(PORT(LED2_PORT), LED2_BIT);

	SetBit(DDR(LED_PROG_PORT), LED_PROG_BIT);
	ClrBit(PORT(LED_PROG_PORT), LED_PROG_BIT);

	uartInit();			// serial port (debugging only)
	
	progParseInit();	// init the programming protocol interface

	ProgSpiInit();			// init the programming hardware (SPI and the rest of the pins)
	
	// setup v-usb
	usbInit();
	usbDeviceDisconnect();	// enforce re-enumeration, do this while interrupts are disabled!
	_delay_ms(260);
	usbDeviceConnect();

	// enable interrupts
	sei();
}

int main(void)
{
	init_hw();
	
	for (;;)
	{
		usbPoll();
		
		progParsePoll();

		/*
		// new character?
		if (uartHasRecvByte())
			progParseSetRxByte(UDR0);

		progParsePoll();

		// anything to send?
		if (progParseGetTxCount())
		{
			// send it all
			int c;
			while ((c = progParseGetTxByte()) != -1)
			{
				loop_until_bit_is_set(UCSR0A, UDRE0);
				UDR0 = c;
			}
		}
		*/
	}
}

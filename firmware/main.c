#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hw_setup.h"
#include "avrdbg.h"
#include "avrutils.h"
#include "prg_spi.h"
#include "prg_parse.h"
#include "usbdrv.h"

void init_hw(void)
{
	// the LEDs
	SetBit(DDR(LED_ERR_PORT), LED_ERR_BIT);
	ClrBit(PORT(LED_ERR_PORT), LED_ERR_BIT);

	SetBit(DDR(LED_PROG_PORT), LED_PROG_BIT);
	ClrBit(PORT(LED_PROG_PORT), LED_PROG_BIT);

	SetBit(DDR(LED_USB_PORT), LED_USB_BIT);
	ClrBit(PORT(LED_USB_PORT), LED_USB_BIT);

	dbgInit();			// init the UART debug output
	
	progParseInit();	// init the programming protocol interface

	ProgSpiInit();		// init the programming hardware (SPI and the rest of the pins)
	
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
		// poll the V-USB library
		usbPoll();

		// turn the USB LED on if we are configured
		if (usbConfiguration != 0)
			SetBit(PORT(LED_USB_PORT), LED_USB_BIT);
		else
			ClrBit(PORT(LED_USB_PORT), LED_USB_BIT);
		
		// handle the requests, and create responses
		progParsePoll();
	}
}

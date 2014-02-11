#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "reg24lu1.h"
#include "utils.h"

#include "usb_defs.h"
#include "usb_desc.h"
#include "usb_regs.h"

hid_report_t kbdRep;

void main()
{
	bool sendReport = false;
	
	P0DIR = 0x00;	// all outputs
	P0ALT = 0x00;	// all GPIO default behavior

	usbInit();
	
	memset(&kbdRep, 0, sizeof kbdRep);

	for (;;)
	{
		usbPoll();	// handles USB interrupts

		/*
		if (usbHasIdleElapsed())
			sendReport = true;

		// send the report if the endpoint is not busy
		if (sendReport  &&  (in1cs & 0x04) == 0)
		{
			// copy the keyboard report into the endpoint buffer
			in1buf[0] = kbdRep.modifiers;
			in1buf[1] = 0;
			in1buf[2] = kbdRep.keys[0];
			in1buf[3] = kbdRep.keys[1];
			in1buf[4] = kbdRep.keys[2];
			in1buf[5] = kbdRep.keys[3];
			in1buf[6] = kbdRep.keys[4];
			in1buf[7] = kbdRep.keys[5];

			// send the data on it's way
			in1bc = 8;
			
			sendReport = false;
		}
		
		if (usbLEDReport & 0x01)
			P01 = 1;
		else
			P01 = 0;

		if (usbLEDReport & 0x02)
			P02 = 1;
		else
			P02 = 0;

		if (usbLEDReport & 0x04)
			P03 = 1;
		else
			P03 = 0;
			*/
	}
}

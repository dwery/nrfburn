#include <stdbool.h>
#include <stdint.h>

#include "reg24lu1.h"
#include "utils.h"

#include "usb_defs.h"
#include "usb_desc.h"

#define USB_EP_DEFAULT_BUF_SIZE		0x20

#define MIN(a, b) ((a) < (b) ? (a) : (b))

volatile __xdata __at (0xC440) uint8_t out5buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC480) uint8_t in5buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC4C0) uint8_t out4buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC500) uint8_t in4buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC540) uint8_t out3buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC580) uint8_t in3buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC5C0) uint8_t out2buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC600) uint8_t in2buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC640) uint8_t out1buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC680) uint8_t in1buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC6C0) uint8_t out0buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC700) uint8_t in0buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC760) uint8_t out8data;
volatile __xdata __at (0xC768) uint8_t in8data;
volatile __xdata __at (0xC770) uint8_t out8bch;
volatile __xdata __at (0xC771) uint8_t out8bcl;
volatile __xdata __at (0xC781) uint8_t bout1addr;
volatile __xdata __at (0xC782) uint8_t bout2addr;
volatile __xdata __at (0xC783) uint8_t bout3addr;
volatile __xdata __at (0xC784) uint8_t bout4addr;
volatile __xdata __at (0xC785) uint8_t bout5addr;
volatile __xdata __at (0xC788) uint8_t binstaddr;
volatile __xdata __at (0xC789) uint8_t bin1addr;
volatile __xdata __at (0xC78A) uint8_t bin2addr;
volatile __xdata __at (0xC78B) uint8_t bin3addr;
volatile __xdata __at (0xC78C) uint8_t bin4addr;
volatile __xdata __at (0xC78D) uint8_t bin5addr;
volatile __xdata __at (0xC7A0) uint8_t isoerr;
volatile __xdata __at (0xC7A2) uint8_t zbcout;
volatile __xdata __at (0xC7A8) uint8_t ivec;
volatile __xdata __at (0xC7A9) uint8_t in_irq;
volatile __xdata __at (0xC7AA) uint8_t out_irq;
volatile __xdata __at (0xC7AB) uint8_t usbirq;
volatile __xdata __at (0xC7AC) uint8_t in_ien;
volatile __xdata __at (0xC7AD) uint8_t out_ien;
volatile __xdata __at (0xC7AE) uint8_t usbien;
volatile __xdata __at (0xC7AF) uint8_t usbbav;
volatile __xdata __at (0xC7B4) uint8_t ep0cs;
volatile __xdata __at (0xC7B5) uint8_t in0bc;
volatile __xdata __at (0xC7B6) uint8_t in1cs;
volatile __xdata __at (0xC7B7) uint8_t in1bc;
volatile __xdata __at (0xC7B8) uint8_t in2cs;
volatile __xdata __at (0xC7B9) uint8_t in2bc;
volatile __xdata __at (0xC7BA) uint8_t in3cs;
volatile __xdata __at (0xC7BB) uint8_t in3bc;
volatile __xdata __at (0xC7BC) uint8_t in4cs;
volatile __xdata __at (0xC7BD) uint8_t in4bc;
volatile __xdata __at (0xC7BE) uint8_t in5cs;
volatile __xdata __at (0xC7BF) uint8_t in5bc;
volatile __xdata __at (0xC7C5) uint8_t out0bc;
volatile __xdata __at (0xC7C6) uint8_t out1cs;
volatile __xdata __at (0xC7C7) uint8_t out1bc;
volatile __xdata __at (0xC7C8) uint8_t out2cs;
volatile __xdata __at (0xC7C9) uint8_t out2bc;
volatile __xdata __at (0xC7CA) uint8_t out3cs;
volatile __xdata __at (0xC7CB) uint8_t out3bc;
volatile __xdata __at (0xC7CC) uint8_t out4cs;
volatile __xdata __at (0xC7CD) uint8_t out4bc;
volatile __xdata __at (0xC7CE) uint8_t out5cs;
volatile __xdata __at (0xC7CF) uint8_t out5bc;
volatile __xdata __at (0xC7D6) uint8_t usbcs;
volatile __xdata __at (0xC7D7) uint8_t togctl;
volatile __xdata __at (0xC7D8) uint8_t usbfrml;
volatile __xdata __at (0xC7D9) uint8_t usbfrmh;
volatile __xdata __at (0xC7DB) uint8_t fnaddr;
volatile __xdata __at (0xC7DD) uint8_t usbpair;
volatile __xdata __at (0xC7DE) uint8_t inbulkval;
volatile __xdata __at (0xC7DF) uint8_t outbulkval;
volatile __xdata __at (0xC7E0) uint8_t inisoval;
volatile __xdata __at (0xC7E1) uint8_t outisoval;
volatile __xdata __at (0xC7E2) uint8_t isostaddr;
volatile __xdata __at (0xC7E3) uint8_t isosize;
volatile __xdata __at (0xC7E8) uint8_t setupbuf[8];
volatile __xdata __at (0xC7F0) uint8_t out8addr;
volatile __xdata __at (0xC7F8) uint8_t in8addr;

static uint8_t usb_current_config;
static usb_state_t usb_state;

static __code const uint8_t* packetizer_data_ptr;
static uint8_t packetizer_data_size;

void usbInit(void)
{
	// disconnect from USB-bus since we are in this routine from a power on and not a soft reset
	usbcs |= 0x08;
	delay_ms(50);
	usbcs &= ~0x08;

	// set up interrupts and clear interrupt flags
	usbien = 0b00011001;	// bit	description
							// 4	uresie	USB reset interrupt enable
							// 3	suspie	USB suspend interrupt enable
							// 2	sutokie	SETUP token interrupt enable
							// 1	sofie	Start of frame interrupt enable
							// 0	sudavie	SETUP data valid interrupt enable
	
	in_ien = 0x01;		// IN interrupt enables for endpoints
	in_irq = 0x1f;		// IN interrupt flags (write 1 to reset)
	out_ien = 0x01;		// OUT interrupt enables
	out_irq = 0x1f;		// OUT interrupt flags (write 1 to reset)

	// setup the USB RAM
	bout1addr = MAX_PACKET_SIZE_EP0/2;
	bout2addr = 0x0000;
	bout3addr = 0x0000;
	bout4addr = 0x0000;
	bout5addr = 0x0000;

	binstaddr = MAX_PACKET_SIZE_EP0/4;	// IN start address

	bin1addr = MAX_PACKET_SIZE_EP0/2;
	bin2addr = 0x0000;
	bin3addr = 0x0000;
	bin4addr = 0x0000;
	bin5addr = 0x0000;

	// set up endpoint interrupts
	inbulkval = 0x03;	// enables IN endpoints on EP0 and EP1
	outbulkval = 0x01;	// enables OUT endpoints on EP0
	inisoval = 0x00;	// ISO not used
	outisoval = 0x00;	// ISO not used
	
	in_ien = 0x03;		// IN0, IN1
	out_ien = 0x01;		// OUT0
}

static void packetizer_isr_ep0_in()
{
	uint8_t size, i;

	if (packetizer_data_size == 0)
	{
		// We are getting a ep0in interrupt when the host sends ACK and do not
		//   have any more data to send
		// Arm the in0bsy bit by writing to byte count reg
		in0bc = 0;
		// ACK the status stage
		USB_EP0_HSNAK();
		return;
	}

	// Send the smallest of the data size and USB RAM EP0 IN size
	size = MIN(packetizer_data_size, MAX_PACKET_SIZE_EP0);

	// Copy data to the USB-controller buffer
	for (i = 0; i < size; ++i)
		in0buf[i] = *packetizer_data_ptr++;

	// Tell the USB-controller how many bytes to send
	// If a IN is received from host after this the USB-controller will send the data
	in0bc = size;

	// update the packetizer data count
	packetizer_data_size -= size;
}

static void usb_process_get_descriptor()
{
	uint8_t descriptor = setupbuf[3];
	packetizer_data_ptr = 0;
	
	if (descriptor == USB_DESC_DEVICE)
	{
		packetizer_data_ptr = (__code uint8_t*) &usb_dev_desc;
	} else if (descriptor == USB_DESC_CONFIGURATION) {
		packetizer_data_ptr = (__code uint8_t*) &usb_conf_desc;
	} else if (descriptor == USB_DESC_STRING) {

		uint8_t string_id = setupbuf[2];
		
		// string index 0 is list of supported lang ids
		if (string_id < USB_STRING_DESC_COUNT)
		{
			if (string_id == 0)
				packetizer_data_ptr = usb_string_desc_0;
			else if (string_id == 1)
				packetizer_data_ptr = (__code uint8_t*) usb_string_desc_1;
			else
				packetizer_data_ptr = (__code uint8_t*) usb_string_desc_2;
		}
	}

	if (packetizer_data_ptr)
	{
		packetizer_data_size = MIN(setupbuf[6], packetizer_data_ptr[0]);
		packetizer_isr_ep0_in();
	} else {
		USB_EP0_STALL();
	}
}

static void usb_std_device_request()
{
	switch (setupbuf[1])		// bRequest
	{
	case USB_REQ_GET_STATUS:
		// We must be in ADDRESSED or CONFIGURED state, and wIndex must be 0
		if ((usb_state == ADDRESSED || usb_state == CONFIGURED)  &&  setupbuf[4] == 0x00)
		{
			// We aren't self-powered and we don't support remote wakeup
			in0buf[0] = 0x00;
			in0buf[1] = 0x00;
			in0bc = 0x02;
		} else {
			// Stall for invalid requests
			USB_EP0_STALL();
		}
		break;

	case USB_REQ_SET_ADDRESS:
		// USB controller takes care of setting our address
		usb_state = ADDRESSED;
		break;

	case USB_REQ_GET_DESCRIPTOR:
		usb_process_get_descriptor();
		break;

	case USB_REQ_GET_CONFIGURATION:
		if ( usb_state == ADDRESSED )
		{
			in0buf[0] = 0x00;
			in0bc = 0x01;
		}
		else if ( usb_state == CONFIGURED )
		{
			in0buf[0] = usb_current_config;
			in0bc = 0x01;
		}
		else
		{
			// Behavior not specified in other states, so STALL
			USB_EP0_STALL();
		}
		break;

	case USB_REQ_SET_CONFIGURATION:
		// setupbuf[2] == wValue
		if ( setupbuf[2] == 0x00 )
		{
			usb_state = ADDRESSED;
			usb_current_config = 0x00;
			// Since there isn't a data stage for this request,
			//   we have to explicitly clear the NAK bit
			USB_EP0_HSNAK();
		}
		else if ( setupbuf[2] == 0x01 )
		{
			usb_state = CONFIGURED;
			usb_current_config = 0x01;
			// Since there isn't a data stage for this request,
			//   we have to explicitly clear the NAK bit
			USB_EP0_HSNAK();
		}
		else
		{
			// Stall for invalid config values
			USB_EP0_STALL();
		}
		break;
	}
}

static void usb_std_endpoint_request()
{
	switch( setupbuf[1] ) // bRequest
	{
	case USB_REQ_GET_STATUS:
		if ( usb_state == CONFIGURED )
		{
			// Return Halt feature status
			if ( setupbuf[4] == 0x81 )
				in0buf[0] = in1cs & 0x01;
			else if ( setupbuf[4] == 0x82 )
				in0buf[0] = in2cs & 0x01;
			else if ( setupbuf[4] == 0x01 )
				in0buf[0] = out1cs & 0x01;
			in0bc = 0x02;
		}
		break;

	default:
		USB_EP0_STALL();
	}
}

static void usb_std_interface_request()
{
	switch( setupbuf[1] ) // bRequest
	{
	case USB_REQ_GET_STATUS:
		if ( usb_state == CONFIGURED )
		{
			// All values are reserved for interfaces
			in0buf[0] = 0x00;
			in0buf[1] = 0x00;
			in0bc = 0x02;
		}
		break;

	default:
		USB_EP0_STALL();
	}
}

static void isr_sudav()
{
	// setupbuf[0] is bmRequestType
	uint8_t requestType = setupbuf[0] & 0x60;

	// if standard request
	if (requestType == 0x00)	
	{
		uint8_t recipient = setupbuf[0] & 0x1f;
		if (recipient == 0)			// device
			usb_std_device_request();
		else if (recipient == 1)	// interface
			usb_std_interface_request();
		else if (recipient == 2)	// endpoint
			usb_std_endpoint_request();
		else
			USB_EP0_STALL();
	} else {
		// stall on unsupported requests
		USB_EP0_STALL();
	}
}

bool usb_irq(void)
{
	bool ret = false;

	switch (ivec)
	{
	case INT_USBRESET:	// Bus reset
		usbirq = 0x10;	// clear interrupt flag
		// Reset internal states
		usb_state = DEFAULT;
		usb_current_config = 0;
		break;
	case INT_SUDAV:		// SETUP data packet
		usbirq = 0x01;	// clear interrupt flag
		// Process setup data
		isr_sudav();
		break;
	/*case INT_SOF:		// Start of Frame packet
		usbirq = 0x02;	// clear interrupt flag
		break;
	case INT_SUTOK:		// Setup token
		usbirq = 0x04;	// clear interrupt flag
		// Clear EP0 IN data pointers
		packetizer_data_ptr = 0;
		packetizer_data_size = 0;*/
		break;
	case INT_SUSPEND:	// SUSPEND signal
		usbirq = 0x08;	// clear interrupt flag
		break;
	case INT_EP0IN:
		in_irq = 0x01;	// clear interrupt flag
		// update USB RAM EP0 IN with new data
		packetizer_isr_ep0_in();
		break;
	case INT_EP0OUT:
		out_irq = 0x01;	// clear interrupt flag
		break;
	case INT_EP1IN:
		in_irq = 0x02;	// clear interrupt flag
		// user code will have already filled IN1 buffer and set byte count
		// USB controller clears busy flag when data is sent
		break;
	case INT_EP1OUT:
		out_irq = 0x02;	// clear interrupt flag
		// Set packet rx flag
		ret = true;
		break;
	}

	return ret;
}

void main()
{
	// All pins inputs
	P0DIR = 0xff;
	// All GPIO default behavior
	P0ALT = 0x00;

	// Initialize USB
	usbInit();

	for (;;)
	{
		// Check for USB interrupt
		if (USBF)
		{
			// Clear USB interrupt
			USBF = 0;

			// Process interrupt
			if ( usb_irq() )
			{
				switch(out1buf[0])
				{
					case 1:
					/*
						// Copy RF data into USB controller RAM
						in1buf[0] = rx_data[0];
						in1buf[1] = rx_data[1];
						in1buf[2] = rx_data[2];
						in1buf[3] = rx_data[3];
						in1buf[4] = rx_cnt;
						*/
						// Setting byte count sets in1cs busy flag
						in1bc = 5;
						break;
					default:
						break;
				}

				// Write to byte count to re-arm EP for next transfer
				out1bc = 0xff;
			}
		}
	}
}

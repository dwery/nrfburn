#include <stdbool.h>
#include <stdint.h>

#include "reg24lu1.h"
#include "utils.h"

#include "usb_defs.h"
#include "usb_desc.h"

#define USB_EP_DEFAULT_BUF_SIZE		0x20

#define MIN(a, b) ((a) < (b) ? (a) : (b))

/*
volatile __xdata __at (0xC440) uint8_t out5buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC480) uint8_t in5buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC4C0) uint8_t out4buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC500) uint8_t in4buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC540) uint8_t out3buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC580) uint8_t in3buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC5C0) uint8_t out2buf[USB_EP_DEFAULT_BUF_SIZE];
volatile __xdata __at (0xC600) uint8_t in2buf[USB_EP_DEFAULT_BUF_SIZE];
*/
volatile __xdata __at (0xC640) uint8_t out1buf[USB_EP1_SIZE];
volatile __xdata __at (0xC680) uint8_t in1buf[USB_EP1_SIZE];
volatile __xdata __at (0xC6C0) uint8_t out0buf[MAX_PACKET_SIZE_EP0];
volatile __xdata __at (0xC700) uint8_t in0buf[MAX_PACKET_SIZE_EP0];
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
volatile __xdata __at (0xC7D8) uint16_t usbframe;
volatile __xdata __at (0xC7D8) uint8_t usbframel;
volatile __xdata __at (0xC7D9) uint8_t usbframeh;
volatile __xdata __at (0xC7DB) uint8_t fnaddr;
volatile __xdata __at (0xC7DD) uint8_t usbpair;
volatile __xdata __at (0xC7DE) uint8_t inbulkval;
volatile __xdata __at (0xC7DF) uint8_t outbulkval;
volatile __xdata __at (0xC7E0) uint8_t inisoval;
volatile __xdata __at (0xC7E1) uint8_t outisoval;
volatile __xdata __at (0xC7E2) uint8_t isostaddr;
volatile __xdata __at (0xC7E3) uint8_t isosize;

// we're overlapping the request with specific request structures
// this makes it a little easier to extract the correct data
volatile __xdata __at (0xC7E8) uint8_t setupbuf[8];
volatile __xdata __at (0xC7E8) usb_request_value_t		usbRequest;
volatile __xdata __at (0xC7E8) usb_req_std_get_desc_t	usbReqGetDesc;
volatile __xdata __at (0xC7E8) usb_req_hid_get_desc_t	usbReqHidGetDesc;

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
							// 5-7	unused
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

void packetizer_isr_ep0_in(void)
{
	uint8_t size, i;

	if (packetizer_data_size == 0)
	{
		// We are getting a ep0in interrupt when the host sends ACK and do not have
		// any more data to send. Arm the in0bsy bit by writing to byte count reg
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

bool hasIdlePassed(uint8_t idleInterval)
{
	static uint16_t started;
	uint16_t passed_ms, currFrame;
	bool retVal = false;
	
	if (idleInterval == 0)
	{
		started = usbframe;
		return retVal;
	}
	
	currFrame = usbframe;
	passed_ms = (currFrame - started) & 0x03ff;
	
	retVal = passed_ms >= idleInterval * 4;
	
	if (retVal)
		started = currFrame;
	
	return retVal;
}

void usb_process_get_descriptor(void)
{
	uint8_t descriptor = usbReqGetDesc.descType;

	packetizer_data_ptr = 0;
	packetizer_data_size = 0;
	
	if (descriptor == USB_DESC_DEVICE)
	{
		packetizer_data_ptr = (__code uint8_t*) &usb_dev_desc;
		packetizer_data_size = MIN(usbReqGetDesc.lengthLSB, packetizer_data_ptr[0]);
	} else if (descriptor == USB_DESC_CONFIGURATION) {
		packetizer_data_ptr = (__code uint8_t*) &usb_conf_desc;
		packetizer_data_size = MIN(usbReqGetDesc.lengthLSB, sizeof usb_conf_desc);
	} else if (descriptor == USB_DESC_STRING) {

		uint8_t string_id = usbReqGetDesc.descIndex;
		
		// string index 0 is list of supported lang ids
		if (string_id < USB_STRING_DESC_COUNT)
		{
			if (usbReqGetDesc.descIndex == 0)
				packetizer_data_ptr = usb_string_desc_0;
			else if (string_id == 1)
				packetizer_data_ptr = (__code uint8_t*) usb_string_desc_1;
			else if (string_id == 2)
				packetizer_data_ptr = (__code uint8_t*) usb_string_desc_2;
			else
				packetizer_data_ptr = (__code uint8_t*) usb_string_desc_3;

			packetizer_data_size = MIN(usbReqGetDesc.lengthLSB, packetizer_data_ptr[0]);
		}
	} else if (descriptor == USB_DESC_HID_REPORT) {
		packetizer_data_ptr = usb_hid_report_descriptor;
		packetizer_data_size = MIN(usbReqGetDesc.lengthLSB, USB_HID_REPORT_DESCRIPTOR_SIZE);
	}

	if (packetizer_data_ptr)
		packetizer_isr_ep0_in();
	else
		USB_EP0_STALL();
}

void usb_std_device_request(void)
{
	switch (usbRequest.bRequest)
	{
	case USB_REQ_GET_STATUS:
		// We must be in ADDRESSED or CONFIGURED state, and wIndex must be 0
		if ((usb_state == ADDRESSED || usb_state == CONFIGURED)  &&  usbRequest.wIndexLSB == 0x00)
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
	
		if (usb_state == ADDRESSED)
		{
			in0buf[0] = 0x00;
			in0bc = 0x01;
		} else if (usb_state == CONFIGURED) {
			in0buf[0] = usb_current_config;
			in0bc = 0x01;
		} else {
			// Behavior not specified in other states, so STALL
			USB_EP0_STALL();
		}

		break;

	case USB_REQ_SET_CONFIGURATION:

		if (usbRequest.wValueLSB == 0x00)
		{
			usb_state = ADDRESSED;
			usb_current_config = 0x00;
			// Since there isn't a data stage for this request,
			//   we have to explicitly clear the NAK bit
			USB_EP0_HSNAK();
		} else if (usbRequest.wValueLSB == 0x01) {
			usb_state = CONFIGURED;
			usb_current_config = 0x01;
			// Since there isn't a data stage for this request,
			//   we have to explicitly clear the NAK bit
			USB_EP0_HSNAK();
		} else {
			// Stall for invalid config values
			USB_EP0_STALL();
		}
		break;
	}
}

void usb_std_endpoint_request(void)
{
	if (usbRequest.bRequest == USB_REQ_GET_STATUS)
	{
		if (usb_state == CONFIGURED)
		{
			// return Halt feature status
			uint8_t endpoint = usbRequest.wIndexLSB;
			if (endpoint == 0x81)
				in0buf[0] = in1cs & 0x01;
			else if (endpoint == 0x82)
				in0buf[0] = in2cs & 0x01;
			else if (endpoint == 0x01)
				in0buf[0] = out1cs & 0x01;

			in0bc = 0x02;
		}
	} else {
		USB_EP0_STALL();
	}
}

void usb_std_interface_request(void)
{
	uint8_t bRequest = usbRequest.bRequest;
	
	if (bRequest == USB_REQ_GET_STATUS)
	{
		if (usb_state == CONFIGURED)
		{
			// all values are reserved for interfaces
			in0buf[0] = 0x00;
			in0buf[1] = 0x00;
			in0bc = 0x02;
		}
	} else if (bRequest == USB_REQ_GET_DESCRIPTOR) {
		// this requests the HID report descriptor
		usb_process_get_descriptor();
	} else {
		USB_EP0_STALL();
	}
}

void usbRequestReceived(void)
{
	uint8_t requestType = usbRequest.bmRequestType & 0x60;

	// reset the ep0 packetizer
	packetizer_data_ptr = 0;
	packetizer_data_size = 0;
	
	if (requestType == 0x00)		// standard request
	{
		uint8_t recipient = usbRequest.bmRequestType & 0x1f;
		if (recipient == 0)			// device
			usb_std_device_request();
		else if (recipient == 1)	// interface
			usb_std_interface_request();
		else if (recipient == 2)	// endpoint
			usb_std_endpoint_request();
		else
			USB_EP0_STALL();
	//} else if (requestType == 0x20) {	// class request
	//} else if (requestType == 0x40) {	// vendor request
	} else {
		// stall on unsupported requests
		USB_EP0_STALL();
	}
}

bool usbPoll(void)
{
	bool ret = false;
	
	if (!USBF)
		return ret;

	// clear USB interrupt
	USBF = 0;

	switch (ivec)
	{
	case INT_SUDAV:		// SETUP data packet
		usbirq = 0x01;	// clear interrupt flag
		usbRequestReceived();	// process setup data
		break;
	/*
	case INT_SOF:		// SOF packet
		usbirq = 0x02;	// clear interrupt flag
		break;
	case INT_SUTOK:		// setup token
		usbirq = 0x04;	// clear interrupt flag
		break;
		*/
	case INT_SUSPEND:	// SUSPEND signal
		usbirq = 0x08;	// clear interrupt flag
		break;
	case INT_USBRESET:	// USB bus reset
		usbirq = 0x10;	// clear interrupt flag
		usb_state = DEFAULT;	// reset internal states
		usb_current_config = 0;
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
		// set packet rx flag
		ret = true;
		break;
	}

	return ret;
}

void main()
{
	P0DIR = 0x00;	// all outputs
	P0ALT = 0x00;	// all GPIO default behavior

	// init the USB controller
	usbInit();	
	
	hasIdlePassed(0);
	
	for (;;)
	{
		usbPoll();
		
		if (hasIdlePassed(10))
			P00 = P00 ? 0 : 1;
	}
}

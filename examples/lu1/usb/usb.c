#include <stdbool.h>
#include <stdint.h>

#include "reg24lu1.h"
#include "nrfutils.h"

#include "usb_defs.h"
#include "usb_desc.h"

#define DEFINE_USB_REGS
#include "usb_regs.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

uint8_t		usb_current_config;
usb_state_t	usb_state;

__code const uint8_t* packetizer_data_ptr;
uint8_t packetizer_data_size;

// We are counting SOF packets as a timer for the HID idle rate.
// usbframel & usbframeh are not good enough for this because of
// difficulty accesing both LSB and MSB in a predictable manner
uint16_t usbFrameCnt = 0;
uint8_t usbHidIdle = 0;			// forever
uint8_t usbLEDReport = 0;
hid_report_t kbdReport;

void usbInit(void)
{
	// disconnect from USB-bus since we are in this routine from a power on and not a soft reset
	usbcs |= 0x08;
	delay_ms(50);
	usbcs &= ~0x08;

	// set up interrupts and clear interrupt flags
	usbien = 0b00011011;	// bit	description
							// 5-7	unused
							// 4	uresie	USB reset interrupt enable
							// 3	suspie	USB suspend interrupt enable
							// 2	sutokie	SETUP token interrupt enable
							// 1	sofie	Start of frame interrupt enable
							// 0	sudavie	SETUP data valid interrupt enable
	
	// we only want to get interrupts for EP0 IN/OUT
	// the other interrupts are not needed (but EP1 IN is still used)
	in_ien = 0x03;		// enable IN interrupts on EP0 and EP1
	in_irq = 0x1f;		// reset IN interrupt flags
	out_ien = 0x01;		// enable OUT interrupts on EP0
	out_irq = 0x1f;		// reset OUT interrupt flags

	// setup the USB RAM
	bout1addr = USB_EP0_SIZE/2;
	bout2addr = bout1addr + 0;
	bout3addr = bout2addr + 0;
	bout4addr = bout3addr + 0;
	bout5addr = bout4addr + 0;

	binstaddr = bout5addr/4;	// IN start address

	bin1addr = USB_EP0_SIZE/2;
	bin2addr = bin1addr + USB_EP1_SIZE/2;
	bin3addr = bin2addr + 0;
	bin4addr = bin3addr + 0;
	bin5addr = bin4addr + 0;

	// enable endpoints
	inbulkval = 0x03;	// enables IN endpoints on EP0 and EP1
	outbulkval = 0x01;	// enables OUT endpoints on EP0
	inisoval = 0x00;	// ISO not used
	outisoval = 0x00;	// ISO not used
}

bool usbHasIdleElapsed(void)
{
	bool retVal;
	
	if (usbHidIdle == 0)
		return false;

	retVal = usbFrameCnt >= usbHidIdle * 4;
	
	if (retVal)
		usbFrameCnt = 0;
	
	return retVal;
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
	size = MIN(packetizer_data_size, USB_EP0_SIZE);

	// Copy data to the USB-controller buffer
	for (i = 0; i < size; ++i)
		in0buf[i] = *packetizer_data_ptr++;

	// Tell the USB-controller how many bytes to send
	// If a IN is received from host after this the USB-controller will send the data
	in0bc = size;

	// update the packetizer data count
	packetizer_data_size -= size;
}

void usbGetDescriptor(void)
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

void usbStdDeviceRequest(void)
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
		usbGetDescriptor();
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

void usbStdEndpointRequest(void)
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

void usbStdInterfaceRequest(void)
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
		usbGetDescriptor();
	} else {
		USB_EP0_STALL();
	}
}

void usbHidRequest(void)
{
	uint8_t bRequest = usbRequest.bRequest;

	if (bRequest == USB_REQ_HID_SET_REPORT)
	{
		// we have to wait for the 1 byte LED report
		// which will come with the next EP0OUT interrupt

	} else if (bRequest == USB_REQ_HID_GET_REPORT) {

		// this requests the HID report we defined with the HID report descriptor.
		// this is usually sent over EP1 IN, but can be sent over EP0 too.

		in0buf[0] = kbdReport.modifiers;
		in0buf[1] = 0;
		in0buf[2] = kbdReport.keys[0];
		in0buf[3] = kbdReport.keys[1];
		in0buf[4] = kbdReport.keys[2];
		in0buf[5] = kbdReport.keys[3];
		in0buf[6] = kbdReport.keys[4];
		in0buf[7] = kbdReport.keys[5];

		// send the data on it's way
		in0bc = 8;
		
	} else if (bRequest == USB_REQ_HID_GET_IDLE) {

		in0buf[0] = usbHidIdle;
		in0bc = 0x01;
	
	} else if (bRequest == USB_REQ_HID_SET_IDLE) {

		usbHidIdle = usbRequest.wValueMSB;
		
		// wValueLSB holds the reportID for which this rate applies,
		// but we only have one, so this does not concern us

		usbFrameCnt = 0;	// reset idle counter

		// send an empty packet and ACK the request
		in0bc = 0x00;
		USB_EP0_HSNAK();
		
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
			usbStdDeviceRequest();
		else if (recipient == 1)	// interface
			usbStdInterfaceRequest();
		else if (recipient == 2)	// endpoint
			usbStdEndpointRequest();
		else
			USB_EP0_STALL();
			
	} else if (requestType == 0x20) {	// class request

		usbHidRequest();
		
	//} else if (requestType == 0x40) {	// vendor request
	} else {
		// stall on unsupported requests
		USB_EP0_STALL();
	}
}

void usbRequestDataReceived(void)
{
	if (usbRequest.bRequest == USB_REQ_HID_SET_REPORT)
		usbLEDReport = out0buf[0];
		
	// send an empty packet and ACK the request
	in0bc = 0x00;
	USB_EP0_HSNAK();
}

void usbPoll(void)
{
	if (!USBIRQ)
		return;

	// clear USB interrupt flag
	USBIRQ = 0;

	switch (ivec)
	{
	case INT_SUDAV:		// SETUP data packet
		usbirq = 0x01;	// clear interrupt flag

		usbRequestReceived();	// process setup data

		// arm the EP0 OUT in case we have data after the request
		out0bc = 0x40;
		
		break;
	case INT_SOF:		// SOF packet
		usbirq = 0x02;	// clear interrupt flag
		++usbFrameCnt;
		break;
	/*
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
		
		usbRequestDataReceived();
		
		// rearm the next EP0 OUT
		out0bc = 0x40;
		break;

	case INT_EP1IN:
		in_irq = 0x02;	// clear interrupt flag
		// user code will have already filled IN1 buffer and set byte count
		// USB controller clears busy flag when data is sent
		
		break;
	case INT_EP1OUT:
		out_irq = 0x02;	// clear interrupt flag
		break;
	}
}

#include <stdint.h>

#include "usb_desc.h"

const usb_dev_desc_t g_usb_dev_desc =
{
	sizeof(usb_dev_desc_t),
	USB_DESC_DEVICE, 
	0x0200,					// bcdUSB
	0x00,					// bDeviceClass		- deferred to interface
	0x00,					// bDeviceSubclass
	0x00,					// bDeviceProtocol
	MAX_PACKET_SIZE_EP0,	// bMaxPacketSize0
	0x0925,					// idVendor - (0x0925) : Lakeview Research
	0x9000,					// idProduct
	0x0001,					// bcdDevice - Device Release Number (BCD)
	0x01,					// iManufacturer
	0x02,					// iProduct
	0x00,					// iSerialNumber
	0x01					// bNumConfigurations
};

//const uint8_t* 

const usb_conf_desc_keyboard_t g_usb_conf_desc = 
{
	// configuration descriptor
	{
		sizeof(usb_conf_desc_t),
		USB_DESC_CONFIGURATION,
		sizeof(usb_conf_desc_keyboard_t),
		1,		// bNumInterfaces
		1,		// bConfigurationValue
		2,		// iConfiguration
		0x80,	// bmAttributes - bus powered, no remote wakeup
		25,		// bMaxPower == 50mA
	},
	// interface descriptor
	{
		sizeof(usb_if_desc_t),
		USB_DESC_INTERFACE,
		0,		// bInterfaceNumber
		0,		// bAlternateSetting
		1,		// bNumEndpoints
		0x03,	// bInterfaceClass		- HID
		0x01,	// bInterfaceSubClass  	- Boot
		0x01,	// bInterfaceProtocol	- Keyboard
		0x00,	// iInterface
	},
	// HID descriptor
	{
		sizeof(usb_hid_desc_t),
		USB_DESC_HID,
		0x0101,					// bcdHID
		0x00,					// bCountryCode
		1,						// bNumDescriptors
		USB_DESC_HID_REPORT,	// bDescriptorType_HID
				// wDescriptorLength
	},
	// endpoint descriptor EP1IN
	{
		sizeof usb_ep_desc_t,
		USB_DESC_ENDPOINT,
		0x81,				// bEndpointAddress
		USB_EP_TYPE_INT,	// bmAttributes
		USB_EP1_SIZE,		// wMaxPacketSize
		0x06				// bInterval
	},
};

#define USB_STRING_IDX_1_DESC "Carson Morrow"

const uint8_t g_usb_string_desc_1[] = 
{
	sizeof(USB_STRING_IDX_1_DESC) * 2, 0x03,
	'C', 00,
	'a', 00,
	'r', 00,
	's', 00,
	'o', 00,
	'n', 00,
	' ', 00,
	'M', 00,
	'o', 00,
	'r', 00,
	'r', 00,
	'o', 00,
	'w', 00
};

#define USB_STRING_IDX_2_DESC "nRF24LU1+ Base Station"
const uint8_t g_usb_string_desc_2[] = 
{
	sizeof(USB_STRING_IDX_2_DESC) * 2, 0x03,
	'n', 00,
	'R', 00,
	'F', 00,
	'2', 00,
	'4', 00,
	'L', 00,
	'U', 00,
	'1', 00,
	'+', 00,
	' ', 00,
	'B', 00,
	'a', 00,
	's', 00,
	'e', 00,
	' ', 00,
	'S', 00,
	't', 00,
	'a', 00,
	't', 00,
	'i', 00,
	'o', 00,
	'n', 00
};

// This is for setting language American English (String descriptor 0 is an array of supported languages):
const uint8_t string_zero[] = {0x04, 0x03, 0x09, 0x04} ;

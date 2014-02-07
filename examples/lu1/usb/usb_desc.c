#include <stdint.h>

#include "usb_desc.h"

__code const usb_dev_desc_t usb_dev_desc =
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
	0x01,					// bNumConfigurations
};

// the default keyboard descriptor - compatible with keyboard boot protocol 
// taken from the HID Descriptor Tool
__code const uint8_t usb_hid_report_descriptor[] =
{
	0x05, 0x01,			// USAGE_PAGE (Generic Desktop)
	0x09, 0x06,			// USAGE (Keyboard)
	0xa1, 0x01,			// COLLECTION (Application)
	0x05, 0x07,			//		USAGE_PAGE (Keyboard)
	0x19, 0xe0,			//		USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,			//		USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,			//		LOGICAL_MINIMUM (0)
	0x25, 0x01,			//		LOGICAL_MAXIMUM (1)
	0x75, 0x01,			//		REPORT_SIZE (1)
	0x95, 0x08,			//		REPORT_COUNT (8)
	0x81, 0x02,			//		INPUT (Data,Var,Abs)
	0x95, 0x01,			//		REPORT_COUNT (1)
	0x75, 0x08,			//		REPORT_SIZE (8)
	0x81, 0x03,			//		INPUT (Cnst,Var,Abs)
	0x95, 0x05,			//		REPORT_COUNT (5)
	0x75, 0x01,			//		REPORT_SIZE (1)
	0x05, 0x08,			//		USAGE_PAGE (LEDs)
	0x19, 0x01,			//		USAGE_MINIMUM (Num Lock)
	0x29, 0x05,			//		USAGE_MAXIMUM (Kana)
	0x91, 0x02,			//		OUTPUT (Data,Var,Abs)
	0x95, 0x01,			//		REPORT_COUNT (1)
	0x75, 0x03,			//		REPORT_SIZE (3)
	0x91, 0x03,			//		OUTPUT (Cnst,Var,Abs)
	0x95, 0x06,			//		REPORT_COUNT (6)
	0x75, 0x08,			//		REPORT_SIZE (8)
	0x15, 0x00,			//		LOGICAL_MINIMUM (0)
	0x25, 0x65,			//		LOGICAL_MAXIMUM (101)
	0x05, 0x07,			//		USAGE_PAGE (Keyboard)
	0x19, 0x00,			//		USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,			//		USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,			//		INPUT (Data,Ary,Abs)
	0xc0,				// END_COLLECTION
};

__code const usb_conf_desc_keyboard_t usb_conf_desc = 
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
		sizeof(usb_hid_report_descriptor),	// wDescriptorLength
	},
	// endpoint descriptor EP1IN
	{
		sizeof(usb_ep_desc_t),
		USB_DESC_ENDPOINT,
		0x81,				// bEndpointAddress
		USB_EP_TYPE_INT,	// bmAttributes
		USB_EP1_SIZE,		// wMaxPacketSize
		0x06,				// bInterval
	},
};

// This is for setting language American English (String descriptor 0 is an array of supported languages):
__code const uint8_t usb_string_desc_0[] = {0x04, 0x03, 0x09, 0x04};

__code const uint16_t usb_string_desc_1[] = 
{
	(sizeof(usb_string_desc_1) << 8) | 0x03,		// length and string descriptor ID
	'F','e','r','e','n','c',' ','S','z','i','l','i'
};

__code const uint16_t usb_string_desc_2[] = 
{
	(sizeof(usb_string_desc_2) << 8) | 0x03,		// length and string descriptor ID
	'U','S','B',' ','K','e','y','b','o','a','r','d',' ','D','e','m','o'
};

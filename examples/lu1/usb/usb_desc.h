#pragma once

typedef struct
{
	uint8_t		bmRequestType;
	uint8_t		bRequest;
	uint16_t	wValue;
	uint16_t	wIndex;
	uint16_t	wLength;
} usb_request_t;

typedef struct
{
	uint8_t		bmRequestType;
	uint8_t		bRequest;
	uint8_t		wValueLSB;
	uint8_t		wValueMSB;
	uint8_t		wIndexLSB;
	uint8_t		wIndexMSB;
	uint8_t		wLengthLSB;
	uint8_t		wLengthMSB;
} usb_request_value_t;

typedef struct
{
	uint8_t		bmRequestType;
	uint8_t		bRequest;
	uint8_t		descIndex;
	uint8_t		descType;
	uint16_t	langID;
	uint8_t		lengthLSB;
	uint8_t		lengthMSB;
} usb_req_std_get_desc_t;

typedef struct
{
	uint8_t		bmRequestType;
	uint8_t		bRequest;
	uint8_t		descIndex;
	uint8_t		descType;
	uint8_t		interface;
	uint8_t		filler;
	uint16_t	wLength;
} usb_req_hid_get_desc_t;

typedef struct
{
	uint8_t		bLength;
	uint8_t		bDescriptorType;
	uint16_t	bcdUSB;
	uint8_t		bDeviceClass;
	uint8_t		bDeviceSubClass;
	uint8_t		bDeviceProtocol;
	uint8_t		bMaxPacketSize0;
	uint16_t	idVendor;
	uint16_t	idProduct;
	uint16_t	bcdDevice;
	uint8_t		iManufacturer;
	uint8_t		iProduct;
	uint8_t		iSerialNumber;
	uint8_t		bNumConfigurations;
} usb_dev_desc_t;

typedef struct
{
	uint8_t		bLength;
	uint8_t		bDescriptorType;
	uint16_t	wTotalLength;
	uint8_t		bNumInterfaces;
	uint8_t		bConfigurationValue;
	uint8_t		iConfiguration;
	uint8_t		bmAttributes;
	uint8_t		bMaxPower;
} usb_conf_desc_t;

typedef struct
{
	uint8_t		bLength;
	uint8_t		bDescriptorType;
	uint8_t		bInterfaceNumber;
	uint8_t		bAlternateSetting;
	uint8_t		bNumEndpoints;
	uint8_t		bInterfaceClass;
	uint8_t		bInterfaceSubClass;
	uint8_t		bInterfaceProtocol;
	uint8_t		iInterface;
} usb_if_desc_t;

typedef struct
{
	uint8_t		bLength;
	uint8_t		bDescriptorType;
	uint8_t		bEndpointAddress;
	uint8_t		bmAttributes;
	uint16_t	wMaxPacketSize;
	uint8_t		bInterval;
} usb_ep_desc_t;

typedef struct
{
	uint8_t		bLength;
	uint8_t		bDescriptorType;
	uint16_t	bcdHID;
	uint8_t		bCountryCode;
	uint8_t		bNumDescriptors;
	uint8_t		bDescriptorType_HID;
	uint16_t	wDescriptorLength;
} usb_hid_desc_t;

typedef struct
{
    usb_conf_desc_t	conf;
    usb_if_desc_t	if0;
    usb_hid_desc_t	hid0;
    usb_ep_desc_t	ep1in;
} usb_conf_desc_keyboard_t;

#define USB_STRING_DESC_COUNT			4
#define USB_HID_REPORT_DESCRIPTOR_SIZE	0x3f

extern __code const usb_conf_desc_keyboard_t usb_conf_desc;
extern __code const usb_dev_desc_t usb_dev_desc;
extern __code const uint8_t  usb_string_desc_0[];
extern __code const uint16_t usb_string_desc_1[];
extern __code const uint16_t usb_string_desc_2[];
extern __code const uint16_t usb_string_desc_3[];
extern __code const uint8_t usb_hid_report_descriptor[USB_HID_REPORT_DESCRIPTOR_SIZE];

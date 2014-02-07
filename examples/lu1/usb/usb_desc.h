#pragma once

#include "usb_defs.h"

#define USB_STRING_DESC_COUNT 2

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

extern const usb_conf_desc_keyboard_t g_usb_conf_desc;
extern const usb_dev_desc_t g_usb_dev_desc;
extern const uint8_t g_usb_string_desc_1[];
extern const uint8_t g_usb_string_desc_2[];
extern const uint8_t string_zero[4];

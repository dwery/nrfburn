#pragma once

#include "usb_defs.h"

#define USB_STRING_DESC_COUNT 2

typedef struct
{
	volatile uint8_t bLength;
	volatile uint8_t bDescriptorType;
	volatile uint16_t bcdUSB;
	volatile uint8_t bDeviceClass;
	volatile uint8_t bDeviceSubClass;
	volatile uint8_t bDeviceProtocol;
	volatile uint8_t bMaxPacketSize0;
	volatile uint16_t idVendor;
	volatile uint16_t idProduct;
	volatile uint16_t bcdDevice;
	volatile uint8_t iManufacturer;
	volatile uint8_t iProduct;
	volatile uint8_t iSerialNumber;
	volatile uint8_t bNumConfigurations;
} usb_dev_desc_t;

typedef struct
{
	volatile uint8_t bLength;
	volatile uint8_t bDescriptorType;
	volatile uint16_t wTotalLength;
	volatile uint8_t bNumInterfaces;
	volatile uint8_t bConfigurationValue;
	volatile uint8_t iConfiguration;
	volatile uint8_t bmAttributes;
	volatile uint8_t bMaxPower;
} usb_conf_desc_t;

typedef struct
{
	volatile uint8_t bLength;
	volatile uint8_t bDescriptorType;
	volatile uint8_t bInterfaceNumber;
	volatile uint8_t bAlternateSetting;
	volatile uint8_t bNumEndpoints;
	volatile uint8_t bInterfaceClass;
	volatile uint8_t bInterfaceSubClass;
	volatile uint8_t bInterfaceProtocol;
	volatile uint8_t iInterface;
} usb_if_desc_t;

typedef struct
{
	volatile uint8_t bLength;
	volatile uint8_t bDescriptorType;
	volatile uint8_t bEndpointAddress;
	volatile uint8_t bmAttributes;
	volatile uint16_t wMaxPacketSize;
	volatile uint8_t bInterval;
} usb_ep_desc_t;

typedef struct
{
	volatile uint8_t bLength;
	volatile uint8_t bDescriptorType;
	volatile uint16_t bcdHID;
	volatile uint8_t bCountryCode;
	volatile uint8_t bNumDescriptors;
	volatile uint8_t bDescriptorType_HID;
	volatile uint16_t wDescriptorLength;
} usb_hid_desc_t;

typedef struct
{
    usb_conf_desc_t conf;
    usb_if_desc_t if0;
    usb_ep_desc_t ep1in;
} usb_conf_desc_keyboard_t;

extern const usb_conf_desc_keyboard_t g_usb_conf_desc;
extern const usb_dev_desc_t g_usb_dev_desc;
extern const uint8_t g_usb_string_desc_1[];
extern const uint8_t g_usb_string_desc_2[];
extern const uint8_t string_zero[4];

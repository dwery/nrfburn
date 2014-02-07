#pragma once

// standard request codes
#define USB_REQ_GET_STATUS         0x00
#define USB_REQ_CLEAR_FEATURE      0x01
#define USB_REQ_SET_FEATURE        0x03
#define USB_REQ_SET_ADDRESS        0x05
#define USB_REQ_GET_DESCRIPTOR     0x06
#define USB_REQ_SET_DESCRIPTOR     0x07
#define USB_REQ_GET_CONFIGURATION  0x08
#define USB_REQ_SET_CONFIGURATION  0x09
#define USB_REQ_GET_INTERFACE      0x0a
#define USB_REQ_SET_INTERFACE      0x0b
#define USB_REQ_SYNCH_FRAME        0x0c

// descriptor types
#define USB_DESC_DEVICE				0x01
#define USB_DESC_CONFIGURATION		0x02
#define USB_DESC_STRING				0x03
#define USB_DESC_INTERFACE			0x04
#define USB_DESC_ENDPOINT			0x05
#define USB_DESC_DEVICE_QUAL		0x06
#define USB_DESC_OTHER_SPEED_CONF	0x07
#define USB_DESC_INTERFACE_POWER	0x08

#define USB_DESC_HID				0x21
#define USB_DESC_HID_REPORT			0x22
#define USB_DESC_HID_PHYS			0x23

// endpoint types
#define USB_EP_TYPE_CTRL		0x00
#define USB_EP_TYPE_ISO			0x01
#define USB_EP_TYPE_BULK		0x02
#define USB_EP_TYPE_INT			0x03

// clear hsnak bit
#define USB_EP0_HSNAK()		ep0cs = 0x02
// set stall and dstall bits to stall during setup data transaction
#define USB_EP0_STALL()		ep0cs = 0x11

// Interrupt codes
#define INT_SUDAV    0x00
#define INT_SOF      0x04
#define INT_SUTOK    0x08
#define INT_SUSPEND  0x0C
#define INT_USBRESET 0x10
#define INT_EP0IN    0x18
#define INT_EP0OUT   0x1C
#define INT_EP1IN    0x20
#define INT_EP1OUT   0x24
#define INT_EP2IN    0x28
#define INT_EP2OUT   0x2C
#define INT_EP3IN    0x30
#define INT_EP3OUT   0x34
#define INT_EP4IN    0x38
#define INT_EP4OUT   0x3C
#define INT_EP5IN    0x40
#define INT_EP5OUT   0x44


#define USB_BM_STATE_CONFIGURED           0x01
#define USB_BM_STATE_ALLOW_REMOTE_WAKEUP  0x02

#define MAX_PACKET_SIZE_EP0		0x20
#define USB_EP1_SIZE			0x80

typedef enum 
{
    ATTACHED,
    POWERED,
    DEFAULT,
    ADDRESSED,
    CONFIGURED,
    SUSPENDED
} usb_state_t;

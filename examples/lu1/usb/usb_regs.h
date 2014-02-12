#pragma once

#ifdef DEFINE_USB_REGS
# define USB_REGS_EXTERN
# define __AT(addr)		__at (addr)
#else
# define USB_REGS_EXTERN extern
# define __AT(addr)
#endif

/*
// we don't use these in our project, 

#define USB_EP_DEFAULT_BUF_SIZE		0x10

USB_REGS_EXTERN volatile __xdata __AT (0xC440) uint8_t out5buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC480) uint8_t in5buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC4C0) uint8_t out4buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC500) uint8_t in4buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC540) uint8_t out3buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC580) uint8_t in3buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC5C0) uint8_t out2buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC600) uint8_t in2buf[USB_EP_DEFAULT_BUF_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC640) uint8_t out1buf[USB_EP_DEFAULT_BUF_SIZE];
*/
USB_REGS_EXTERN volatile __xdata __AT (0xC680) uint8_t in1buf[USB_EP1_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC6C0) uint8_t out0buf[USB_EP0_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC700) uint8_t in0buf[USB_EP0_SIZE];
USB_REGS_EXTERN volatile __xdata __AT (0xC760) uint8_t out8data;
USB_REGS_EXTERN volatile __xdata __AT (0xC768) uint8_t in8data;
USB_REGS_EXTERN volatile __xdata __AT (0xC770) uint8_t out8bch;
USB_REGS_EXTERN volatile __xdata __AT (0xC771) uint8_t out8bcl;
USB_REGS_EXTERN volatile __xdata __AT (0xC781) uint8_t bout1addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC782) uint8_t bout2addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC783) uint8_t bout3addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC784) uint8_t bout4addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC785) uint8_t bout5addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC788) uint8_t binstaddr;
USB_REGS_EXTERN volatile __xdata __AT (0xC789) uint8_t bin1addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC78A) uint8_t bin2addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC78B) uint8_t bin3addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC78C) uint8_t bin4addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC78D) uint8_t bin5addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC7A0) uint8_t isoerr;
USB_REGS_EXTERN volatile __xdata __AT (0xC7A2) uint8_t zbcout;
USB_REGS_EXTERN volatile __xdata __AT (0xC7A8) uint8_t ivec;
USB_REGS_EXTERN volatile __xdata __AT (0xC7A9) uint8_t in_irq;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AA) uint8_t out_irq;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AB) uint8_t usbirq;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AC) uint8_t in_ien;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AD) uint8_t out_ien;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AE) uint8_t usbien;
USB_REGS_EXTERN volatile __xdata __AT (0xC7AF) uint8_t usbbav;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B4) uint8_t ep0cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B5) uint8_t in0bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B6) uint8_t in1cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B7) uint8_t in1bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B8) uint8_t in2cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7B9) uint8_t in2bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BA) uint8_t in3cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BB) uint8_t in3bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BC) uint8_t in4cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BD) uint8_t in4bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BE) uint8_t in5cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7BF) uint8_t in5bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7C5) uint8_t out0bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7C6) uint8_t out1cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7C7) uint8_t out1bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7C8) uint8_t out2cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7C9) uint8_t out2bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CA) uint8_t out3cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CB) uint8_t out3bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CC) uint8_t out4cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CD) uint8_t out4bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CE) uint8_t out5cs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7CF) uint8_t out5bc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7D6) uint8_t usbcs;
USB_REGS_EXTERN volatile __xdata __AT (0xC7D7) uint8_t togctl;
USB_REGS_EXTERN volatile __xdata __AT (0xC7D8) uint8_t usbframel;
USB_REGS_EXTERN volatile __xdata __AT (0xC7D9) uint8_t usbframeh;
USB_REGS_EXTERN volatile __xdata __AT (0xC7DB) uint8_t fnaddr;
USB_REGS_EXTERN volatile __xdata __AT (0xC7DD) uint8_t usbpair;
USB_REGS_EXTERN volatile __xdata __AT (0xC7DE) uint8_t inbulkval;
USB_REGS_EXTERN volatile __xdata __AT (0xC7DF) uint8_t outbulkval;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E0) uint8_t inisoval;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E1) uint8_t outisoval;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E2) uint8_t isostaddr;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E3) uint8_t isosize;

// we're overlapping the request array with specific request structures
// this makes it a little easier to extract the correct data
USB_REGS_EXTERN volatile __xdata __AT (0xC7E8) uint8_t setupbuf[8];
USB_REGS_EXTERN volatile __xdata __AT (0xC7E8) usb_request_value_t		usbRequest;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E8) usb_req_std_get_desc_t	usbReqGetDesc;
USB_REGS_EXTERN volatile __xdata __AT (0xC7E8) usb_req_hid_get_desc_t	usbReqHidGetDesc;

USB_REGS_EXTERN volatile __xdata __AT (0xC7F0) uint8_t out8addr;
USB_REGS_EXTERN volatile __xdata __AT (0xC7F8) uint8_t in8addr;

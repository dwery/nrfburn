#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "reg24lu1.h"
#include "nrfutils.h"

#include "keycode.h"

#include "usb_defs.h"
#include "usb_desc.h"
#include "usb_regs.h"

typedef struct 
{
	uint8_t		keycode;
	uint8_t		modifiers;
} char2keycode_t;

#define MOD_LCTRL	0x01
#define MOD_LSHIFT	0x02

__code const char2keycode_t char2keycode[0x80] = {
	{KC_NO, 0},		// 0x00
	// the next two are special codes for selecting all text in an editor
	// and selecting the current line. this is used for deleting the selected
	// text by 'typing' over it.
	{KC_A, MOD_LCTRL},		// 0x01 ctrl-a
	{KC_HOME, MOD_LSHIFT},	// 0x02 shift-home
	{KC_NO, 0},		// 0x03
	{KC_NO, 0},		// 0x04
	{KC_NO, 0},		// 0x05
	{KC_NO, 0},		// 0x06
	{KC_NO, 0},		// 0x07
	{KC_NO, 0},		// 0x08
	{KC_NO, 0},		// 0x09
	{KC_ENTER, 0},	// 0x0a	\n
	{KC_NO, 0},		// 0x0b
	{KC_NO, 0},		// 0x0c
	{KC_NO, 0},		// 0x0d
	{KC_NO, 0},		// 0x0e
	{KC_NO, 0},		// 0x0f
	{KC_NO, 0},		// 0x10
	{KC_NO, 0},		// 0x11
	{KC_NO, 0},		// 0x12
	{KC_NO, 0},		// 0x13
	{KC_NO, 0},		// 0x14
	{KC_NO, 0},		// 0x15
	{KC_NO, 0},		// 0x16
	{KC_NO, 0},		// 0x17
	{KC_NO, 0},		// 0x18
	{KC_NO, 0},		// 0x19
	{KC_NO, 0},		// 0x1a
	{KC_NO, 0},		// 0x1b
	{KC_NO, 0},		// 0x1c
	{KC_NO, 0},		// 0x1d
	{KC_NO, 0},		// 0x1e
	{KC_NO, 0},		// 0x1f
	{KC_SPACE, 0},	// space
	{KC_1, MOD_LSHIFT},		// !
	{KC_QUOTE, MOD_LSHIFT},	// "
	{KC_3, MOD_LSHIFT},		// #
	{KC_4, MOD_LSHIFT},		// $
	{KC_5, MOD_LSHIFT},		// %
	{KC_7, MOD_LSHIFT},		// &
	{KC_QUOTE, 0},			// '
	{KC_9, MOD_LSHIFT},		// (
	{KC_0, MOD_LSHIFT},		// )
	{KC_KP_ASTERISK, 0},	// *
	{KC_KP_PLUS, 0},		// +
	{KC_COMMA, 0},			// ,
	{KC_KP_MINUS, 0},		// -
	{KC_DOT, 0},			// .
	{KC_KP_SLASH, 0},		// /
	{KC_0, 0},		// 0
	{KC_1, 0},		// 1
	{KC_2, 0},		// 2
	{KC_3, 0},		// 3
	{KC_4, 0},		// 4
	{KC_5, 0},		// 5
	{KC_6, 0},		// 6
	{KC_7, 0},		// 7
	{KC_8, 0},		// 8
	{KC_9, 0},		// 9
	{KC_SCOLON, MOD_LSHIFT},	// :
	{KC_SCOLON, 0},				// ;
	{KC_COMMA, 0},				// <
	{KC_EQUAL, 0},				// =
	{KC_DOT, MOD_LSHIFT},		// >
	{KC_SLASH, MOD_LSHIFT},		// ?
	{KC_2, MOD_LSHIFT},		// @
	{KC_A, MOD_LSHIFT},		// A
	{KC_B, MOD_LSHIFT},		// B
	{KC_C, MOD_LSHIFT},		// C
	{KC_D, MOD_LSHIFT},		// D
	{KC_E, MOD_LSHIFT},		// E
	{KC_F, MOD_LSHIFT},		// F
	{KC_G, MOD_LSHIFT},		// G
	{KC_H, MOD_LSHIFT},		// H
	{KC_I, MOD_LSHIFT},		// I
	{KC_J, MOD_LSHIFT},		// J
	{KC_K, MOD_LSHIFT},		// K
	{KC_L, MOD_LSHIFT},		// L
	{KC_M, MOD_LSHIFT},		// M
	{KC_N, MOD_LSHIFT},		// N
	{KC_O, MOD_LSHIFT},		// O
	{KC_P, MOD_LSHIFT},		// P
	{KC_Q, MOD_LSHIFT},		// Q
	{KC_R, MOD_LSHIFT},		// R
	{KC_S, MOD_LSHIFT},		// S
	{KC_T, MOD_LSHIFT},		// T
	{KC_U, MOD_LSHIFT},		// U
	{KC_V, MOD_LSHIFT},		// V
	{KC_W, MOD_LSHIFT},		// W
	{KC_X, MOD_LSHIFT},		// X
	{KC_Y, MOD_LSHIFT},		// Y
	{KC_Z, MOD_LSHIFT},		// Z
	{KC_LBRACKET, 0},		// [
	{KC_BSLASH, 0},			// backslash
	{KC_RBRACKET, 0},		// ]
	{KC_6, MOD_LSHIFT},		// ^
	{KC_MINUS, MOD_LSHIFT},	// _
	{KC_GRAVE, 0},			// `
	{KC_A, 0},		// a
	{KC_B, 0},		// b
	{KC_C, 0},		// c
	{KC_D, 0},		// d
	{KC_E, 0},		// e
	{KC_F, 0},		// f
	{KC_G, 0},		// g
	{KC_H, 0},		// h
	{KC_I, 0},		// i
	{KC_J, 0},		// j
	{KC_K, 0},		// k
	{KC_L, 0},		// l
	{KC_M, 0},		// m
	{KC_N, 0},		// n
	{KC_O, 0},		// o
	{KC_P, 0},		// p
	{KC_Q, 0},		// q
	{KC_R, 0},		// r
	{KC_S, 0},		// s
	{KC_T, 0},		// t
	{KC_U, 0},		// u
	{KC_V, 0},		// v
	{KC_W, 0},		// w
	{KC_X, 0},		// x
	{KC_Y, 0},		// y
	{KC_Z, 0},		// z
	{KC_LBRACKET, MOD_LSHIFT},	// {
	{KC_BSLASH, MOD_LSHIFT},	// |
	{KC_RBRACKET, MOD_LSHIFT},	// }
	{KC_GRAVE, MOD_LSHIFT},		// ~
	{KC_DELETE, 0},				// 0x7f
};

uint8_t get_keycode_for_char(char c)
{
	uint8_t ndx = c & 0x7f;
	return char2keycode[ndx].keycode;
}

uint8_t get_modifiers_for_char(char c)
{
	uint8_t ndx = c & 0x7f;
	return char2keycode[ndx].modifiers;
}

void main()
{
	bool reportPending = false;
	__code const char* msg = "This is a message that the keyboard will type when scroll lock is activated.";
	__code const char* pMsg = msg;
	uint8_t prev_keycode = KC_NO;
	
	P0DIR = 0x00;	// all outputs
	P0ALT = 0x00;	// all GPIO default behavior

	usbInit();
	
	memset(&kbdReport, 0, sizeof kbdReport);

	for (;;)
	{
		usbPoll();	// handles USB interrupts

		// make a keyboard report
		if (!reportPending  &&  (usbLEDReport & SCROLL_LOCK_MASK) != 0  &&  pMsg)
		{
			char c = *pMsg;

			// get the next char from the stored text message
			uint8_t new_keycode = get_keycode_for_char(c);

			memset(&kbdReport, 0, sizeof kbdReport);	// reset the report
			
			// if the keycode is different than the previous
			// otherwise just send an empty report to simulate key went up
			if (new_keycode != prev_keycode  ||  new_keycode == KC_NO)
			{
				kbdReport.keys[0] = new_keycode;
				kbdReport.modifiers = get_modifiers_for_char(c);

				if (*pMsg == '\0')
					pMsg = NULL;
				else
					++pMsg;
			} else {
				new_keycode = KC_NO;
			}

			prev_keycode = new_keycode;		// remember for later

			reportPending = true;
		} else if ((usbLEDReport & SCROLL_LOCK_MASK) == 0) {
			pMsg = msg;		// rearm for next scroll lock
		}

		// send the report if the endpoint is not busy
		if ((in1cs & 0x02) == 0   &&   (reportPending  ||  usbHasIdleElapsed()))
		{
			// copy the keyboard report into the endpoint buffer
			in1buf[0] = kbdReport.modifiers;
			in1buf[1] = 0;
			in1buf[2] = kbdReport.keys[0];
			in1buf[3] = kbdReport.keys[1];
			in1buf[4] = kbdReport.keys[2];
			in1buf[5] = kbdReport.keys[3];
			in1buf[6] = kbdReport.keys[4];
			in1buf[7] = kbdReport.keys[5];

			// send the data on it's way
			in1bc = 8;
			
			reportPending = false;
		}
	}
}

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include <avr/io.h>

#include "avr_serial.h"

#define BAUD 57600
#include <util/setbaud.h>

void uartPutChar(char c)
{
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

static int uartPutCharStream(char c, FILE *stream)
{
    if (c == '\n')
		uartPutChar('\r');

	uartPutChar(c);
    return 0;
}

uint8_t uartGetChar(void)
{
	loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

static FILE mystdout = FDEV_SETUP_STREAM(uartPutCharStream, NULL, _FDEV_SETUP_WRITE);

void uartInit(void)
{
    // USART Baud rate:
    /*UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;*/
	UBRR0 = 1;

    UCSR0B = _BV(TXEN0) | _BV(RXEN0);
    
    stdout = &mystdout;
}

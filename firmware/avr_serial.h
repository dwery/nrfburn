#pragma once

void uartInit(void);
uint8_t uartGetChar(void);
void uartPutChar(char c);

static inline bool uartHasRecvByte(void)
{
	return UCSR0A & _BV(RXC0);
}

static inline bool uartCanSendByte(void)
{
	return UCSR0A & _BV(UDRE0);
}

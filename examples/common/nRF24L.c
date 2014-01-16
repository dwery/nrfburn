#include <stdint.h>

#include "nRF24L.h"

__xdata uint8_t nRF_data[MAX_COMMAND_LENGTH];

#ifdef AVR

void nRF_Init(void)
{
#ifdef NRF_PWR_PORT
	// the 3.3v voltage regulator
	SetBit(DDR(NRF_PWR_PORT), NRF_PWR_BIT);
	ClrBit(PORT(NRF_PWR_PORT), NRF_PWR_BIT);

	nRF_Reset();
#endif

	ClrBit(DDR(NRF_IRQ_PORT), NRF_IRQ_BIT);		// input pin
	SetBit(PORT(NRF_IRQ_PORT), NRF_IRQ_BIT);	// enable pull-up

	// if SS pin is defined, set it as output
	// to prevent SPI going into slave mode
#ifdef NRF_SS_PORT
	SetBit(DDR(NRF_SS_PORT), NRF_SS_BIT);
#endif	
	
	// set the CSN and CE as output pins
	SetBit(DDR(NRF_CSN_PORT), NRF_CSN_BIT);
	SetBit(DDR(NRF_CE_PORT), NRF_CE_BIT);

	// set these to default states
    nRF_CE_lo();
    nRF_CSN_hi();

	// init SPI pins
    SetBit(DDR(NRF_MOSI_PORT), NRF_MOSI_BIT);	// outputs
    SetBit(DDR(NRF_SCK_PORT), NRF_SCK_BIT);
	ClrBit(DDR(NRF_MISO_PORT), NRF_MISO_BIT);	// input

	// enable SPI in Master Mode with SCK = CK/4
	SetVal(SPCR, _BV(SPE) | _BV(MSTR));

	SPSR;	// clear SPIF bit in SPSR
	SPDR;
}

#else

void nRF_Init(void)
{
# ifdef NRF24LU1
	RFCTL = 0x11;	// enable SPI, 1/2 clock
# endif

	// nRF24LE1 has the internal SPI always enabled

	RFCON = 0x04;	// enable RF clock, CSN low, CE low
}

#endif

static uint8_t nRF_SpiShiftByte(uint8_t byte)
{
#ifdef AVR		
	SPDR = byte;			// set byte to send the nRF through MOSI
	loop_until_bit_is_set(SPSR, SPIF);	// wait until char is sent
	byte = SPDR;			// remember the byte received from nRF through MISO
#else

# ifdef NRF24LE1

	SPIRDAT = byte;			// set byte to send the nRF through the internal MOSI
	
	// wait while there is data in the internal SPI fifo
	while ((SPIRSTAT & (uint8_t)0x02U) == 0)
		;
		
	byte = SPIRDAT;			// remember the byte received from nRF through MISO
	
# elif defined(NRF24LU1)

	RFDAT = byte;			// set byte to send the nRF through the internal MOSI
	RFSPIF = 0;				// reset the RF SPI interrupt flag
	while ( !RFSPIF );		// wait for byte to finish
	byte = RFDAT;			// remember the byte received from nRF through MISO
	
# endif

#endif		

	return byte;
}

static uint8_t nRF_ShiftCommand(uint8_t cmd_len)
{
	uint8_t* pData = nRF_data;
	
	nRF_CSN_lo();

	while (cmd_len > 0)
	{
		*pData = nRF_SpiShiftByte(*pData);
		++pData;
		--cmd_len;
	}

	nRF_CSN_hi();

	// return status register
	return *nRF_data;
}

uint8_t nRF_ShiftByte(const uint8_t one_byte)
{
	nRF_CSN_lo();

	// remember the byte received from nRF through miso
	*nRF_data = nRF_SpiShiftByte(one_byte);

	nRF_CSN_hi();

	// return the STATUS register
	return *nRF_data;
}

uint8_t nRF_ReadReg(const enum nRFRegister_e reg)
{
	nRF_data[0] = R_REGISTER | reg;

	return nRF_ShiftCommand(2);
}

uint8_t nRF_WriteReg(const enum nRFRegister_e reg, const uint8_t val)
{
	nRF_data[0] = W_REGISTER | reg;
	nRF_data[1] = val;

	return nRF_ShiftCommand(2);
}

uint8_t nRF_WriteAddrReg(const enum nRFRegister_e reg, const __xdata uint8_t* addr, const uint8_t addr_len)
{
	uint8_t c;
	
	nRF_data[0] = W_REGISTER | reg;

	// set the data to be sent
	for (c = 0; c < addr_len; c++)
		nRF_data[1 + c] = addr[c];

	return nRF_ShiftCommand(addr_len + 1);
}

uint8_t nRF_ReadAddrReg(const enum nRFRegister_e reg, const uint8_t addr_len)
{
	nRF_data[0] = R_REGISTER | reg;

	return nRF_ShiftCommand(addr_len + 1);
}

uint8_t nRF_ReadRxPayload(const uint8_t num_bytes)
{
	nRF_data[0] = R_RX_PAYLOAD;

	return nRF_ShiftCommand(num_bytes + 1);
}

uint8_t nRF_WriteTxPayload(const uint8_t* payload, const uint8_t num_bytes)
{
	uint8_t c;
	
	nRF_data[0] = W_TX_PAYLOAD;

	// set the data to be sent
	for (c = 0; c < num_bytes; c++)
		nRF_data[1 + c] = payload[c];

	return nRF_ShiftCommand(num_bytes + 1);
}

uint8_t nRF_FlushTX(void)
{
	return nRF_ShiftByte(FLUSH_TX);
}

uint8_t nRF_FlushRX(void)
{
	return nRF_ShiftByte(FLUSH_RX);
}

uint8_t nRF_NOP(void)
{
	return nRF_ShiftByte(NOP);
}

uint8_t nRF_ReadRxPayloadWidth(void)
{
	nRF_data[0] = R_RX_PL_WID;

	return nRF_ShiftCommand(2);
}

uint8_t nRF_WriteAckPayload(const uint8_t* payload, const uint8_t num_bytes, const uint8_t pipe_num)
{
	uint8_t c;

	nRF_data[0] = W_ACK_PAYLOAD | pipe_num;

	// set the data to be sent
	for (c = 0; c < num_bytes; c++)
		nRF_data[1 + c] = payload[c];

	return nRF_ShiftCommand(num_bytes + 1);
}

#ifdef NRF_PWR_PORT

void nRF_Reset(void)
{
	// First turn off all the output pins and the pull-up resistors of the input pins
	// of the ATmega that are used to communicate with the nRF module.
	// If these are left on, the nRF will not reset. I am not sure why this is, but
	// I'm guessing it's because in this case the nRF chip is powered through the pull-up
	// resistors on the input pins of the nRF.

	ClrBit(PORT(NRF_IRQ_PORT), NRF_IRQ_BIT);		// pull-up
	ClrBit(PORT(NRF_CE_PORT), NRF_CE_BIT);			// output
	ClrBit(PORT(NRF_CSN_PORT), NRF_CSN_BIT);		// output
	ClrBit(PORT(NRF_MOSI_PORT), NRF_MOSI_BIT);		// output
	ClrBit(PORT(NRF_MISO_PORT), NRF_MISO_BIT);		// pull-up
	ClrBit(PORT(NRF_SCK_PORT), NRF_SCK_BIT);		// output

	// Now turn the voltage regulator off
	ClrBit(PORT(NRF_PWR_PORT), NRF_PWR_BIT);

	// Wait for the voltage regulator output filtering capacitor to discharge.
	// I got this duration using the program below
	_delay_ms(200);

	// turn the pull-ups and the outputs back on
	SetBit(PORT(NRF_IRQ_PORT), NRF_IRQ_BIT);		// pull-up
	ClrBit(PORT(NRF_MOSI_PORT), NRF_MOSI_BIT);		// output
	SetBit(PORT(NRF_MISO_PORT), NRF_MISO_BIT);		// pull-up
	ClrBit(PORT(NRF_SCK_PORT), NRF_SCK_BIT);		// output

    nRF_CE_lo();
    nRF_CSN_hi();

	// turn the voltage regulator back on
	SetBit(PORT(NRF_PWR_PORT), NRF_PWR_BIT);

	// wait for the chip to wake up and the voltage to stabilize
	_delay_ms(50);
}

#endif	// NRF_PWR_PORT

/*
// this can be used to find the duration that is necessary to keep the nRF's
// voltage regulator in the off state to reset the nRF chip.
void main(void)
{
	init_serial();	// UART is currently only used for debugging
	init_hw();
	nRF_Init();

	// the main send loop
	const uint8_t TestAddr[] = {0x12, 0x34, 0x56, 0x78, 0x90};
	const uint16_t MAX_LOOP = 50;

	uint16_t ms_off, cloop;
	uint8_t reset, not_reset;

	for (ms_off = 110; ms_off < 500; ms_off++)
	{
		printf("testing with: %4ums  ", ms_off);

		reset = not_reset = 0;

		for (cloop = 0; cloop < MAX_LOOP  &&  not_reset < 5; cloop++)
		{
			nRF_WriteAddrReg(TX_ADDR, TestAddr, 5);	// write the address

			nRF_Reset(ms_off);

			nRF_ReadAddrReg(TX_ADDR, 5);			// read the address back

			if (nRF_data[1] == TestAddr[0])
				++not_reset;
			else
				++reset;
		}

		printf("reset/NOT reset: %u/%u\n", reset, not_reset);

		if (not_reset == 0)
			break;
	}

	if (not_reset != 0)
		printf("off duration not found. Increse upper limit of ms_off loop value\n");
	else
		printf("Off duration found: %ums\n", ms_off);

	for (;;)
		;
}
*/

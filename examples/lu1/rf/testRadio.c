#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "reg24lu1.h"
#include "nrfutils.h"
#include "nrfdbg.h"

#include "nRF24L.h"

void main()
{
	// receiver address
	__code uint8_t RxAddr[] = {0x34, 0x43, 0x10, 0x10, 0x01};
	
	P0DIR = 0x00;	// all out; LED is on P03

	uartInit();
	printf("here, here");
	P03 = 1;
	
	nRF_Init();

	P03 = 0;
	
	// init the receiver
	nRF_FlushRX();
	nRF_WriteAddrReg(RX_ADDR_P0, RxAddr, 5);
	nRF_WriteReg(RF_SETUP, vRF_DR_250KBPS);	// data rate
	nRF_WriteReg(RX_PW_P0, 7);				// RX payload length
	nRF_WriteReg(EN_RXADDR, vERX_P0);		// enable address
	nRF_WriteReg(RF_CH, 30);				// receiver channel
	nRF_WriteReg(STATUS, vRX_DR | vTX_DS | vMAX_RT);	// reset the IRQ flags
	nRF_WriteReg(CONFIG, vEN_CRC | vCRCO | vPWR_UP | vPRIM_RX);

	P03 = 1;

	// enable the receiver
	nRF_CE_hi();

	P03 = 0;
	while (1)
	{
		if (RFIRQ)
		{
			nRF_ReadRxPayload(7);
			nRF_WriteReg(STATUS, vRX_DR);
			RFIRQ = 0;
			printf("pl=0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", nRF_data[1], nRF_data[2], nRF_data[3], nRF_data[4], nRF_data[5], nRF_data[6], nRF_data[7]);
			P03 = 1;
		} else {
			P00 = (P00 == 1 ? 0 : 1);
		}
	}
}

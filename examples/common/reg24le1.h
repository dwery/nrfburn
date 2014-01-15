#pragma once

//-----------------------------------------------------------------------------
// Byte Registers
//-----------------------------------------------------------------------------

__sfr __at 0x80 P0;
__sfr __at 0x81 SP;
__sfr __at 0x82 DPL;
__sfr __at 0x83 DPH;
__sfr __at 0x84 DPL1;
__sfr __at 0x85 DPH1;
__sfr __at 0x87 PCON;
__sfr __at 0x88 TCON;
__sfr __at 0x89 TMOD;
__sfr __at 0x8A TL0;
__sfr __at 0x8B TL1;
__sfr __at 0x8C TH0;
__sfr __at 0x8D TH1;
__sfr __at 0x8F P3CON;
__sfr __at 0x90 P1;
__sfr __at 0x92 DPS;
__sfr __at 0x93 P0DIR;
__sfr __at 0x94 P1DIR;
__sfr __at 0x95 P2DIR;
__sfr __at 0x96 P3DIR;
__sfr __at 0x97 P2CON;
__sfr __at 0x98 S0CON;
__sfr __at 0x99 S0BUF;
__sfr __at 0x9E P0CON;
__sfr __at 0x9F P1CON;
__sfr __at 0xA0 P2;
__sfr __at 0xA1 PWMDC0;
__sfr __at 0xA2 PWMDC1;
__sfr __at 0xA3 CLKCTRL;
__sfr __at 0xA4 PWRDWN;
__sfr __at 0xA5 WUCON;
__sfr __at 0xA6 INTEXP;
__sfr __at 0xA7 MEMCON;
__sfr __at 0xA8 IEN0;
__sfr __at 0xA9 IP0;
__sfr __at 0xAA S0RELL;
__sfr __at 0xAB RTC2CPT01;
__sfr __at 0xAC RTC2CPT10;
__sfr __at 0xAD CLKLFCTRL;
__sfr __at 0xAE OPMCON;
__sfr __at 0xAF WDSV;
__sfr __at 0xB0 P3;
__sfr __at 0xB1 RSTREAS;
__sfr __at 0xB2 PWMCON;
__sfr __at 0xB3 RTC2CON;
__sfr __at 0xB4 RTC2CMP0;
__sfr __at 0xB5 RTC2CMP1;
__sfr __at 0xB6 RTC2CPT00;
__sfr __at 0xB7 SPISRDSZ;
__sfr __at 0xB8 IEN1;
__sfr __at 0xB9 IP1;
__sfr __at 0xBA S0RELH;
__sfr __at 0xBC SPISCON0;
__sfr __at 0xBD SPISCON1;
__sfr __at 0xBE SPISSTAT;
__sfr __at 0xBF SPISDAT;
__sfr __at 0xC0 IRCON;
__sfr __at 0xC1 CCEN;
__sfr __at 0xC2 CCL1;
__sfr __at 0xC3 CCH1;
__sfr __at 0xC4 CCL2;
__sfr __at 0xC5 CCH2;
__sfr __at 0xC6 CCL3;
__sfr __at 0xC7 CCH3;
__sfr __at 0xC8 T2CON;
__sfr __at 0xC9 MPAGE;
__sfr __at 0xCA CRCL;
__sfr __at 0xCB CRCH;
__sfr __at 0xCC TL2;
__sfr __at 0xCD TH2;
__sfr __at 0xCE WUOPC1;
__sfr __at 0xCF WUOPC0;
__sfr __at 0xD0 PSW;
__sfr __at 0xD1 ADCCON3;
__sfr __at 0xD2 ADCCON2;
__sfr __at 0xD3 ADCCON1;
__sfr __at 0xD4 ADCDATH;
__sfr __at 0xD5 ADCDATL;
__sfr __at 0xD6 RNGCTL;
__sfr __at 0xD7 RNGDAT;
__sfr __at 0xD8 ADCON;
__sfr __at 0xD9 W2SADR;
__sfr __at 0xDA W2DAT;
__sfr __at 0xDB COMPCON;
__sfr __at 0xDC POFCON;
__sfr __at 0xDD CCPDATIA;
__sfr __at 0xDE CCPDATIB;
__sfr __at 0xDF CCPDATO;
__sfr __at 0xE0 ACC;
__sfr __at 0xE1 W2CON1;
__sfr __at 0xE2 W2CON0;
__sfr __at 0xE4 SPIRCON0;
__sfr __at 0xE5 SPIRCON1;
__sfr __at 0xE6 SPIRSTAT;
__sfr __at 0xE7 SPIRDAT;
__sfr __at 0xE8 RFCON;
__sfr __at 0xE9 MD0;
__sfr __at 0xEA MD1;
__sfr __at 0xEB MD2;
__sfr __at 0xEC MD3;
__sfr __at 0xED MD4;
__sfr __at 0xEE MD5;
__sfr __at 0xEF ARCON;
__sfr __at 0xF0 B;
__sfr __at 0xF8 FSR;
__sfr __at 0xF9 FPCR;
__sfr __at 0xFA FCR;
__sfr __at 0xFB FDCR;
__sfr __at 0xFC SPIMCON0;
__sfr __at 0xFD SPIMCON1;
__sfr __at 0xFE SPIMSTAT;
__sfr __at 0xFF SPIMDAT;

//-----------------------------------------------------------------------------
// Word Registers
//-----------------------------------------------------------------------------

__sfr16 __at 0xC3C2 CC1;
__sfr16 __at 0xC5C4 CC2;
__sfr16 __at 0xC7C6 CC3;
__sfr16 __at 0xCBCA CRC;
__sfr16 __at 0xCDCC T2;


//  FSR
__sbit __at 0xFF DBG;
__sbit __at 0xFE STP;
__sbit __at 0xFD WEN;
__sbit __at 0xFC RDYN;
__sbit __at 0xFB INFEN;
__sbit __at 0xFA RDISMB;

// PSW
__sbit __at 0xD7 CY;
__sbit __at 0xD6 AC;
__sbit __at 0xD5 F0;
__sbit __at 0xD4 RS1;
__sbit __at 0xD3 RS0;
__sbit __at 0xD2 OV;
__sbit __at 0xD0 P;


// TCON
__sbit __at 0x8F TF1;
__sbit __at 0x8E TR1;
__sbit __at 0x8D TF0;
__sbit __at 0x8C TR0;
__sbit __at 0x8B IE1;
__sbit __at 0x8A IT1;
__sbit __at 0x89 IE0;
__sbit __at 0x88 IT0;

// S0CON
__sbit __at 0x9F SM0;
__sbit __at 0x9E SM1;
__sbit __at 0x9D SM20;
__sbit __at 0x9C REN0;
__sbit __at 0x9B TB80;
__sbit __at 0x9A RB80;
__sbit __at 0x99 TI0;
__sbit __at 0x98 RI0;

// T2CON
__sbit __at 0xCF T2PS;
__sbit __at 0xCE I3FR;
__sbit __at 0xCD I2FR;
__sbit __at 0xCC T2R1;
__sbit __at 0xCB T2R0;
__sbit __at 0xCA T2CM;
__sbit __at 0xC9 T2I1;
__sbit __at 0xC8 T2I0;

// IEN0
__sbit __at 0xAF EA;
__sbit __at 0xAD ET2;
__sbit __at 0xAC ES0;
__sbit __at 0xAB ET1;
__sbit __at 0xAA EX1;
__sbit __at 0xA9 ET0;
__sbit __at 0xA8 EX0;

// IEN1
__sbit __at 0xBF EXEN2;

__sbit __at 0xBD WUIRQ;
__sbit __at 0xBC USB;
__sbit __at 0xBB USBWU;
__sbit __at 0xBA SPI;
__sbit __at 0xB9 RF;
__sbit __at 0xB8 RFSPI;

// IRCON
__sbit __at 0xC7 EXF2;
__sbit __at 0xC6 TF2;
__sbit __at 0xC5 WUF;
__sbit __at 0xC4 MISCF;
__sbit __at 0xC3 WUPINF;
__sbit __at 0xC2 SPIF;
__sbit __at 0xC1 RFF;		// RFIRQ
__sbit __at 0xC0 RFSPIF;	// RFRDY

// PORT0-3
__sbit __at 0x80 P00;
__sbit __at 0x81 P01;
__sbit __at 0x82 P02;
__sbit __at 0x83 P03;
__sbit __at 0x84 P04;
__sbit __at 0x85 P05;
__sbit __at 0x86 P06;
__sbit __at 0x87 P07;

__sbit __at 0x90 P10;
__sbit __at 0x91 P11;
__sbit __at 0x92 P12;
__sbit __at 0x93 P13;
__sbit __at 0x94 P14;
__sbit __at 0x95 P15;
__sbit __at 0x96 P16;
__sbit __at 0x97 P17;

__sbit __at 0xA0 P20;
__sbit __at 0xA1 P21;
__sbit __at 0xA2 P22;
__sbit __at 0xA3 P23;
__sbit __at 0xA4 P24;
__sbit __at 0xA5 P25;
__sbit __at 0xA6 P26;
__sbit __at 0xA7 P27;

__sbit __at 0xB0 P30;
__sbit __at 0xB1 P31;
__sbit __at 0xB2 P32;
__sbit __at 0xB3 P33;
__sbit __at 0xB4 P34;
__sbit __at 0xB5 P35;
__sbit __at 0xB6 P36;
__sbit __at 0xB7 P37;

// RFCON
__sbit __at 0xE8 RFCE;
__sbit __at 0xE9 RFCSN;
__sbit __at 0xEA RFCKEN;

// WDCON
//__sbit __at 0xDF BD;

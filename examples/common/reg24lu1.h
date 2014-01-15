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
__sfr __at 0x8E CKCON;
__sfr __at 0x90 RFCON;
__sfr __at 0x92 DPS;
__sfr __at 0x94 P0DIR;
__sfr __at 0x95 P0ALT;
__sfr __at 0x98 S0CON;
__sfr __at 0x99 S0BUF;
__sfr __at 0xA0 USBCON;
__sfr __at 0xA3 CLKCTL;
__sfr __at 0xA4 PWRDWN;
__sfr __at 0xA5 WUCONF;
__sfr __at 0xA6 INTEXP;
__sfr __at 0xA8 IEN0;
__sfr __at 0xA9 IP0;
__sfr __at 0xAA S0RELL;
__sfr __at 0xAB REGXH;
__sfr __at 0xAC REGXL;
__sfr __at 0xAD REGXC;
__sfr __at 0xB1 RSTRES;
__sfr __at 0xB2 SMDAT;
__sfr __at 0xB3 SMCTL;
__sfr __at 0xB5 TICKDV;
__sfr __at 0xB8 IEN1;
__sfr __at 0xB9 IP1;
__sfr __at 0xBA S0RELH;
__sfr __at 0xBC SSCONF;
__sfr __at 0xBD SSDATA;
__sfr __at 0xBE SSSTAT;
__sfr __at 0xC0 IRCON;
__sfr __at 0xC1 CCEN;
__sfr __at 0xC2 CCL1;
__sfr __at 0xC3 CCH1;
__sfr __at 0xC4 CCL2;
__sfr __at 0xC5 CCH2;
__sfr __at 0xC6 CCL3;
__sfr __at 0xC7 CCH3;
__sfr __at 0xC8 T2CON;
__sfr __at 0xC9 P0EXP;
__sfr __at 0xCA CRCL;
__sfr __at 0xCB CRCH;
__sfr __at 0xCC TL2;
__sfr __at 0xCD TH2;
__sfr __at 0xD0 PSW;
__sfr __at 0xD8 WDCON;
__sfr __at 0xD9 USBSLP;
__sfr __at 0xE0 ACC;
__sfr __at 0xE5 RFDAT;
__sfr __at 0xE6 RFCTL;
__sfr __at 0xE8 AESCS;
__sfr __at 0xE9 MD0;
__sfr __at 0xEA MD1;
__sfr __at 0xEB MD2;
__sfr __at 0xEC MD3;
__sfr __at 0xED MD4;
__sfr __at 0xEE MD5;
__sfr __at 0xEF ARCON;
__sfr __at 0xF0 B;
__sfr __at 0xF1 AESKIN;
__sfr __at 0xF2 AESIV;
__sfr __at 0xF3 AESD;
__sfr __at 0xF5 AESIA1;
__sfr __at 0xF6 AESIA2;
__sfr __at 0xF8 FSR;
__sfr __at 0xF9 FPCR;
__sfr __at 0xFA FCR;

//-----------------------------------------------------------------------------
// Word Registers
//-----------------------------------------------------------------------------

__sfr16 __at 0xC3C2 CC1;
__sfr16 __at 0xC5C4 CC2;
__sfr16 __at 0xC7C6 CC3;
__sfr16 __at 0xCBCA CRC;
__sfr16 __at 0xCDCC T2;

//-----------------------------------------------------------------------------
// Bit Definitions
//-----------------------------------------------------------------------------

// FSR
__sbit __at 0xFF DBG;
__sbit __at 0xFE STP;
__sbit __at 0xFD WEN;
__sbit __at 0xFC RDYN;
__sbit __at 0xFB INFEN;
__sbit __at 0xFA RDISMB;
__sbit __at 0xF9 RDISIP;

// PSW
__sbit __at 0xD7 CY;
__sbit __at 0xD6 AC;
__sbit __at 0xD5 F0;
__sbit __at 0xD4 RS1;
__sbit __at 0xD3 RS0;
__sbit __at 0xD2 OV;
__sbit __at 0xD1 F1;
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
__sbit __at 0xC4 USBF;
__sbit __at 0xC3 USBWUF;
__sbit __at 0xC2 SPIF;
__sbit __at 0xC1 RFIRQ;
__sbit __at 0xC0 RFSPIF;	// RFRDY

// USBCON
__sbit __at 0xA7 SWRST;
__sbit __at 0xA6 WU;
__sbit __at 0xA5 SUSPEND;
__sbit __at 0xA4 IV4;
__sbit __at 0xA3 IV3;
__sbit __at 0xA2 IV2;
__sbit __at 0xA1 IV1;
__sbit __at 0xA0 IV0;

// PORT0
__sbit __at 0x80 P00;
__sbit __at 0x81 P01;
__sbit __at 0x82 P02;
__sbit __at 0x83 P03;
__sbit __at 0x83 MCSN;
__sbit __at 0x83 SCSN;
__sbit __at 0x84 P04;
__sbit __at 0x85 P05;

// RFCON
__sbit __at 0x90 RFCE;
__sbit __at 0x91 RFCSN;
__sbit __at 0x92 RFCKEN;

// WDCON
__sbit __at 0xDF BD;

// AESCS
__sbit __at 0xE9 DECR;
__sbit __at 0xE8 GO;

// REGX commands
#define RWD         0x00
#define WWD         0x08
#define RGTIMER     0x01
#define WGTIMER     0x09
#define RRTCLAT     0x02
#define WRTCLAT     0x0A
#define RRTC        0x03
#define WRTCDIS     0x0B
#define RWSTA0      0x04
#define WWCON0      0x0C
#define RWSTA1      0x05
#define WWCON1      0x0D

//-----------------------------------------------------------------------------
// Interrupt Vector Definitions
//-----------------------------------------------------------------------------

#define INTERRUPT_EXT_INT0     0   // External Interrupt0 (P0.3)
#define INTERRUPT_T0           1   // Timer0 Overflow
#define INTERRUPT_AES_RDY      2   // AES ready interrupt
#define INTERRUPT_T1           3   // Timer1 Overflow
#define INTERRUPT_UART0        4   // UART0, Receive & Transmitt interrupt
#define INTERRUPT_T2           5   // Timer2 Overflow
#define INTERRUPT_RF_RDY       8   // RF SPI ready interrupt
#define INTERRUPT_RFIRQ        9   // RF interrupt
#define INTERRUPT_SPI          10  // SPI interrupt
#define INTERRUPT_USB_WU       11  // USB wakeup interrupt
#define INTERRUPT_USB_INT      12  // USB interrupt
#define INTERRUPT_WU           13  // Internal wakeup interrupt

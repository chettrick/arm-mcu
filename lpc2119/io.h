// Register definitions for LPC2119

// $Id: io.h,v 1.1 2006-12-14 00:40:48 cvs Exp $

#ifndef LPC2119_IO__H
#define LPC2119_IO__H

// WD

extern volatile unsigned char WDMOD;
extern volatile unsigned int WDTC;
extern volatile unsigned char WDFEED;
extern volatile const unsigned int WDTV;

// TIMER0

extern volatile unsigned char T0IR;
extern volatile unsigned char T0TCR;
extern volatile unsigned int T0TC;
extern volatile unsigned int T0PR;
extern volatile unsigned int T0PC;
extern volatile unsigned short T0MCR;
extern volatile unsigned int T0MR0;
extern volatile unsigned int T0MR1;
extern volatile unsigned int T0MR2;
extern volatile unsigned int T0MR3;
extern volatile unsigned short T0CCR;
extern volatile const unsigned int T0CR0;
extern volatile const unsigned int T0CR1;
extern volatile const unsigned int T0CR2;
extern volatile unsigned short T0EMR;

// TIMER1

extern volatile unsigned char T1IR;
extern volatile unsigned char T1TCR;
extern volatile unsigned int T1TC;
extern volatile unsigned int T1PR;
extern volatile unsigned int T1PC;
extern volatile unsigned short T1MCR;
extern volatile unsigned int T1MR0;
extern volatile unsigned int T1MR1;
extern volatile unsigned int T1MR2;
extern volatile unsigned int T1MR3;
extern volatile unsigned short T1CCR;
extern volatile const unsigned int T1CR0;
extern volatile const unsigned int T1CR1;
extern volatile const unsigned int T1CR2;
extern volatile const unsigned int T1CR3;
extern volatile unsigned short T1EMR;

// UART0

extern volatile const unsigned char U0RBR;
extern volatile unsigned char U0THR;
extern volatile unsigned char U0DLL;
extern volatile unsigned char U0IER;
extern volatile unsigned char U0DLM;
extern volatile const unsigned char U0IIR;
extern volatile unsigned char U0FCR;
extern volatile unsigned char U0LCR;
extern volatile const unsigned char U0LSR;
extern volatile unsigned char U0SCR;

// UART1

extern volatile const unsigned char U1RBR;
extern volatile unsigned char U1THR;
extern volatile unsigned char U1DLL;
extern volatile unsigned char U1IER;
extern volatile unsigned char U1DLM;
extern volatile const unsigned char U1IIR;
extern volatile unsigned char U1FCR;
extern volatile unsigned char U1LCR;
extern volatile unsigned char U1MCR;
extern volatile const unsigned char U1LSR;
extern volatile const unsigned char U1MSR;
extern volatile unsigned char U1SCR;

// PWM

extern volatile unsigned short PWMIR;
extern volatile unsigned char PWMTCR;
extern volatile unsigned int PWMTC;
extern volatile unsigned int PWMPR;
extern volatile unsigned int PWMPC;
extern volatile unsigned int PWMMCR;
extern volatile unsigned int PWMMR0;
extern volatile unsigned int PWMMR1;
extern volatile unsigned int PWMMR2;
extern volatile unsigned int PWMMR3;
extern volatile unsigned int PWMMR4;
extern volatile unsigned int PWMMR5;
extern volatile unsigned int PWMMR6;
extern volatile unsigned short PWMPCR;
extern volatile unsigned char PWMLER;

// IIC

extern volatile unsigned char I2CONSET;
extern volatile const unsigned char I2STAT;
extern volatile unsigned char I2DAT;
extern volatile unsigned char I2ADR;
extern volatile unsigned short I2SCLH;
extern volatile unsigned short I2SCLL;
extern volatile unsigned char I2CONCLR;

// SPI/SPI0

extern volatile unsigned char S0PCR;
extern volatile const unsigned char S0PSR;
extern volatile unsigned char S0PPR;
extern volatile unsigned char S0PCCR;
extern volatile unsigned char S0PINT;

// Synonyms for compatibility with the 210x series

extern volatile unsigned char SPCR;
extern volatile const unsigned char SPSR;
extern volatile unsigned char SPPR;
extern volatile unsigned char SPCCR;
extern volatile unsigned char SPINT;

// RTC

extern volatile unsigned char ILR;
extern volatile const unsigned char CTC;
extern volatile unsigned char CCR;
extern volatile unsigned char CIIR;
extern volatile unsigned char AMR;
extern volatile unsigned int CTIME0;
extern volatile unsigned int CTIME1;
extern volatile unsigned int CTIME2;
extern volatile unsigned char SEC;
extern volatile unsigned char MINUTE;	// MIN conflicts with linker
extern volatile unsigned char HOUR;
extern volatile unsigned char DOM;
extern volatile unsigned char DOW;
extern volatile unsigned short DOY;
extern volatile unsigned MONTH;
extern volatile unsigned short YEAR;
extern volatile unsigned char ALSEC;
extern volatile unsigned char ALMIN;
extern volatile unsigned char ALHOUR;
extern volatile unsigned char ALDOM;
extern volatile unsigned char ALDOW;
extern volatile unsigned short ALDOY;
extern volatile unsigned char ALMON;
extern volatile unsigned short ALYEAR;
extern volatile unsigned short PREINT;
extern volatile unsigned short PREFRAC;

// GPIO PORT0

extern volatile unsigned int IO0PIN;
extern volatile unsigned int IO0DIR;
extern volatile unsigned int IO0CLR;
extern volatile unsigned int IO0SET;

// Synonyms for compatibility with the 210x series

extern volatile unsigned int IOPIN;
extern volatile unsigned int IODIR;
extern volatile unsigned int IOCLR;
extern volatile unsigned int IOSET;

// GPIO PORT1

extern volatile unsigned int IO1PIN;
extern volatile unsigned int IO1DIR;
extern volatile unsigned int IO1CLR;
extern volatile unsigned int IO1SET;

// GPIO PORT2

extern volatile unsigned int IO2PIN;
extern volatile unsigned int IO2DIR;
extern volatile unsigned int IO2CLR;
extern volatile unsigned int IO2SET;

// GPIO PORT3

extern volatile unsigned int IO3PIN;
extern volatile unsigned int IO3DIR;
extern volatile unsigned int IO3CLR;
extern volatile unsigned int IO3SET;

// PIN CONNECT BLOCK

extern volatile unsigned int PINSEL0;
extern volatile unsigned int PINSEL1;
extern volatile unsigned int PINSEL2;

// SPI1

extern volatile unsigned char S1PCR;
extern volatile const unsigned char S1PSR;
extern volatile unsigned char S1PPR;
extern volatile unsigned char S1PCCR;
extern volatile unsigned char S1PINT;

// ADC
// Renamed from AD... to prevent ld conflict

extern volatile unsigned int A2DCR;
extern volatile unsigned int A2DDR;

// CAN

extern volatile unsigned int CAN_RECV[0x200];
extern volatile unsigned int AFMR;
extern volatile unsigned int SFF_sa;
extern volatile unsigned int SFF_GRP_sa;
extern volatile unsigned int EFF_sa;
extern volatile unsigned int EFF_GRP_sa;
extern volatile unsigned int ENDofTable;
extern const volatile unsigned int LUTerrAd;
extern const volatile unsigned int LUTerr;
extern const volatile unsigned int CANTxSR;
extern const volatile unsigned int CANRxSR;
extern const volatile unsigned int CANMSR;

// CAN1 Interface

extern volatile unsigned int C1MOD;
extern volatile unsigned int C1CMR;
extern const volatile unsigned int C1GSR;
extern const volatile unsigned int C1ICR;
extern volatile unsigned int C1IER;
extern volatile unsigned int C1BTR;
extern volatile unsigned int C1EWL;
extern const volatile unsigned int C1SR;
extern volatile unsigned int C1RFS;
extern volatile unsigned int C1RID;
extern volatile unsigned int C1RDA;
extern volatile unsigned int C1RDB;
extern volatile unsigned int C1TFI1;
extern volatile unsigned int C1TID1;
extern volatile unsigned int C1TDA1;
extern volatile unsigned int C1TDB1;
extern volatile unsigned int C1TFI2;
extern volatile unsigned int C1TID2;
extern volatile unsigned int C1TDA2;
extern volatile unsigned int C1TDB2;
extern volatile unsigned int C1TFI3;
extern volatile unsigned int C1TID3;
extern volatile unsigned int C1TDA3;
extern volatile unsigned int C1TDB3;

// CAN2 Interface

extern volatile unsigned int C2MOD;
extern volatile unsigned int C2CMR;
extern const volatile unsigned int C2GSR;
extern const volatile unsigned int C2ICR;
extern volatile unsigned int C2IER;
extern volatile unsigned int C2BTR;
extern volatile unsigned int C2EWL;
extern const volatile unsigned int C2SR;
extern volatile unsigned int C2RFS;
extern volatile unsigned int C2RID;
extern volatile unsigned int C2RDA;
extern volatile unsigned int C2RDB;
extern volatile unsigned int C2TFI1;
extern volatile unsigned int C2TID1;
extern volatile unsigned int C2TDA1;
extern volatile unsigned int C2TDB1;
extern volatile unsigned int C2TFI2;
extern volatile unsigned int C2TID2;
extern volatile unsigned int C2TDA2;
extern volatile unsigned int C2TDB2;
extern volatile unsigned int C2TFI3;
extern volatile unsigned int C2TID3;
extern volatile unsigned int C2TDA3;
extern volatile unsigned int C2TDB3;

// CAN3 Interface

extern volatile unsigned int C3MOD;
extern volatile unsigned int C3CMR;
extern const volatile unsigned int C3GSR;
extern const volatile unsigned int C3ICR;
extern volatile unsigned int C3IER;
extern volatile unsigned int C3BTR;
extern volatile unsigned int C3EWL;
extern const volatile unsigned int C3SR;
extern volatile unsigned int C3RFS;
extern volatile unsigned int C3RID;
extern volatile unsigned int C3RDA;
extern volatile unsigned int C3RDB;
extern volatile unsigned int C3TFI1;
extern volatile unsigned int C3TID1;
extern volatile unsigned int C3TDA1;
extern volatile unsigned int C3TDB1;
extern volatile unsigned int C3TFI2;
extern volatile unsigned int C3TID2;
extern volatile unsigned int C3TDA2;
extern volatile unsigned int C3TDB2;
extern volatile unsigned int C3TFI3;
extern volatile unsigned int C3TID3;
extern volatile unsigned int C3TDA3;
extern volatile unsigned int C3TDB3;

// CAN4 Interface

extern volatile unsigned int C4MOD;
extern volatile unsigned int C4CMR;
extern const volatile unsigned int C4GSR;
extern const volatile unsigned int C4ICR;
extern volatile unsigned int C4IER;
extern volatile unsigned int C4BTR;
extern volatile unsigned int C4EWL;
extern const volatile unsigned int C4SR;
extern volatile unsigned int C4RFS;
extern volatile unsigned int C4RID;
extern volatile unsigned int C4RDA;
extern volatile unsigned int C4RDB;
extern volatile unsigned int C4TFI1;
extern volatile unsigned int C4TID1;
extern volatile unsigned int C4TDA1;
extern volatile unsigned int C4TDB1;
extern volatile unsigned int C4TFI2;
extern volatile unsigned int C4TID2;
extern volatile unsigned int C4TDA2;
extern volatile unsigned int C4TDB2;
extern volatile unsigned int C4TFI3;
extern volatile unsigned int C4TID3;
extern volatile unsigned int C4TDA3;
extern volatile unsigned int C4TDB3;

// SYSTEM CONTROL BLOCK

// MAM

extern volatile unsigned char MAMCR;
extern volatile unsigned char MAMTIM;
extern volatile unsigned char MEMAP;

// PLL

extern volatile unsigned char PLLCON;
extern volatile unsigned char PLLCFG;
extern volatile const unsigned short PLLSTAT;
extern volatile unsigned char PLLFEED;

// POWER CONTROL

extern volatile unsigned char PCON;
extern volatile unsigned short PCONP;

// VPB

extern volatile unsigned char VPBDIV;

// EXTERNAL INTERUPT/WAKE

extern volatile unsigned char EXTINT;
extern volatile unsigned char EXTWAKE;
extern volatile unsigned char EXTMODE;
extern volatile unsigned char EXTPOLAR;

// Vector Interrupt Controller (VIC)

extern volatile const unsigned int VICIRQStatus;
extern volatile const unsigned int VICFIQStatus;
extern volatile const unsigned int VICRawIntr;
extern volatile unsigned int VICIntSelect;
extern volatile unsigned int VICIntEnable;
extern volatile unsigned int VICIntEnClr;
extern volatile unsigned int VICSoftInt;
extern volatile unsigned int VICSoftIntClear;
extern volatile unsigned int VICProtection;
extern void (* volatile VICVectAddrRead)( void);
extern void (* volatile VICDefVectAddr)( void);
extern void (* volatile VICVectAddr[16])(void);
extern volatile unsigned int VICVectCntl[16];

#endif // LPC2119_IO__H

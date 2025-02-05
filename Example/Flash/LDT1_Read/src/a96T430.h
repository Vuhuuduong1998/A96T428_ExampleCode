/**
 *******************************************************************************
 * @file        a96T428.h
 * @author      ABOV R&D Division
 * @brief       A96T418 Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __a96T428_H_
#define __a96T428_H_

#define	A96T418_MODE	0//1//0//1

#if A96T418_MODE==1
#define	XRAM_SIZE 0x700 //1.75KB 
#endif
#if A96T418_MODE==0
#define	XRAM_SIZE 0xF00 //3.75KB  = 3840Byte 
#endif

//-----------------------------------------------------
//  A96T418 Special Function Register Definitions
//----------------------------------------------------- 0x80
sfr     P0          =   0x80;       // P0 Data Register
sbit    P00         =   0x80;
sbit    P01         =   0x81;
sbit    P02         =   0x82;
sbit    P03         =   0x83;
sbit    P04         =   0x84;
sbit    P05         =   0x85;
sbit    P06         =   0x86;
sbit    P07         =   0x87;

sfr     SP          =   0x81;       // Stack Pointer
sfr16   DPTR0       =   0x82;       // Data Pointer Register
sfr     DPL         =   0x82;       // Data Pointer Register Low
sfr     DPH         =   0x83;       // Data Pointer Register High
sfr16   DPTR1       =   0x84;       // Data Pointer Register 1
sfr     DPL1        =   0x84;       // Data Pointer Register Low 1
sfr     DPH1        =   0x85;       // Data Pointer Register High 1
sfr     LVICR       =   0x86;       // Low Voltage Indicator Control Register
sfr     PCON        =   0x87;       // Power Control Register
//----------------------------------------------------- 0x88
sfr     P1          =   0x88;       // P1 Data Register
sbit    P10         =   0x88;
sbit    P11         =   0x89;
sbit    P12         =   0x8A;
sbit    P13         =   0x8B;
sbit    P14         =   0x8C;
sbit    P15         =   0x8D;
sbit    P16         =   0x8E;
sbit    P17         =   0x8F;

sfr     WTDR        =   0x89;       // Watch Timer Data Register (Write Only)
sfr     WTCNT       =   0x89;       // Watch Timer Counter Register (Read Only)
sfr     SCCR        =   0x8A;       // System and Clock Control Register
sfr     BITCR       =   0x8B;       // Basic Interval Timer Control Register
sfr     BITCNT      =   0x8C;       // Basic Interval Timer Counter Register (Read Only)
sfr     WDTCR       =   0x8D;       // Watch Dog Timer Control Register
sfr     WDTDR       =   0x8E;       // Watch Dog Timer Data Register (Write Only)
sfr     WDTCNT      =   0x8E;       // Watch Dog Timer Counter Register (Read Only)
sfr     BUZDR       =   0x8F;       // BUZZER Data Register
//----------------------------------------------------- 0x90
sfr     P2          =   0x90;       // P2 Data Register
sbit    P20         =   0x90;
sbit    P21         =   0x91;
sbit    P22         =   0x92;
sbit    P23         =   0x93;
sbit    P24         =   0x94;
sbit    P25         =   0x95;
sbit    P26         =   0x96;
sbit    P27         =   0x97;

sfr     P0OD        =   0x91;       // P0 Open-drain Selection Register    
sfr     P1OD        =   0x92;       // P1 Open-drain Selection Register
sfr     P2OD        =   0x93;       // P2 Open-drain Selection Register
#if A96T418_MODE==0
sfr     P3OD        =   0x94;       // P3 Open-drain Selection Register
sfr     P4OD        =   0x95;       // P4 Open-drain Selection Register
#endif
sfr     WTCR        =   0x96;       // Watch Timer Control Register
sfr     BUZCR       =   0x97;       // BUZZER Control Register
//----------------------------------------------------- 0x98
sfr     P3          =   0x98;       // P3 Data Register
sbit    P30         =   0x98;
sbit    P31         =   0x99;
#if A96T418_MODE==0
sbit    P32         =   0x9A;
sbit    P33         =   0x9B;
sbit    P34         =   0x9C;
sbit    P35         =   0x9D;
#endif

#if A96T418_MODE==0
sfr     MCRC_CTRL   =   0x9A;       // MCRC Control Register
sfr     MCRC_DATA0  =   0x9B;       // MCRC Data Register 0
sfr     MCRC_DATA1  =   0x9C;       // MCRC Data Register 1
#endif
sfr     ADCCR       =   0x9C;       // A/D Converter Control Register
sfr     ADCCRL      =   0x9C;       // A/D Converter Control Low Register
sfr     ADCCRH      =   0x9D;       // A/D Converter Control High Register
sfr16   ADCDR       =   0x9E;       // A/D Converter Data Register
sfr     ADCDRL      =   0x9E;       // A/D Converter Data Low Register (Read Only)
sfr     ADCDRH      =   0x9F;       // A/D Converter Data High Register (Read Only)
//----------------------------------------------------- 0xA0
#if A96T418_MODE==0
sfr     P4          =   0xA0;       // P4 Data Register
sbit    P40         =   0xA0;
sbit    P41         =   0xA1;
sbit    P42         =   0xA2;
sbit    P43         =   0xA3;
sbit    P44         =   0xA4;
sbit    P45         =   0xA5;
sbit    P46         =   0xA6;
sbit    P47         =   0xA7;
#endif

sfr     P0IO        =   0xA1;       // P0 Direction Register
sfr     EO          =   0xA2;       // Extended Operation Register
#if A96T418_MODE==0
sfr     P5OD        =   0xA3;       // P5 Open-drain Selection Register
#endif
sfr16   EIPOL0      =   0xA4;       // External Interrupt Polarity 0 Register
sfr     EIPOL0L     =   0xA4;       // External Interrupt Polarity 0 Low Register
sfr     EIPOL0H     =   0xA5;       // External Interrupt Polarity 0 High Register
sfr     EIFLAG1     =   0xA6;       // External Interrupt Flag 1 Register
sfr     EIPOL1      =   0xA7;       // External Interrupt Polarity 1 Register
//----------------------------------------------------- 0xA8
sfr     IE          =   0xA8;       // Interrupt Enable Register
sbit    EINT10_INT_EN_BIT   =   0xA8;
sbit    EINT11_INT_EN_BIT   =   0xA9;
sbit    LED_INT_EN_BIT 		=   0xAA;
sbit    TOUCH_INT_EN_BIT  	=   0xAB;
sbit    EINT_INT0_5_EN_BIT  =   0xAD;
sbit    EA              =   0xAF;

sfr     IE1         =   0xA9;       // Interrupt Enable Register 1
sfr     IE2         =   0xAA;       // Interrupt Enable Register 2
sfr     IE3         =   0xAB;       // Interrupt Enable Register 3
sfr     P0PU        =   0xAC;       // P0 Pull-up Resistor Selection Register
sfr     P1PU        =   0xAD;       // P1 Pull-up Resistor Selection Register
sfr     P2PU        =   0xAE;       // P2 Pull-up Resistor Selection Register
sfr     P3PU        =   0xAF;       // P3 Pull-up Resistor Selection Register
//----------------------------------------------------- 0xB0
#if A96T418_MODE==0
sfr     P5          =   0xB0;       // P5 Data Register
sbit    P50         =   0xB0;
sbit    P51         =   0xB1;
sbit    P52         =   0xB2;
sbit    P53         =   0xB3;
sbit    P54         =   0xB4;
sbit    P55         =   0xB5;
sbit    P56         =   0xB6;
sbit    P57         =   0xB7;
#endif

sfr     P1IO        =   0xB1;       // P1 Direction Register
sfr     T0CR        =   0xB2;       // Timer 0 Control Register
sfr     T0CNT       =   0xB3;       // Timer 0 Counter Register (Read Only)
sfr     T0DR        =   0xB4;       // Timer 0 Data Register   
sfr     T0CDR       =   0xB4;       // Timer 0 Capture Data Register (Read Only)
#if A96T418_MODE==0
sfr     P4PU        =   0xB5;       // P4 Pull-up Resistor Selection Register
sfr     P5PU        =   0xB6;       // P5 Pull-up Resistor Selection Register
sfr     VDCCON      =   0xB7;       // Wakeup Control Register
sfr     WKCON       =   0xB7;        // Wakeup Control Register
#endif
//----------------------------------------------------- 0xB8
sfr     IP          =   0xB8;       // Interrupt Priority Register
sfr     P2IO        =   0xB9;       // P2 Direction Register
sfr16   T1CR        =   0xBA;       // Timer 1 Control Register
sfr     T1CRL       =   0xBA;       // Timer 1 Control Low Register
sfr     T1CRH       =   0xBB;       // Timer 1 Counter High Register
sfr16   T1ADR       =   0xBC;       // Timer 1 A Data Register
sfr     T1ADRL      =   0xBC;       // Timer 1 A Data Low Register
sfr     T1ADRH      =   0xBD;       // Timer 1 A Data High Register
sfr16   T1BDR       =   0xBE;       // Timer 1 B Data Register
sfr     T1BDRL      =   0xBE;       // Timer 1 B Data Low Register
sfr     T1BDRH      =   0xBF;       // Timer 1 B Data High Register
//----------------------------------------------------- 0xC0
sfr     EIFLAG0     =   0xC0;       // External Interrupt Flag 0 Register
sfr     P3IO        =   0xC1;       // P3 Direction Register
sfr16   T2CR        =   0xC2;       // Timer 2 Control Register
sfr     T2CRL       =   0xC2;       // Timer 2 Control Low Register
sfr     T2CRH       =   0xC3;       // Timer 2 Control High Register
sfr16   T2ADR       =   0xC4;       // Timer 2 A Data Register
sfr     T2ADRL      =   0xC4;       // Timer 2 A Data Low Register
sfr     T2ADRH      =   0xC5;       // Timer 2 A Data High Register
sfr16   T2BDR       =   0xC6;       // Timer 2 B Data Register
sfr     T2BDRL      =   0xC6;       // Timer 2 B Data Low Register
sfr     T2BDRH      =   0xC7;       // Timer 2 B Data High Register
//----------------------------------------------------- 0xC8
sfr     OSCCR       =   0xC8;       // Oscillator Control Register
#if A96T418_MODE==0
sfr     P4IO        =   0xC9;       // P4 Direction Register
#endif
sfr     UCTRL1      =   0xCB;       // USART Control Register 1
sfr     UCTRL2      =   0xCC;       // USART Control Register 2
sfr     UCTRL3      =   0xCD;       // USART Control Register 3
sfr     USTAT       =   0xCF;       // USART Status Register
//----------------------------------------------------- 0xD0
sfr     PSW         =   0xD0;       // Program Status Word Register
sbit    P           =   0xD0;       
sbit    F1          =   0xD1;
sbit    OV          =   0xD2;
sbit    RS0         =   0xD3;
sbit    RS1         =   0xD4;
sbit    F0          =   0xD5;
sbit    AC          =   0xD6;
sbit    CY          =   0xD7;

#if A96T418_MODE==0
sfr     P5IO        =   0xD1;       // P5 Direction Register
#endif
#if A96T418_MODE==1
sfr16   P0FSR       =   0xD2;       // P0 Function Selection Register
sfr     P0FSRL      =   0xD2;       // P0 Function Selection Low Register
sfr     P0FSRH      =   0xD3;       // P0 Function Selection High Register
#endif
#if A96T418_MODE==0
sfr     UCTRL21     =   0xD2;       // USART2 Control Register 1
sfr     UCTRL22     =   0xD3;       // USART2 Control Register 2
sfr     UCTRL23     =   0xD4;       // USART2 Control Register 3
#endif

#if A96T418_MODE==1
sfr16   P1FSR       =   0xD4;       // P1 Function Selection Register
sfr     P1FSRL      =   0xD4;       // P1 Function Selection Low Register
sfr     P1FSRH      =   0xD5;       // P1 Function Selection High Register
#endif
#if A96T418_MODE==0
sfr     UBAUD2      =   0xD5;       // USART2 Baud Rate Generation Register
sfr     UDATA2      =   0xD6;       // USART2 Data Register
sfr     USTAT2      =   0xD7;       // USART2 Status Register
#endif
#if A96T418_MODE==1
sfr16   P2FSR       =   0xD6;       // P2 Function Selection Register
sfr     P2FSRL      =   0xD6;       // P2 Function Selection Low Register
sfr     P2FSRH      =   0xD7;       // P2 Function Selection High Register
#endif
//----------------------------------------------------- 0xD8
sfr     LVRCR       =   0xD8;       // Low Voltage Reset Control Register
sfr     USI0CR1     =   0xD9;       // USI0 Control Register 1
sfr     USI0CR2     =   0xDA;       // USI0 Control Register 2
sfr     USI0CR3     =   0xDB;       // USI0 Control Register 3
sfr     USI0CR4     =   0xDC;       // USI0 Control Register 4
sfr     USI0SAR     =   0xDD;       // USI0 Slave Address Register
#if A96T418_MODE==1
sfr     P0DB        =   0xDE;       // P0 De-bounce Enable Register
sfr     P123DB      =   0xDF;       // P1/P2/P3 De-bounce Enable Register 
#endif
#if A96T418_MODE==0
sfr     ADCCR3      =   0xDE;      // A/D Converter Control Register 3
sfr     ADCCR4      =   0xDF;       // A/D Converter Control Register 4
#endif
//----------------------------------------------------- 0xE0
sfr     ACC         =   0xE0;       // Accumulator Register
sfr     USI0ST1     =   0xE1;       // USI0 Status Register 1
sfr     USI0ST2     =   0xE2;       // USI0 Status Register 2 (Read Only)
sfr     USI0BD      =   0xE3;       // USI0 Baud Rate Generation Register
sfr     USI0SDHR    =   0xE4;       // USI0 SDA Hold Time Register
sfr     USI0DR      =   0xE5;       // USI0 Data Register
sfr16   USI0SCR     =   0xE6;       // USI0 SCL Period Register
sfr     USI0SCLR    =   0xE6;       // USI0 SCL Low Period Register
sfr     USI0SCHR    =   0xE7;       // USI0 SCL High Period Register
//----------------------------------------------------- 0xE8
sfr     RSTFR       =   0xE8;       // Reset Flag Register

#if A96T418_MODE==0
sfr 	DCT_REG0    =   0xE9;       // Flash DCT0 Register
sfr 	DCT_REG1    =   0xEA;       // Flash DCT1 Register
sfr 	DCT_REG2    =   0xEB;       // Flash DCT2 Register
sfr 	DCT_REG3    =   0xEC;       // Flash DCT3 Register
sfr 	DCT_REG4    =   0xED;       // Flash DCT4 Register
sfr 	DCT_REG5    =   0xEE;       // Flash DCT5 Register
sfr 	DCT_REG6    =   0xEF;       // Flash DCT6 Register
#endif 

#if A96T418_MODE==1
sfr     P3FSR       =   0xEE;       // Port3 Function Selection Register
#endif
//----------------------------------------------------- 0xF0
sfr     B           =   0xF0;       // B Register
#if A96T418_MODE==0
sfr 	DCT_REG7    =   0xF1;       // Flash DCT7 Register
sfr 	TEST_AR     =   0xF2;       // Flash TEST_AR Register
//sfr 	FETR		=   0xF3;       //FETR register
sfr 	TEST_AR1    =   0xF4;       // Flash TEST_AR1 Register
#endif 

//----------------------------------------------------- 0xF8
sfr     IP1         =   0xF8;       // Interrupt Priority Register 1
#if A96T418_MODE==0
sfr     TS_CON      =   0xF9;       // Touch Sensor Control Register
#endif
sfr     UBAUD       =   0xFC;       // USART Baud Rate Generation Register
sfr     UDATA       =   0xFD;       // USART Data Register

//==================================================================== //
// XSFR                                                                //
//==================================================================== //

#define     T3CRH       *(volatile unsigned char xdata *) 0x1000        // Timer 3 Control High Register
#define     T3CRL       *(volatile unsigned char xdata *) 0x1001        // Timer 3 Control Low Register
#define     T3ADR       *(volatile unsigned int xdata *)  0x1002        // Timer 3 A Data Register
#define     T3ADRH      *(volatile unsigned char xdata *) 0x1002        // Timer 3 A Data High Register
#define     T3ADRL      *(volatile unsigned char xdata *) 0x1003        // Timer 3 A Data Low Register
#define     T3BDR       *(volatile unsigned int xdata *)  0x1004        // Timer 3 B Data Register
#define     T3BDRH      *(volatile unsigned char xdata *) 0x1004        // Timer 3 B Data High Register
#define     T3BDRL      *(volatile unsigned char xdata *) 0x1005        // Timer 3 B Data Low Register

#define     T4CRH       *(volatile unsigned char xdata *) 0x1008        // Timer 4 Control High Register
#define     T4CRL       *(volatile unsigned char xdata *) 0x1009        // Timer 4 Control Low Register

#define     T4ADR       *(volatile unsigned int xdata *)  0x100A        // Timer 4 A Data Register
#define     T4ADRH      *(volatile unsigned char xdata *) 0x100A        // Timer 4 A Data High Register
#define     T4ADRL      *(volatile unsigned char xdata *) 0x100B        // Timer 4 A Data Low Register
#define     T4BDR       *(volatile unsigned int xdata *)  0x100C        // Timer 4 B Data Register
#define     T4BDRH      *(volatile unsigned char xdata *) 0x100C        // Timer 4 B Data High Register
#define     T4BDRL      *(volatile unsigned char xdata *) 0x100D        // Timer 4 B Data Low Register

#define     T5CRH       *(volatile unsigned char xdata *) 0x1010        // Timer 5 Control High Register
#define     T5CRL       *(volatile unsigned char xdata *) 0x1011        // Timer 5 Control Low Register
#define     T5ADR       *(volatile unsigned int xdata *)  0x1012        // Timer 5 A Data Register
#define     T5ADRH      *(volatile unsigned char xdata *) 0x1012        // Timer 5 A Data High Register
#define     T5ADRL      *(volatile unsigned char xdata *) 0x1013        // Timer 5 A Data Low Register
#define     T5BDR       *(volatile unsigned int xdata *)  0x1014        // Timer 5 B Data Register
#define     T5BDRH      *(volatile unsigned char xdata *) 0x1014        // Timer 5 B Data High Register
#define     T5BDRL      *(volatile unsigned char xdata *) 0x1015        // Timer 5 B Data Low Register

#define     UCTRL4      *(volatile unsigned char xdata *) 0x1018        // USART Control Register 4
#define     FPCR        *(volatile unsigned char xdata *) 0x1019        // USART Floating Point Counter
#define     RTOC        *(volatile unsigned int xdata *)  0x101A        // Receiver Time Out Counter Register (Read Only)
#define     RTOCH       *(volatile unsigned char xdata *) 0x101A        // Receiver Time Out Counter High Register (Read Only)
#define     RTOCL       *(volatile unsigned char xdata *) 0x101B        // Receiver Time Out Counter Low Register (Read Only)

#if A96T418_MODE==0
#define     CHECKSUMH	*(volatile unsigned char xdata *) 0x101E        // Flash CHECKSUM High Register
#define     CHECKSUMM	*(volatile unsigned char xdata *) 0x101D        // Flash CHECKSUM Middle Register
#define     CHECKSUML	*(volatile unsigned char xdata *) 0x101C        // Flash CHECKSUM Low Register
#endif

#define     FEMR        *(volatile unsigned char xdata *) 0x1020        // Flash Mode Register
#if A96T418_MODE==1
#define     FECR        *(volatile unsigned char xdata *) 0x1021        // Flash Control Register
#endif	
#define     FESR        *(volatile unsigned char xdata *) 0x1022        // Flash Status Register
#if A96T418_MODE==1
#define     FETCR       *(volatile unsigned char xdata *) 0x1023        // Flash Time Control Register
#endif	
#define     FEARM1      *(volatile unsigned char xdata *) 0x1024        // Flash Address Middle Register 1
#define     FEARL1      *(volatile unsigned char xdata *) 0x1025        // Flash Address Low Register 1
#if A96T418_MODE==0
#define     FEMR2       *(volatile unsigned char xdata *) 0x1026        // Flash Mode Register 2
#define     FECR2       *(volatile unsigned char xdata *) 0x1027        // Flash Control Register 2
#endif	
#define     FEARH       *(volatile unsigned char xdata *) 0x1028        // Flash Address High Register
#define     FEARM       *(volatile unsigned char xdata *) 0x1029        // Flash Address Middle Register
#define     FEARL       *(volatile unsigned char xdata *) 0x102A        // Flash Address Low Register
#if A96T418_MODE==0
#define     FEDR3       *(volatile unsigned char xdata *) 0x102E        // Flash Data Register 3
#define     FEDR2       *(volatile unsigned char xdata *) 0x102D        // Flash Data Register 2
#define     FEDR1       *(volatile unsigned char xdata *) 0x102C        // Flash Data Register 1
#define     FEDR0       *(volatile unsigned char xdata *) 0x102B        // Flash Data Register 0
#endif	
#if A96T418_MODE==1
#define     FEDR	    *(volatile unsigned char xdata *) 0x102B        // Flash Data Register 
#define     FETR        *(volatile unsigned char xdata *) 0x102C
#endif
#if A96T418_MODE==0
#define     FECR        *(volatile unsigned char xdata *) 0x102F        // Flash Control Register
#define     UCTRL24     *(volatile unsigned char xdata *) 0x1030        // USART2 Control Register 4
#define     FPCR2       *(volatile unsigned char xdata *) 0x1031        // USART Floating Point Counter
#define     RTOCH2      *(volatile unsigned char xdata *) 0x1032        // Receiver Time Out Counter 2 High Register (Read Only)
#define     RTOCL2      *(volatile unsigned char xdata *) 0x1033        // Receiver Time Out Counter 2 Low Register (Read Only)
#define     FETR2       *(volatile unsigned char xdata *) 0x1034        //FETR2 register
#define     FETR3       *(volatile unsigned char xdata *) 0x1035        //FETR3 register
#define     FETR4       *(volatile unsigned char xdata *) 0x1036        //FETR4 register
#define     FETR		*(volatile unsigned char xdata *) 0x1037        //Flash Test register
	
#endif

#if A96T418_MODE==1
#define     XTFLSR      *(volatile unsigned char xdata *) 0x1038        // Main Crystal OSC Filter Selection Register
#endif


#if A96T418_MODE==0
#define     P0FSR  		*(volatile unsigned int xdata *)  0x1040        // P0 Function Selection Register
#define     P0FSRL      *(volatile unsigned char xdata *) 0x1040        // P0 Function Selection Low Register
#define     P0FSRH      *(volatile unsigned char xdata *) 0x1041        // P0 Function Selection High Register
#define     P1FSR  		*(volatile unsigned int xdata *)  0x1042        // P1 Function Selection Register
#define     P1FSRL      *(volatile unsigned char xdata *) 0x1042        // P1 Function Selection Low Register
#define     P1FSRH      *(volatile unsigned char xdata *) 0x1043        // P1 Function Selection High Register
#define     P2FSR  		*(volatile unsigned int xdata *)  0x1044        // P2 Function Selection Register
#define     P2FSRL      *(volatile unsigned char xdata *) 0x1044        // P2 Function Selection Low Register
#define     P2FSRH      *(volatile unsigned char xdata *) 0x1045        // P2 Function Selection High Register
#define     P3FSR  		*(volatile unsigned int xdata *)  0x1046        // P3 Function Selection Register
#define     P3FSRL      *(volatile unsigned char xdata *) 0x1046        // P3 Function Selection Low Register
#define     P3FSRH      *(volatile unsigned char xdata *) 0x1047        // P3 Function Selection High Register
#define     P4FSR  		*(volatile unsigned int xdata *)  0x1048        // P4 Function Selection Register
#define     P4FSRL      *(volatile unsigned char xdata *) 0x1048        // P4 Function Selection Low Register
#define     P4FSRH      *(volatile unsigned char xdata *) 0x1049        // P4 Function Selection High Register
#define     P5FSR       *(volatile unsigned int xdata *)  0x104A        // P5 Function Selection Register
#define     P5FSRL      *(volatile unsigned char xdata *) 0x104A        // P5 Function Selection Low Register
#define     P5FSRH      *(volatile unsigned char xdata *) 0x104B        // P5 Function Selection Low Register
#define     DBCONT0     *(volatile unsigned char xdata *) 0x104C        // 
#define     DBCONT1     *(volatile unsigned char xdata *) 0x104D        // 
#define     DBCONT2     *(volatile unsigned char xdata *) 0x104E        // 
#define     DBCONT3     *(volatile unsigned char xdata *) 0x104F        // 
#define     P2LEDDLY    *(volatile unsigned char xdata *) 0x1050        // P2 LED delay enable register	
#endif

#define     CONFOPTION1     (*(volatile unsigned char xdata *) 0x2F50)        // - 	- 	- 	- 	PAEN	PASS2 PASS1 PASS0
#define     CONFOPTION2     (*(volatile unsigned char xdata *) 0x2F51)        // R_P	HL	-	VAPEN	-	-	-	RSTS

// ==================================================================== //
// Flash and EEPROM Memory REGISTER                                     //
// ==================================================================== //
// (0xF1) FEMR;              // FECON        Flash and EEPROM mode register
#define FLASH_SEL               (0x80)
#define FLASH_PGM_MODE          (0x20)
#define FLASH_ERASE_MODE        (0x10)
#define FLASH_PBUFF_SEL         (0x08)
#define FLASH_OTPE_SEL          (0x04)
#define FLASH_VERFY_MODE        (0x02)          // self verify mode
#define FLASH_CON_ENABLE        (0x01)

// (0xF2) FECR;              // FECON        Flash and EEPROM control register
#define FLASH_BULK_ERASE        (0x80 | 0x03)
#define FLASH_MODE_EXIT         (0x30 | 0x03)
#define FLASH_START_ERASE_PGM   (0x08 | 0x03)
#define FLASH_START_READ        (0x04 | 0x03)
#define FLASH_RESET             (0x01)
#define FLASH_PBUFF_RESET       (0x02)
#define FLASH_FECR_INIT         (0x03)

// (0xF3) FESR;              // FECON        Flash and EEPROM status register
#define FLASH_BUSY              (0x80)
#define FLASH_VERIFY_OK         (0x40)
#define FLASH_CRC_MODE          (0x20)
#define FLASH_MWAIT_EN          (0x10)
#define FLASH_IRQ               (0x08)
#define FLASH_ST_PGM_MODE       (0x04)
#define FLASH_ST_ERASE_MODE     (0x02)
#define FLASH_ST_VERIFY_MODE    (0x01)

// (0xE7) FETR;              // FECON        Flash and EEPROM test register
#define FLASH_LOCK_DISABLE      (0x80)
#define FLASH_VPP_OUT_ENABLE    (0x60)
#define FLASH_FULL_READ         (0x08)
#define FLASH_PAGE_READ         (0x00)
#define FLASH_X_FAST            (0x04)
#define FLASH_Y_FAST            (0x00)
#define FLASH_EVEN_ENABLE       (0x02)
#define FLASH_ODD_ENABLE        (0x01)
#define FLASH_VMARGIN_ENABLE    (0x01)

//------------------------------------------------------------------------------
// Interrupt vectors address of A96T418 SFR.
#define HW_RESET_VECTOR             0x0000
#define EXTERNAL_INTERRUPT_10       0x0003
#define EXTERNAL_INTERRUPT_11       0x000B
#define LED_INTERRUPT          		0x0013
#define TOUCH_INTERRPUT           	0x001B
#define DUMMY_INTERRPUT           	0x0023
#define EXTERNAL_INTERRUPT_0TO5     0x002B
#define EXTERNAL_INTERRUPT_8        0x0033
#define USART1_TX_INTERRUPT         0x003B
#define USI0_I2C_INTERRUPT          0x0043
#define USI0_RX_INTERRUPT           0x004B
#define USI0_TX_INTERRUPT           0x0053
#define EXTERNAL_INTERRUPT_12       0x005B
#define T0_OVERFLOW_INTERRUPT       0x0063
#define T0_MACTCH_INTERRUPT         0x006B
#define T1_MACTCH_INTERRUPT         0x0073
#define T2_MACTCH_INTERRUPT         0x007B
#define T3_MACTCH_INTERRUPT         0x0083
#define T4T5_MACTH_INTERRUPT        0x008B
#define ADC_INTERRUPT               0x0093
#define USART1_RX_INTERRUPT         0x009B
#define WT_INTERRUPT                0x00A3
#define WDT_INTERRUPT               0x00AB
#define BIT_INTERRUPT               0x00B3
#define LVI_INTERRUPT               0x00BB

// Interrupt vectors Prioirty of A96T418 SFR. (For Keil C51)
#define EINT10_VECT         0   // IE.0
#define EINT11_VECT         1   // IE.1
#define USART2_TX_VECT 		2   // IE.2
#define TOUCH_VECT        	3   // IE.3
#define USART2_RX_VECT      4   // IE.4
#define EINT0_5_VECT        5   // IE.5

#define EINT8_VECT          6   // IE1.0
#define USART1_TX_VECT      7   // IE1.1
#define USI0_I2C_VECT       8   // IE1.2
#define USI0_RX_VECT        9   // IE1.3
#define USI0_TX_VECT        10  // IE1.4
#define EINT12_VECT         11  // IE1.5

#define T0_OVER_VECT        12  // IE2.0
#define T0_MATCH_VECT       13  // IE2.1
#define T1_MATCH_VECT       14  // IE2.2
#define T2_MATCH_VECT       15  // IE2.3
#define T3_MATCH_VECT       16  // IE2.4
#define T45_MATCH_VECT      17  // IE2.5

#define ADC_VECT            18  // IE3.0
#define USART1_RX_VECT      19  // IE3.1
#define WT_VECT             20  // IE3.2
#define WDT_VECT            21  // IE3.3
#define BIT_VECT            22  // IE3.4
#define LVI_VECT            23  // IE3.5


//------------------------------------------------------------------------------
// Interrupt enable/disable control
// EA REG
#define EINT10_EN()         (EINT10_INT_EN_BIT = 1)
#define EINT10_DIS()        (EINT10_INT_EN_BIT = 0)

#define EINT11_EN()         (EINT11_INT_EN_BIT = 1)
#define EINT11_DIS()        (EINT11_INT_EN_BIT = 0)

#define LED_INT_EN()        (LED_INT_EN_BIT = 1)
#define LED_INT_DIS()       (LED_INT_EN_BIT = 0)

#define TOUCH_INT_EN()      (TOUCH_INT_EN_BIT = 1)
#define TOUCH_INT_DIS()     (TOUCH_INT_EN_BIT = 0)

#define EINT0_5_EN()        (EINT_INT0_5_EN_BIT = 1)
#define EINT0_5_DIS()       (EINT_INT0_5_EN_BIT = 0)

#define GLOBAL_INTERRUPT_EN()       (EA = 1)
#define GLOBAL_INTERRUPT_DIS()      (EA = 0)

#define EI()                (EA = 1)
#define DI()                (EA = 0)

// IE1 REG
#define EINT8_INT_EN()      (IE1 |=0X01)
#define EINT8_INT_DIS()     (IE1 &= ~(0X01))

#define USART1_TX_EN()      (IE1 |=0X02)
#define USART1_TX_DIS()     (IE1 &= ~(0X02))

#define USI0_I2C_EN()       (IE1 |=0X04)
#define USI0_I2C_DIS()      (IE1 &= ~(0X04))

#define USI0_RX_EN()        (IE1 |=0X08)
#define USI0_RX_DIS()       (IE1 &= ~(0X08))

#define USI0_TX_EN()        (IE1 |=0X10)
#define USI0_TX_DIS()       (IE1 &= ~(0X10))

#define EINT12_INT_EN()     (IE1 |=0X20)
#define EINT12_INT_DIS()    (IE1 &= ~(0X20))

// IE2 REG
#define TIMER0_OVER_EN()    (IE2 |=0X01)
#define TIMER0_OVER_DIS()   (IE2 &= ~(0X01))

#define TIMER0_MATCH_EN()   (IE2 |=0X02)
#define TIMER0_MATCH_DIS()  (IE2 &= ~(0X02))

#define TIMER1_MATCH_EN()   (IE2 |=0X04)
#define TIMER1_MATCH_DIS()  (IE2 &= ~(0X04))

#define TIMER2_MATCH_EN()   (IE2 |=0X08)
#define TIMER2_MATCH_DIS()  (IE2 &= ~(0X08))

#define TIMER3_MATCH_EN()   (IE2 |=0X10)
#define TIMER3_MATCH_DIS()  (IE2 &= ~(0X10))

#define TIMER4_5_MATCH_EN()  (IE2 |=0X20)
#define TIMER4_5_MATCH_DIS() (IE2 &= ~(0X20))

// IE3 REG
#define ADC_INT_EN()        (IE3 |=0X01)
#define ADC_INT_DIS()       (IE3 &= ~(0X01))

#define USART1_RX_EN()      (IE3 |=0X02)
#define USART1_RX_DIS()     (IE3 &= ~(0X02))

#define WT_INT_EN()         (IE3 |=0X04)
#define WT_INT_DIS()        (IE3 &= ~(0X04))

#define WDT_INT_EN()        (IE3 |=0X08)
#define WDT_INT_DIS()       (IE3 &= ~(0X08))

#define BIT_INT_EN()        (IE3 |=0X10)
#define BIT_INT_DIS()       (IE3 &= ~(0X10))

#define LVI_INT_EN()        (IE3 |=0X20)
#define LVI_INT_DIS()       (IE3 &= ~(0X20))
//------------------------------------------------------------------------------
/* CLOCK Control Register bits */
//------------------------------------------------------------------------------
//	SCCR (System and clock control Register : 0x8A, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define SCCR_IRC_16MHZ      ((INT8U)0x00)   /*!< Internal 16MHZ RC OSC for system clock */
#define SCCR_RESERVED       ((INT8U)0x01)   /*!< External Main OSC for system clock  */
#if A96T418_MODE==1			
#define SCCR_EXT_SOSC       ((INT8U)0x02)   /*!< External Sub OSC for system clock  */
#define SCCR_IRC_128KHZ     ((INT8U)0x03)   /*!< Internal 128Khz RC OSC for system clock  */
#endif
#if A96T418_MODE==0		
#define SCCR_IRC_32KHZ     ((INT8U)0x03)   /*!< Internal 32Khz RC OSC for system clock  */
#endif

//------------------------------------------------------------------------------
//	OSCCR (Oscillator Control Register : 0xC8, Initial Value : 0x28 )
//------------------------------------------------------------------------------
#define OSCCR_LSIRCE_DIS    ((INT8U)0x00)   /*!< OSCCR[6]
                                            Control the Operation the Low Frequency (128Khz)
                                            internal RC Oscillator at stop mode.
                                            0 : Disable
                                            */
#define OSCCR_LSIRCE_EN     ((INT8U)0x40)   /*!< OSCCR[6]
                                            Control the Operation the Low Frequency (128Khz)
                                            internal RC Oscillator at stop mode.
                                            1 : Enable
                                            */
#define OSCCR_IRCS_DIV64    ((INT8U)0x00)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/64 = 0.5Mhz
                                            */
#define OSCCR_IRCS_DIV32    ((INT8U)0x08)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/32 = 1Mhz
                                            */
#define OSCCR_IRCS_DIV16    ((INT8U)0x10)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/16 = 2Mhz
                                            */
#define OSCCR_IRCS_DIV8     ((INT8U)0x18)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/8 = 4Mhz
                                            */
#define OSCCR_IRCS_DIV4     ((INT8U)0x20)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/4 = 8Mhz
                                            */
#define OSCCR_IRCS_DIV2     ((INT8U)0x28)   /*!< OSCCR[5:3]
                                            Internal RC Oscillator Post-devider Selection
                                            INTRC/2 = 16Mhz
                                            */               
#define OSCCR_HIRCE_EN      ((INT8U)0x00)   /*!< OSCCR[2]
                                            Control the Operation of the High Frequency (16Mhz)
                                            Internal RC oscillator
                                            !! Caution 1 : Disable
                                            */                                                           
#define OSCCR_HIRCE_DIS     ((INT8U)0x04)   /*!< OSCCR[2]
                                            Control the Operation of the High Frequency (16Mhz)
                                            Internal RC oscillator
                                            !! Caution 0 : Enable
                                            */                                     
#if A96T418_MODE==1		
#define OSCCR_SCLKE_DIS     ((INT8U)0x00)   /*!< OSCCR[0]
                                            Control the Operation of the External Sub Oscillator
                                            0 : Disable
                                            */
#define OSCCR_SCLKE_EN      ((INT8U)0x01)   /*!< OSCCR[0]
                                            Control the Operation of the External Sub Oscillator
                                            1 : Enable
                                            */
#endif
//------------------------------------------------------------------------------
//	LVICR (Low Voltage Indicator Control Register : 0x86, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define LVIF        ((INT8U)0x20) 	/*!< LVICR[5]
                                    Low Voltage Indicator Flag Bit
                                    0: No detection, 1 : Detection
                                    */
#define LVIEN       ((INT8U)0x10)	/*!< LVICR[4]
                                    Low Voltage Indicator Enable Bit
                                    0: Disable, 1 : Enable
                                    */							
#define LVIVS_2P28  ((INT8U)0x06) 	/*!< LVICR[3:0]
                                    LVI Level Select
									0110 : 2.28V Select
                                    */	
#define LVIVS_2P46  ((INT8U)0x07) 	/*!< LVICR[3:0]
                                    LVI Level Select
									0111 : 2.46V Select
                                    */	
#define LVIVS_2P68  ((INT8U)0x08) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1000 : 2.68V Select
                                    */	
#define LVIVS_2P81  ((INT8U)0x09) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1001 : 2.81V Select
                                    */	
#define LVIVS_3P06  ((INT8U)0x0A) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1010 : 3.06V Select
                                    */	
#define LVIVS_3P21  ((INT8U)0x0B) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1011 : 3.21V Select
                                    */	
#define LVIVS_3P56  ((INT8U)0x0C) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1100 : 3.56V Select
                                    */	
#define LVIVS_3P73  ((INT8U)0x0D) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1101 : 3.73V Select
                                    */	
#define LVIVS_3P91  ((INT8U)0x0E) 	/*!< LVICR[3:0]
                                    LVI Level Select
									0100 : 3.91V Select
                                    */	
#define LVIVS_4P25  ((INT8U)0x0F) 	/*!< LVICR[3:0]
                                    LVI Level Select
									1111 : 4.25V Select
                                    */				
//------------------------------------------------------------------------------
//	WTDR (Watch Timer Data Register : 0x89, Initial Value : 0x7F )
//------------------------------------------------------------------------------
#define WTCL        ((INT8U)0x80)   /*!< WTDR[7]
                                    Clear WT Counter
                                    0 : Free Run, 1 : Clear WT Counter (auto clear after 1 Cycle)
                                    */	 
//------------------------------------------------------------------------------
//	BITCR (Basic Interval Timer Control Register : 0x8B, Initial Value : 0x45 )
//------------------------------------------------------------------------------
#define BITIFR          ((INT8U)0x80) 	/*!< BITCR[7]
                                        When BIT Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : BIT interrupt no generation
                                        1 : BIT interrupt generation
                                        */
#define BITCK_DIV4096   ((INT8U)0x00) 	/*!< BITCR[6:4]
                                        Select BIT clock source
										000 : fx/4096
                                        */
#define BITCK_DIV1024   ((INT8U)0x10) 	/*!< BITCR[6:4]
                                        Select BIT clock source
										001 : fx/1024
                                         */
#define BITCK_DIV128    ((INT8U)0x20) 	/*!< BITCR[6:4]
                                        Select BIT clock source
                                        010 : fx/128
                                        */
#define BITCK_DIV16     ((INT8U)0x30) 	/*!< BITCR[6:4]
                                        Select BIT clock source
                                        011 : fx/16
                                        */
#define BITCK_DIV32     ((INT8U)0x40) 	/*!< BITCR[6:4]
                                        Select BIT clock source
                                        100 : LSIRC/32 (Default)
                                        */
#define BCLR            ((INT8U)0x08) 	/*!< BITCR[3]
                                        If this bit is written to '1', BIT Counter is cleared to '0'
                                        0 : Free Running
                                        1 : Clear Counter
                                        */
#define BCK_0P5         ((INT8U)0x00) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        000 : 0.5ms (BIT Clock * 2)
                                        */
#define BCK_1           ((INT8U)0x01) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        001 : 1ms (BIT Clock * 4)
                                        */
#define BCK_2           ((INT8U)0x02) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        010 : 2ms (BIT Clock * 8)
                                        */
#define BCK_4           ((INT8U)0x03) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        011 : 4ms (BIT Clock * 16)
                                        */
#define BCK_8           ((INT8U)0x04) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        100 : 8ms (BIT Clock * 32)
                                        */
#define BCK_16          ((INT8U)0x05) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        101 : 16ms (BIT Clock * 64) (default)
                                        */	
#define BCK_32          ((INT8U)0x06) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        110 : 32ms (BIT Clock * 128)
                                        */	
#define BCK_64          ((INT8U)0x07) 	/*!< BITCR[2:0]
                                        Select BIT overflow period
                                        111 : 64ms (BIT Clock * 256)
                                        */												
//------------------------------------------------------------------------------
//	WDTCR (Watch Dog Timer Control Register : 0x8D, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define WDTEN           ((INT8U)0x80) 	/*!< WDTCR[7]
                                        Control WDT Operation
                                        0 : Disable, 1 : Enable
                                        */
#define WDTRSON         ((INT8U)0x40) 	/*!< WDTCR[6]
                                        Control WDT RESET Operation
                                        0 : Free Running 8-bit timer
                                        1 : Watch Dog Timer RESET ON
                                        */
#define WDTCL           ((INT8U)0x20) 	/*!< WDTCR[5]
                                        Control WDT Operation
                                        0 : Free Run
                                        1 : Clear WDT Counter (auto clear after 1 Cycle)
                                        */
#if A96T418_MODE==1
#define WDTCK           ((INT8U)0x02) 	/*!< WDTCR[1]
                                        Control WDT Operation
                                        0 : BIT overflow for WDT clock
                                        1 : BIT overflow/8 for WDT clock
                                        */
#endif
#if A96T418_MODE==0
#define WDTCK_1           ((INT8U)0x02) 	
#define WDTCK_2           ((INT8U)0x02) 	
#define WDTCK_4           ((INT8U)0x02) 	
#define WDTCK_8           ((INT8U)0x02) 	
#define WDTCK_16           ((INT8U)0x02) 	
#define WDTCK_32           ((INT8U)0x02) 	
#define WDTCK_64           ((INT8U)0x02) 	/*!< WDTCR[3:1]
                                        Control WDT Operation
                                        0 : BIT overflow for WDT clock
                                        1 : BIT overflow/8 for WDT clock
                                        */
#endif
#define WDTIFR          ((INT8U)0x01) 	/*!< WDTCR[0]
                                        Control WDT Operation
                                        0 : WDT Interrupt no generation
                                        1 : WDT Interrupt generation
                                        */		
//------------------------------------------------------------------------------
//	P0OD (P0 Open-drain Selection Register : 0x91, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P07OD   ((INT8U)0x80)   /*!< P0OD[7]
                                Configure Open-drain of P07 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P06OD   ((INT8U)0x40)   /*!< P0OD[6]
                                Configure Open-drain of P06 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P05OD   ((INT8U)0x20)   /*!< P0OD[5]
                                Configure Open-drain of P05 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P04OD   ((INT8U)0x10)   /*!< P0OD[4]
                                Configure Open-drain of P04 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P03OD   ((INT8U)0x08)   /*!< P0OD[3]
                                Configure Open-drain of P03 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P02OD   ((INT8U)0x04)   /*!< P0OD[2]
                                Configure Open-drain of P02 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P01OD   ((INT8U)0x02)   /*!< P0OD[1]
                                Configure Open-drain of P01 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P00OD   ((INT8U)0x01)   /*!< P0OD[0]
                                Configure Open-drain of P00 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
//------------------------------------------------------------------------------
//	P1OD (P1 Open-drain Selection Register : 0x92, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P17OD   ((INT8U)0x80)   /*!< P1OD[7]
                                Configure Open-drain of P17 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P16OD   ((INT8U)0x40)   /*!< P1OD[6]
                                Configure Open-drain of P16 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P15OD   ((INT8U)0x20)   /*!< P1OD[5]
                                Configure Open-drain of P15 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P14OD   ((INT8U)0x10)   /*!< P1OD[4]
                                Configure Open-drain of P14 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P13OD   ((INT8U)0x08)   /*!< P1OD[3]
                                Configure Open-drain of P13 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P12OD   ((INT8U)0x04)   /*!< P1OD[2]
                                Configure Open-drain of P12 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P11OD   ((INT8U)0x02)   /*!< P1OD[1]
                                Configure Open-drain of P11 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P10OD   ((INT8U)0x01)   /*!< P1OD[0]
                                Configure Open-drain of P10 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
//------------------------------------------------------------------------------
//	P2OD (P2 Open-drain Selection Register : 0x93, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P27OD   ((INT8U)0x80)   /*!< P2OD[7]
                                Configure Open-drain of P27 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P26OD   ((INT8U)0x40)   /*!< P2OD[6]
                                Configure Open-drain of P26 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P25OD   ((INT8U)0x20)   /*!< P2OD[5]
                                Configure Open-drain of P25 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P24OD   ((INT8U)0x10)   /*!< P2OD[4]
                                Configure Open-drain of P24 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P23OD   ((INT8U)0x08)   /*!< P2OD[3]
                                Configure Open-drain of P23 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P22OD   ((INT8U)0x04)   /*!< P2OD[2]
                                Configure Open-drain of P22 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P21OD   ((INT8U)0x02)   /*!< P2OD[1]
                                Configure Open-drain of P21 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
#define P20OD   ((INT8U)0x01)   /*!< P2OD[0]
                                Configure Open-drain of P20 Port
                                0 : Push-pull output
                                1 : Open-drain output
                                */
//------------------------------------------------------------------------------
//	WTCR (Watch Dog Timer Control Register : 0x96, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define WTEN                ((INT8U)0x80) 	/*!< WTCR[7]
                                            Control Watch Timer
                                            0 : Disable, 1 : Enable
                                            */
#define WTIFR               ((INT8U)0x10) 	/*!< WTCR[4]
                                            When WT Interrupt occurs, this bit becomes '1'.
                                            For clearing bit, write '0' to this bit
                                            or automatically clear by INT_ACK signal.
                                            Writing '1' has no effect.
                                            0 : WT Interrupt no generation
                                            1 : WT Interrupt generation
                                            */
#define WTIN_DIV2_7         ((INT8U)0x00) 	/*!< WTCR[3:2]
                                            Determine interrupt interval
                                            00 : fWCK/2^7
                                            */
#define WTIN_DIV2_13        ((INT8U)0x04) 	/*!< WTCR[3:2]
                                            Determine interrupt interval
                                            01 : fWCK/2^13
                                            */
#define WTIN_DIV2_14        ((INT8U)0x08) 	/*!< WTCR[3:2]
                                            Determine interrupt interval
                                            10 : fWCK/2^14
                                            */
#define WTIN_DIV2_14_WTDR   ((INT8U)0x0C) 	/*!< WTCR[3:2]
                                            Determine interrupt interval
											11 : fWCK/(2^14 x (7bit WTDR Value+1))
                                            */
#define WTCK_FSUB           ((INT8U)0x00) 	/*!< WTCR[1:0]
                                            Determine Source Clock
                                            00 : fSUB
                                            */
#define WTCK_DIV256         ((INT8U)0x01) 	/*!< WTCR[1:0]
                                            Determine Source Clock
                                            01 : fx/256
                                            */
#define WTCK_DIV128         ((INT8U)0x02) 	/*!< WTCR[1:0]
                                            Determine Source Clock
                                            10 : fx/128
                                            */
#define WTCK_DIV64          ((INT8U)0x003) 	/*!< WTCR[1:0]
                                            Determine Source Clock
                                            11 : fx/64
                                            */											
//------------------------------------------------------------------------------
//	BUZCR (Buzzer Control Register : 0x97, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define BUCK_DIV32  ((INT8U)0x00) 	/*!< BUZCR[2:1]
                                    Buzzer Driver Source Clock Selection
									00 : fx/32
                                    */
#define BUCK_DIV64  ((INT8U)0x02) 	/*!< BUZCR[2:1]
                                    Buzzer Driver Source Clock Selection
									01 : fx/64
                                    */
#define BUCK_DIV128 ((INT8U)0x04) 	/*!< BUZCR[2:1]
                                    Buzzer Driver Source Clock Selection
									10 : fx/128
                                    */
#define BUCK_DIV256 ((INT8U)0x06) 	/*!< BUZCR[2:1]
                                    Buzzer Driver Source Clock Selection
									11 : fx/256
                                    */
#define BUZEN       ((INT8U)0x01) 	/*!< BUZCR[0]
                                    Buzzer Driver Operation Control
                                    0 : Buzzer Driver disable
                                    1 : Buzzer Driver enable
                                    */
//------------------------------------------------------------------------------
//	ADCCRL (A/D Converter Counter Low Register : 0x9C, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define STBY      ((INT8U)0x80) 	/*!< ADCCRL[7]
                                    Control Operation of A/D
                                    (The ADC module is automatically disabled at stop mode)
                                    0 : ADC module disable
                                    1 : ADC module enable
                                    */
#define ADST      ((INT8U)0x40) 	/*!< ADCCRL[6]
                                    Control A/D Conversion stop/start.
                                    0 : No effect
                                    1 : ADC Conversion Start and auto clear
                                    */
#if A96T418_MODE==1			
#define REFSEL    ((INT8U)0x20) 	/*!< ADCCRL[5]
                                    A/D Converter Reference Selection
                                    0 : Internal Reference (VDD)
                                    1 : External Reference (AVREF)
                                    */
#endif
#define AFLAG     ((INT8U)0x10) 	/*!< ADCCRL[4]
                                    A/D Converter Operation State
                                    (This bit is cleared to '0' when the STBY bit
                                    is set to '0' or when the CPU is at STOP mode)
                                    0 : During A/D Conversion
                                    1 : A/D Conversion finished
                                    */
#define ADSEL_AN0 ((INT8U)0x00) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0000 : AN0
                                    */
#define ADSEL_AN1 ((INT8U)0x01) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0001 : AN1
                                    */
#define ADSEL_AN2 ((INT8U)0x02) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0010 : AN2
                                    */
#define ADSEL_AN3 ((INT8U)0x03) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0011 : AN3
                                    */
#define ADSEL_AN4 ((INT8U)0x04) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0100 : AN4
                                    */
#define ADSEL_AN5 ((INT8U)0x05) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0101 : AN5
                                    */
#define ADSEL_AN6 ((INT8U)0x06) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0110 : AN6
                                    */
#define ADSEL_AN7 ((INT8U)0x07) 	/*!< ADCCRL[3:0]
                                    A/D Converter input selection
									0111 : AN7
                                    */
//------------------------------------------------------------------------------
//	ADCCRH (A/D Converter Counter High Register : 0x9D, Initial Value : 0x01 )
//------------------------------------------------------------------------------
#define ADCIFR              ((INT8U)0x80) 	/*!< ADCCRH[7]
                                            When ADC interrupt occurs, this bit becomes '1'.
                                            For clearing bit, write '0' to this bit
                                            or auto clear by INT_ACK signal.
                                            Writing '1' has no effect.
                                            0 : ADC Interrupt no generation
                                            1 : ADC Interrupt generation
                                            */
#define IREF                ((INT8U)0x40) 	/*!< ADCCRH[6]
                                            Select internal voltage reference.
                                            0 : External input signal source select
                                            1 : Test only
                                            */
#define TRIG_ADST           ((INT8U)0x00) 	/*!< ADCCRH[5:3]
                                            A/D Trigger Signal Selection
                                            000 : ADST
                                            */
#define TRIG_T1_A_MATCH_SIG ((INT8U)0x08) 	/*!< ADCCRH[5:3]
                                            A/D Trigger Signal Selection
											001 : Timer 1 A match signal
                                            */
#define TRIG_T3_A_MATCH_SIG ((INT8U)0x10) 	/*!< ADCCRH[5:3]
                                            A/D Trigger Signal Selection
											010 : Timer 3 A match signal
                                            */
#define TRIG_EXTINT0_7      ((INT8U)0x18) 	/*!< ADCCRH[5:3]
                                            A/D Trigger Signal Selection
                                            011 : EXTINT0~7
                                            */
#define TRIG_EXTINT8        ((INT8U)0x20) 	/*!< ADCCRH[5:3]
                                            A/D Trigger Signal Selection
                                            100 : EXTINT8
                                            */
#define ALIGN               ((INT8U)0x20) 	/*!< ADCCRH[2]
                                            A/D Converter data align selection.
                                            0 : MSB align (ADCDRH[7:0], ADCDRL[7:4])
                                            1 : LSB align (ADCRDH[3:0], ADCDRL[7:0])
                                            */
#define CKSEL_DIV1          ((INT8U)0x00) 	/*!< ADCCRH[1:0]
                                            A/D Converter Clock selection
                                            00 : fx/1
                                            */
#define CKSEL_DIV2          ((INT8U)0x01) 	/*!< ADCCRH[1:0]
                                            A/D Converter Clock selection
                                            01 : fx/2
                                            */
#define CKSEL_DIV4          ((INT8U)0x02) 	/*!< ADCCRH[1:0]
                                            A/D Converter Clock selection
                                            10 : fx/4
                                            */
#define CKSEL_DIV8          ((INT8U)0x03) 	/*!< ADCCRH[1:0]
                                            A/D Converter Clock selection
                                            11 : fx/8
                                            */
//------------------------------------------------------------------------------
//	P0IO (P0 Direction Register : 0xA1, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P07IO   ((INT8U)0x80) 	/*!< P0IO[7]
                                P07 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P06IO   ((INT8U)0x40) 	/*!< P0IO[6]
                                P06 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P05IO   ((INT8U)0x20) 	/*!< P0IO[5]
                                P05 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P04IO   ((INT8U)0x10) 	/*!< P0IO[4]
                                P04 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P03IO   ((INT8U)0x08) 	/*!< P0IO[3]
                                P03 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P02IO   ((INT8U)0x04) 	/*!< P0IO[2]
                                P02 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P01IO   ((INT8U)0x02) 	/*!< P0IO[1]
                                P01 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P00IO   ((INT8U)0x01) 	/*!< P0IO[0]
                                P00 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
//------------------------------------------------------------------------------
//	EIPOL0L (External Interrupt Polarity 0 Low Register : 0xA4, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define POL3_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0L[7:6]
                                        EINT3 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL3_RIS_ADGE   ((INT8U)0x40) 	/*!< EIPOL0L[7:6]
                                        EINT3 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL3_FAL_ADGE   ((INT8U)0x80) 	/*!< EIPOL0L[7:6]
                                        EINT3 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL3_BOTH_ADGE  ((INT8U)0xC0) 	/*!< EIPOL0L[7:6]
                                        EINT3 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL2_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0L[5:4]
                                        EINT2 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL2_RIS_ADGE   ((INT8U)0x10) 	/*!< EIPOL0L[5:4]
                                        EINT2 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL2_FAL_ADGE   ((INT8U)0x20) 	/*!< EIPOL0L[5:4]
                                        EINT2 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL2_BOTH_ADGE  ((INT8U)0x30) 	/*!< EIPOL0L[5:4]
                                        EINT2 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL1_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0L[3:2]
                                        EINT1 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL1_RIS_ADGE   ((INT8U)0x04) 	/*!< EIPOL0L[3:2]
                                        EINT1 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL1_FAL_ADGE   ((INT8U)0x08) 	/*!< EIPOL0L[3:2]
                                        EINT1 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL1_BOTH_ADGE  ((INT8U)0x0C) 	/*!< EIPOL0L[3:2]
                                        EINT1 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL0_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0L[1:0]
                                        EINT0 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL0_RIS_ADGE   ((INT8U)0x01) 	/*!< EIPOL0L[1:0]
                                        EINT0 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL0_FAL_ADGE   ((INT8U)0x02) 	/*!< EIPOL0L[1:0]
                                        EINT0 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL0_BOTH_ADGE  ((INT8U)0x03) 	/*!< EIPOL0L[1:0]
                                        EINT0 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */                                
//------------------------------------------------------------------------------
//	EIPOL0H (External Interrupt Polarity 0 High Register : 0xA5, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define POL7_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0H[7:6]
                                        EINT7 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL7_RIS_ADGE   ((INT8U)0x40) 	/*!< EIPOL0H[7:6]
                                        EINT7 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL7_FAL_ADGE   ((INT8U)0x80) 	/*!< EIPOL0H[7:6]
                                        EINT7 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL7_BOTH_ADGE  ((INT8U)0xC0) 	/*!< EIPOL0H[7:6]
                                        EINT7 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL6_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0H[5:4]
                                        EINT6 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL6_RIS_ADGE   ((INT8U)0x10) 	/*!< EIPOL0H[5:4]
                                        EINT6 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL6_FAL_ADGE   ((INT8U)0x20) 	/*!< EIPOL0H[5:4]
                                        EINT6 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL6_BOTH_ADGE  ((INT8U)0x30) 	/*!< EIPOL0H[5:4]
                                        EINT6 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL5_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0H[3:2]
                                        EINT5 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL5_RIS_ADGE   ((INT8U)0x04) 	/*!< EIPOL0H[3:2]
                                        EINT5 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL5_FAL_ADGE   ((INT8U)0x08) 	/*!< EIPOL0H[3:2]
                                        EINT5 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL5_BOTH_ADGE  ((INT8U)0x0C) 	/*!< EIPOL0H[3:2]
                                        EINT5 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL4_NO_INT     ((INT8U)0x00) 	/*!< EIPOL0H[1:0]
                                        EINT4 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL4_RIS_ADGE   ((INT8U)0x01) 	/*!< EIPOL0H[1:0]
                                        EINT4 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL4_FAL_ADGE   ((INT8U)0x02) 	/*!< EIPOL0H[1:0]
                                        EINT4 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL4_BOTH_ADGE  ((INT8U)0x03) 	/*!< EIPOL0H[1:0]
                                        EINT4 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */  
//------------------------------------------------------------------------------
//	EIFLAG1 (External Interrupt Flag 1 Register : 0xA6, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T0OVIFR         ((INT8U)0x80) 	/*!< EIFLAG1[7]
                                        When T0 overflow interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or automatically clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T0 overflow Interrupt no generation
                                        1 : T0 overflow Interrupt generation
                                        */
#define T0IFR           ((INT8U)0x40) 	/*!< EIFLAG1[6]
                                        When T0 interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or automatically clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T0 Interrupt no generation
                                        1 : T0 Interrupt generation
                                        */
#define EIFLAG1_FLAG12  ((INT8U)0x08) 	/*!< EIFLAG1[3]
										When an External Interrupt 12 is occurred, the flag becomes '1'.
										The flag is cleared by writing '0' to the bit or automatically cleared by INT_ACK signal.
										Writing '1' has no effect.
										0 : External Interrupt 12 not occurred
										1 : External Interrupt 12 occurred
										*/
#define EIFLAG1_FLAG11  ((INT8U)0x04) 	/*!< EIFLAG1[2]
										When an External Interrupt 11 is occurred, the flag becomes '1'.
										The flag is cleared by writing '0' to the bit or automatically cleared by INT_ACK signal.
										Writing '1' has no effect.
										0 : External Interrupt 11 not occurred
										1 : External Interrupt 11 occurred
										*/
#define EIFLAG1_FLAG10  ((INT8U)0x02) 	/*!< EIFLAG1[1]
										When an External Interrupt 10 is occurred, the flag becomes '1'.
										The flag is cleared by writing '0' to the bit or automatically cleared by INT_ACK signal.
										Writing '1' has no effect.
										0 : External Interrupt 10 not occurred
										1 : External Interrupt 10 occurred
										*/
#define EIFLAG1_FLAG8   ((INT8U)0x01) 	/*!< EIFLAG1[0]
										When an External Interrupt 8 is occurred, the flag becomes '1'.
										The flag is cleared by writing '0' to the bit or automatically cleared by INT_ACK signal.
										Writing '1' has no effect.
										0 : External Interrupt 8 not occurred
										1 : External Interrupt 8 occurred
										*/
//------------------------------------------------------------------------------
//	EIPOL1 (External Interrupt Polarity 1 Register : 0xA7, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define POL12_NO_INT     ((INT8U)0x00) 	/*!< EIPOL1[7:6]
                                        EINT12 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL12_RIS_ADGE   ((INT8U)0x40) 	/*!< EIPOL1[7:6]
                                        EINT12 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL12_FAL_ADGE   ((INT8U)0x80) 	/*!< EIPOL1[7:6]
                                        EINT12 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL12_BOTH_ADGE  ((INT8U)0xC0) 	/*!< EIPOL1[7:6]
                                        EINT12 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL11_NO_INT     ((INT8U)0x00) 	/*!< EIPOL1[5:4]
                                        EINT11 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL11_RIS_ADGE   ((INT8U)0x10) 	/*!< EIPOL1[5:4]
                                        EINT11 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL11_FAL_ADGE   ((INT8U)0x20) 	/*!< EIPOL1[5:4]
                                        EINT11 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL11_BOTH_ADGE  ((INT8U)0x30) 	/*!< EIPOL1[5:4]
                                        EINT11 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL10_NO_INT     ((INT8U)0x00) 	/*!< EIPOL1[3:2]
                                        EINT10 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL10_RIS_ADGE   ((INT8U)0x04) 	/*!< EIPOL1[3:2]
                                        EINT10 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL10_FAL_ADGE   ((INT8U)0x08) 	/*!< EIPOL1[3:2]
                                        EINT10 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL10_BOTH_ADGE  ((INT8U)0x0C) 	/*!< EIPOL1[3:2]
                                        EINT10 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */
#define POL8_NO_INT     ((INT8U)0x00) 	/*!< EIPOL1[1:0]
                                        EINT8 polarity selection
                                        00 : No interrupt at any edge
                                        */
#define POL8_RIS_ADGE   ((INT8U)0x01) 	/*!< EIPOL1[1:0]
                                        EINT8 polarity selection
                                        01 : Interrupt on rising edge
                                        */    
#define POL8_FAL_ADGE   ((INT8U)0x02) 	/*!< EIPOL1[1:0]
                                        EINT8 polarity selection
                                        10 : Interrupt on falling edge
                                        */    
#define POL8_BOTH_ADGE  ((INT8U)0x03) 	/*!< EIPOL1[1:0]
                                        EINT8 polarity selection
                                        11 : Interrupt on both of rising and falling edge
                                        */  
//------------------------------------------------------------------------------
//	IE (Interrupt Enable Register 1 : 0xA8, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define INT5E  ((INT8U)0x20) 	/*!< IE1[5]
                                Enable or Disable External Interrupt 0~5 (EINT0~EINT5)
								0 : Disable, 1 : Enable
                                */
#define INT4E  ((INT8U)0x10) 	/*!< IE1[4]
                                Reserved
                                */
#define INT3E   ((INT8U)0x08) 	/*!< IE1[3]
                                Enable or Disable Touch Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT2E   ((INT8U)0x04) 	/*!< IE1[2]
                                Enable or Disable LED Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT1E   ((INT8U)0x02) 	/*!< IE1[1]
                                Enable or Disable External Interrupt 11 (EINT11)
								0 : Disable, 1 : Enable
                                */
#define INT0E   ((INT8U)0x01) 	/*!< IE1[0]
                                Enable or Disable External Interrupt 10 (EINT10)
								0 : Disable, 1 : Enable
                                */
//------------------------------------------------------------------------------
//	IE1 (Interrupt Enable Register 1 : 0xA9, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define INT11E  ((INT8U)0x20) 	/*!< IE1[5]
                                Enable or Disable External Interrupt 12 (EINT12)
								0 : Disable, 1 : Enable
                                */
#define INT10E  ((INT8U)0x10) 	/*!< IE1[4]
                                Enable or Disable USI0Tx Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT9E   ((INT8U)0x08) 	/*!< IE1[3]
                                Enable or Disable USI0 Rx Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT8E   ((INT8U)0x04) 	/*!< IE1[2]
                                Enable or Disable USI0 I2C Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT7E   ((INT8U)0x02) 	/*!< IE1[1]
                                Enable or Disable USART1 TX Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT6E   ((INT8U)0x01) 	/*!< IE1[0]
                                Enable or Disable External Interrupt 8 (EINT8)
								0 : Disable, 1 : Enable
                                */
//------------------------------------------------------------------------------
//	IE2 (Interrupt Enable Register 2 : 0xAA, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define INT17E ((INT8U)0x20) 	/*!< IE2[5]
                                Enable or Disable Timer 4/5 Match Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT16E ((INT8U)0x10) 	/*!< IE2[4]
                                Enable or Disable Timer 3 Match Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT15E ((INT8U)0x08) 	/*!< IE2[3]
                                Enable or Disable Timer 2 Match Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT14E ((INT8U)0x04) 	/*!< IE2[2]
                                Enable or Disable Timer 1 Match Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT13E ((INT8U)0x02) 	/*!< IE2[1]
                                Enable or Disable Timer 0 I Match Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT12E ((INT8U)0x01) 	/*!< IE2[0]
                                Enable or Disable Timer 0 Overflow Interrupt
								0 : Disable, 1 : Enable
                                */
//------------------------------------------------------------------------------
//	IE3 (Interrupt Enable Register 3 : 0xAB, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define INT23E ((INT8U)0x20) 	/*!< IE3[5]
                                Enable or Disable LVI Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT22E ((INT8U)0x10) 	/*!< IE3[4]
                                Enable or Disable BIT Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT21E ((INT8U)0x08) 	/*!< IE3[3]
                                Enable or Disable WDT Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT20E ((INT8U)0x04) 	/*!< IE3[2]
                                Enable or Disable WT Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT19E ((INT8U)0x02) 	/*!< IE3[1]
                                Enable or Disable USART1 RX Interrupt
								0 : Disable, 1 : Enable
                                */
#define INT18E ((INT8U)0x01) 	/*!< IE3[0]
                                Enable or Disable ADC Interrupt
								0 : Disable, 1 : Enable
                                */
//------------------------------------------------------------------------------
//	P0PU (P0 Pull-up Resistor Selection Register : 0xAC, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P07PU   ((INT8U)0x80)   /*!< P0PU[7]
                                Configure Pull-up Resistor of P07 Port
                                0 : Disable, 1 : Enable
                                */
#define P06PU   ((INT8U)0x40)   /*!< P0PU[6]
                                Configure Pull-up Resistor of P06 Port
                                0 : Disable, 1 : Enable
                                */
#define P05PU   ((INT8U)0x20)   /*!< P0PU[5]
                                Configure Pull-up Resistor of P05 Port
                                0 : Disable, 1 : Enable
                                */
#define P04PU   ((INT8U)0x10)   /*!< P0PU[4]
                                Configure Pull-up Resistor of P04 Port
                                0 : Disable, 1 : Enable
                                */
#define P03PU   ((INT8U)0x08)   /*!< P0PU[3]
                                Configure Pull-up Resistor of P03 Port
                                0 : Disable, 1 : Enable
                                */
#define P02PU   ((INT8U)0x04)   /*!< P0PU[2]
                                Configure Pull-up Resistor of P02 Port
                                0 : Disable, 1 : Enable
                                */
#define P01PU   ((INT8U)0x02)   /*!< P0PU[1]
                                Configure Pull-up Resistor of P01 Port
                                0 : Disable, 1 : Enable
                                */
#define P00PU   ((INT8U)0x01)   /*!< P0PU[0]
                                Configure Pull-up Resistor of P00 Port
                                0 : Disable, 1 : Enable
                                */ 
//------------------------------------------------------------------------------
//	P1PU (P1 Pull-up Resistor Selection Register : 0xAD, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P17PU   ((INT8U)0x80)   /*!< P1PU[7]
                                Configure Pull-up Resistor of P17 Port
                                0 : Disable, 1 : Enable
                                */
#define P16PU   ((INT8U)0x40)   /*!< P1PU[6]
                                Configure Pull-up Resistor of P16 Port
                                0 : Disable, 1 : Enable
                                */
#define P15PU   ((INT8U)0x20)   /*!< P1PU[5]
                                Configure Pull-up Resistor of P15 Port
                                0 : Disable, 1 : Enable
                                */
#define P14PU   ((INT8U)0x10)   /*!< P1PU[4]
                                Configure Pull-up Resistor of P14 Port
                                0 : Disable, 1 : Enable
                                */
#define P13PU   ((INT8U)0x08)   /*!< P1PU[3]
                                Configure Pull-up Resistor of P13 Port
                                0 : Disable, 1 : Enable
                                */
#define P12PU   ((INT8U)0x04)   /*!< P1PU[2]
                                Configure Pull-up Resistor of P12 Port
                                0 : Disable, 1 : Enable
                                */
#define P11PU   ((INT8U)0x02)   /*!< P1PU[1]
                                Configure Pull-up Resistor of P11 Port
                                0 : Disable, 1 : Enable
                                */
#define P10PU   ((INT8U)0x01)   /*!< P1PU[0]
                                Configure Pull-up Resistor of P10 Port
                                0 : Disable, 1 : Enable
                                */ 
//------------------------------------------------------------------------------
//	P2PU (P2 Pull-up Resistor Selection Register : 0xAE, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P27PU   ((INT8U)0x80)   /*!< P2PU[7]
                                Configure Pull-up Resistor of P27 Port
                                0 : Disable, 1 : Enable
                                */
#define P26PU   ((INT8U)0x40)   /*!< P2PU[6]
                                Configure Pull-up Resistor of P26 Port
                                0 : Disable, 1 : Enable
                                */
#define P25PU   ((INT8U)0x20)   /*!< P2PU[5]
                                Configure Pull-up Resistor of P25 Port
                                0 : Disable, 1 : Enable
                                */
#define P24PU   ((INT8U)0x10)   /*!< P2PU[4]
                                Configure Pull-up Resistor of P24 Port
                                0 : Disable, 1 : Enable
                                */
#define P23PU   ((INT8U)0x08)   /*!< P2PU[3]
                                Configure Pull-up Resistor of P23 Port
                                0 : Disable, 1 : Enable
                                */
#define P22PU   ((INT8U)0x04)   /*!< P2PU[2]
                                Configure Pull-up Resistor of P22 Port
                                0 : Disable, 1 : Enable
                                */
#define P21PU   ((INT8U)0x02)   /*!< P2PU[1]
                                Configure Pull-up Resistor of P21 Port
                                0 : Disable, 1 : Enable
                                */
#define P20PU   ((INT8U)0x01)   /*!< P2PU[0]
                                Configure Pull-up Resistor of P20 Port
                                0 : Disable, 1 : Enable
                                */ 
//------------------------------------------------------------------------------
//	P3PU (P3 Pull-up Resistor Selection Register : 0xAF, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P31PU   ((INT8U)0x02)   /*!< P3PU[1]
                                Configure Pull-up Resistor of P31 Port
                                0 : Disable, 1 : Enable
                                */
#define P30PU   ((INT8U)0x01)   /*!< P3PU[0]
                                Configure Pull-up Resistor of P30 Port
                                0 : Disable, 1 : Enable
                                */ 
//------------------------------------------------------------------------------
//	P1IO (P1 Direction Register : 0xB1, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P17IO   ((INT8U)0x80) 	/*!< P1IO[7]
                                P17 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P16IO   ((INT8U)0x40) 	/*!< P1IO[6]
                                P16 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P15IO   ((INT8U)0x20) 	/*!< P1IO[5]
                                P15 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P14IO   ((INT8U)0x10) 	/*!< P1IO[4]
                                P14 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P13IO   ((INT8U)0x08) 	/*!< P1IO[3]
                                P13 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P12IO   ((INT8U)0x04) 	/*!< P1IO[2]
                                P12 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P11IO   ((INT8U)0x02) 	/*!< P1IO[1]
                                P11 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P10IO   ((INT8U)0x01) 	/*!< P1IO[0]
                                P10 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
//------------------------------------------------------------------------------
//	T0CR (Timer 0 Control Register : 0xB2, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T0EN            ((INT8U)0x80) 	/*!< T0CR[7]
                                        Control Timer 0
                                        0 : Timer 0 disable, 1 : Timer 0 enable
                                        */
#define T0MS_TC         ((INT8U)0x00) 	/*!< T0CR[5:4]
                                        Control Timer 0 Operation Mode
                                        00 : Timer/counter mode
                                        */
#define T0MS_PWM        ((INT8U)0x10) 	/*!< T0CR[5:4]
                                        Control Timer 0 Operation Mode
										01 : PWM mode
                                        */
#define T0MS_CAP        ((INT8U)0x20) 	/*!< T0CR[5:4]
                                        Control Timer 0 Operation Mode
										10 : Capture mode
                                        */
#define T0CK_DIV2       ((INT8U)0x00) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        000 : fx/2
                                        */
#define T0CK_DIV4       ((INT8U)0x02) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        001 : fx/4
                                        */
#define T0CK_DIV8       ((INT8U)0x04) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        010 : fx/8
                                        */
#define T0CK_DIV32      ((INT8U)0x06) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        011 : fx/32
                                        */
#define T0CK_DIV128     ((INT8U)0x08) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        100 : fx/128
                                        */
#define T0CK_DIV512     ((INT8U)0x0A) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        101 : fx/512
                                        */
#define T0CK_DIV2048    ((INT8U)0x0C) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        110 : fx/2048
                                        */
#define T0CK_EC         ((INT8U)0x0E) 	/*!< T0CR[3:1]
                                        Select Timer 0 clock source. 
                                        fx is a system clock frequency
                                        111 : External Clock (EC0)
                                        */
#define T0CC            ((INT8U)0x01) 	/*!< T0CR[0]
                                        Clear timer 0 Counter
                                        0 : No effect
                                        1 : Clear the Timer 0 counter
                                        */
//------------------------------------------------------------------------------
//	P2IO (P2 Direction Register : 0xB9, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P27IO   ((INT8U)0x80) 	/*!< P2IO[7]
                                P27 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P26IO   ((INT8U)0x40) 	/*!< P2IO[6]
                                P26 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P25IO   ((INT8U)0x20) 	/*!< P2IO[5]
                                P25 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P24IO   ((INT8U)0x10) 	/*!< P2IO[4]
                                P24 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P23IO   ((INT8U)0x08) 	/*!< P2IO[3]
                                P23 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P22IO   ((INT8U)0x04) 	/*!< P2IO[2]
                                P22 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P21IO   ((INT8U)0x02) 	/*!< P2IO[1]
                                P21 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P20IO   ((INT8U)0x01) 	/*!< P2IO[0]
                                P20 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
//------------------------------------------------------------------------------
//	T1CRL (Timer 1 Control Low Register : 0xBA, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T1CK_DIV2048    ((INT8U)0x00) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        000 : fx/2048
                                        */
#define T1CK_DIV512     ((INT8U)0x20) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        001 : fx/512
                                        */
#define T1CK_DIV64      ((INT8U)0x40) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        010 : fx/64
                                        */
#define T1CK_DIV8       ((INT8U)0x60) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        011 : fx/8
                                        */
#define T1CK_DIV4       ((INT8U)0x80) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        100 : fx/4
                                        */
#define T1CK_DIV2       ((INT8U)0xA0) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        101 : fx/2
                                        */
#define T1CK_DIV1       ((INT8U)0xC0) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        110 : fx/1
                                        */
#define T1CK_EC         ((INT8U)0xE0) 	/*!< T1CRL[7:5]
                                        Select Timer 1 clock source.
                                        111 : External clock (EC1)
                                        */
#define T1IFR           ((INT8U)0x10) 	/*!< T1CRL[4]
                                        When T1 Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T1 Interrupt no generation
                                        1 : T1 Interrupt generation
                                        */
#define T1POL           ((INT8U)0x04) 	/*!< T1CRL[2]
                                        T1O/PWM1O Polarity Selection
                                        0 : Start High (T1O/PWM1O is low level at disable)
                                        1 : Start Low (T1O/PWM1O is high level at disable)
                                        */											
#define T1ECE           ((INT8U)0x02) 	/*!< T1CRL[1]
                                        Timer 1 External Clock Edge Selection
                                        0 : External clock falling edge
                                        1 : External clock rising edge
                                        */
#define T1CNTR          ((INT8U)0x01) 	/*!< T1CRL[0]
                                        Timer 1 Counter Read Control
                                        0 : No effect
                                        1 : Load the counter value to the B data register
                                        */											
//------------------------------------------------------------------------------
//	T1CRH (Timer 1 Control High Register : 0xBB, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T1EN             ((INT8U)0x80) 	/*!< T1CRH[7]
                                        Control Timer 1
                                        0 : Timer 1 disable
                                        1 : Timer 1 enable (Counter clear and start)
                                        */
#define T1MS_TC          ((INT8U)0x00) 	/*!< T1CRH[5:4]
                                        Control Timer 1 Operation Mode
                                        00 : Timer/counter mode (T1O: toggle at A match)
                                        */
#define T1MS_CAP         ((INT8U)0x10) 	/*!< T1CRH[5:4]
                                        Control Timer 1 Operation Mode
										01 : Capture mode (The A match interrupt can occur)
                                        */
#define T1MS_PPG_OS      ((INT8U)0x20) 	/*!< T1CRH[5:4]
                                        Control Timer 1 Operation Mode
										10 : PPG one-shot mode (PWM1O)
                                        */
#define T1MS_PPG_RP      ((INT8U)0x30) 	/*!< T1CRH[5:4]
                                        Control Timer 1 Operation Mode
										11 : PPG repeat mode (PWM1O)
                                        */
#define T1CC             ((INT8U)0x01) 	/*!< T1CRH[0]
                                        Clear Timer 1 Counter
                                        0 : No effect
                                        1 : Clear the Timer 1 counter
                                        */
//------------------------------------------------------------------------------
//	EIFLAG0 (External Interrupt Flag0 Register : 0xC0, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define EIFLAG0_FLAG7 ((INT8U)0x80) 	/*!< EIFLAG0[7]
                                        When an External Interrupt 7 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 7 not occurred
                                        1 : External Interrupt 7 occurred
                                        */
#define EIFLAG0_FLAG6 ((INT8U)0x40) 	/*!< EIFLAG0[6]
                                        When an External Interrupt 6 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 6 not occurred
                                        1 : External Interrupt 6 occurred
                                        */
#define EIFLAG0_FLAG5 ((INT8U)0x20) 	/*!< EIFLAG0[5]
                                        When an External Interrupt 5 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 5 not occurred
                                        1 : External Interrupt 5 occurred
                                        */
#define EIFLAG0_FLAG4 ((INT8U)0x10) 	/*!< EIFLAG0[4]
                                        When an External Interrupt 4 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 4 not occurred
                                        1 : External Interrupt 4 occurred
                                        */
#define EIFLAG0_FLAG3 ((INT8U)0x08) 	/*!< EIFLAG0[3]
                                        When an External Interrupt 3 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 3 not occurred
                                        1 : External Interrupt 3 occurred
                                        */
#define EIFLAG0_FLAG2 ((INT8U)0x04) 	/*!< EIFLAG0[2]
                                        When an External Interrupt 2 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 2 not occurred
                                        1 : External Interrupt 2 occurred
                                        */
#define EIFLAG0_FLAG1 ((INT8U)0x02) 	/*!< EIFLAG0[1]
                                        When an External Interrupt 1 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 1 not occurred
                                        1 : External Interrupt 1 occurred
                                        */
#define EIFLAG0_FLAG0 ((INT8U)0x01) 	/*!< EIFLAG0[0]
                                        When an External Interrupt 0 is occurred, the flag becomes '1'.
                                        The flag is cleared only by writing '0' to the bit.
                                        So, the flag should be cleared by software.
                                        0 : External Interrupt 0 not occurred
                                        1 : External Interrupt 0 occurred
                                        */
//------------------------------------------------------------------------------
//	P3IO (P3 Direction Register : 0xC1, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P31IO   ((INT8U)0x02) 	/*!< P3IO[1]
                                P31 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
#define P30IO   ((INT8U)0x01) 	/*!< P3IO[0]
                                P30 Data I/O Direction.
                                0 : Input, 1 : Output
                                */ 
//------------------------------------------------------------------------------
//	T2CRL (Timer 2 Control Low Register : 0xC2, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T2CK_DIV512     ((INT8U)0x00) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        000 : fx/512
                                        */
#define T2CK_DIV128     ((INT8U)0x20) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        001 : fx/128
                                        */
#define T2CK_DIV32      ((INT8U)0x40) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        010 : fx/32
                                        */
#define T2CK_DIV8       ((INT8U)0x60) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        011 : fx/8
                                        */
#define T2CK_DIV4       ((INT8U)0x80) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        100 : fx/4
                                        */
#define T2CK_DIV2       ((INT8U)0xA0) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        101 : fx/2
                                        */
#define T2CK_DIV1       ((INT8U)0xC0) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        110 : fx/1
                                        */
#define T2CK_T1_A_MATCH ((INT8U)0xE0) 	/*!< T2CRL[7:5]
                                        Select Timer 2 clock source.
                                        fx is main system clock frequency
                                        111 : T1 A Match
                                        */
#define T2IFR           ((INT8U)0x10) 	/*!< T2CRL[4]
                                        When T2 Match Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T2 interrupt no generation
                                        1 : T2 interrupt generation
                                        */
#define T2POL           ((INT8U)0x04) 	/*!< T2CRL[2]
                                        T2O/PWM2O Polarity Selection
                                        0 : Start High (T2O/PWM2O is low level at disable)
                                        1 : Start Low (T2O/PWM2O is high level at disable)
                                        */
#define T2CNTR          ((INT8U)0x01) 	/*!< T2CRL[0]
                                        Timer 2 Counter Read Control
                                        0 : No effect
                                        1 : Load the counter value to the B data register
                                            (When write, automatically cleared '0' after being loaded)
                                        */
//------------------------------------------------------------------------------
//	T2CRH (Timer 2 Control High Register : 0xC3, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T2EN             ((INT8U)0x80) 	  /*!< T2CRH[7]
                                          Control Timer 2
                                          0 : Timer 2 disable
                                          1 : Timer 2 enable (Counter clear and start)
                                          */
#define T2MS_TC          ((INT8U)0x00) 	  /*!< T2CRH[5:4]
                                          Control Timer 2 Operation Mode
                                          00 : Timer/counter mode (T2O: toggle at A match)
                                          */
#define T2MS_CAP         ((INT8U)0x10) 	  /*!< T2CRH[5:4]
                                          Control Timer 2 Operation Mode
                                          01 : Capture mode (The A match interrupt can occur)
                                          */
#define T2MS_PPG_OS      ((INT8U)0x20)    /*!< T2CRH[5:4]
                                          Control Timer 2 Operation Mode
                                          10 : PPG one-shot mode (PWM2O)
                                          */
#define T2MS_PPG_RP      ((INT8U)0x30)    /*!< T2CRH[5:4]
                                          Control Timer 2 Operation Mode
                                          11 : PPG repeat mode (PWM2O)
                                          */
#define T2CC             ((INT8U)0x01) 	  /*!< T2CRH[0]
                                          Clear Timer 2 Counter
                                          0 : No effect
                                          1 : Clear the Timer 2 counter
                                              (When write, automatically cleared '0' after being cleared counter)
                                          */
//------------------------------------------------------------------------------
//	UCTRL1 (USART1 Control 1 Register : 0xCB, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define UMSEL_ASYN          ((INT8U)0x00) 	/*!< UCTRL1[7:6]
                                            Selects operation mode of USART1
                                            00 : Asynchronous Mode (Normal Uart)
                                            */ 
#define UMSEL_SYN           ((INT8U)0x40) 	/*!< UCTRL1[7:6]
                                            Selects operation mode of USART1
                                            01 : Synchronous Mode (Synchronous Uart)
                                            */ 
#define UMSEL_SPI           ((INT8U)0xC0) 	/*!< UCTRL1[7:6]
                                            Selects operation mode of USART1
                                            11 : SPI Mode
                                            */ 
#define UPM_NO              ((INT8U)0x00) 	/*!< UCTRL1[5:4]
                                            Selects Parity Generation and Check methods
                                            00 : No Parity
                                            */ 
#define UPM_EVEN            ((INT8U)0x20) 	/*!< UCTRL1[5:4]
                                            Selects Parity Generation and Check methods
                                            10 : Even Parity
                                            */ 
#define UPM_ODD             ((INT8U)0x30) 	/*!< UCTRL1[5:4]
                                            Selects Parity Generation and Check methods
                                            11 : Odd Parity
                                            */ 
#define USIZE_5             ((INT8U)0x00) 	/*!< UCTRL1[3:1]
                                            When in asynchronous or synchronous mode of operation,
                                            selects the length of data bits in frame.
                                            000 : 5-bit
                                            */ 
#define USIZE_6             ((INT8U)0x02) 	/*!< UCTRL1[3:1]
                                            When in asynchronous or synchronous mode of operation,
                                            selects the length of data bits in frame.
                                            001 : 6-bit
                                            */ 
#define USIZE_7             ((INT8U)0x04) 	/*!< UCTRL1[3:1]
                                            When in asynchronous or synchronous mode of operation,
                                            selects the length of data bits in frame.
                                            010 : 7-bit
                                            */ 
#define USIZE_8             ((INT8U)0x06) 	/*!< UCTRL1[3:1]
                                            When in asynchronous or synchronous mode of operation,
                                            selects the length of data bits in frame.
                                            011 : 8-bit
                                            */ 
#define USIZE_9             ((INT8U)0x0E) 	/*!< UCTRL1[3:1]
                                            When in asynchronous or synchronous mode of operation,
                                            selects the length of data bits in frame.
                                            111 : 9-bit
                                            */ 
#define UDORD               ((INT8U)0x04) 	/*!< UCTRL1[2]
                                            This bit is in the same bit position with USIZE1.
                                            In SPI mode, when set to one the MSB of the data byte is transmitted first.
                                            When set to zero the LSB of the data byte is transmitted first.
                                            0 : LSB First
                                            1 : MSB First
                                            */ 
#define UCPOL               ((INT8U)0x01) 	/*!< UCTRL1[0]
                                            Selects polarity of XCK in synchronous or SPI mode
                                            0 : TXD2 change @ Rising Edge, RXD2 change @ Falling Edge
                                            1 : TXD2 change @ Falling Edge, RXD2 change @ Rising Edge
                                            */ 
#define UCPHA               ((INT8U)0x02) 	/*!< UCTRL1[1]
                                            This bit is in the same bit position with USIZE0.
                                            In SPI mode, along with UCPOL bit, selects one of two clock formats for different kinds of synchronous serial peripherals.
                                            Leading edge means first XCK edge and trailing edge means 2nd or last clock edge of XCK in one XCK pulse.
                                            And Sample means detecting of incoming receive bit, Setup means preparing transmit data.
                                            UCPOL UCPHA     Leading Edge        Trailing Edge
                                             0      0   :   Sample (Rising)     Setup (Falling)
                                             0      1   :   Setup (Rising)      Sample (Falling)
                                             1      0   :   Sample (Falling)    Setup (Rising)
                                             1      1   :   Setup (Falling)     Sample (Rising)
                                            */
//------------------------------------------------------------------------------
//	UCTRL2 (USART1 Control 2 Register : 0xCC, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define UDRIE       ((INT8U)0x80)   /*!< UCTRL2[7]
                                    Interrupt enable bit for USART1 Data Register Empty.
                                    0 : Interrupt from UDRE is inhibited (use polling)
                                    1 : When UDRE is set, request an interrupt
                                    */
#define TXCIE       ((INT8U)0x40)   /*!< UCTRL2[6]
                                    Interrupt enable bit for Transmit Complete.
                                    0 : Interrupt from TXC is inhibited (use polling)
                                    1 : When TXC is set, request an interrupt
                                    */
#define RXCIE       ((INT8U)0x20)   /*!< UCTRL2[5]
                                    Interrupt enable bit for Receive Complete
                                    0 : Interrupt from RXC is inhibited (use polling)
                                    1 : When RXC is set, request an interrupt
                                    */
#define WAKEIE       ((INT8U)0x10)   /*!< UCTRL2[4]
                                    Interrupt enable bit for Asynchronous Wake in STOP mode.
                                    When device is in stop mode,
                                    if RXD2 goes to LOW level an interrupt can be requested to wake-up system.
                                    0 : Interrupt from Wake is inhibited
                                    1 : When WAKE is set, request an interrupt
                                    */
#define TXE         ((INT8U)0x08)   /*!< UCTRL2[3]
                                    Enables the transmitter unit.
                                    0 : Transmitter is disabled
                                    1 : Transmitter is enabled
                                    */
#define RXE         ((INT8U)0x04)   /*!< UCTRL2[2]
                                    Interrupt enable bit for Receive Complete
                                    0 : Receiver is disabled
                                    1 : Receiver is enabled
                                    */
#define USARTEN     ((INT8U)0x02)   /*!< UCTRL2[1]
                                    Activate USART1 module by supplying clock.
                                    0 : USART1 is disabled (clock is halted)
                                    1 : USART1 is enabled
                                    */
#define U2X         ((INT8U)0x01)   /*!< UCTRL2[0]
                                    This bit only has effect for the asynchronous operation
                                    and selects receiver sampling rate.
                                    0 : Normal asynchronous operation
                                    1 : Double Speed asynchronous operation
                                    */
//------------------------------------------------------------------------------
//	UCTRL3 (USART1 Control 3 Register : 0xCD, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define MASTER      ((INT8U)0x80)   /*!< UCTRL3[7]
                                    Selects master or slave in SPI or Synchronous mode operation and controls the direction of XCK pin.
                                    0 : Slave mode operation and XCK is input pin.
                                    1 : Master mode operation and XCK is output pin
                                    */
#define LOOPS       ((INT8U)0x40)   /*!< UCTRL3[6]
                                    Controls the Loop Back mode of USART1, for test mode
                                    0 : Normal operation
                                    1 : Loop Back mode
                                    */
#define DISXCK      ((INT8U)0x20)   /*!< UCTRL3[5]
                                    In Synchronous mode of operation, selects the waveform of XCK output.
                                    0 : XCK is free-running while USART is enabled in synchronous master mode.
                                    1 : XCK is active while any frame is on transferring.
                                    */
#define SPISS       ((INT8U)0x10)   /*!< UCTRL3[4]
                                    Controls the functionality of SS2 pin in master SPI mode.
                                    0 : SS2 pin is normal GPIO or other primary function
                                    1 : SS2 output to other slave device
                                    */
#define USBS        ((INT8U)0x04)   /*!< UCTRL3[2]
                                    Selects the length of stop bit in Asynchronous or Synchronous mode of operation.
                                    0 : 1 Stop bit
                                    1 : 2 Stop bit
                                    */
#define TX8         ((INT8U)0x02)   /*!< UCTRL3[1]
                                    The ninth bit of data frame in Asynchronous or Synchronous mode of operation.
                                    Write this bit first before loading the UDATA register.
                                    0 : MSB (9th bit) to be transmitted is '0'
                                    1 : MSB (9th bit) to be transmitted is '1'
                                    */
#define RX8         ((INT8U)0x01)   /*!< UCTRL3[0]
                                    The ninth bit of data frame in Asynchronous or Synchronous mode of operation.
                                    Read this bit first before reading the receive buffer.
                                    0 : MSB (9th bit) received is '0'
                                    1 : MSB (9th bit) received is '1'
                                    */
//------------------------------------------------------------------------------
//	USTAT (USART1 Status Register : 0xCF, Initial Value : 0x80 )
//------------------------------------------------------------------------------
#define UDRE   ((INT8U)0x80) 	/*!< USTAT[7]
                                The UDRE flag indicates if the transmit buffer (UDATA) is ready to be loaded with new data.
                                If UDRE is '1', it means the transmit buffer is empty and can hold one or two new data.
                                This flag can generate an UDRE interrupt.
                                Writing '0' to this bit position will clear UDRE flag.
                                0 : Transmit buffer is not empty.
                                1 : Transmit buffer is empty.
                                */
#define TXC     ((INT8U)0x40) 	/*!< USTAT[6]
                                This flag is set when the entire frame in the transmit shift register has been shifted out
                                and there is no new data currently present in the transmit buffer.
                                This flag is automatically cleared when the interrupt service routine of a TXC interrupt is executed.
                                It is also cleared by writing ��0�� to this bit position. This flag can generate a TXC interrupt.
                                0 : Transmit buffer is not empty.
                                1 : Transmit buffer is empty.
                                */
#define RXC     ((INT8U)0x20) 	/*!< USTAT[5]
                                This flag is set when there are unread data in the receive buffer and cleared when all the data in the receive buffer are read.
                                The RXC flag can be used to generate a RXC interrupt.
                                0 : There is no data unread in the receive buffer
                                1 : There are more than 1 data in the receive buffer
                                */
#define WAKE     ((INT8U)0x10) 	/*!< USTAT[4]
                                This flag is set when the RX pin is detected low while the CPU is in stop mode.
                                This flag can be used to generate a WAKE interrupt.
                                This bit is set only when in asynchronous mode of operation.
                                0 : No WAKE interrupt is generated.
                                1 : WAKE interrupt is generated.
                                */
#define SOFTRST  ((INT8U)0x08) 	/*!< USTAT[3]
                                This is an internal reset and only has effect on USART.
                                Writing '1' to this bit initializes the internal logic of USART and is auto cleared.
                                0 : No operation
                                1 : Reset USART
                                */
#define DOR      ((INT8U)0x04) 	/*!< USTAT[2]
                                This bit is set if a Data OverRun occurs.
                                While this bit is set, the incoming data frame is ignored.
                                This flag is valid until the receive buffer is read.
                                0 : No Data OverRun
                                1 : Data OverRun detected
                                */
#define FE       ((INT8U)0x02) 	/*!< USTAT[1]
                                This bit is set if the first stop bit of next character in the receive buffer is detected as '0'.
                                This bit is valid until the receive buffer is read.
                                0 : No Frame Error
                                1 : Frame Error detected
                                */
#define PE       ((INT8U)0x01) 	/*!< USTAT[0]
                                This bit is set if the next character in the receive buffer has a Parity Error when received while Parity Checking is enabled.
                                This bit is valid until the receive buffer is read.
                                0 : No Parity Error
                                1 : Parity Error detected
                                */                      
//------------------------------------------------------------------------------
//	P0FSRL (Port 0 Function Selection Low Register : 0xD2, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P0FSRL_P03_IO           ((INT8U)0x00) 	/*!< P0FSRL[7:6]
                                                P03 Function Select
                                                00 : I/O Port (EINT1 function possible when input)
                                                */	
#define P0FSRL_P03_BUZ0          ((INT8U)0x40) 	/*!< P0FSRL[7:6]
                                                P03 Function Select
                                                01 : BUZ0 Function
                                                */	
#if A96T418_MODE==1			
#define P0FSRL_P03_AN7_AVREF     ((INT8U)0x80) 	/*!< P0FSRL[7:6]
                                                P03 Function Select
                                                10 : AN7_AVREF Function
                                                */	
#endif
#define P0FSRL_P03_SCK0          ((INT8U)0xC0) 	/*!< P0FSRL[7:6]
                                                P03 Function Select
                                                11 : SCK0 Function
                                                */	
#define P0FSRL_P02_IO           ((INT8U)0x00) 	/*!< P0FSRL[5:4]
                                                P02 Function Select
                                                00 : I/O Port (EINT4 function possible when input)
                                                */	
#define P0FSRL_P02_TXD0_MOSI0_SDA0    ((INT8U)0x30) 	/*!< P0FSRL[5:4]
														P02 Function Select
														11 : TXD0_MOSI0_SDA0 Function
														*/
#define P0FSRL_P01_IO           ((INT8U)0x00) 	/*!< P0FSRL[3:2]
                                                P01 Function Select
                                                00 : I/O Port
                                                */	
#define P0FSRL_P01_T3O_PWM3O    ((INT8U)0x04) 	/*!< P0FSRL[3:2]
                                                P01 Function Select
                                                01 : T3O/PWM3O Function
                                                */	
#define P0FSRL_P01_RXD0_MISO0_SCL0  ((INT8U)0x0C) 	/*!< P0FSRL[3:2]
													P01 Function Select
													11 : RXD0/MISO0/SCL0 Function
													*/	
#define P0FSRL_P00_IO           ((INT8U)0x00) 	/*!< P0FSRL[1:0]
                                                P00 Function Select
                                                00 : I/O Port (EC3 function possible when input)
                                                */	
#define P0FSRL_P00_TXD1_MOSI1    ((INT8U)0x03) 	/*!< P0FSRL[1:0]
                                                P00 Function Select
                                                11 : TXD1_MOSI1 Function
                                                */	
//------------------------------------------------------------------------------
//	P0FSRH (Port 0 Function Selection High Register : 0xD3, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P0FSRH_P07_IO           ((INT8U)0x00) 	/*!< P0FSRH[7:6]
                                                P07 Function Select
                                                00 : I/O Port (EINT5 function possible when input)
                                                */	
#define P0FSRH_P07_AN3          ((INT8U)0x80) 	/*!< P0FSRH[7:6]
                                                P07 Function Select
                                                10 : AN3 Function
                                                */	
#define P0FSRH_P07_T5O_PWM5O    ((INT8U)0xC0) 	/*!< P0FSRH[7:6]
                                                P07 Function Select
                                                11 : T5O_PWM5O Function
                                                */	
#define P0FSRH_P06_IO           ((INT8U)0x00) 	/*!< P0FSRH[5:4]
                                                P06 Function Select
                                                00 : I/O Port (EINT4 function possible when input)
                                                */	
#define P0FSRH_P06_EC3          ((INT8U)0x10) 	/*!< P0FSRH[5:4]
                                                P06 Function Select
                                                01 : EC3 Function
                                                */	
#define P0FSRH_P06_AN2          ((INT8U)0x20) 	/*!< P0FSRH[5:4]
                                                P06 Function Select
                                                10 : AN2 Function
                                                */	
#define P0FSRH_P06_T4O_PWM4O    ((INT8U)0x30) 	/*!< P0FSRH[5:4]
                                                P06 Function Select
                                                11 : T4O_PWM4O Function
                                                */	
#define P0FSRH_P05_IO           ((INT8U)0x00) 	/*!< P0FSRH[3:2]
                                                P05 Function Select
                                                00 : I/O Port (EINT3 function possible when input)
                                                */	
#define P0FSRH_P05_AN1          ((INT8U)0x08) 	/*!< P0FSRH[3:2]
                                                P05 Function Select
                                                10 : AN1 Function
                                                */	
#define P0FSRH_P05_T3O_PWM3O     ((INT8U)0x0C) 	/*!< P0FSRH[3:2]
                                                P05 Function Select
                                                11 : T3O_PWM3O Function
                                                */	
#define P0FSRH_P04_IO           ((INT8U)0x00) 	/*!< P0FSRH[1:0]
                                                P04 Function Select
                                                00 : I/O Port (EINT2 function possible when input)
                                                */	
#define P0FSRH_P04_AN0          ((INT8U)0x02) 	/*!< P0FSRH[1:0]
                                                P04 Function Select
                                                10 : AN0 Function
                                                */	
#define P0FSRH_P04_SS0    		((INT8U)0x03) 	/*!< P0FSRH[1:0]
                                                P04 Function Select
                                                11 : SS0 Function
                                                */	
//------------------------------------------------------------------------------
//	P1FSRL (Port 1 Function Selection Low Register : 0xD4, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P1FSRL_P13_IO           ((INT8U)0x00) 	/*!< P1FSRL[7:6]
                                                P13 Function Select
                                                00 : I/O Port (EC1 function possible when input)
                                                */	
#define P1FSRL_P12_IO           ((INT8U)0x00) 	/*!< P1FSRL[5:4]
                                                P12 Function Select
                                                00 : I/O Port (EINT11 function possible when input)
                                                */	
#define P1FSRL_P12_AN6         ((INT8U)0x20) 	/*!< P1FSRL[5:4]
                                                P12 Function Select
                                                10 : AN6 Function
                                                */	
#define P1FSRL_P12_T2O_PWM2O    ((INT8U)0x30) 	/*!< P1FSRL[5:4]
                                                P12 Function Select
                                                11 : T2O/PWM2O Function
                                                */	
#define P1FSRL_P11_IO           ((INT8U)0x00) 	/*!< P1FSRL[3:2]
                                                P11 Function Select
                                                00 : I/O Port (EINT12 function possible when input)
                                                */	
#define P1FSRL_P11_T1O_PWM1O    ((INT8U)0x04) 	/*!< P1FSRL[3:2]
                                                P11 Function Select
                                                01 : T1O_PWM1O Function
                                                */	
#define P1FSRL_P11_AN5	         ((INT8U)0x08) 	/*!< P1FSRL[3:2]
                                                P11 Function Select
                                                10 : AN5 Function
                                                */	
#define P1FSRL_P11_TXD0_MOSI0_SDA0    ((INT8U)0x0C) 	/*!< P1FSRL[3:2]
														P11 Function Select
														11 : TXD0_MOSI0_SDA0 Function
														*/	
#define P1FSRL_P10_IO           ((INT8U)0x00) 	/*!< P1FSRL[1:0]
                                                P10 Function Select
                                                00 : I/O Port
                                                */	
#define P1FSRL_P10_AN4	         ((INT8U)0x02) 	/*!< P1FSRL[1:0]
                                                P10 Function Select
                                                10 : AN4 Function
                                                */	
#define P1FSRL_P10_RXD0_MISO0_SCL0 ((INT8U)0x03)/*!< P1FSRL[1:0]
                                                P10 Function Select
                                                11 : RXD0/MISO0/SCL0 Function
                                                */	
//------------------------------------------------------------------------------
//	P1FSRH (Port 1 Function Selection High Register : 0xD5, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P1FSRH_P17_IO           ((INT8U)0x00) 	/*!< P1FSRH[7:6]
                                                P17 Function Select
                                                00 : I/O Port (EINT6 function possible when input)
                                                */
#define P1FSRH_P17_TXD1_MOSI1    ((INT8U)0xC0) 	/*!< P1FSRH[7:6]
                                                P17 Function Select
                                                11 : TXD1/MOSI1 Function
                                                */
#define P1FSRH_P16_IO           ((INT8U)0x00) 	/*!< P1FSRH[5:4]
                                                P16 Function Select
                                                00 : I/O Port (EINT7 function possible when input)
                                                */
#define P1FSRH_P16_RXD1_MISO1    ((INT8U)0x30) 	/*!< P1FSRH[5:4]
                                                P16 Function Select
                                                11 : RXD1/MISO1 Function
                                                */
#define P1FSRH_P15_IO           ((INT8U)0x00) 	/*!< P1FSRH[3:2]
                                                P15 Function Select
                                                00 : I/O Port
                                                */
#define P1FSRH_P15_SCK1          ((INT8U)0x0C) 	/*!< P1FSRH[3:2]
                                                P15 Function Select
                                                11 : SCK1 Function
                                                */
#define P1FSRH_P14_IO           ((INT8U)0x00) 	/*!< P1FSRH[1:0]
                                                P14 Function Select
                                                00 : I/O Port
                                                */
#define P1FSRH_P14_SS1          ((INT8U)0x03)   /*!< P1FSRH[1:0]
                                                P14 Function Select
                                                03 :  : SS1 Function
                                                */												
//------------------------------------------------------------------------------
//	P2FSRH (Port 2 Function Selection High Register : 0xD7, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P2FSRH_P27_IO                ((INT8U)0x00) 	/*!< P2FSRH[7:6]
                                                    P27 Function Select
                                                    00 : I/O Port
                                                    */
#if A96T418_MODE==1			
#define P2FSRH_P27_SXIN              ((INT8U)0x40) 	/*!< P2FSRH[7:6]
                                                    P27 Function Select
                                                    01 : SXIN Function
                                                    */
#define P2FSRH_P27_T0O_PWM0O         ((INT8U)0x80) 	/*!< P2FSRH[7:6]
                                                    P27 Function Select
                                                    10 : T0O_PWM0O Function
                                                    */
#endif
#if A96T418_MODE==0			
#define P2FSRH_P27_T0O_PWM0O         ((INT8U)0x40) 	/*!< P2FSRH[7:6]
													P27 Function Select
													10 : T0O_PWM0O Function
													*/
#endif

#define P2FSRH_P26_IO                ((INT8U)0x00) 	/*!< P2FSRH[5:4]
                                                    P26 Function Select
                                                    00 : I/O Port
                                                    */
#define P2FSRH_P26_SXOUT              ((INT8U)0x10) /*!< P2FSRH[5:4]
                                                    P26 Function Select
                                                    01 : SXOUT Function
                                                    */
#define P2FSRH_P25_IO                ((INT8U)0x00) 	/*!< P2FSRH[3:2]
                                                    P25 Function Select
                                                    00 : I/O Port
                                                    */
#define P2FSRH_P25_EC1                ((INT8U)0x04) /*!< P2FSRH[3:2]
                                                    P25 Function Select
                                                    01 : EC1 Function
                                                    */
#define P2FSRH_P24_IO                ((INT8U)0x00) 	/*!< P2FSRH[1:0]
                                                    P24 Function Select
                                                    00 : I/O Port
                                                    */
//------------------------------------------------------------------------------
//	P2FSRL (Port 2 Function Selection Low Register : 0xD6, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P2FSRL_P23_IO                ((INT8U)0x00) 	/*!< P2FSRL[7:6]
                                                    P23 Function Select
                                                    00 : I/O Port
                                                    */
#define P2FSRL_P23_EC1                ((INT8U)0x40) /*!< P2FSRL[7:6]
                                                    P23 Function Select
                                                    01 : EC1 Function
                                                    */
#define P2FSRL_P22_IO                ((INT8U)0x00) 	/*!< P2FSRL[5:4]
                                                    P22 Function Select
                                                    00 : I/O Port
                                                    */
#define P2FSRL_P21_IO                ((INT8U)0x00) 	/*!< P2FSRL[3:2]
                                                    P21 Function Select
                                                    00 : I/O Port
                                                    */
#define P2FSRL_P20_IO                ((INT8U)0x00)   /*!< P2FSRL[1:0]
                                                    P20 Function Select
                                                    00 : I/O Port
                                                    */
//------------------------------------------------------------------------------
//	LVRCR (Low Voltage Reset Control Register : 0xD8, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define LVRVS_1P61 ((INT8U)0x00) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0000 : 1.61V
                                    */	
#define LVRVS_1P77 ((INT8U)0x04) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0010 : 1.77V
                                    */	
#define LVRVS_1P88 ((INT8U)0x06) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0011 : 1.88V
                                    */	
#define LVRVS_2P00 ((INT8U)0x08) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0100 : 2.00V
                                    */	
#define LVRVS_2P13 ((INT8U)0x0A) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0101 : 2.13V
                                    */	
#define LVRVS_2P28 ((INT8U)0x0D) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0110 : 2.28V
                                    */	
#define LVRVS_2P46 ((INT8U)0x0E) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									0111 : 2.46V
                                    */	
#define LVRVS_2P68 ((INT8U)0x10) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1000 : 2.68V
                                    */	
#define LVRVS_2P81 ((INT8U)0x12) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1001 : 2.81V
                                    */	
#define LVRVS_3P06 ((INT8U)0x14) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1010 : 3.06V
                                    */	
#define LVRVS_3P21 ((INT8U)0x16) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1011 : 3.21V
                                    */	
#define LVRVS_3P56 ((INT8U)0x18) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1100 : 3.56V
                                    */	
#define LVRVS_3P73 ((INT8U)0x1A) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1101 : 3.73V
                                    */	
#define LVRVS_3P91 ((INT8U)0x1C) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1110 : 3.91V
                                    */	
#define LVRVS_4P25 ((INT8U)0x1E) 	/*!< LVRCR[4:1]
                                    LVR Voltage Select
									1111 : 4.25V
                                    */	
#define LVREN      ((INT8U)0x01) 	/*!< LVRCR[0]
                                    LVR Operation
                                    0 : LVR Enable
                                    1 : LVR Disable
                                    */
//------------------------------------------------------------------------------
//	USI0CR1 (USI0 Control Register 1: For UART, SPI, and I2C mode : 0xD9, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define USI0MS_ASYNC    ((INT8U)0x00)   /*!< USI0CR1[7:6]
                                        Selects operation mode of USI0
                                        00 : Asynchronous Mode (UART)                                          
                                        */
#define USI0MS_SYNC     ((INT8U)0x40)   /*!< USI0CR1[7:6]
                                        Selects operation mode of USI0
                                        01 : Synchronous Mode   
                                        */
#define USI0MS_I2C      ((INT8U)0x80)   /*!< USI0CR1[7:6]
                                        Selects operation mode of USI0
                                        10 : I2C Mode   
                                        */
#define USI0MS_SPI      ((INT8U)0xC0)   /*!< USI0CR1[7:6]
                                        Selects operation mode of USI0
                                        11 : SPI Mode   
                                        */
#define USI0PM_NO       ((INT8U)0x00)   /*!< USI0CR1[5:4]
                                        Selects parity generation and check methods (only UART mode)
                                        00 : No Parity   
                                        */
#define USI0PM_EVEN     ((INT8U)0x20)   /*!< USI0CR1[5:4]
                                        Selects parity generation and check methods (only UART mode)
                                        10 : Even Parity   
                                        */
#define USI0PM_ODD      ((INT8U)0x30)   /*!< USI0CR1[5:4]
                                        Selects parity generation and check methods (only UART mode)
                                        11 : Odd Parity   
                                        */
#define USI0S_5         ((INT8U)0x00)   /*!< USI0CR1[3:1]
                                        When in asynchronous or synchronous mode of operation,
                                        selects the length of data bits in frame                        
                                        000 : 5bit   
                                        */                                        
#define USI0S_6         ((INT8U)0x02)   /*!< USI0CR1[3:1]
                                        When in asynchronous or synchronous mode of operation,
                                        selects the length of data bits in frame                        
                                        001 : 6bit   
                                        */                                        
#define USI0S_7         ((INT8U)0x04)   /*!< USI0CR1[3:1]
                                        When in asynchronous or synchronous mode of operation,
                                        selects the length of data bits in frame                        
                                        010 : 7bit   
                                        */                                        
#define USI0S_8         ((INT8U)0x06)   /*!< USI0CR1[3:1]
                                        When in asynchronous or synchronous mode of operation,
                                        selects the length of data bits in frame                        
                                        011 : 8bit   
                                        */                                        
#define USI0S_9         ((INT8U)0x0E)   /*!< USI0CR1[3:1]
                                        When in asynchronous or synchronous mode of operation,
                                        selects the length of data bits in frame                        
                                        111 : 9bit   
                                        */                        
#define ORD0_LSB        ((INT8U)0x00)   /*!< USI0CR1[2]
                                        This bit in the same bit position with USI0S1. The MSB of the data byte is transmitted
                                        first when set to '1' and the LSB when set to '0' (only SPI mode)
                                        0 : LSB-first
                                        */
#define ORD0_MSB        ((INT8U)0x04)   /*!< USI0CR1[2]
                                        This bit in the same bit position with USI0S1. The MSB of the data byte is transmitted
                                        first when set to '1' and the LSB when set to '0' (only SPI mode)
                                        1 : MSB-first   
                                        */                                           
#define USI0_CP0        ((INT8U)0x00)   /*!< CPHA[1], CPOL[0]
                                        This bit is in the same bit position with USInS0. This bit determines if data are
                                        sampled on the leading or trailing edge of SCKn (only SPI mode)                                          
                                        CPHA  CPOL   Leading Edge 	  Trailing Edge		
									 	 0     0  :  Sample(Rising)	  Setup(Falling)
										*/  
#define USI0_CP1        ((INT8U)0x01)   /*!< CPHA[1], CPOL[0]
                                        This bit is in the same bit position with USInS0. This bit determines if data are
                                        sampled on the leading or trailing edge of SCKn (only SPI mode)                                          
                                        CPHA  CPOL   Leading Edge 	  Trailing Edge		
										 0     1  :  Setup(Rising)    Sample(Falling)
										*/     
#define USI0_CP2        ((INT8U)0x02)   /*!< CPHA[1], CPOL[0]
                                        This bit is in the same bit position with USInS0. This bit determines if data are
                                        sampled on the leading or trailing edge of SCKn (only SPI mode)                                          
                                        CPHA  CPOL   Leading Edge 	  Trailing Edge		
										 1     0  :  Sample(Falling)  Setup(Rising)
										*/
#define USI0_CP3        ((INT8U)0x03)   /*!< CPHA[1], CPOL[0] 
                                        This bit is in the same bit position with USInS0. This bit determines if data are
                                        sampled on the leading or trailing edge of SCKn (only SPI mode)                                          
                                        CPHA  CPOL   Leading Edge 	  Trailing Edge		
										 1     1  :  Setup(Falling)   Sample(Rising)
                                        */
//------------------------------------------------------------------------------
//	USI0CR2 (USI0 Control Register 2: For UART, SPI, and I2C mode : 0xDA, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define DRIE0           ((INT8U)0x80)   /*!< USI0CR2[7]
                                        Interrupt enable bit for data register empty (only UART and SPI mode)
                                        0 : Interrupt from DRE0 is inhibited (use polling)
                                        1 : When DREn is set, request an interrupt
                                        */
#define TXCIE0          ((INT8U)0x40)   /*!< USI0CR2[6]
                                        Interrupt enable bit for transmit complete (only UART and SPI mode)
                                        0 : Interrupt from TXC0 is inhibited (use polling)
                                        1 : When TXC0 is set, request an interrupt
                                        */
#define RXCIE0          ((INT8U)0x20)   /*!< USI0CR2[5]
                                        Interrupt enable bit for receive complete (only UART and SPI mode)
                                        0 : Interrupt from RXC0 is inhibited (use polling)
                                        1 : When RXC0 is set, request an interrupt
                                        */
#define WAKEIE0         ((INT8U)0x10)   /*!< USI0CR2[4]
                                        Interrupt enable bit for asynchronous wake in STOP mode. When device is in stop
                                        mode, if RXD0 goes to low level an interrupt can be requested to wake-up system.
                                        (only UART mode). At that time the DRIEn bit and USI0ST1 register value should be
                                        set to '0b' and '00H', respectively.
                                        0 : Interrupt from Wake is inhibited
                                        1 : When WAKE0 is set, request an interrupt
                                        */
#define TXE0            ((INT8U)0x08)   /*!< USI0CR2[3]
                                        Enables the transmitter unit (only UART and SPI mode)
                                        0 : Transmitter is disabled
                                        1 : Transmitter is enabled
                                        */
#define RXE0            ((INT8U)0x04)   /*!< USI0CR2[2]
                                        Enables the receiver unit (only UART and SPI mode)
                                        0 : Receiver is disabled
                                        1 : Receiver is enabled
                                        */
#define USI0EN          ((INT8U)0x02)   /*!< USI0CR2[1]
                                        Activate USI0 function block by supplying
                                        0 : USI0 is disabled
                                        1 : USI0 is enabled
                                        */
#define DBLS0           ((INT8U)0x01)   /*!< USI0CR2[0]
                                        This bit selects receiver sampling rate (only UART)                 
                                        0 : Normal asynchronous operation
                                        1 : Double Speed asynchronous operation
                                        */                                        
//------------------------------------------------------------------------------
//	USI0CR3 (USI0 Control Register 3: For UART, SPI, and I2C mode : 0xDB, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define MASTER0         ((INT8U)0x80)   /*!< USI0CR3[7]
                                        Selects master or slave in SPI and synchronous mode operation and controls the 
                                        direction of SCK0 pin
                                        0 : Slave mode operation (External clock for SCK0)
                                        1 : Master mode operation(Internal clock for SCK0)
                                        */
#define LOOPS0          ((INT8U)0x40)   /*!< USI0CR3[6]
                                        Controls the loop back mode of USI0 for test mode (only UART and SPI mode)
                                        0 : Normal operation
                                        1 : Loop Back mode
                                        */
#define DISSCK0         ((INT8U)0x20)   /*!< USI0CR3[5]
                                        In synchronous mode of operation, selects the waveform of SCK0 output
                                        0 : ACK is free-running while UART is enabled in synchronous master mode
                                        1 : ACK is active while any frame is on transferring
                                        */
#define USI0SSEN        ((INT8U)0x10)   /*!< USI0CR3[4]
                                        This bit controls the SS0 pin operation (only SPI mode)
                                        0 : Disable
                                        1 : Enable
                                        */
#define FXCH0           ((INT8U)0x08)   /*!< USI0CR3[3]
                                        SPI port function exchange control bit (only SPI mode)
                                        0 : No effect
                                        1 : Exchange MOSI0 and MISO0 function
                                        */
#define USI0SB          ((INT8U)0x00)   /*!< USI0CR3[2]
                                        Selects the length of stop bit in asynchronous or synchronous mode of operation
                                        0 : 1 Stop Bit
                                        */
#define USI0TX8         ((INT8U)0x02)   /*!< USI0CR3[1]
                                        The ninth bit of data frame in asynchronous or synchronous mode of operation.
                                        Write this bit first before loading the USI0DR register
                                        0 : MSB (9th bit) to be transmitted is '0'
                                        1 : MSB (9th bit) to be transmitted is '1'
                                        */
#define USI0RX8         ((INT8U)0x01)   /*!< USI0CR3[0]
                                        The ninth bit of data frame in asynchronous or synchronous mode of operation.
                                        Write this bit first before loading the USI0DR register
                                        0 : MSB (9th bit) to be transmitted is '0'
                                        1 : MSB (9th bit) to be transmitted is '1'
                                        */  
//------------------------------------------------------------------------------
//	USI0CR4 (USI0 Control Register 4: For I2C mode : 0xDC, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define IIC0IFR         ((INT8U)0x80)   /*!< USI0CR4[7]
                                        This is an interrupt flag bit for I2C mode. When an interrupt occurs, this bit becomes '1'.
                                        This bit is cleared when write any values in the USI0ST2. Writing '1' has no effect.
                                        0 : I2C interrupt no generation
                                        1 : I2C interrupt generation
                                        */
#define RESET0          ((INT8U)0x20)   /*!< USI0CR4[5]
                                        Initialize Internal registers of I2C
                                        0 : No operation
                                        1 : Initialize I2C, auto cleared
                                        */
#define IIC0IE          ((INT8U)0x10)   /*!< USI0CR4[4]
                                        Interrupt Enable bit for I2C mode
                                        0 : Interrupt from I2C is inhibited (use polling)
                                        1 : Enable interrupt for I2C
                                        */
#define ACK0EN          ((INT8U)0x08)   /*!< USI0CR4[3]
                                        Controls ACK signal Generation at ninth SCL0 period.
                                        0 : No ACK signal is generated (SDA0 =1)
                                        1 : ACK signal is generated (SDA0 =0)
                                        */
#define IMASTER0        ((INT8U)0x04)   /*!< USI0CR4[2]
                                        Represent operating mode of I2C
                                        0 : I2C is in slave mode
                                        1 : I2C is in master mode
                                        */
#define STOPC0          ((INT8U)0x02)   /*!< USI0CR4[1]
                                        When I2C is master, STOP condition generation
                                        0 : No effect
                                        1 : STOP condition is to be generated
                                        */
#define STARTC0         ((INT8U)0x01)   /*!< USI0CR4[0]
                                        When I2C is master, START condition generation
                                        0 : No effect
                                        1 : START or repeated START condition is to be generated
                                        */
//------------------------------------------------------------------------------
//	USI0SAR (USI0 Slave Address Register: For I2C mode : 0xDD, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define USI0GCE         ((INT8U)0x01) 	/*!< USI0SAR[0]
                                        This bit decides whether I2C allows general call address or not in I2C slave mode.
                                        0 : Ignore general call address
                                        1 : Allow general call address
                                        */
//------------------------------------------------------------------------------
//	P0DB (P0 De-bounce Enable Register : 0xDE, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define DBCLK_DIV1      ((INT8U)0x00) 	/*!< P0DB[7:6]
                                        Configure De-bounce Clock of Port
                                        00 : fx/1
                                        */
#define DBCLK_DIV4      ((INT8U)0x40) 	/*!< P0DB[7:6]
                                        Configure De-bounce Clock of Port
                                        01 : fx/4
                                        */
#define DBCLK_DIV4096   ((INT8U)0x80)   /*!< P0DB[7:6]
                                        Configure De-bounce Clock of Port
                                        10 : fx/4096
                                        */
#define DBCLK_LSIRC     ((INT8U)0xC0) 	/*!< P0DB[7:6]
                                        Configure De-bounce Clock of Port
                                        11 : LSIRC (128KHz)
                                        */
#define P07DB           ((INT8U)0x10) 	/*!< P0DB[4]
                                        Configure De-bounce of P07 Port
                                        0 : Disable, 1 Enable
                                        */
#define P06DB           ((INT8U)0x08) 	/*!< P0DB[3]
                                        Configure De-bounce of P06 Port
                                        0 : Disable, 1 Enable
                                        */
#define P05DB           ((INT8U)0x04) 	/*!< P0DB[2]
                                        Configure De-bounce of P05 Port
                                        0 : Disable, 1 Enable
                                        */
#define P04DB           ((INT8U)0x02) 	/*!< P0DB[1]
                                        Configure De-bounce of P04 Port
                                        0 : Disable, 1 Enable
                                        */
#define P03DB           ((INT8U)0x01) 	/*!< P0DB[0]
                                        Configure De-bounce of P03 Port
                                        0 : Disable, 1 Enable
                                        */
//------------------------------------------------------------------------------
//	P123DB (P1/P2/P3 De-bounce Enable Register : 0xDF, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P31DB ((INT8U)0x10) 	/*!< P15DB[4]
                                Configure De-bounce of P31 Port
                                0 : Disable, 1 Enable
                                */
#define P26DB ((INT8U)0x08) 	/*!< P15DB[3]
                                Configure De-bounce of P26 Port
                                0 : Disable, 1 Enable
                                */
#define P25DB ((INT8U)0x04) 	/*!< P15DB[2]
                                Configure De-bounce of P25 Port
                                0 : Disable, 1 Enable
                                */
#define P12DB ((INT8U)0x02) 	/*!< P15DB[1]
                                Configure De-bounce of P12 Port
                                0 : Disable, 1 Enable
                                */
#define P11DB ((INT8U)0x01) 	/*!< P15DB[0]
                                Configure De-bounce of P11 Port
                                0 : Disable, 1 Enable
                                */
//------------------------------------------------------------------------------
//	USI0ST1 (USI0 Status Register 1 : 0xE1, Initial Value : 0x80 )
//------------------------------------------------------------------------------
#define DRE0        ((INT8U)0x80)  	/*!< USI0ST1[7]
                                    The DRE0 flag indicates if the transmit buffer (USI0DR) is ready to receive new data.
                                    If DRE0 is '1', the buffer is empty and ready to be written.
                                    This flag can generate a DRE1 interrupt.
                                    0 : Transmit buffer is not empty.
                                    1 : Transmit buffer is empty.
                                    */
#define TXC0        ((INT8U)0x40)  	/*!< USI0ST1[6]
                                    This flag is set when the entire frame in the transmit shift register has been shifted out 
                                    and there is no new data currently present in the transmit buffer.
                                    This flag is automatically cleared when the interrupt service routine of a TXC0 interrupt is executed.
                                    This flag can generate a TXC0 interrupt.
                                    This bit is automatically cleared.
                                    0 : Transmission is ongoing.
                                    1 : Transmit buffer is empty and the data in transmit shift register are shifted out completely.
                                    */
#define RXC0        ((INT8U)0x20)  	/*!< USI0ST1[5]
                                    This flag is set when there are unread data in the receive buffer
                                    and cleared when all the data in the receive buffer are read.
                                    The RXC0 flag can be used to generate a RXC0 interrupt.
                                    0 : There is no data unread in the receive buffer
                                    1 : There are more than 1 data in the receive buffer
                                    */
#define WAKE0       ((INT8U)0x10)  	/*!< USI0ST1[4]
                                    This flag is set when the RXD0 pin is detected low while the CPU is in STOP mode.
                                    This flag can be used to generate a WAKE0 interrupt.
                                    This bit is set only when in asynchronous mode of operation.
                                    This bit should be cleared by program software. (only UART mode)
                                    0 : No WAKE interrupt is generated.
                                    1 : WAKE interrupt is generated
                                    */
#define USI0RST     ((INT8U)0x08)  	/*!< USI0ST1[3]
                                    This is an internal reset and only has effect on USI0.
                                    Writing '1' to this bit initializes the internal logic of USI0 
                                    and this bit is automatically cleared to '0'.
                                    0 : No operation
                                    1 : Reset USI0
                                    */
#define DOR0        ((INT8U)0x04)  	/*!< USI0ST1[2]
                                    This bit is set if a Data Overrun occurs.
                                    While this bit is set, the incoming data frame is ignored.
                                    This flag is valid until the receive buffer is read.
                                    0 : No Data Overrun
                                    1 : Data Overrun detected
                                    */
#define FE0         ((INT8U)0x02)  	/*!< USI0ST1[1]
                                    This bit is set if the first stop bit of next character in the receive buffer is detected as '0'.
                                    This bit is valid until the receive buffer is read. (only UART mode)
                                    0 : No Frame Error
                                    1 : Frame Error detected
                                    */
#define PE0         ((INT8U)0x01)  	/*!< USI0ST1[0]
                                    This bit is set if the next character in the receive buffer
                                    has a Parity Error to be received while Parity Checking is enabled.
                                    This bit is valid until the receive buffer is read. (only UART mode)
                                    0 : No Parity Error
                                    1 : Parity Error detected
                                    */
//------------------------------------------------------------------------------
//	USI0ST2 (USI0 Status Register 2 : 0xE2, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define GCALL0      ((INT8U)0x80)  	/*!< USI0ST2[7]
                                    This bit has different meaning depending on whether I2C is master or slave.
                                    When I2C is a master, this bit represents whether it received AACK (address ACK) from slave.
                                    0 : No AACK is received (Master mode)
                                    1 : AACK is received (Master mode)
                                    When I2C is a slave, this bit is used to indicated general call.
                                    0 : General call address is not detected (Slave mode)
                                    1 : General call address is detected (Slave mode)
                                    */
#define TEND0       ((INT8U)0x40)  	/*!< USI0ST2[6]
                                    This bit is set when 1-byte of data is transferred completely
                                    0 : 1 byte of data is not completely transferred
                                    1 : 1 byte of data is completely transferred
                                    */
#define STOPD0      ((INT8U)0x20)  	/*!< USI0ST2[5]
                                    This bit is set when a STOP condition is detected.
                                    0 : No STOP condition is detected
                                    1 : STOP condition is detected
                                    */
#define SSEL0       ((INT8U)0x10)  	/*!< USI0ST2[4]
                                    This bit is set when I2C is addressed by other master.
                                    0 : I2C is not selected as a slave
                                    1 : I2C is addressed by other master and acts as a slave
                                    */
#define MLOST0      ((INT8U)0x08)  	/*!< USI0ST2[3]
                                    This bit represents the result of bus arbitration in master mode.
                                    0 : I2C maintains bus mastership
                                    1 : I2C maintains bus mastership during arbitration process
                                    */
#define BUSY0       ((INT8U)0x04)  	/*!< USI0ST2[2]
                                    This bit reflects bus status.
                                    0 : I2C bus is idle, so a master can issue a START condition
                                    1 : I2C bus is busy
                                    */
#define TMODE0      ((INT8U)0x02)  	/*!< USI0ST2[1]
                                    This bit is used to indicate whether I2C is transmitter or receiver.
                                    0 : I2C is a receiver
                                    1 : I2C is a transmitter
                                    */
#define RXACK0      ((INT8U)0x01)  	/*!< USI0ST2[0]
                                    This bit shows the state of ACK signal
                                    0 : No ACK is received
                                    1 : ACK is received at ninth SCL period
                                    */
//------------------------------------------------------------------------------
//	RSTFR (Reset Flag Register : 0xE8, Initial Value : 0x80 )
//------------------------------------------------------------------------------
#define PORF    ((INT8U)0x80)   /*!< RSTFR[7]
                                Power-On Reset flag bit.
                                The bit is reset by writing '0' to this bit.
                                0 : No detection, 1 Detection
                                */
#define EXTRF   ((INT8U)0x40)   /*!< RSTFR[6]
                                External Reset (RESETB) flag bit.
                                The bit is reset by writing '0' to this bit or by Power-On Reset.
                                0 : No detection, 1 Detection
                                */
#define WDTRF   ((INT8U)0x20)   /*!< RSTFR[5]
                                Watch Dog Reset flag bit.
                                The bit is reset by writing '0' to this bit or by Power-On Reset.
                                0 : No detection, 1 Detection
                                */
#define OCDRF   ((INT8U)0x10)   /*!< RSTFR[4]
                                On-chip debugger reset flag bit.
                                The bit is reset by writing '0' to this bit or by Power-On Reset.
                                0 : No detection, 1 Detection
                                */
#define LVRF    ((INT8U)0x08)   /*!< RSTFR[3]
                                Low Voltage Reset flag bit.
                                The bit is reset by writing '0' to this bit or by Power-On Reset.
                                0 : No detection, 1 Detection
                                */                                 
//------------------------------------------------------------------------------
//	P3FSR (Port 3 Function Selection Register : 0xEE, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define P3FSR_P31_IO    ((INT8U)0x00)   /*!< P3FSR[1]
                                        P31 Function Select
                                        00 : I/O Port
                                        */
#define P3FSR_P31_RXD1_MISO1  ((INT8U)0x0C) 	/*!< P3FSR[1]
												P31 Function Select
												11 : RXD1_MISO1 Function
												*/
#define P3FSR_P30_IO    ((INT8U)0x00)   /*!< P3FSR[0]
                                        P30 Function Select
                                        00 : I/O Port
                                        */
//------------------------------------------------------------------------------
//	T3CRH (Timer 3 Control High Register : 0x1000, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T3EN                ((INT8U)0x80)  	/*!< T3CRH[7]
                                            Control Timer 3
                                            0 : Timer 3 disable
                                            1 : Timer 3 enable (Counter clear and start)
                                            */
#define T3MS_TC             ((INT8U)0x00)  	/*!< T3CRH[5:4]
                                            Control Timer 3 Operation Mode
                                            00 : Timer/counter mode (T3O: toggle at A match)
                                            */
#define T3MS_CAP            ((INT8U)0x10)  	/*!< T3CRH[5:4]
                                            Control Timer 3 Operation Mode
                                            01 : Capture mode (The A match interrupt can occur)
                                            */
#define T3MS_PPG_OS         ((INT8U)0x20)  	/*!< T3CRH[5:4]
                                            Control Timer 3 Operation Mode
                                            10 : PPG one-shot mode (PWM3O)
                                            */
#define T3MS_PPG_RP         ((INT8U)0x30)  	/*!< T3CRH[5:4]
                                            Control Timer 3 Operation Mode
                                            11 : PPG repeat mode (PWM3O)
                                            */
#define T3CC                ((INT8U)0x01)  	/*!< T3CRH[0]
                                            Clear Timer 3 Counter
                                            0 : No effect
                                            1 : Clear the Timer 3 counter
                                                (When write, automatically cleared '0' after being cleared counter)
                                            */
//------------------------------------------------------------------------------
//	T3CRL (Timer 3 Control Low Register : 0x1001, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T3CK_DIV2048    ((INT8U)0x00)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        000 : fx/2048
                                        */
#define T3CK_DIV512     ((INT8U)0x20)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        001 : fx/512
                                        */
#define T3CK_DIV64      ((INT8U)0x40)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        010 : fx/64
                                        */
#define T3CK_DIV8       ((INT8U)0x60)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        011 : fx/8
                                        */
#define T3CK_DIV4       ((INT8U)0x80)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        100 : fx/4
                                        */
#define T3CK_DIV2       ((INT8U)0xA0)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        101 : fx/2
                                        */
#define T3CK_DIV1       ((INT8U)0xC0)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        110 : fx/1
                                        */
#define T3CK_EC3        ((INT8U)0xE0)   /*!< T3CRH[7:5]
                                        Select Timer 3 clock source.
                                        fx is main system clock frequency
                                        111 : External clock (EC3)
                                        */
#define T3IFR           ((INT8U)0x10)   /*!< T3CRH[4]
                                        When T3 Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T3 Interrupt no generation
                                        1 : T3 Interrupt generation
                                        */
#define T3POL           ((INT8U)0x04)   /*!< T3CRH[2]
                                        T3O/PWM3O Polarity Selection
                                        0 : Start High (T3O/PWM3O is low level at disable)
                                        1 : Start Low (T3O/PWM3O is high level at disable)
                                        */
#define T3ECE           ((INT8U)0x02)   /*!< T3CRH[1]
                                        Timer 3 External Clock Edge Selection
                                        0 : External clock falling edge
                                        1 : External clock rising edge
                                        */
#define T3CNTR          ((INT8U)0x01)   /*!< T3CRH[0]
                                        Timer 3 Counter Read Control
                                        0 : No effect
                                        1 : Load the counter value to the B data register
                                            (When write, automatically cleared '0' after being loaded)
                                        */
//------------------------------------------------------------------------------
//	T4CRH (Timer 4 Control High Register : 0x1008, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T3EN                ((INT8U)0x80)  	/*!< T4CRH[7]
                                            Control Timer 4
                                            0 : Timer 4 disable
                                            1 : Timer 4 enable (Counter clear and start)
                                            */
#define T4MS_TC             ((INT8U)0x00)  	/*!< T4CRH[5:4]
                                            Control Timer 4 Operation Mode
                                            00 : Timer/counter mode (T4O: toggle at A match)
                                            */
#define T4MS_CAP            ((INT8U)0x10)  	/*!< T4CRH[5:4]
                                            Control Timer 4 Operation Mode
                                            01 : Capture mode (The A match interrupt can occur)
                                            */
#define T4MS_PPG_OS         ((INT8U)0x20)  	/*!< T4CRH[5:4]
                                            Control Timer 4 Operation Mode
                                            10 : PPG one-shot mode (PWM4O)
                                            */
#define T4MS_PPG_RP         ((INT8U)0x30)  	/*!< T4CRH[5:4]
                                            Control Timer 4 Operation Mode
                                            11 : PPG repeat mode (PWM4O)
                                            */
#define T4CC                ((INT8U)0x01)  	/*!< T4CRH[0]
                                            Clear Timer 4 Counter
                                            0 : No effect
                                            1 : Clear the Timer 4 counter
                                                (When write, automatically cleared '0' after being cleared counter)
                                            */
//------------------------------------------------------------------------------
//	T4CRL (Timer 4 Control Low Register : 0x1009, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T4CK_DIV512    ((INT8U)0x00)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        000 : fx/512
                                        */
#define T4CK_DIV128     ((INT8U)0x20)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        001 : fx/128
                                        */
#define T4CK_DIV32      ((INT8U)0x40)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        010 : fx/32
                                        */
#define T4CK_DIV8       ((INT8U)0x60)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        011 : fx/8
                                        */
#define T4CK_DIV4       ((INT8U)0x80)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        100 : fx/4
                                        */
#define T4CK_DIV2       ((INT8U)0xA0)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        101 : fx/2
                                        */
#define T4CK_DIV1       ((INT8U)0xC0)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        110 : fx/1
                                        */
#define T4CK_T3_A_MATCH        ((INT8U)0xE0)   /*!< T4CRH[7:5]
                                        Select Timer 4 clock source.
                                        fx is main system clock frequency
                                        111 : T3 A Match
                                        */
#define T4IFR           ((INT8U)0x10)   /*!< T4CRH[4]
                                        When T4 Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T4 Interrupt no generation
                                        1 : T4 Interrupt generation
                                        */
#define T4POL           ((INT8U)0x04)   /*!< T4CRH[2]
                                        T4O/PWM4O Polarity Selection
                                        0 : Start High (T4O/PWM4O is low level at disable)
                                        1 : Start Low (T4O/PWM4O is high level at disable)
                                        */
#define T4CNTR          ((INT8U)0x01)   /*!< T4CRH[0]
                                        Timer 4 Counter Read Control
                                        0 : No effect
                                        1 : Load the counter value to the B data register
                                            (When write, automatically cleared '0' after being loaded)
                                        */
//------------------------------------------------------------------------------
//	T5CRH (Timer 5 Control High Register : 0x1010, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T5EN                ((INT8U)0x80)  	/*!< T4CRH[7]
                                            Control Timer 5
                                            0 : Timer 5 disable
                                            1 : Timer 5 enable (Counter clear and start)
                                            */
#define T5MS_TC             ((INT8U)0x00)  	/*!< T5CRH[5:4]
                                            Control Timer 5 Operation Mode
                                            00 : Timer/counter mode (T5O: toggle at A match)
                                            */
#define T5MS_CAP            ((INT8U)0x10)  	/*!< T4CRH[5:4]
                                            Control Timer 5 Operation Mode
                                            01 : Capture mode (The A match interrupt can occur)
                                            */
#define T5MS_PPG_OS         ((INT8U)0x20)  	/*!< T4CRH[5:4]
                                            Control Timer 5 Operation Mode
                                            10 : PPG one-shot mode (PWM5O)
                                            */
#define T5MS_PPG_RP         ((INT8U)0x30)  	/*!< T4CRH[5:4]
                                            Control Timer 5 Operation Mode
                                            11 : PPG repeat mode (PWM5O)
                                            */
#define T5CC                ((INT8U)0x01)  	/*!< T5CRH[0]
                                            Clear Timer 5 Counter
                                            0 : No effect
                                            1 : Clear the Timer 5 counter
                                                (When write, automatically cleared '0' after being cleared counter)
                                            */
//------------------------------------------------------------------------------
//	T5CRL (Timer 5 Control Low Register : 0x1011, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define T5CK_DIV512    ((INT8U)0x00)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        000 : fx/512
                                        */
#define T5CK_DIV128     ((INT8U)0x20)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        001 : fx/128
                                        */
#define T5CK_DIV32      ((INT8U)0x40)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        010 : fx/32
                                        */
#define T5CK_DIV8       ((INT8U)0x60)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        011 : fx/8
                                        */
#define T5CK_DIV4       ((INT8U)0x80)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        100 : fx/4
                                        */
#define T5CK_DIV2       ((INT8U)0xA0)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        101 : fx/2
                                        */
#define T5CK_DIV1       ((INT8U)0xC0)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        110 : fx/1
                                        */
#define T5CK_HSIRC      ((INT8U)0xE0)   /*!< T5CRH[7:5]
                                        Select Timer 5 clock source.
                                        fx is main system clock frequency
                                        111 : HSIRC Direct (16MHz)
                                        */
#define T5IFR           ((INT8U)0x10)   /*!< T5CRH[4]
                                        When T5 Interrupt occurs, this bit becomes '1'.
                                        For clearing bit, write '0' to this bit or auto clear by INT_ACK signal.
                                        Writing '1' has no effect.
                                        0 : T5 Interrupt no generation
                                        1 : T5 Interrupt generation
                                        */
#define T5POL           ((INT8U)0x04)   /*!< T5CRH[2]
                                        T5O/PWM5O Polarity Selection
                                        0 : Start High (T5O/PWM5O is low level at disable)
                                        1 : Start Low (T5O/PWM5O is high level at disable)
                                        */
#define T5CNTR          ((INT8U)0x01)   /*!< T5CRH[0]
                                        Timer 5 Counter Read Control
                                        0 : No effect
                                        1 : Load the counter value to the B data register
                                            (When write, automatically cleared '0' after being loaded)
                                        */
//------------------------------------------------------------------------------
//	UCTRL4 (USART1 Control 4 Register : 0x1018, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define RTOEN       ((INT8U)0x10)   /*!< UCTRL4[4]
                                    Enable receiver time out.
                                    0 : Disable, 1 : Enable
                                    */
#define RTO_FLAG    ((INT8U)0x08)   /*!< UCTRL4[3]
                                    This bit is set when RTO count overflows.
                                    This flag can generate an RTO interrupt.
                                    Writing '0' to this bit position will clear RTO_FLAG.
                                    0 : RTO count dose not overflow.
                                    1 : RTO count overflow.
                                    */
#define FPCREN      ((INT8U)0x04)   /*!< UCTRL4[2]
                                    Enable baud rate compensation
                                    0 : Disable, 1 : Enable
                                    */
#define AOVSSEL     ((INT8U)0x02)   /*!< UCTRL4[1]
                                    Select additional oversampling rates
                                    0 : Select X13
                                    1 : Select X4
                                    */
#define AOVSEN      ((INT8U)0x01)   /*!< UCTRL4[0]
                                    Enable additional oversampling rates selection
                                    0 : Disable, 1 : Enable
                                    */
//------------------------------------------------------------------------------
//	FEMR (Flash Mode Register : 0x1020, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define FSEL        ((INT8U)0x80)   /*!< FEMR[7]
                                    Select flash memory.
                                    0 : Deselect flash memory
                                    1 : Select flash memory
                                    */
#define PGM         ((INT8U)0x20)   /*!< FEMR[5]
                                    Enable program or program verify mode with VFY
                                    0 : Disable program or program verify mode
                                    1 : Enable program or program verify mode
                                    */
#define ERASE       ((INT8U)0x10)   /*!< FEMR[4]
                                    Enable erase or erase verify mode with VFY
                                    0 : Disable erase or erase verify mode
                                    1 : Enable erase or erase verify mode
                                    */
#define PBUFF       ((INT8U)0x08)   /*!< FEMR[3]
                                    Select page buffer
                                    0 : Deselect page buffer
                                    1 : Select page buffer
                                    */
#define OTPE        ((INT8U)0x04)   /*!< FEMR[2]
                                    Select OTP area instead of program memory
                                    0 : Deselect OTP area
                                    1 : Select OTP area
                                    */
#define VFY         ((INT8U)0x02)   /*!< FEMR[1]
                                    Set program or erase verify mode with PGM or ERASE
                                    Program Verify: PGM=1, VFY=1
                                    Erase Verify: ERASE=1, VFY=1
                                    */
#define FEEN        ((INT8U)0x01)   /*!< FEMR[0]
                                    Enable program and erase of Flash.
                                    When inactive, it is possible to read as normal mode
                                    0 : Disable program and erase
                                    1 : Enable program and erase
                                    */
//------------------------------------------------------------------------------
//	FECR (Flash Control Register : 0x1021, Initial Value : 0x03 )
//------------------------------------------------------------------------------
#define AEF         ((INT8U)0x80)   /*!< FECR[7]
                                    Enable flash bulk erase mode
                                    0 : Disable bulk erase mode of Flash memory
                                    1 : Enable bulk erase mode of Flash memory
                                    */
#define EXIT        ((INT8U)0x30)   /*!< FECR[5:4]
                                    Exit from program mode.
                                    It is cleared automatically after 1 clock
                                    11 : Exit from program mode
                                    */
#define WRITE       ((INT8U)0x08)   /*!< FECR[3]
                                    Start to program or erase of Flash.
                                    It is cleared automatically after 1 clock
                                    0 : No operation
                                    1 : Start to program or erase of Flash
                                    */
#define READ        ((INT8U)0x04)   /*!< FECR[2]
                                    Start auto-verify of Flash.
                                    It is cleared automatically after 1 clock
                                    0 : No operation
                                    1 : Start auto-verify of Flash (Checksum or CRC16)
                                    */
#define nFERST      ((INT8U)0x02)   /*!< FECR[1]
                                    Reset Flash control logic.
                                    It is cleared automatically after 1 clock
                                    0 : Reset Flash control logic
                                    1 : No operation (default)
                                    */
#define nPBRST      ((INT8U)0x01)   /*!< FECR[0]
                                    Reset page buffer with PBUFF.
                                    It is set automatically after 1 clock
                                    PBUFF nPBRST     Description
                                      0     0    :   Page buffer reset
                                      1     0    :   Page buffer select register reset
                                      X     1    :   No operation (default)
                                    */
//------------------------------------------------------------------------------
//	FESR (Flash Status Register : 0x1022, Initial Value : 0x00 )
//------------------------------------------------------------------------------
#define PEVBSY      ((INT8U)0x80)   /*!< FESR[7]
                                    Operation status flag.
                                    It is cleared automatically when operation starts.
                                    Operations are program, erase or verification
                                    0 : Busy (Operation processing)
                                    1 : No operation (default)
                                    */
#define REMAPSI     ((INT8U)0x70)   /*!< FESR[6:4]
                                    Remapping for check the serial ID.
                                    0 : No operation
                                    1 : Remapping OTP area to FFC0~FFFF.
                                    */
#define ROMINT      ((INT8U)0x08)   /*!< FESR[3]
                                    Flash interrupt request flag.
                                    Auto-cleared when program/erase/verify starts.
                                    Active in program/erase/verify completion
                                    0 : No interrupt request.
                                    1 : Interrupt request.
                                    */
									
									
#endif  /* End of __a96T428_H_ */
/* --------------------------------- End Of File ------------------------------ */

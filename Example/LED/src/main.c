/**
 *******************************************************************************
 * @file        main.c
 * @author      ABOV R&D Division
 * @brief       Main Example Code
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include    "Intrins.h"
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_timer0.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

#define	_MAX_KEY	20 
/* Private Variable ----------------------------------------------------------*/
uint8_t ccomindex, cP0SegMask, cP1SegMask, cP3SegMask;
//	unsigned char LEDPort[_MAX_KEY]={ 0x17, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, //COM port 
//	0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x07,  //SEG port
//	0x06, 0x05, 0x04, 0x03 };  //SEG port
uint16_t SegmentVal=0xFFFF;
	
//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------

char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
	return c;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 LED PORT TEST!!");
}

void LED_TimerCounter_set()
{	
	/* Enable Timer0 overflow interrupt */
	//Timer0_ConfigureInterrupt(OVERFLOW_INT, TRUE);
	Timer0_ConfigureInterrupt(MATCH_INT, TRUE);

	//scan period=8ms, com ON time=1ms 
	printf("\n\r T0_COUNTER_MODE, TIMER0_DIV128, LED Scan Period=8ms");
    /* Timer0 initialize @16MHz*/
	Timer0_Initial(T0_COUNTER_MODE, TIMER0_DIV128); // (128/16)us=8us 
	Timer0_SetMatchCounter(125-1);	//period=1000us, 1000/(8)=125
	/* Timer0 Start */
	Timer0_Start();	
	//Timer0_Stop();	
}

void LED_GPIOInit()
{
	data uint8_t cP0, cP1, cP2, cP3;
		cP2 = P2 | 0xFF; //COM 8ea output High 
		cP0 = P0 & ~0xF9; //SEG13, SEG12~SEG8, 6ea output Low
		cP1 = P1 & ~0x01; //SEG15, 1ea output Low 
		cP3 = P3 & ~0x02; //SEG14 1ea output Low 
		P2=cP2;
		P0=cP0;
		P1=cP1;
		P3=cP3;

		if((P2IO&0xFF)!=0xFF)
			P2IO |= 0xFF; //COM 8ea output  	
		if((P0IO&0xF9)!=0xF9)
			P0IO |= 0xF9; //SEG13, SEG12~SEG8, 6ea output
		if((P1IO&0x01)!=0x01)
			P1IO |= 0x01; //SEG15, 1ea output
		if((P3IO&0x02)!=0x02) 
			P3IO |= 0x02; //SEG14 1ea output		
}

void SegmentPortMask(void)
{
		if(SegmentVal&(1<<15))
			cP1SegMask |= (1<<0);
		else 
			cP1SegMask &= ~(1<<0);
		if(SegmentVal&(1<<14))
			cP3SegMask |= (1<<1);
		else 
			cP3SegMask &= ~(1<<1);
		if(SegmentVal&(1<<13))
			cP0SegMask |= (1<<0);
		else 
			cP0SegMask &= ~(1<<0);
		if(SegmentVal&(1<<12))
			cP0SegMask |= (1<<3);
		else 
			cP0SegMask &= ~(1<<3);
		if(SegmentVal&(1<<11))
			cP0SegMask |= (1<<4);
		else 
			cP0SegMask &= ~(1<<4);
		if(SegmentVal&(1<<10))
			cP0SegMask |= (1<<5);
		else 
			cP0SegMask &= ~(1<<5);
		if(SegmentVal&(1<<9))
			cP0SegMask |= (1<<6);
		else 
			cP0SegMask &= ~(1<<6);
		if(SegmentVal&(1<<8))
			cP0SegMask |= (1<<7);
		else 
			cP0SegMask &= ~(1<<7);		
}
	
void LED_GPIOSet1COM(uint8_t ccomind)
{
	static data uint8_t cP0, cP1, cP2, cP3;
	//data uint8_t cP0IO, cP1IO, cP2IO, cP3IO;
	
	if(1) { //All COM, SEG port OFF, deadtime = around 7us deadtime
		cP2 = P2 | 0xFF; //COM 8ea output High 
		cP0 = P0 & ~0xF9; //SEG13, SEG12~SEG8, 6ea output Low
		cP1 = P1 & ~0x01; //SEG15, 1ea output Low 
		cP3 = P3 & ~0x02; //SEG14 1ea output Low 
		P2=cP2; //COM off
		P0=cP0; //SEG off
		P1=cP1;	//SEG off
		P3=cP3;	//SEG off
	}
	
	if(ccomindex<8) { //COM 1ea scan, SEG port setting  
		cP0|=cP0SegMask;
		cP1|=cP1SegMask;
		cP3|=cP3SegMask;
//		cP0 |= 0xF9; //SEG13, SEG12~SEG8, 6ea output High 
//		cP1 |= 0x01; //SEG15, 1ea output High 
//		cP3 |= 0x02; //SEG14 1ea output High 
		cP2 &= ~(1<<ccomind); //COM 1ea output Low 
		P0=cP0; //SEG on
		P1=cP1; //SEG on
		P3=cP3; //SEG on
		P2=cP2; //COM on
	}
	
}

void LED_GPIO_display()
{
	LED_GPIOInit();
	
	LED_GPIOSet1COM(8); //LED OFF 
	
	LED_TimerCounter_set();
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t com_num;
	uint8_t com_seg[8];
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	
//	Display_project();
//	
//	NOP_10us_Delay(1);         // 10usec
//			
//    /* Enable INT */
//	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);    // 10usec delay

	
#if A96T418_MODE==0
	P2LEDDLY = 0x00; //Configure P2 Port N/P drive non-overlap delay enable
#endif	
	
	// P2 Register Init
	P2 = 0x00;
	P2IO = 0xFF;
	//P2OD = 0xFF;
	P2FSRL = 0x00;
	P2FSRH = 0x00;
	
	// Check LED 0,1,2,3 (LED = P20, P21, P22, P23 ////// Toggle Port = P27)
	P2 = 0xFF; // P20 ~ P23, P27 Low
  P2FSRL = 0xFF; // P20 ~ P23 AF LED
	P2FSRH = 0xFF; // P24 ~ P27 AF LED
	
	
	#if 0 // 15-2 Test
	
	P1IO |= (1<<0); // GPIO Monitoring Port
	P1 &= ~(1<<0);  // P10 Low
	
	while(1)
	{
		P1 |= (1<<0);   // P10 High (Monitoring)
		P2 = 0xFF;
		NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();    // 5usec delay
		P1 &= ~(1<<0);  // P10 Low (Monitoring)
		P2 = 0x00;
		NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();    // 5usec delay
	}
	
	#endif
	
	#if 1 // 15-3 Test
	
	P1IO |= 0x3F;
	P3IO |= 0x30;
	P5IO |= 0xFF;
	P1 |= 0x3F; //SEG(LED 0~3)  6ea output High 
	P3 |= 0x30; //SEG(LED 0~3)  2ea output High 
	P5 |= 0xFF; //SEG(LED 4~7)  8ea output High 
	
	com_seg[0] = 0xFE;
	com_seg[1] = 0xFD;
	com_seg[2] = 0xFB;
	com_seg[3] = 0xF7;
	com_seg[4] = 0xEF;
	com_seg[5] = 0xDF;
	com_seg[6] = 0xBF;
	com_seg[7] = 0x7F;
	
	while(1)
	{
		for(com_num=0; com_num<8; com_num++)
		{
			//P1 |= (1<<1); // Monitoring GPIO Port P11 High
			P2 = com_seg[com_num]; // P2n Low
			NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();NOP_1us_Delay();    // 5usec delay
			//NOP_10us_Delay(10);
		}
	}
	#endif


}

/**********************************************************************
 * @brief		Timer0 match interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_MAT_Int(void) interrupt T0_MATCH_VECT
{
	//Port_SetOutputTogglepin(PORT2, PIN0);
	ccomindex%=8;
	LED_GPIOSet1COM(ccomindex);
	ccomindex++;
	ccomindex%=8;
	NOP;
	//Port_SetOutputTogglepin(PORT2, PIN0);
}

/* --------------------------------- End Of File ------------------------------ */


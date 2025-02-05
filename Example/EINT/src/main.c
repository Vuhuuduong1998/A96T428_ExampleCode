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
#include "a96T428_bit.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
//EIPOL0H
#define	POL5	2
#define	POL4	0

//EIPOL0L
#define	POL3	6
#define POL2	4
#define	POL1	2
#define	POL0	0

//EIPOL1
#define	POL12	6
#define POL11	4
#define	POL10	2
#define	POL8	0
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
uint8_t EINT_int_cnt=0;

/* Public Function -----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

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
	
	printf("\n\ra96T428 BIT TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main(void)
{
	unsigned char i=0;

    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);
	Display_project();
    
	EINT0_5_EN();
	EINT8_INT_EN();
	EINT10_EN();
	EINT11_EN();
	EINT12_INT_EN();
		
	EIPOL0H	=	0
		|(3<<POL5)		//EINT5 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL4)		//EINT4  Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge	
		;
	EIPOL0L	=	0
		|(3<<POL3)		//EINT3 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL2)		//EINT2 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL1)		//EINT1 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL0)		//EINT0  Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge	
		;
	EIPOL1	=	0
		|(3<<POL12)		//EINT12 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL11)		//EINT11 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL10)		//EINT10 Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge
		|(3<<POL8)		//EINT8  Polarity selection. 0 : No interrupt , 1 : Interrupt on rising, 2 : Interrupt on falling , 3 : Interrupt on both edge	
		;	
    
    /* Enable INT */
	GLOBAL_INTERRUPT_EN(); 
	
	NOP_10us_Delay(10);
    /* Infinite loop */
	while(1)
	{
		if(EINT_int_cnt) { 
			printf("\n\r EINT_int_cnt=%x ", (uint16_t)EINT_int_cnt);
			EINT_int_cnt=0;
		}
		NOP;
	}
}

/**
 * @brief		EXT interrupt subroutine
 * @param   	None
 * @return	    None
*/
void INT_EXT() interrupt EINT0_5_VECT
{
	EINT_int_cnt++;
    Port_SetOutputTogglepin(PORT2, PIN0);			
    Port_SetOutputTogglepin(PORT2, PIN1);			
	
	// External interrupt
	if((EIFLAG0 & 0x01) == 0x01)
	{
		EIFLAG0 &=~(0x01);	// FLAG0 Clear.
	}
	else if((EIFLAG0 & 0x02) == 0x02)
	{
		EIFLAG0 &=~(0x02);	// FLAG1 Clear.
	}
	else if((EIFLAG0 & 0x04) == 0x04)
	{
		EIFLAG0 &=~(0x04);	// FLAG2 Clear.
	}
	else if((EIFLAG0 & 0x08) == 0x08)
	{
		EIFLAG0 &=~(0x08);	// FLAG3 Clear.
	}
	else if((EIFLAG0 & 0x10) == 0x10)
	{
		EIFLAG0 &=~(0x10);	// FLAG4 Clear.
	}
	else if((EIFLAG0 & 0x20) == 0x20)
	{
		EIFLAG0 &=~(0x20);	// FLAG5 Clear.
	}
}

void INT_EXT8() interrupt EINT8_VECT
{
	EINT_int_cnt++;
    Port_SetOutputTogglepin(PORT2, PIN0);			
    Port_SetOutputTogglepin(PORT2, PIN1);			
}

void INT_EXT10() interrupt EINT10_VECT
{
	EINT_int_cnt++;
    Port_SetOutputTogglepin(PORT2, PIN0);			
    Port_SetOutputTogglepin(PORT2, PIN1);			
}

void INT_EXT11() interrupt EINT11_VECT
{
	EINT_int_cnt++;
    Port_SetOutputTogglepin(PORT2, PIN0);			
    Port_SetOutputTogglepin(PORT2, PIN1);			
}

void INT_EXT12() interrupt EINT12_VECT
{
	EINT_int_cnt++;
    Port_SetOutputTogglepin(PORT2, PIN0);			
    Port_SetOutputTogglepin(PORT2, PIN1);			
}

/* --------------------------------- End Of File ------------------------------ */


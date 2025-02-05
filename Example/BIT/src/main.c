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
//#include    "Global.h"      //
//#include    "Sysfunc.h"     //
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_bit.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
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
	uint8_t test_mode=0;
	unsigned char i=0;

    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);
	Display_project();

	//test_mode=0;
	test_mode=1;
	
    /* BIT initialize (default period 16ms)*/   
	BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //64ms 
	//BIT_Initial(BIT_LSI_4KHZ, BIT_X64); //16ms
	//BIT_Initial(BIT_DIV4096, BIT_X256); //65ms 
	//BIT_Initial(BIT_DIV1024, BIT_X256); //16ms 
 #if A96T418_MODE==1
	//BIT_Initial(BIT_TEMPSENSOR, BIT_X256);
#endif	
   
	if(test_mode==0)
	{
		/* Enable BIT INT */
		BIT_Interrupt_config(TRUE);
    }
	else if (test_mode==1)
	{
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN(); 
	NOP_10us_Delay(10);
    /* Infinite loop */
	while(1)
	{
		if(test_mode==0)
		{
			if(fBIT_int)
			{
				Port_SetOutputTogglepin(PORT2, PIN0);			//BIT Int 64ms toggle!
				Port_SetOutputTogglepin(PORT2, PIN1);			//BIT Int 64ms toggle!
				printf("\n\r fBIT_int OK, 0x%02x", BITCR&0xffff);
				fBIT_int=0;
			}
			NOP;
		}
		else if(test_mode==1)
		{
			BIT_Int_Flag_polling();
			if(fBIT_int)
			{
				Port_SetOutputTogglepin(PORT2, PIN0);			//BIT Int 64ms toggle!
				Port_SetOutputTogglepin(PORT2, PIN1);			//BIT Int 64ms toggle!
				printf("\n\r fBIT_Flag OK, 0x%02x", BITCR&0xffff);
				fBIT_int=0;
			}
			NOP;
		}
	}
}

/**
 * @brief		BIT interrupt subroutine
 * @param   	None
 * @return	    None
*/
void BIT_Int_Handler(void) interrupt BIT_VECT
{
	fBIT_int=1;
}

/* --------------------------------- End Of File ------------------------------ */


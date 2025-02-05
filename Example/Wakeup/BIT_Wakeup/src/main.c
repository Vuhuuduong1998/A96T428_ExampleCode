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
	
	printf("\n\ra96T428 BIT Wakeup TEST!!");
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

	if(1) 
	{
		/* BIT initialize (period 64ms)*/   
		BIT_Initial(BIT_LSI_4KHZ, BIT_X256);	//64ms 
		//BIT_Initial(BIT_DIV4096, BIT_X256); //65ms 
#if A96T418_MODE==1
		//BIT_Initial(BIT_TEMPSENSOR, BIT_X256); //64ms 
#endif
		   
		/* Enable BIT INT */
		BIT_Interrupt_config(TRUE);
	}
	
	/* Enable INT */
	GLOBAL_INTERRUPT_EN(); 
    
    /* Infinite loop */
	while(1)
	{
		
		Port_SetOutputTogglepin(PORT2, PIN1);			
		if(fBIT_int)
		{
			fBIT_int=0;
			Clock_ConfigureOSC(LSIRC,0,OSC_EN);

			Port_SetOutputHighpin(PORT2, PIN0);			
			//STOP MODE
			NOP;
			NOP;
		//	PCON = 0x01;		// IDLE
			PCON = 0x03;			// STOP
			NOP;
			NOP;
			NOP;
			fBIT_int=0;
			printf("\n\r Wakeup OK");
		}
		NOP;
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
    Port_SetOutputTogglepin(PORT2, PIN0);			//BIT Int toggle!
}

/* --------------------------------- End Of File ------------------------------ */


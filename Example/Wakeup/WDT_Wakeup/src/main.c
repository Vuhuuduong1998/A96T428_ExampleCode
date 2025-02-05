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
#include "delay.h"
#include "a96T428_wdt.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_bit.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/

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
	
	printf("\n\ra96T428 WDT Wakeup TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	
	Port_SetOutputHighpin(PORT2, PIN0);
	Port_SetOutputHighpin(PORT2, PIN1);

	if(RSTFR & (0x20))  // WDT reset flag check
	{
		Port_SetOutputTogglepin(PORT2, PIN1);
		printf("\n\r WDT reset flag occurred !!");
	}
		
	if(1)
	{		
		/* WDT initialize */
		BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //BIT period=64ms 
		//WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV1);	//WDT clock source=64ms 
		WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1);	//WDT clock source=64ms 
		WDT_SetDATA(7); //WDT period=512ms
			
		//WDT_Set_500msec_Reset();

		/* Enable WDT INT */
		WDT_ConfigureInterrrupt(WDT_INT_EN);    

		/* Enable INT */
		GLOBAL_INTERRUPT_EN();
		WDT_Start();
	}
	
    /* Infinite loop */
	while(1)
	{
		if(fWDT_int)
		{			
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
			printf("\n\r Wakeup OK , fWDT_int=%x", (uint16_t)fWDT_int);
			fWDT_int=0;
			//BIT_ClearInterruptStatus();
			//while(!BIT_GetInterruptStatus()); //wait for printf complete 
		}				
	}
}

/**********************************************************************
 * @brief		Watch Dog Timer overflow interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void WDT_OVER_Int(void) interrupt WDT_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);
	fWDT_int=1;
}

/* --------------------------------- End Of File ------------------------------ */

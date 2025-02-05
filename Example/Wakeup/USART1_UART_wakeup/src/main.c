/**
 *******************************************************************************
 * @file        Main.c
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
#include "a96T428_usart1_uart.h"
#include "stdio.h"     

/* Private Pre-processor Definition & Macro ----------------------------------*/

/* Private Typedef -----------------------------------------------------------*/

/* Private Variable ----------------------------------------------------------*/

/* Private Function Prototype ------------------------------------------------*/
uint8_t RXdata, USTATdata;
//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	USTAT&=~TXC;
	UDATA = c;
	while(!(USTAT&TXC)); //TXC check for safe stop mode 
	return c;
}

char getchar()
{
	char c;
	while((USTAT & RXC)!= RXC);		// Wait Data in
	c = UDATA;
	return c;
}

char KBHit(void)
{
	if(USTAT & RXC)		// Wait Data in
		return 1;
	else 
		return 0;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 USART1 UART Wakeup TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	volatile uint8_t temp=0;
	char c;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);    // 10usec delay

	/* Infinite loop */
	while(1)
	{    
		printf("\n\r Press any key to enter stop mode !!");
		c=getchar();
		putchar(c);
		
		if(!KBHit())
		{
			USART1_ConfigureWakeUp(TRUE);
			USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, TRUE);
			//STOP MODE
			NOP;
			NOP;
		//	PCON = 0x01;		// IDLE
			PCON = 0x03;			// STOP
			NOP;
			NOP;
			NOP;
			printf("\n\rWakeup OK From UART ");			
			printf("\n\r RXdata=%02x,  USTATdata=%02x", RXdata, USTATdata);			
			printf("\n\r UDATA=%02x,  USTAT=%02x ", UDATA, USTAT);			
			printf("\n\r UDATA=%02x,  USART1_GetInterruptStatus()=%02x ", UDATA, USART1_GetInterruptStatus());			
			if((temp=USART1_GetInterruptStatus())&WAKE) 
				printf("\n\r WAKE bit OK ");			
			else 
				printf("\n\r WAKE bit Fail  ");			
			USART1_ClearWakeUpFlag();
			NOP_10us_Delay(100);         // 1msec
			NOP;
		}
	}

}

void USART1_RXInt_Handler() interrupt USART1_RX_VECT
{	
	RXdata=UDATA;
	USTATdata=USTAT;
	USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, FALSE);
	USART1_ConfigureWakeUp(FALSE);
}

/* --------------------------------- End Of File ------------------------------ */

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
#include "a96T428_usart2_uart.h"
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
	while(!(USTAT2 & (UDRE)));
	USTAT2&=~TXC;
	UDATA2 = c;
	while(!(USTAT2&TXC)); //TXC check for safe stop mode 
	return c;
}

char getchar()
{
	char c;
	while((USTAT2 & RXC)!= RXC);		// Wait Data in
	c = UDATA2;
	return c;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART2_UART_Initial(9600, USART2_DATA_8BIT, USART2_STOP_1BIT, USART2_PARITY_NO, USART2_TX_RX_MODE);
	
	printf("\n\ra96T428 USART2 UART Wakeup TEST!!");
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
		
		if(1)
		{
			USART2_ConfigureWakeUp(TRUE);
			USART2_ConfigureInterrupt(USART2_RX_COMPLETE_INT, TRUE);
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
			printf("\n\r UDATA2=%02x,  USART2_GetInterruptStatus()=%02x ", UDATA2, USART2_GetInterruptStatus());			
			if((temp=USART2_GetInterruptStatus())&WAKE) 
				printf("\n\r WAKE bit OK ");			
			else 
				printf("\n\r WAKE bit Fail  ");			
			USART2_ClearWakeUpFlag();
			NOP_10us_Delay(100);         // 1msec
			NOP;
		}
	}

}

void USART2_RXInt_Handler() interrupt USART2_RX_VECT
{	
	RXdata=UDATA2;
	USTATdata=USTAT2;
	USART2_ConfigureInterrupt(USART2_RX_COMPLETE_INT, FALSE);
	USART2_ConfigureWakeUp(FALSE);
}

/* --------------------------------- End Of File ------------------------------ */

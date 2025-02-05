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
#include "a96T428_usi_usart.h"
#include "stdio.h"  

uint8_t RXdata, USTATdata;

/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USI0ST1 & (UDRE)));
	USI0ST1&=~TXC;
	USI0DR = c;
	while(!(USI0ST1&TXC)); //TXC check for safe stop mode 
	return c;
}

char getchar()
{
	char c;
	while((USI0ST1 & RXC)!= RXC);		// Wait Data in
	c = USI0DR;
	return c;
}

char KBHit(void)
{
	if(USI0ST1 & RXC)		// Wait Data in
		return 1;
	else 
		return 0;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P10(RXD0) / P11(TXD0)*/
	Port_SetInputpin(PORT1, PIN0, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
	
	USI_UART_Initial(USART_CH0, 9600, USART_DATA_8BIT, USART_STOP_1BIT, USART_PARITY_NO, USART_TX_RX_MODE);
	
	printf("\n\ra96T428 USI UART Wakeup TEST!!");
}

void putstring(char *str)
{
	while(*str != 0)
		USI_UART_SendDataWithInterrupt(USART_CH0, *str++);
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	char c;
	volatile uint8_t temp=0;
	
	//uint8_t temp;
	GLOBAL_INTERRUPT_DIS();     // disable INT. during peripheral setting
  /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec
	
	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);         // 10usec	

	while (1)
	{
		printf("\n\r Press any key to enter stop mode !!");
		c=getchar();
		putchar(c);
		
		if(!KBHit())
		{
			USI_USART_ConfigureWakeUp(USART_CH0, TRUE);
			USI_USART_ConfigureInterrupt(USART_CH0, USART_RX_COMPLETE_INT, TRUE);
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
			printf("\n\r USI0DR=%02x,  USI0ST1=%02x ", USI0DR, USI0ST1);			
			printf("\n\r USI0DR=%02x,  USI_USART_GetInterruptStatus()=%02x ", USI0DR, USI_USART_GetInterruptStatus(USART_CH0));			
			if((temp=USI_USART_GetInterruptStatus(USART_CH0))&WAKE) 
				printf("\n\r WAKE bit OK ");			
			else 
				printf("\n\r WAKE bit Fail  ");			
			USI_USART_ClearWakeUpFlag(USART_CH0);
			NOP_10us_Delay(100);         // 1msec
			NOP;
		}

	}
}

//==============================================================================
// interrupt routines(USI0)
//==============================================================================
void USI0_RXInt_Handler() interrupt USI0_RX_VECT
{	
	RXdata=USI0DR;
	USTATdata=USI0ST1;
	USI_USART_ConfigureInterrupt(USART_CH0, USART_RX_COMPLETE_INT, FALSE);
	USI_USART_ConfigureWakeUp(USART_CH0, FALSE); 
}



/* --------------------------------- End Of File ------------------------------ */

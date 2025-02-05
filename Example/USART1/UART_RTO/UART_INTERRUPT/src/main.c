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
#include "a96T428_usi_usart.h"
#include "stdio.h"  

/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USI0ST1 & (UDRE)));
		USI0DR = c;
	return c;
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
	
	printf("\n\ra96T428 USART1 UART INTERRUPT TEST !!");
}

void putstring(char *str)
{
	while(*str != 0)
		USART1_UART_SendDataWithInterrupt(*str++);
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t tempw=0, tempr=0;
	GLOBAL_INTERRUPT_DIS();     // disable INT. during peripheral setting
  /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	USART1_ConfigureRTO(TRUE, 4807); //RTO time=5000000us/(104us*10)=4807 //RTO time=1000000us/104us=961
	
	USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, TRUE);
	USART1_ConfigureInterrupt(USART1_TX_COMPLETE_INT, TRUE);
	
	GLOBAL_INTERRUPT_EN();

	putstring("a96T428 USART1 UART INTERRUPT TEST!!\n\r");
	
	NOP_10us_Delay(1);         // 10usec	

	while (1)
	{
		if(USART1_UART_ReceiveCheckWithInterrupt(&tempr))
		{
			tempw=tempr;
			USART1_UART_SendDataWithInterrupt(tempw);  
			printf("%c", tempw);
		}
		if(fRTO_FLAG_occurred)
		{
			fRTO_FLAG_occurred=0;
			Port_SetOutputTogglepin(PORT2,BIT0);
			
			printf("\r\n RTOFlag occurred ");
		}
		
	}
}

//==============================================================================
// interrupt routines
//==============================================================================
void USART1_RXInt_Handler() interrupt USART1_RX_VECT
{	
	extern void USART1_RXInt_Handler_ISR(); 
	USART1_RXInt_Handler_ISR();
}

void USART1_TXInt_Handler() interrupt USART1_TX_VECT
{
	void USART1_TXInt_Handler_ISR(); 
	USART1_TXInt_Handler_ISR();
}

/* --------------------------------- End Of File ------------------------------ */

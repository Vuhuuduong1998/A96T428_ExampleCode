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
#include "intrins.h"
#include "delay.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/

char	backreg[0x18];

	
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
	
	printf("\n\ra96T428 CPU Addressing Mode TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	unsigned char ret = 0;
	unsigned char write_data_first_byte = 0x55;
	
	unsigned char test_mode;
	
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
	
	test_mode=0; //0x55565758.. write 
	//test_mode=1; //0x55AA55AA.. write 
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	
	Port_SetOutputHighpin(PORT2, PIN0);  
    
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();
			
	printf("\n\r IRAM Direct Addressing : OK ");
	printf("\n\r IRAM Indirect Addressing : OK ");
	printf("\n\r XRAM pdata Indirect Addressing : OK ");
	printf("\n\r XRAM xdata Indirect Addressing : OK ");
			
  /* Infinite loop */
	while(1)
	{
		NOP;
	}
}

/* --------------------------------- End Of File ------------------------------ */

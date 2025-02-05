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
#include "a96T428.h"
#include "delay.h"
#include "Intrins.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_buzzer.h"
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
	
	printf("\n\ra96T428 BUZZER TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main(void)
{
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);
	Display_project();

    /* Enable INT */
	GLOBAL_INTERRUPT_EN();   

	NOP_10us_Delay(100);        // 1msec delay

	/*Set Alernative Function for Buzzer Port P03*/
	Port_SetAlterFunctionpin(PORT0, PIN3, 0x1);
	/*Set Alernative Function for Buzzer Port P40*/
	//Port_SetAlterFunctionpin(PORT4, PIN0, 0x1);
	
	/* Buzzer initialize @ sys 16MHz*/
	Buzzer_Initial(16000000, 0, BUZZER_DIV32);	//4us=250kHz 
	//Buzzer_Initial(16000000, 0, BUZZER_DIV128); //16us=62.5kHz  
	//Buzzer_Initial(16000000, 0, BUZZER_DIV256); //32us=31.25kHz  
	//Buzzer_Initial(16000000, 10, BUZZER_DIV256); //352us=2.84kHz  
	//Buzzer_Initial(16000000, 100, BUZZER_DIV256); //3232us=0.309kHz   

	/* Infinite loop */
	while(1)
	{
			/* Buzzer Start @ Buzzer Freq */
			Buzzer_Start();
			NOP_10us_Delay(10000);        // 100msec delay
			/* Buzzer Stop@ Buzzer Freq = 250kHz*/
			Buzzer_Stop();
			NOP_10us_Delay(10000);        // 100msec delay
	}
}

/* --------------------------------- End Of File ------------------------------ */

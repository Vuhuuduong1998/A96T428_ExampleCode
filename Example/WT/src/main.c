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
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_wt.h"
#include "intrins.h"
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
	
	printf("\n\ra96T428 WT TEST!!");
}
void main(void)
{
	uint8_t test_mode;

	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);                      // 10usec    

#if A96T418_MODE==1
	
//    /* WT initialize 16Mhz -> 65.536ms*/
//	WT_Initial(FWCK_DIV16384_WTDR1, FX_DIV64);
//	WT_SetDataValue(1);  //524ms
//	//WT_SetDataValue(15);  //1s

	Clock_ConfigureOSC(SUBCLK,0,OSC_EN);
    /* WT initialize 32.768Khz -> 65.536ms*/
	//WT_Initial(FWCK_DIV128, SUB); //3.9ms 	
	WT_Initial(FWCK_DIV8192, SUB); //250ms 	
	//WT_Initial(FWCK_DIV16384, SUB); //500ms 	
#endif	
#if A96T418_MODE==0

    /* WT initialize 32.768Khz -> 65.536ms*/
	//WT_Initial(FWCK_DIV128, WTLSIRC); //3.9ms 	
	//WT_Initial(FWCK_DIV8192, WTLSIRC); //250ms 	
	//WT_Initial(FWCK_DIV16384, WTLSIRC); //500ms 	
	WT_Initial(FWCK_DIV16384_WTDR1, WTLSIRC); //1000ms 	
	WTDR=1;
#endif	

	test_mode=0;
	//test_mode=1;
	if(test_mode==0)
	{	
		/* Enable WT INT */
		WT_ConfigureInterrrupt(WT_INT_EN);

		/* Watch Timer Start */ 
		WT_Start();
	}
	else if(test_mode==1)
	{
		/* Watch Timer Start */ 
		WT_Start();
		
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();  

    Port_SetOutputTogglepin(PORT2, PIN0);

    /* Infinite loop */
	while(1)
	{
		if(test_mode==0)
		{
			if(fWT_int)
			{
				fWT_int=0;
				Port_SetOutputTogglepin(PORT2, PIN0);
				printf("\n\r fWT int. OK");
			}
		}
		else if(test_mode==1)
		{
			WDT_Int_Flag_polling();
			if(fWT_int)
			{
				fWT_int=0;
				Port_SetOutputTogglepin(PORT2, PIN0);
				printf("\n\r fWT Flag occurred ");
			}
		}
		
	}
}

/**********************************************************************
 * @brief		WT interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void WT_Int_Handler() interrupt WT_VECT
{
	fWT_int=1;
}

/* --------------------------------- End Of File ------------------------------ */

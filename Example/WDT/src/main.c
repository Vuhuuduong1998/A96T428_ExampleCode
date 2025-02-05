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
	
	printf("\n\ra96T428 WDT TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	uint8_t test_mode=0;
	uint8_t tmp1, tmp2=0;
	bit fWDT_Reset_detected=0;

	if(1) //F/W Start check after WDT reset 
	{
		Port_SetOutputHighpin(PORT2, PIN0);
		Port_SetOutputHighpin(PORT2, PIN1);
		NOP_10us_Delay(2);        // 20usec
		Port_SetOutputLowpin(PORT2, PIN0);
		Port_SetOutputLowpin(PORT2, PIN1);
		NOP_10us_Delay(2);        // 20usec
		Port_SetOutputHighpin(PORT2, PIN0);
		Port_SetOutputHighpin(PORT2, PIN1);
		NOP_10us_Delay(2);        // 20usec
	}		
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
	Port_SetOutputHighpin(PORT2, PIN0);
	Port_SetOutputHighpin(PORT2, PIN1);
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
		
	if(RSTFR & (0x20))  // WDT reset flag check
	{
		fWDT_Reset_detected=1;
		printf("\n\r WDT Reset detected. \r\n");
	}

	printf("\n\r\r\n RSTFR=0x%02x", RSTFR&0xffff);
	RSTFR=0x00;
	printf("\n\r BITCR=0x%02x \r\n", BITCR&0xffff);
	
	//test_mode=0; //WDT Int mode 
	//test_mode=1; //WDT polling mode 
	test_mode=2; //WDT Reset mode 

	BIT_Interrupt_config(TRUE);
	
	if(test_mode==0)
	{
		/* WDT initialize */
		//BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //BIT period=64ms 		
		//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1);	//WDT clock source=BIT period
		//WDT_SetDATA(10-1); //WDT period=512ms=64ms*8 //167ms 
		
		BIT_Initial(BIT_LSI_32KHZ, BIT_X2); //BIT period=0.064ms 
		WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1);	//WDT clock source=BIT period
		WDT_SetDATA(99); //WDT period=50ms //0.064ms *100=6.4ms 

		//BIT_Initial(BIT_LSI_4KHZ, BIT_X64); //BIT period=16ms 		
		//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1);	//WDT clock source=BIT period
		//WDT_SetDATA(9); //WDT period=160ms //
		
		/* Enable WDT INT */
		WDT_ConfigureInterrrupt(WDT_INT_EN);
		WDT_Start();
	}
	else if(test_mode==1)
	{
		/* WDT initialize */
		BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //BIT period=64ms 
		WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1);	//WDT clock source=BIT period
		WDT_SetDATA(7); //WDT period=512ms=64ms*8
		
		WDT_Start();
	}
	if(test_mode==2)
	{
		/* WDT initialize */
		BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //BIT period=64ms 
		WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV1);	//WDT clock source=BIT period
		//WDT_SetDATA(7); //WDT period=512ms=64ms*8
		WDT_SetDATA(9); //WDT period=640ms=64ms*9
		
		WDT_Start();
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();
    
    /* Infinite loop */
	while(1)
	{
		
		if(test_mode==0)
		{
			if(fWDT_int)
			{
				fWDT_int=0;
				Port_SetOutputTogglepin(PORT2, PIN0);
				printf("\n\r WDT Int. occurred. ");
			}
		}
		else if(test_mode==1)
		{
			WDT_Int_Flag_polling();
			if(fWDT_int)
			{
				fWDT_int=0;
				Port_SetOutputTogglepin(PORT2, PIN0);
				printf("\n\r WDT flag occurred. ");
			}
		}		
		else if(test_mode==2)
		{			
			tmp1=CONFOPTION1;
			tmp2=CONFOPTION2;
			printf("\n\r CONFOPTION1=0x%02x ", tmp1&0xFFFF); //- - - - PAEN PASS2 PASS1 PASS0
			printf("\n\r CONFOPTION2=0x%02x \r\n", tmp2&0xFFFF); //R_P HL - VAPEN - - - RSTS
			CONFOPTION1&=~0xFF;
			CONFOPTION2&=~0xFF;
			_nop_();
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
	fWDT_int=1;
}

void BIT_Int_Handler(void) interrupt BIT_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN1);
	fBIT_int=1;
}

/* --------------------------------- End Of File ------------------------------ */

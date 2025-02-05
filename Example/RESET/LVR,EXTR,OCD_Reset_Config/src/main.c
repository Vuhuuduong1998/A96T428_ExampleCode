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
#include "a96T428_pwr.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
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
	
	printf("\n\n\ra96T428 LVR, EXTR, OCDR TEST!!");
}

void GPIO_inputFloating_inputPullup_test(void)
{
	uint8_t c;
	bit fOCDMode=(RSTFR&0x10)?1:0;
	
	//output Low 
	for(c=0;c<8;c++) 
	{
		P0&=~(1<<c);
		P0IO|=(1<<c);
		P1&=~(1<<c);
		P1IO|=(1<<c);
		P2&=~(1<<c);
		P2IO|=(1<<c);
		P3&=~(1<<c);
		P3IO|=(1<<c);
#if A96T418_MODE==0
		P4&=~(1<<c);
		P4IO|=(1<<c);
		P5&=~(1<<c);
		P5IO|=(1<<c);
#endif		
	}	
	
	//input floating 
	for(c=0;c<8;c++)
	{
		P0PU&=~(1<<c);
		P0IO&=~(1<<c);
		P1PU&=~(1<<c);
		P1IO&=~(1<<c);
		P2PU&=~(1<<c);
		P2IO&=~(1<<c);
		P3PU&=~(1<<c);
		P3IO&=~(1<<c);
#if A96T418_MODE==0
		P4PU&=~(1<<c);
		P4IO&=~(1<<c);
		P5PU&=~(1<<c);
		P5IO&=~(1<<c);
#endif		
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0x00) ; 
	else 
		while(P0!=0x00) ; 
	while(P1!=0x00) ; 
	while(P2!=0x00) ; 
	while(P3!=0x00) ; 
#if A96T418_MODE==0
	while(P4!=0x00) ; 
	while(P5!=0x00) ; 
#endif	
	_nop_();
	
	//input pullup 
	for(c=0;c<8;c++)
	{
		P0PU|=(1<<c);
		P0IO&=~(1<<c);
		P1PU|=(1<<c);
		P1IO&=~(1<<c);
		P2PU|=(1<<c);
		P2IO&=~(1<<c);
		P3PU|=(1<<c);
		P3IO&=~(1<<c);
#if A96T418_MODE==0		
		P4PU|=(1<<c);
		P4IO&=~(1<<c);
		P5PU|=(1<<c);
		P5IO&=~(1<<c);
#endif		
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0xF9) ; 
	else 
		while(P0!=0xFF) ; 
	while(P1!=0xFF) ; 
	while(P2!=0xFF) ; 
	while(P3!=0x03) ; 
#if A96T418_MODE==0		
	while(P4!=0x03) ; 
	while(P5!=0x03) ; 
#endif		
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	uint8_t n=100;
	uint8_t tmp1, tmp2=0;

	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     

	while(n--)
	{
		Port_SetOutputTogglepin(PORT2, PIN0);	
		NOP_10us_Delay(2);        // 20usec
	}
	n=10;
	while(n)
	{
		if(BITCR&0x80)
		{
			BITCR&=~0x80;
			n--;
			Port_SetOutputTogglepin(PORT2, PIN0);	
		}
	}
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec

	if(1)
	{
		if(RSTFR&0x08) //LVRF 
		{
			printf("\n\r LVRF(LVR Reset Flag detected)");
		}
		if(RSTFR&0x40) //EXTRF 
		{
			printf("\n\r EXTRF(Ext. Reset Flag detected)");
		}
		if(RSTFR&0x10) //OCDRF 
		{
			printf("\n\r OCDRF(OCD Reset Flag detected)");
		}
		printf("\n\r\r\n RSTFR=0x%02x", RSTFR&0xffff);
		RSTFR=0x00;
	}
	printf("\n\r BITCR=0x%02x \r\n", BITCR&0xffff);
	
	Port_SetOutputHighpin(PORT2, PIN1);
    
#if A96T418_MODE==1    
	/* Enable LVR 3.56V */
	//PWR_ConfigureLVR(LVR_3_56, TRUE);
	PWR_ConfigureLVR(LVR_2_00, TRUE);
	
#endif
#if A96T418_MODE==0    
	/* Enable LVR_L3 */
	//PWR_ConfigureLVR(LVR_L3, TRUE);
	PWR_ConfigureLVR(LVR_L0, TRUE);
	
#endif
	BITCR=0x00; //0.5ms oscillation stability time for next reset 
	
    
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();
    
    /* Infinite loop */
	while(1)
	{		
		if(BITCR&0x80)
		{
			BITCR&=~0x80;
			Port_SetOutputTogglepin(PORT2, PIN0);	
			
			tmp1=CONFOPTION1;
			tmp2=CONFOPTION2;
			printf("\n\r CONFOPTION1=0x%02x ", tmp1&0xFFFF); //- - - - PAEN PASS2 PASS1 PASS0
			printf("\n\r CONFOPTION2=0x%02x \r\n", tmp2&0xFFFF); //R_P HL - VAPEN - - - RSTS
			CONFOPTION1=0x00;
			CONFOPTION2=0x00;
			_nop_();
			
		}
		
	}
}

/* --------------------------------- End Of File ------------------------------ */

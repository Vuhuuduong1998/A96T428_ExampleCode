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
#include    "Intrins.h"
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_timer0.h"
#include "a96T428_timer1.h"
#include "a96T428_bit.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

/* Public Variable -----------------------------------------------------------*/
bit fTimer0_int=0;
bit fTimer0_Int_Flag=0, fTimer1_Int_Flag=0, fBIT_Int_Flag;
uint16_t Timer0_multi_level=0, Timer1_multi_level=0, BIT_multi_level=0;
/* Public Function -----------------------------------------------------------*/
unsigned char test_mode=0;

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
	
	printf("\n\ra96T428 Timer0 TEST!!");
}

void Timer0_Counter_mode_set()
{
    /* Timer0 initialize @0.5MHz*/
	Timer0_Initial(T0_COUNTER_MODE, TIMER0_DIV128);	//128/16us=8us clock 
	Timer0_SetMatchCounter(125-1); //1000us/(8us)=125 
	
	/* Enable Timer0 overflow interrupt */
	Timer0_ConfigureInterrupt(MATCH_INT, TRUE);

	IP&=~(1<<1); //group1 lowest 
	IP1&=~(1<<1); //group1 lowest 

	/* Timer0 Start */
	Timer0_Start();
}

void Timer1_Counter_mode_set()
{
    /* Timer1 initialize @ 16MHz */
	Timer1_Initial(T1_COUNTER_MODE, TIMER1_DIV1);	//1/16us clock 
	Timer1_SetMatchCounter(16000-1); //1000us/(1/16us)=16000
	/* Enable timer1 INT */   
	Timer1_ConfigureInterrupt(TRUE);

	IP|=(1<<2); //group2 highest 
	IP1|=(1<<2); //group2 highest  
	
	/* Timer1 start */
	Timer1_Start();	
	
}

void BIT_mode_set()
{
	BIT_Initial(BIT_LSI_4KHZ,BIT_X4);//1ms period 
	
	IP|=(1<<4); //group4 middle 
	IP1&=~(1<<4); //group4 middle 
	
	BIT_Interrupt_config(TRUE);
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
int Main(void)
{
	unsigned char i=0;

	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 1usec
	
	Timer0_Counter_mode_set();
	Timer1_Counter_mode_set();
	BIT_mode_set();
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();   
	
	test_mode = 0; //allow multi level 
	//test_mode = 1; //don't allow multi level 

    /* Infinite loop */
	while(1)
	{
		if(fTimer0_Int_Flag)
		{
			fTimer0_Int_Flag=0;
			
			if(Timer0_multi_level==1)
			{
				Timer0_multi_level=0;
				printf(" T0=1 ");
				while(1);//Fail 
			}
			else if(Timer0_multi_level==2)
			{
				Timer0_multi_level=0;
				printf("\n\r T0=2 !!\n\r");
				while(1);//Fail 
			}
			else 
			{
				printf(" T0=0 ");
			}
		}
		if(fTimer1_Int_Flag)
		{
			fTimer1_Int_Flag=0;
			
			if(Timer1_multi_level==1)
			{
				Timer1_multi_level=0;
				printf(" T1=1 ");
			}
			else if(Timer1_multi_level==2)
			{
				Timer1_multi_level=0;
				printf("\n\r T1=2 !!\n\r");
			}
			else 
			{
				printf(" T1=0 ");
			}
		}
		if(fBIT_Int_Flag)
		{
			fBIT_Int_Flag=0;
			if(BIT_multi_level==1)
			{
				BIT_multi_level=0;
				printf(" BT=1 ");
			}
			else if(BIT_multi_level==2)
			{
				BIT_multi_level=0;
				printf("\n\r BT=2 !!\n\r");
				while(1);//Fail 
			}
			else 
			{
				printf(" BT=0 ");
			}
		}
	}
}

/**********************************************************************
 * @brief		Timer0 match interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_MAT_Int(void) interrupt T0_MATCH_VECT
{
	uint16_t i;

	Port_SetOutputTogglepin(PORT2, PIN0);
	fTimer0_int=1;
	if(test_mode==0)
		EA=1; //allow multi level
	i=100;//200:230us
	while(i--);
	if(fTimer1_int && fBIT_int)
	{
		Timer0_multi_level=2;
	}
	else if(fTimer1_int || fBIT_int)
	{
		Timer0_multi_level=1;
	}
	//Timer0_ClearCountData(); //for randonmize T0 
	fTimer0_Int_Flag=1;
	fTimer0_int=0;
	Port_SetOutputTogglepin(PORT2, PIN0);
}

/**********************************************************************
 * @brief		Timer1 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER1_Int(void) interrupt T1_MATCH_VECT
{
	uint16_t i;
	Port_SetOutputTogglepin(PORT2, PIN1);
	fTimer1_int=1;
	if(test_mode==0)
		EA=1; //allow multi level
	i=100;//200:230us
	while(i--);
	if(fTimer0_int && fBIT_int)
	{
		Timer1_multi_level=2;
	}
	else if(fTimer0_int || fBIT_int)
	{
		Timer1_multi_level=1;
	}
	Timer1_ClearCountData(); //for randonmize T1
	fTimer1_Int_Flag=1;		
	fTimer1_int=0;
	Port_SetOutputTogglepin(PORT2, PIN1);
}

/**
 * @brief		BIT interrupt subroutine
 * @param   	None
 * @return	    None
*/
void BIT_Int_Handler(void) interrupt BIT_VECT
{
	uint16_t i;
    Port_SetOutputTogglepin(PORT2, PIN2);			
	fBIT_int=1;
	if(test_mode==0)
		EA=1; //allow multi level
	i=100;//200:230us
	while(i--);
	if(fTimer0_int && fTimer1_int)
	{
		BIT_multi_level=2;
	}
	else if(fTimer0_int || fTimer1_int)
	{
		BIT_multi_level=1;
	}
	fBIT_Int_Flag=1;		
	fBIT_int=0;	

    Port_SetOutputTogglepin(PORT2, PIN2);			
}

/* --------------------------------- End Of File ------------------------------ */

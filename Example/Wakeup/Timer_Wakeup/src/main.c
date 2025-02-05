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
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/

/* Private Function Prototype ------------------------------------------------*/
bit fTimer0Match=0;
bit fTimer0Overflow=0;

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
	NOP_10us_Delay(1);        // 10usec
	
    /* Timer0 initialize @0.5MHz*/
	Timer0_Initial(T0_COUNTER_MODE, TIMER0_EXT_CLK);
	
	/* Set PMW output (Alternative function) */
#if A96T418_MODE==1			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x2); //T0O/PWM0O
#endif
#if A96T418_MODE==0			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x1); //T0O/PWM0O
#endif
	Port_SetAlterFunctionpin(PORT2, PIN5, 0x2); //EC0 input  
	
	/* Enable Timer0 overflow interrupt */
	Timer0_ConfigureInterrupt(OVERFLOW_INT, TRUE);
	Timer0_ConfigureInterrupt(MATCH_INT, TRUE);
	Timer0_SetMatchCounter(1);

	/* Timer0 Start */
	Timer0_Start();
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();   

    /* Infinite loop */
	while(1)
	{
		if(fTimer0Match)
		{
			fTimer0Match=0;
			printf("\n\r Timer0 EC0 Int OK");
			NOP;
		}
		else 
		{
			Port_SetOutputTogglepin(PORT2, PIN0);
			
			/* BIT initialize (period 16ms)*/   			
			//STOP MODE
			NOP;
			NOP;
		//	PCON = 0x01;		// IDLE
			PCON = 0x03;			// STOP
			NOP;
			NOP;
			NOP;
			
			if(fTimer0Match)
			{
				fTimer0Match=0;
				printf("\n\r wakeup OK by Timer0 EC0 ");
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
	Port_SetOutputTogglepin(PORT2, PIN1);
	fTimer0Match=1;
	NOP;
}

/**********************************************************************
 * @brief		Timer0 overflow interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_OVER_Int(void) interrupt T0_OVER_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN1);
}

/* --------------------------------- End Of File ------------------------------ */

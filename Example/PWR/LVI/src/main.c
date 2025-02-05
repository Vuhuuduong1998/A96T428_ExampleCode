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
uint8_t LVI_IntFlag_count=0;

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
	
	printf("\n\ra96T428 LVI TEST!!");
}

/* Private Function Prototype ------------------------------------------------*/
/**
* @brief		Get status of low voltage interrupt status by interrupt service.
* @param   None
* @return		Status of LVI detect.
*/
uint8_t PWR_LVI_CheckWithInterrupt()
{
	uint8_t LVI_Debounce_count=3;
	
	LVI_IntFlag_count=3;
	while(LVI_Debounce_count--) {
		PWR_ClearLVIStatus();
		PWR_LVI_ConfigureInterrupt(TRUE);
	}
	PWR_LVI_ConfigureInterrupt(FALSE);
	if(LVI_IntFlag_count==0) //LVI detected, 62us taken at LVI_Debounce_count=3
		return 1;
	else 
		return 0;
}

/**
* @brief		Get status of low voltage interrupt status by flag polling.
* @param   None
* @return		Status of LVI detect.
*/
uint8_t PWR_LVI_CheckWithPolling()
{
	uint8_t LVI_Flag_count=3;
	uint8_t LVI_Debounce_count=3;
	
	while(LVI_Debounce_count--) {
		PWR_ClearLVIStatus();
		if(PWR_GetLVIStatus()) 
			LVI_Flag_count--;
	}
	if(LVI_Flag_count==0) //LVI detected, 22us taken at LVI_Debounce_count=3
		return 1;
	else 
		return 0;
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	
	Port_SetOutputHighpin(PORT2, PIN0);
	Port_SetOutputHighpin(PORT1, PIN0);
	Port_SetOutputHighpin(PORT1, PIN1);

#if A96T418_MODE==1    
	/* Enable LVR 1.61V */
	PWR_ConfigureLVR(LVR_1_61, TRUE);

	/* Enable LVI 3.56V */
	PWR_ConfigureLVI(LVI_3_56, TRUE);
	//PWR_ConfigureLVI(LVI_2_28, TRUE);
	//PWR_ConfigureLVI(LVI_4_25, TRUE);
#endif
#if A96T418_MODE==0    
	/* Enable LVR Level0 */
	PWR_ConfigureLVR(LVR_L0, TRUE);

	/* Enable LVI Level3 */
	//PWR_ConfigureLVI(LVI_L3, TRUE);
	PWR_ConfigureLVI(LVI_L0, TRUE);
#endif

    /* Enable INT */
	GLOBAL_INTERRUPT_EN();
    
    /* Infinite loop */
	while(1)
	{
		Port_SetOutputTogglepin(PORT2, PIN0);

		if(PWR_LVI_CheckWithPolling()) 
		{
			//Port_SetOutputLowpin(PORT1, PIN0);			
			printf("\n\r PWR_LVI_CheckWithPolling detected ");
		}
		
		if(PWR_LVI_CheckWithInterrupt())
		{
			//Port_SetOutputLowpin(PORT1, PIN1);
			printf("\n\r PWR_LVI_CheckWithInterrupt detected ");
		}
	}	
}

/**********************************************************************
 * @brief		LVI interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void LVI_Int(void) interrupt LVI_VECT
{
	if(LVI_IntFlag_count) 
		LVI_IntFlag_count--;
	PWR_LVI_ConfigureInterrupt(FALSE);
}

/* --------------------------------- End Of File ------------------------------ */

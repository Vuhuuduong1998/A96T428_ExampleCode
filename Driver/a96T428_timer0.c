/**
 *******************************************************************************
 * @file        a96T428_timer0.c
 * @author      ABOV R&D Division
 * @brief       Timer0
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428_timer0.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
bit fTimer0_overflow_int=0;
bit fTimer0_match_int=0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer0 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T0_COUNTER_MODE			= 0
*					- T0_PWM_MODE 				= 1
*					- T0_CAPTURE_MODE			= 2
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER0_DIV2 				= 0
*					- TIMER0_DIV4 				= 1
*					- TIMER0_DIV8 				= 2
*					- TIMER0_DIV32 				= 3
*					- TIMER0_DIV128				= 4
*					- TIMER0_DIV512				= 5
*					- TIMER0_DIV2048			= 6
*					- TIMER0_EXT_CLK 			= 7
* @return		None
*/
void Timer0_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg;
	
	temp_reg = T0CR;
	/* Set timer mode & frequency source */
	temp_reg &= ~((0x3 << 4) | (0x7 << 1));
	temp_reg |= ((mode << 4) | (freq << 1) | (0x1 << 0));
	T0CR = temp_reg;
}

/**
* @brief	 Set Timer0 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFF).
* @return		None
*/
void Timer0_SetMatchCounter(uint8_t match_count) 
{
	T0DR = match_count;
}

/**
* @brief	 Set Timer0 PWM mode operation
* @param   count		This parameter contains the value of timer match count(0~0xFF).
* @return		None
*/
void Timer0_SetPWM(uint8_t count) 
{
	T0DR = count;
}

/**
* @brief	 Get Timer0 Capture mode operation
* @param   None
* @return		The value of timer capture data
*/
uint8_t Timer0_GetCaptureValue(void) 
{
	return T0CDR;
}

/**
* @brief	 Clear the value of Timer0 counter data 
* @param   None
* @return		None
*/
void Timer0_ClearCountData(void) 
{
	T0CR |= 0x01;
}

/**
* @brief		Start Timer0 operation
* @param   None
* @return		None
*/
void Timer0_Start(void) 
{
	T0CR |= 0x80;
}

/**
* @brief		Stop Timer0 operation
* @param   None
* @return		None
*/
void Timer0_Stop(void) 
{
	T0CR &= ~0x80;
}

/**
* @brief		Configure Timer0 interrupt
* @param   mode		This parameter contains the mode of timer match or overflow interrupt
*
*					- MATCH_INT								= 0
*					- OVERFLOW_INT 				= 1
* @param   enable		This parameter contains the enable of timer interrupt
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void Timer0_ConfigureInterrupt(uint8_t mode, uint8_t enable) 
{
	if(mode == MATCH_INT)
	{
		if(enable)
			IE2 |= 0x02;
		else
			IE2 &= ~0x02;
	}
	else if(mode == OVERFLOW_INT)
	{
		if(enable)
			IE2 |= 0x01;
		else
			IE2 &= ~0x01;
	}
}

/**
* @brief		Configure Timer0 interrupt
* @param   mode		This parameter contains the mode of timer match or overflow interrupt
*
*					- MATCH_INT								= 0
*					- OVERFLOW_INT 							= 1
* @return		None
*/
void Timer0_ClearInterruptFlag(uint8_t mode) 
{
	if(mode == MATCH_INT)
	{
		EIFLAG1 = ~(0x40); 
	}
	else if(mode == OVERFLOW_INT)
	{
		EIFLAG1 = ~(0x80); 
	}
}

void Timer0_Int_Flag_Polling(void) 
{
	if(EIFLAG1&0xC0)
	{
		if(EIFLAG1&0xC0)
		{
			EIFLAG1 = ~(0xC0); 
			fTimer0_match_int=1;
			fTimer0_overflow_int=1;
		}
		else if(EIFLAG1&0x40)
		{
			EIFLAG1 = ~(0x40); 
			fTimer0_match_int=1;
		}
		else if(EIFLAG1&0x80)
		{
			EIFLAG1 = ~(0x80); 
			fTimer0_overflow_int=1;
		}
	}
}
/* --------------------------------- End Of File ------------------------------ */
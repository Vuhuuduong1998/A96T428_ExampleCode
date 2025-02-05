/**
 *******************************************************************************
 * @file        a96T428_timer4.c
 * @author      ABOV R&D Division
 * @brief       Timer4
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
#include "a96T428_timer4.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
bit fTimer4_int=0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer4 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T4_COUNTER_MODE						= 0
*					- T4_CAPTURE_MODE						= 1
*					- T4_PPG_ONESHOT_MODE 					= 2
*					- T4_PPG_REPEAT_MODE 					= 3
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER4_DIV512 						= 0
*					- TIMER4_DIV128 						= 1
*					- TIMER4_DIV32 							= 2
*					- TIMER4_DIV8 							= 3
*					- TIMER4_DIV4							= 4
*					- TIMER4_DIV2							= 5
*					- TIMER4_DIV1							= 6
*					- TIMER4_T3_A_MATCH	= 7
* @return		None
*/
void Timer4_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = T4CRH;
	/* Set timer mode & frequency source */
	temp_reg &= ~(0x3 << 4);
	temp_reg |= ((mode << 4) | (0x1 << 0));

	temp_reg2 = T4CRL;
	temp_reg2 &= ~((0x7 << 5) | (0x1 << 0));
	if(mode >= T4_PPG_ONESHOT_MODE)
		temp_reg2 |= (freq << 5);
	else
		temp_reg2 |= ((freq << 5) | (0x1 << 0));
	
	T4CRH = temp_reg;
	T4CRL = temp_reg2;
}

/**
* @brief	 Set Timer4 Clock source edge selection for External Clock
* @param   edge		This parameter contains the value of edge
*
* 					- T4_FALLING_EDGE 						= 0
*					- T4_RISING_EDGE 						= 1
* @return		None
*/
void Time4_SetExternalClockEdge(uint8_t edge) 
{
	uint8_t temp_reg;
	
	temp_reg = T4CRL;
	temp_reg  &= ~(0x02);
	temp_reg  |= (edge << 1);
	
	T4CRL = temp_reg;
}


/**
* @brief	 Set Timer4 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFFFF).
* @return		None
*/
void Timer4_SetMatchCounter(uint16_t match_count) 
{
	T4ADR = match_count;
}

/**
* @brief	 Set Timer4 PPG Polarity
* @param   polarity		This parameter contains the value of polarity.
*
*					- T4_START_HIGH 						= 0
*					- T4_START_LOW 							= 1
* @return		None
*/
void Timer4_SetPPGPolarity(uint8_t polarity) 
{
	uint8_t temp_reg;
	
	temp_reg = T4CRL;
	temp_reg &= ~(0x04); 
	temp_reg |= (polarity << 2);
	
	T4CRL = temp_reg;
}

/**
* @brief	 Set Timer4 PPG mode duty counter
* @param   count		This parameter contains the value of timer duty count(0~0xFFFF).
* @return		None
*/
void Timer4_SetPPGDutyCounter(uint16_t count) 
{
	T4BDR = count;
}

/**
* @brief	 Set Timer4 PPG mode period counter
* @param   count		This parameter contains the value of timer period count(1~0xFFFF).
* @return		None
*/
void Timer4_SetPPGPeriodCounter(uint16_t count) 
{
	T4ADR = count;
}


/**
* @brief	 Get Timer4 Capture mode operation
* @param   None
* @return		The value of timer capture data(16bit)
*/
uint16_t Timer4_GetCaptureValue(void) 
{
	return T4BDR;
}

/**
* @brief	 Clear the value of Timer4 counter data 
* @param   None
* @return		None
*/
void Timer4_ClearCountData(void) 
{
	T4CRH |= 0x01;
}

/**
* @brief		Start Timer4 operation
* @param   None
* @return		None
*/
void Timer4_Start(void) 
{
	T4CRH |= 0x80;
}

/**
* @brief		Stop Timer4 operation
* @param   None
* @return		None
*/
void Timer4_Stop(void) 
{
	T4CRH &= ~0x80;
}

/**
* @brief		Configure Timer4 interrupt
* @param   enable		This parameter contains the enable of timer interrupt
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void Timer4_ConfigureInterrupt(uint8_t enable) 
{
	if(enable)
		IE2 |= 0x20;
	else
		IE2 &= ~0x20;
}

/**
* @brief		Claer Timer4 interrupt
* @param   None
* @return		None
*/
void Timer4_ClearInterruptFlag(void) 
{
	T4CRL &= ~0x10;
}

void Timer4_Int_Flag_Polling(void) 
{
	if(T4CRL & T4IFR) 
	{
		T4CRL &= ~T4IFR; 
		fTimer4_int=1;
	}
}
/* --------------------------------- End Of File ------------------------------ */
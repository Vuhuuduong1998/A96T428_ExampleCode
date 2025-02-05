/**
 *******************************************************************************
 * @file        a96T428_timer5.c
 * @author      ABOV R&D Division
 * @brief       Timer5
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
#include "a96T428_timer5.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
bit fTimer5_int=0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer5 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T5_COUNTER_MODE						= 0
*					- T5_CAPTURE_MODE						= 1
*					- T5_PPG_ONESHOT_MODE 					= 2
*					- T5_PPG_REPEAT_MODE 					= 3
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER5_DIV512 						= 0
*					- TIMER5_DIV128 						= 1
*					- TIMER5_DIV32 							= 2
*					- TIMER5_DIV8 							= 3
*					- TIMER5_DIV4							= 4
*					- TIMER5_DIV2							= 5
*					- TIMER5_DIV1							= 6
*					- TIMER5_HSI_16MHZ						= 7
* @return		None
*/
void Timer5_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = T5CRH;
	/* Set timer mode & frequency source */
	temp_reg &= ~(0x3 << 4);
	temp_reg |= ((mode << 4) | (0x1 << 0));
	
	temp_reg2 = T5CRL;
	temp_reg2 &= ~((0x7 << 5) | (0x1 << 0));
	if(mode >= T5_PPG_ONESHOT_MODE)
		temp_reg2 |= (freq << 5);
	else
		temp_reg2 |= ((freq << 5) | (0x1 << 0));
	
	
	T5CRH = temp_reg;
	T5CRL = temp_reg2;
}

/**
* @brief	 Set Timer5 Clock source edge selection for External Clock
* @param   edge		This parameter contains the value of edge
*
*					- T5_FALLING_EDGE 						= 0
*					- T5_RISING_EDGE 						= 1
* @return		None
*/
void Time5_SetExternalClockEdge(uint8_t edge) 
{
	uint8_t temp_reg;
	
	temp_reg = T5CRL;
	temp_reg  &= ~(0x02);
	temp_reg  |= (edge << 1);
	
	T5CRL = temp_reg;
}


/**
* @brief	 Set Timer5 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFFFF).
* @return		None
*/
void Timer5_SetMatchCounter(uint16_t match_count) 
{
	T5ADR = match_count;
}

/**
* @brief	 Set Timer5 PPG Polarity
* @param   polarity		This parameter contains the value of polarity.
*
*					- T5_START_HIGH 						= 0
*					- T5_START_LOW 							= 1
* @return		None
*/
void Timer5_SetPPGPolarity(uint8_t polarity) 
{
	uint8_t temp_reg;
	
	temp_reg = T5CRL;
	temp_reg &= ~(0x04); 
	temp_reg |= (polarity << 2);
	
	T5CRL = temp_reg;
}

/**
* @brief	 Set Timer5 PPG mode duty counter
* @param   count		This parameter contains the value of timer duty count(0~0xFFFF).
* @return		None
*/
void Timer5_SetPPGDutyCounter(uint16_t count) 
{
	T5BDR = count;
}

/**
* @brief	 Set Timer5 PPG mode period counter
* @param   count		This parameter contains the value of timer period count(1~0xFFFF).
* @return		None
*/
void Timer5_SetPPGPeriodCounter(uint16_t count) 
{
	T5ADR = count;
}


/**
* @brief	 Get Timer5 Capture mode operation
* @param   None
* @return		The value of timer capture data(16bit)
*/
uint16_t Timer5_GetCaptureValue(void) 
{
	return T5BDR;
}

/**
* @brief	 Clear the value of Timer5 counter data 
* @param   None
* @return		None
*/
void Timer5_ClearCountData(void) 
{
	T5CRH |= 0x01;
}

/**
* @brief		Start Timer5 operation
* @param   None
* @return		None
*/
void Timer5_Start(void) 
{
	T5CRH |= 0x80;
}

/**
* @brief		Stop Timer5 operation
* @param   None
* @return		None
*/
void Timer5_Stop(void) 
{
	T5CRH &= ~0x80;
}

/**
* @brief		Configure Timer5 interrupt
* @param   enable		This parameter contains the enable of timer interrupt
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void Timer5_ConfigureInterrupt(uint8_t enable) 
{
	if(enable)
		IE2 |= 0x20;
	else
		IE2 &= ~0x20;
}

/**
* @brief		Claer Timer5 interrupt
* @param   None
* @return		None
*/
void Timer5_ClearInterruptFlag(void) 
{
	T5CRL &= ~0x10;
}

void Timer5_Int_Flag_Polling(void) 
{
	if(T5CRL & T5IFR) 
	{
		T5CRL &= ~T5IFR; 
		fTimer5_int=1;
	}
}
/* --------------------------------- End Of File ------------------------------ */
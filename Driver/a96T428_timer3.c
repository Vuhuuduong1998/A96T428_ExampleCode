/**
 *******************************************************************************
 * @file        a96T428_timer3.c
 * @author      ABOV R&D Division
 * @brief       Timer3
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
#include "a96T428_timer3.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
bit fTimer3_int=0;

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer3 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T3_COUNTER_MODE							= 0
*					- T3_CAPTURE_MODE							= 1
*					- T3_PPG_ONESHOT_MODE 						= 2
*					- T3_PPG_REPEAT_MODE 						= 3
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER3_DIV512 						= 0
*					- TIMER3_DIV128 						= 1
*					- TIMER3_DIV32 							= 2
*					- TIMER3_DIV8 							= 3
*					- TIMER3_DIV4							= 4
*					- TIMER3_DIV2							= 5
*					- TIMER3_DIV1							= 6
*					- TIMER3_EXT_CLK						= 7
* @return		None
*/
void Timer3_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = T3CRH;
	/* Set timer mode & frequency source */
	temp_reg &= ~(0x3 << 4);
	temp_reg |= ((mode << 4) | (0x1 << 0));
	
	temp_reg2 = T3CRL;
	temp_reg2 &= ~((0x7 << 5) | (0x1 << 0));
	if(mode >= T3_PPG_ONESHOT_MODE)
		temp_reg2 |= (freq << 5);
	else
		temp_reg2 |= ((freq << 5) | (0x1 << 0));
	
	T3CRH = temp_reg;
	T3CRL = temp_reg2;
}

/**
* @brief	 Set Timer3 Clock source edge selection for External Clock
* @param   edge		This parameter contains the value of edge
*
*					- T3_FALLING_EDGE 						= 0
*					- T3_RISING_EDGE 							= 1
* @return		None
*/
void Time3_SetExternalClockEdge(uint8_t edge) 
{
	uint8_t temp_reg;
	
	temp_reg = T3CRL;
	temp_reg  &= ~(0x02);
	temp_reg  |= (edge << 1);
	
	T3CRL = temp_reg;
}


/**
* @brief	 Set Timer3 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFFFF).
* @return		None
*/
void Timer3_SetMatchCounter(uint16_t match_count) 
{
	T3ADR = match_count;
}

/**
* @brief	 Set Timer3 PPG Polarity
* @param   polarity		This parameter contains the value of polarity.
*
*					- T3_START_HIGH 						= 0
*					- T3_START_LOW 							= 1
* @return		None
*/
void Timer3_SetPPGPolarity(uint8_t polarity) 
{
	uint8_t temp_reg;
	
	temp_reg = T3CRL;
	temp_reg &= ~(0x04); 
	temp_reg |= (polarity << 2);
	
	T3CRL = temp_reg;
}

/**
* @brief	 Set Timer3 PPG mode duty counter
* @param   count		This parameter contains the value of timer duty count(0~0xFFFF).
* @return		None
*/
void Timer3_SetPPGDutyCounter(uint16_t count) 
{
	T3BDR = count;
}

/**
* @brief	 Set Timer3 PPG mode period counter
* @param   count		This parameter contains the value of timer period count(1~0xFFFF).
* @return		None
*/
void Timer3_SetPPGPeriodCounter(uint16_t count) 
{
	T3ADR = count;
}


/**
* @brief	 Get Timer3 Capture mode operation
* @param   None
* @return		The value of timer capture data(16bit)
*/
uint16_t Timer3_GetCaptureValue(void) 
{
	return T3BDR;
}

/**
* @brief	 Clear the value of Timer3 counter data 
* @param   None
* @return		None
*/
void Timer3_ClearCountData(void) 
{
	T3CRH |= 0x01;
}

/**
* @brief		Start Timer3 operation
* @param   None
* @return		None
*/
void Timer3_Start(void) 
{
	T3CRH |= 0x80;
}

/**
* @brief		Stop Timer3 operation
* @param   None
* @return		None
*/
void Timer3_Stop(void) 
{
	T3CRH &= ~0x80;
}

/**
* @brief		Configure Timer3 interrupt
* @param   enable		This parameter contains the enable of timer interrupt
*
*				- FLASE												= 0
*				- TRUE 												= 1
* @return		None
*/
void Timer3_ConfigureInterrupt(uint8_t enable) 
{
	if(enable)
		IE2 |= 0x10;
	else
		IE2 &= ~0x10;
}

/**
* @brief		Claer Timer3 interrupt
* @param   None
* @return		None
*/
void Timer3_ClearInterruptFlag(void) 
{
	T3CRL &= ~0x10;
}

void Timer3_Int_Flag_Polling(void) 
{
	if(T3CRL & T3IFR) 
	{
		T3CRL &= ~T3IFR; 
		fTimer3_int=1;
	}
}

/* --------------------------------- End Of File ------------------------------ */
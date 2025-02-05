/**
 *******************************************************************************
 * @file        a96T428_timer1.c
 * @author      ABOV R&D Division
 * @brief       Timer1
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
#include "a96T428_timer1.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
bit fTimer1_int=0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer1 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T1_COUNTER_MODE						= 0
*					- T1_CAPTURE_MODE						= 1
*					- T1_PPG_ONESHOT_MODE 					= 2
*					- T1_PPG_REPEAT_MODE 					= 3
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER1_DIV2048 						= 0
*					- TIMER1_DIV512 						= 1
*					- TIMER1_DIV64 							= 2
*					- TIMER1_DIV8 							= 3
*					- TIMER1_DIV4							= 4
*					- TIMER1_DIV2							= 5
*					- TIMER1_DIV1							= 6
*					- TIMER1_EXT_CLK 						= 7
* @return		None
*/
void Timer1_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = T1CRH;
	/* Set timer mode & frequency source */
	temp_reg &= ~(0x3 << 4);
	temp_reg |= ((mode << 4) | (0x1 << 0));
	
	temp_reg2 = T1CRL;
	temp_reg2 &= ~((0x7 << 5) | (0x1 << 0));
	if(mode >= T1_PPG_ONESHOT_MODE)
		temp_reg2 |= (freq << 5);
	else
		temp_reg2 |= ((freq << 5) | (0x1 << 0));
	
	T1CRH = temp_reg;
	T1CRL = temp_reg2;
}

/**
* @brief	 Set Timer1 Clock source edge selection for External Clock
* @param   edge		This parameter contains the value of edge
*
*					- T1_FALLING_EDGE 						= 0
*					- T1_RISING_EDGE 						= 1
* @return		None
*/
void Timer1_SetExternalClockEdge(uint8_t edge) 
{
	uint8_t temp_reg;
	
	temp_reg = T1CRL;
	temp_reg  &= ~(0x02);
	temp_reg  |= (edge << 1);
	
	T1CRL = temp_reg;
}


/**
* @brief	 Set Timer1 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFFFF).
* @return		None
*/
void Timer1_SetMatchCounter(uint16_t match_count) 
{
	T1ADR = match_count;
}

/**
* @brief	 Set Timer1 PPG Polarity
* @param   polarity		This parameter contains the value of polarity.
*
*					- T1_START_HIGH 						= 0
*					- T1_START_LOW 							= 1
* @return		None
*/
void Timer1_SetPPGPolarity(uint8_t polarity) 
{
	uint8_t temp_reg;
	
	temp_reg = T1CRL;
	temp_reg &= ~(0x04); 
	temp_reg |= (polarity << 2);
	
	T1CRL = temp_reg;
}

/**
* @brief	 Set Timer1 PPG mode duty counter
* @param   count		This parameter contains the value of timer duty count(0~0xFFFF).
* @return		None
*/
void Timer1_SetPPGDutyCounter(uint16_t count) 
{
	T1BDR = count;
}

/**
* @brief	 Set Timer1 PPG mode period counter
* @param   count		This parameter contains the value of timer period count(1~0xFFFF).
* @return		None
*/
void Timer1_SetPPGPeriodCounter(uint16_t count) 
{
	T1ADR = count;
}


/**
* @brief	 Get Timer1 Capture mode operation
* @param   None
* @return		The value of timer capture data(16bit)
*/
uint16_t Timer1_GetCaptureValue(void) 
{
	return T1BDR;
}

/**
* @brief	 Clear the value of Timer1 counter data 
* @param   None
* @return		None
*/
void Timer1_ClearCountData(void) 
{
	T1CRH |= 0x01;
}

/**
* @brief		Start Timer1 operation
* @param   None
* @return		None
*/
void Timer1_Start(void) 
{
	T1CRH |= 0x80;
}

/**
* @brief		Stop Timer1 operation
* @param   None
* @return		None
*/
void Timer1_Stop(void) 
{
	T1CRH &= ~0x80;
}

/**
* @brief		Configure Timer1 interrupt
* @param   enable		This parameter contains the enable of timer interrupt
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void Timer1_ConfigureInterrupt(uint8_t enable) 
{
	if(enable)
		IE2 |= 0x04;
	else
		IE2 &= ~0x04;
}

/**
* @brief		Claer Timer1 interrupt
* @param   None
* @return		None
*/
void Timer1_ClearInterruptFlag(void) 
{
	T1CRL &= ~0x10;
}

void Timer1_Int_Flag_Polling(void) 
{
	if(T1CRL & T1IFR) 
	{
		T1CRL &= ~T1IFR; 
		fTimer1_int=1;
	}
}

/* --------------------------------- End Of File ------------------------------ */
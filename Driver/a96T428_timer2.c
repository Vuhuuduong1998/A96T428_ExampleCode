/**
 *******************************************************************************
 * @file        a96T428_timer2.c
 * @author      ABOV R&D Division
 * @brief       Timer2
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
#include "a96T428_timer2.h"

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
bit fTimer2_int=0;

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize timer2 peripheral
* @param   mode		This parameter contains the mode of timer.
*
*					- T2_COUNTER_MODE						= 0
*					- T2_CAPTURE_MODE						= 1
*					- T2_PPG_ONESHOT_MODE 					= 2
*					- T2_PPG_REPEAT_MODE 					= 3
* @param   freq	This parameter contains the selection of frequency.
*
*					- TIMER2_DIV512 						= 0
*					- TIMER2_DIV128 						= 1
*					- TIMER2_DIV32 							= 2
*					- TIMER2_DIV8 							= 3
*					- TIMER2_DIV4							= 4
*					- TIMER2_DIV2							= 5
*					- TIMER2_DIV1							= 6
*					- TIMER2_T1_A_MATCH	= 7
* @return		None
*/
void Timer2_Initial(uint8_t mode, uint8_t freq)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = T2CRH;
	/* Set timer mode & frequency source */
	temp_reg &= ~(0x3 << 4);
	temp_reg |= ((mode << 4) | (0x1 << 0));
	
	temp_reg2 = T2CRL;
	temp_reg2 &= ~((0x7 << 5) | (0x1 << 0));
	if(mode >= T2_PPG_ONESHOT_MODE)
		temp_reg2 |= (freq << 5);
	else
		temp_reg2 |= ((freq << 5) | (0x1 << 0));
	
	T2CRH = temp_reg;
	T2CRL = temp_reg2;
}

/**
* @brief	 Set Timer2 Counter mode operation
* @param   match_count		This parameter contains the value of timer match count(0~0xFFFF).
* @return		None
*/
void Timer2_SetMatchCounter(uint16_t match_count) 
{
	T2ADR = match_count;
}

/**
* @brief	 Set Timer2 PPG Polarity
* @param   polarity		This parameter contains the value of polarity.
*
*					- T2_START_HIGH 						= 0
*					- T2_START_LOW 							= 1
* @return		None
*/
void Timer2_SetPPGPolarity(uint8_t polarity) 
{
	uint8_t temp_reg;
	
	temp_reg = T2CRL;
	temp_reg &= ~(0x04); 
	temp_reg |= (polarity << 2);
	
	T2CRL = temp_reg;
}

/**
* @brief	 Set Timer2 PPG mode duty counter
* @param   count		This parameter contains the value of timer duty count(0~0xFFFF).
* @return		None
*/
void Timer2_SetPPGDutyCounter(uint16_t count) 
{
	T2BDR = count;
}

/**
* @brief	 Set Timer2 PPG mode period counter
* @param   count		This parameter contains the value of timer period count(1~0xFFFF).
* @return		None
*/
void Timer2_SetPPGPeriodCounter(uint16_t count) 
{
	T2ADR = count;
}


/**
* @brief	 Get Timer2 Capture mode operation
* @param   None
* @return		The value of timer capture data(16bit)
*/
uint16_t Timer2_GetCaptureValue(void) 
{
	return T2BDR;
}

/**
* @brief	 Clear the value of Timer2 counter data 
* @param   None
* @return		None
*/
void Timer2_ClearCountData(void) 
{
	T2CRH |= 0x01;
}

/**
* @brief		Start Timer2 operation
* @param   None
* @return		None
*/
void Timer2_Start(void) 
{
	T2CRH |= 0x80;
}

/**
* @brief		Stop Timer2 operation
* @param   None
* @return		None
*/
void Timer2_Stop(void) 
{
	T2CRH &= ~0x80;
}

/**
* @brief		Configure Timer2 interrupt
* @param   enable		This parameter contains the enable of timer interrupt
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void Timer2_ConfigureInterrupt(uint8_t enable) 
{
	if(enable)
		IE2 |= 0x08;
	else
		IE2 &= ~0x08;
}

/**
* @brief		Claer Timer2 interrupt
* @param   None
* @return		None
*/
void Timer2_ClearInterruptFlag(void) 
{
	T2CRL &= ~0x10;
}

void Timer2_Int_Flag_Polling(void) 
{
	if(T2CRL & T2IFR) 
	{
		T2CRL &= ~T2IFR; 
		fTimer2_int=1;
	}
}

/* --------------------------------- End Of File ------------------------------ */
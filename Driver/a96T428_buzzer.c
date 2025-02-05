/**
 *******************************************************************************
 * @file        a96T428_buzzer.c
 * @author      ABOV R&D Division
 * @brief       Buzzer Driver
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
#include "a96T428_buzzer.h"

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

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize Buzzer peripheral
* @param   freq_div		This parameter contains the value of division at System Clock.(0~255)
* @param   pre_scaler		This parameter contains the selection of pre_scaler.
*
*					- BUZZER_DIV32 				= 0
*					- BUZZER_DIV64 				= 1
*					- BUZZER_DIV128 			= 2
*					- BUZZER_DIV256 			= 3
* @return		The Frequency of Buzzer.
*/
uint32_t Buzzer_Initial(uint32_t system_freq, uint8_t freq_div, uint8_t pre_scaler) 
{
	uint32_t buzzer_freq;
	uint8_t temp_reg;
	
	BUZDR = freq_div;
	
	temp_reg = BUZCR;
	temp_reg &= ~(0x3 << 1);
	/*	 buzzer_freq = system_freq / (2 * pre_scaler * (freq_div + 1) */
	if(pre_scaler == BUZZER_DIV32)
	{
		buzzer_freq = system_freq / (64 * (freq_div + 1));
		temp_reg |= (0 << 1);
	}
	else if(pre_scaler == BUZZER_DIV64)
	{
		buzzer_freq = system_freq / (128 * (freq_div + 1));
		temp_reg |= (1 << 1);
	}
	else if(pre_scaler == BUZZER_DIV128)
	{
		buzzer_freq = system_freq / (256 * (freq_div + 1));
		temp_reg |= (2 << 1);
	}
	else if(pre_scaler == BUZZER_DIV256)
	{
		buzzer_freq = system_freq / (512 * (freq_div + 1));
		temp_reg |= (3 << 1);
	}
	
	BUZCR = temp_reg;
	
	return buzzer_freq;

}


/**
* @brief		Start Buzzer operation
* @param   None
* @return		None
*/
void Buzzer_Start(void) 
{
	BUZCR |= 0x1;
}

/**
* @brief		Stop Buzzer operation
* @param   None
* @return		None
*/
void Buzzer_Stop(void) 
{
	BUZCR &= ~0x1;
}

/* --------------------------------- End Of File ------------------------------ */
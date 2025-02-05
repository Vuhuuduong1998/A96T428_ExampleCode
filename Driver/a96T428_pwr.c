/**
 *******************************************************************************
 * @file        a96T428_pwr.c
 * @author      ABOV R&D Division
 * @brief       Power sub System
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
#include "a96T428_pwr.h"

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
* @brief		Enter Idle mode for power function.
* @param 	None
* @return		None
*/
void PWR_EnterIdle(void)
{
	PCON = PWR_IDLE_MODE;
	
	/* Must execute NOP */ 
	NOP;
	NOP;
	NOP;
}


/**
* @brief		Enter Stop mode for power function.
* @param 	None
* @return		None
*/
void PWR_EnterStop(void)
{
	PCON = PWR_STOP_MODE;
	
	/* Must execute NOP */ 
	NOP;
	NOP;
	NOP;
}

/**
* @brief		Get status of Reset status.
* @param   None
* @return		Status of Reset flag.
*/
uint8_t PWR_GetResetStatus(void)
{
	return (RSTFR & 0xF8);
}

/**
* @brief		Clear status of Reset status.
* @param   flag 		status of Reset flag
*
*					- POR_FLAG			= 0x80
*					- EXT_RESET_FLAG	= 0x40
*					- WDT_RESET_FLAG 	= 0x20
*					- OCD_RESET_FLAG 	= 0x10
*					- LVR_RESET_FLAG 	= 0x08
* @return		None
*/
void PWR_ClearResetStatus(uint8_t flag)
{
	RSTFR = ~flag;
}

/**
* @brief		Configure low voltage reset function.
* @param   select_level		This parameter contains the selection of LVR level.
*
*	- 		LVR_1_61		 	= 0
*	-		LVR_1_77		 	= 2
*	-		LVR_1_88		 	= 3
*	-		LVR_2_00		 	= 4
*	-		LVR_2_13		 	= 5
*	-		LVR_2_28		 	= 6
*	-		LVR_2_46		 	= 7
* 	-		LVR_2_68		 	= 8
*	-		LVR_2_81		 	= 9
*	-		LVR_3_06		 	= 10
*	-		LVR_3_21		 	= 11
*	-		LVR_3_56		 	= 12
*	-		LVR_3_73		 	= 13
*	-		LVR_3_91		 	= 14
*	-		LVR_4_25		 	= 15
* @param   enable   This parameter contains the enable of this function. 
* 					- FALSE = 0
*					- TRUE = 1
* @return		None
*/
void PWR_ConfigureLVR(uint8_t select_level, uint8_t enable)
{
	uint8_t temp_reg;
	
	temp_reg = LVRCR;
	temp_reg &= ~(0x1F);
	
	if(enable)
		temp_reg |= ((select_level << 1) | (0 << 0));
	else
		temp_reg |= ((select_level << 1) | (1 << 0));
	
	LVRCR = temp_reg;
}

/**
* @brief		Configure low voltage Interrupt function.
* @param   select_level		This parameter contains the selection of LVI level.
*
*	-		LVI_2_28		 	= 6
*	-		LVI_2_46		 	= 7
* 	-		LVI_2_68		 	= 8
*	-		LVI_2_81		 	= 9
*	-		LVI_3_06		 	= 10
*	-		LVI_3_21		 	= 11
*	-		LVI_3_56		 	= 12
*	-		LVI_3_73		 	= 13
*	-		LVI_3_91		 	= 14
*	-		LVI_4_25		 	= 15
* @param   enable   This parameter contains the enable of this function. 
* 					- FALSE = 0
*					- TRUE = 1
* @return		None
*/
void PWR_ConfigureLVI(uint8_t select_level, uint8_t enable)
{
	uint8_t temp_reg;

	temp_reg = LVICR;
	temp_reg &= ~(0x3F);
	temp_reg |= ((select_level << 0) | (enable << 4));
		
	LVICR = temp_reg;	
}

/**
* @brief		Configure the enable or disable LVI interrupt.
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE = 0
*			- TRUE 	= 1
* @return		None
*/
void PWR_LVI_ConfigureInterrupt(uint8_t enable)
{
	uint8_t temp_reg;
	
	temp_reg = IE3;
	if(enable == TRUE)
	{
		temp_reg |= (enable << 5);
	}
	else
	{
		temp_reg &= ~(1 << 5);
	}
	IE3 = temp_reg;
}

/**
* @brief		Get status of low voltage interrupt status.
* @param   None
* @return		Status of LVI detect flag.
*/
uint8_t PWR_GetLVIStatus(void)
{
	return ((LVICR & 0x20) == 0x20);
}

/**
* @brief		Clear status of low voltage interrupt status.
* @param   		None
* @return		None
*/
void PWR_ClearLVIStatus(void)
{
	LVICR &= ~(1<<5);
}

/* --------------------------------- End Of File ------------------------------ */
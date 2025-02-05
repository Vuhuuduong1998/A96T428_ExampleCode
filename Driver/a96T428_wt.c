/**
 *******************************************************************************
 * @file        a96T428_wt.c
 * @author      ABOV R&D Division
 * @brief       Watch Timer
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/* Included File ---------------------------------------------------------------*/
#include "a96T428_WT.h"

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
bit fWT_int=0;

/* Private Function Prototype ------------------------------------------------*/

/**
* @brief	Initialize Watch Timer peripheral
* @param    wt_interval	 This parameter contains the selection of interrupt interval.
*
*						- fWCK_DIV128	        = 0
*						- fWCK_DIV8192         	= 1
*						- fWCK_DIV16384        	= 2
*						- fWCK_DIV16384_WTDR1	= 3
* @param    wtckfreq	 This parameter contains the selection of source clock.
*
*						- fSUB 		   	= 0
*						- fX_DIV256	   	= 1
*						- fX_DIV128		= 2
*						- fX_DIV64 	  	= 3
* @return	None
*/
void WT_Initial(uint8_t wt_interval, uint8_t wtckfreq)
{
	uint8_t temp_reg;
	
	temp_reg = WTCR;
	/* Set interrupt interval & Source Clock */
	temp_reg &= ~((0x9 << 4) | (0xf << 0));
	temp_reg |= ((wt_interval << 2) | (wtckfreq << 0));
	
	WTCR = temp_reg;
}

/**
* @brief	Start Watch Timer operation
* @param    None
* @return	None
*/
void WT_Start(void) 
{
	WTCR |= 0x80;
}

/**
* @brief	Stop Watch Timer operation
* @param    None
* @return	None
*/
void WT_Stop(void) 
{
	WTCR &= ~0x80;
}

/**
* @brief	Set WT Data Value
* @param    count   This parameter contains the value of watch timer count(0~0x7F).
* @return	None
*/
void WT_SetDataValue(uint8_t count) 
{
	WTDR = count | WTCL; //(Clear WT Counter (auto clear after 1 Cycle))
}

/**
* @brief	Get Watch Timer operation
* @param    None
* @return	The value of Watch timer counter data
*/
uint8_t WT_GetCountValue(void) 
{
	return WTCNT;
}

/**
* @brief	Clear the value of Watch Timer counter data 
* @param    None
* @return	None
*/
void WT_ClearCountData(void) 
{
	WTDR |= 0x80;
}

/**
* @brief	Configure WT interrupt
* @param    enable  This parameter contains the enable of timer interrupt
*
*					- WT_INT_DIS	= 0
*					- WT_INT_EN 	= 1
* @return	None
*/
void WT_ConfigureInterrrupt(uint8_t enable) 
{
    if(enable)
        IE3 |= 0x04;
    else
        IE3 &= ~0x04;
}

void WDT_Int_Flag_polling(void) 
{
	if(WTCR & WTIFR)
	{
		fWT_int=1;
		WTCR &= ~WTIFR;
	}
}
/* --------------------------------- End Of File ------------------------------ */

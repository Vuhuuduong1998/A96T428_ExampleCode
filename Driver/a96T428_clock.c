/**
 *******************************************************************************
 * @file        a96T428_clock.c
 * @author      ABOV R&D Division
 * @brief       Clock Source File
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
#include "a96T428_clock.h"
#include "delay.h"

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
* @brief	Initialize System Clock peripheral
* @param    clock_sel	This parameter contains the selection of clock.
* @return	None
*/
void System_Clock_Initial(uint8_t clock_sel)
{
    uint8_t temp_reg;
	if(clock_sel <= HSI16_DIV1)
	{
		/* Internal 16Mhz RC OSC for system clock */
		SCCR	= SCCR_IRC_16MHZ;            
		/* Internal RC Oscillator Post-divider Select INT-RC/n (32/n MHz) */
		temp_reg = OSCCR;
		temp_reg  &= ~(0x7 << 3);
		temp_reg  |= (clock_sel << 3) | OSCCR_HIRCE_EN;
		OSCCR = temp_reg;
	}
	else if(clock_sel == LSI)
	{
#if A96T418_MODE==1
		/* Internal 128khz RC OSC for system clock */
   		//OSCCR |= OSCCR_LSIRCE_EN;
        //NOP_10us_Delay(1000); //1ms
		SCCR	= SCCR_IRC_128KHZ;   
#endif		
#if A96T418_MODE==0
		/* Internal 32khz RC OSC for system clock */
		SCCR	= SCCR_IRC_32KHZ;   
#endif		
 	}
#if A96T418_MODE==1
	else if(clock_sel == HSE)
	{ 
	}
	else if(clock_sel == LSE)
	{
		if(P2PU&0xC0)
			P2PU&=~0xC0; //P27/SXIN, P26/SXOUT  pullup disable 
		/* Alternative Function for External Sub OSC  */
		P2FSRH = (0x1 << 6) | (0x1 << 4); //P27/SXIN, P26/SXOUT 

		/* External Sub OSC for system clock */
   		OSCCR |= OSCCR_SCLKE_EN;
        NOP_10us_Delay(1000);	
        SCCR	= SCCR_EXT_SOSC;   
	}
#endif		
}

/**
* @brief	Controls clock frequency selection and oscillator operation.
* @param    osc_sel 	This parameter contains the selection of Oscillator.
*
*					- LSIRC  = 0
*					- HSIRC	 = 1
*					- NULLXCLK   = 2
*					- SUBCLK 	 = 3
* @param    hsirc_div 	This parameter contains the Post-divider Selection of Internal RC Oscillator.
*
*					- INTRC32_DIV64 = 0
*					- INTRC32_DIV32 = 1
*					- INTRC32_DIV16 = 2
*					- INTRC32_DIV8  = 3
*					- INTRC32_DIV4  = 4
*					- INTRC32_DIV2  = 5
* @param    osc_enable	This parameter contains the enable of oscillator.
*
*					- OSC_DIS  = 0
*					- OSC_EN   = 1
* @return	None
*/
void Clock_ConfigureOSC(uint8_t osc_sel, uint8_t hsirc_div, uint8_t osc_enable)
{
	uint8_t temp_reg;
	
	if(osc_sel == LSIRC)
	{
		if(osc_enable == OSC_DIS)
        {
            /* Disable Low Frequency(128kHz) Internal RC OSC for system clock at stop mode */
            OSCCR &= ~(0x1 << 6);
        }
        else if(osc_enable == OSC_EN)
        {
            /* Enable Low Frequency(128kHz) Internal RC OSC for system clock at stop mode */
            OSCCR |= (osc_enable << 6);
        }            
	}
	else if(osc_sel == HSIRC)
	{
        if(osc_enable == OSC_DIS)
        {
            /* Disable High Frequency(16MHz) Internal RC OSC for system clock */
            OSCCR |= (0x1 << 2);          
        }
        else if(osc_enable == OSC_EN)
        {
			temp_reg = OSCCR;
            /* Enable High Frequency(16MHz) Internal RC OSC for system clock */
            temp_reg &= ~(osc_enable << 2);
            
            temp_reg &= ~(0x7<<3);
            temp_reg |= (hsirc_div<<3);
			
			OSCCR = temp_reg;
        }
 	}
	else if(osc_sel == NULLXCLK)
	{
	}
#if A96T418_MODE==1			
	else if(osc_sel == SUBCLK)
	{
        if(osc_enable == OSC_DIS)
        {
            /* Disable External Sub OSC for system clock */
            OSCCR  &= ~(0x1 << 0);            
        }
        else if(osc_enable == OSC_EN)
        {
			if(P2PU&0xC0)
				P2PU&=~0xC0; //P27/SXIN, P26/SXOUT  pullup disable 
            /* Alternative Function for External Sub OSC  */
            P2FSRH = (0x1 << 6) | (0x1 << 4); //P27/SXIN, P26/SXOUT 
            /* Enable External Sub OSC for system clock */
            OSCCR  |= (osc_enable << 0);
			NOP_10us_Delay(10000);	//100ms
            OSCCR  |= (osc_enable << 0);			
       }
	}
#endif
}

/**
* @brief		Get Systemclock frequency(speed)
* @param   None
* @return		The value of system clock(frequency)
*/
uint32_t Clock_GetSystemFreq(void)
{
	uint32_t shift=(OSCCR>>3)&0x07; 
	uint32_t sysclk=0;
	if(shift>5) 
		shift=5;
	shift=5-shift;
	switch(SCCR&0x03) {
	case SCCR_IRC_16MHZ : sysclk=16000000UL>>shift;
		break;
#if A96T418_MODE==1			
	case SCCR_EXT_SOSC : sysclk=32768UL;
		break;
	case SCCR_IRC_128KHZ : sysclk=128000UL;
		break;
#endif		
#if A96T418_MODE==0			
	case SCCR_IRC_32KHZ : sysclk=32768UL;
		break;
#endif		
	}
	return sysclk;
	
	//return SYSTEM_CLOCK;
}

/* --------------------------------- End Of File ------------------------------ */
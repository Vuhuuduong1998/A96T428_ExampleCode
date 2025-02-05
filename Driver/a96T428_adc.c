/**
 *******************************************************************************
 * @file        a96T428_adc.c
 * @author      ABOV R&D Division
 * @brief       Analog-to-Digital Convertor
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
#include "a96T428_adc.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
uint8_t adc_count = 0;
uint16_t *adc_buff;
uint8_t buff_cnt = 0;
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize ADC peripheral
* @param   clock_sel			This parameter contains the selection of ADC converter clock (fx <= 8MHz).
*
*			- ADC_CLK_DIV1	 	= 0
*			- ADC_CLK_DIV2		= 1
*			- ADC_CLK_DIV4 		= 2
*			- ADC_CLK_DIV8 		= 3
* @param   trigger_sel		This parameter contains the selection of ADC trigger source.
*
*			- ADC_SW_TRIG	 	= 0
*			- ADC_T1_TRIG 		= 1
*			- ADC_T3_TRIG 		= 2
*			- ADC_EXT0_TRIG 		= 3
*			- ADC_EXT8_TRIG		= 4
* @param   ref_voltage		This parameter contains the selection of ADC reference voltage.
*
*			- ADC_INTERNAL_REF 	= 0
*			- ADC_EXTERNAL_REF 	= 1
* @param   align_sel 		This parameter contains the selection of ADC data align. 
*
*			- ADC_MSB 			= 0
*			- ADC_LSB 			= 1
* @return		None
*/

volatile uint32_t ttt;
void ADC_Initial(uint8_t clock_sel, uint8_t trigger_sel, uint8_t ref_voltage, uint8_t align_sel)
{
		/*  The A/D converter needs at least 8 us for conversion time.
        So you must set the conversion time more than 8 us.
        If the ADC conversion time is set short, the resolution is degraded.
    
        ** ADC Conversion clock = ADCLK * 60 cycles
        
        fx=16Mhz, CKSEL =  fx/4 = 0.25us
        60 clock x 0.25us = 15us at 4Mhz (16Mhz/4)
    */
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = ADCCRH;
	temp_reg &= ~(0xFF);
	temp_reg |= ((trigger_sel << 3) | (align_sel << 2) | (clock_sel << 0));
	
	temp_reg2 = ADCCRL;
	temp_reg2 &= ~(0xF0);
	temp_reg2 |= ((1 << 7) | (ref_voltage << 5));  //ADC Enable + ref_Voltage
	
	ADCCRH = temp_reg;
	ADCCRL = temp_reg2;
	
	ttt=Clock_GetSystemFreq();
	ttt>>= clock_sel;
	//while( !((Clock_GetSystemFreq() >> clock_sel) < 7500000) )
	{
		NOP;  // NOTE : system clock / div < 7.5Mhz
	}
		
}

/**
* @brief		Enables or disables the ADC peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE 	= 0
*			- TRUE 		= 1
* @return		None
*/
void ADC_Enable(uint8_t enable)
{
	if(enable == TRUE)
	{
		ADCCRL |= (1 << 7);
	}
	else
	{
		ADCCRL &= ~(1 << 7);
	}
}

/**
* @brief		Enables the ADC Start conversion(For software trigger).
* @param   		None
* @return		None
*/
void ADC_StartSoftwareTrigger()
{
	P2IO|=(1<<0);	P20=!P20; 
	ADCCRL |= (1 << 6);
}

/**
* @brief		Select the ADC Converter Input Channel.
* @param   channel		This parameter contains the channel of ADC input.
*
*			- ADC_CH0 	= 0
*			- ADC_CH1 	= 1
*			- ADC_CH2 	= 2
*			- ADC_CH3 	= 3
*			- ADC_CH4 	= 4
*			- ADC_CH5 	= 5
*			- ADC_CH6 	= 6
*			- ADC_CH7 	= 7
*			- ADC_CH8	= 8
*			- ADC_CH9 	= 9
*			- ADC_CH10 	= 10
*			- ADC_CH11 	= 11
*			- ADC_CH12 	= 12
*			- ADC_CH13 	= 13
*			- ADC_CH14 	= 14
*			- ADC_CH15 	= 15
* @return		None
*/
void ADC_SelectChannel(uint8_t channel)
{
	uint8_t temp_reg;
	
	temp_reg = ADCCRL;
	temp_reg &= ~(0xF << 0);
	temp_reg |= channel;
	
	ADCCRL = temp_reg;
}

/**
* @brief		Get status of ADC conversion.
* @param   None
* @return		Status of ADC conversion flag.
*/
uint8_t ADC_GetConversionStatus()
{
	return (ADCCRL & 0x10);
}

/**
* @brief		Get data of ADC conversion for ADC interrupt.
* @param   adc_data		This parameter contains the data of conversion ADC.
* @param   count		This parameter contains the number of count.
* @return		None
*/
void ADC_GetDataWithInterrupt(uint16_t *adc_data, uint8_t count)
{
	adc_count = count;
	adc_buff = (uint16_t*)adc_data;
	buff_cnt = 0;
	
	ADC_ConfigureInterrupt(TRUE);

	if( ((ADCCRH & 0x38) == 0x00)) //SW trigger
	{
		ADC_StartSoftwareTrigger();
	}
	
	while(0 < adc_count);  //adc interrupt subroutine execute
	ADC_ConfigureInterrupt(FALSE);
}

/**
* @brief		Get data of ADC conversion for ADC polling.
* @param   adc_data		This parameter contains the data of conversion ADC.
* @param   count		This parameter contains the number of count.
* @return		None
*/
void ADC_GetDataWithPolling(uint16_t *adc_data, uint8_t count)
{
	uint8_t i;
	
	for(i = 0; i < count; i++)
	{
		if( ((ADCCRH & 0x38) == 0x00) ) //SW trigger
			ADC_StartSoftwareTrigger();
			
		while(!(ADCCRL & 0x10)); //while(!(ADC_GetConversionStatus()));		
		P21=!P21; P2IO|=(1<<1);
			
		adc_data[i] = ADCDR;
	}
}

/**
* @brief		Configure the enable or disable ADC interrupt.
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE = 0
*			- TRUE 	= 1
* @return		None
*/
void ADC_ConfigureInterrupt(uint8_t enable)
{
	if(enable == TRUE)
	{
		IE3  |= 0x01; 
	}
	else
	{
		ADCCRH &= ~0x80;
		IE3 &= ~0x01;
	}
}

/**
* @brief		Clear the ADC interrupt status.
* @param   		None
* @return		None
*/
void ADC_ClearInterruptStatus()
{
	ADCCRH &= ~0x80;
}


void ADC_Int_Handler(void) interrupt ADC_VECT
{
	P21=!P21; P2IO|=(1<<1);
	if(adc_count) 
	{
		adc_count--;
		adc_buff[buff_cnt++] = ADCDR;

		if(((ADCCRH & 0x38) == 0x00) && (adc_count != 0)) //SW trigger
		{	
			ADC_StartSoftwareTrigger(); 	
		}
	}
		
	//ADC_ClearInterruptStatus();
}

/* --------------------------------- End Of File ------------------------------ */
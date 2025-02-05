/**
 *******************************************************************************
 * @file        a96T428_touch.c
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
#include "a96T428_touch.h"
#include "typedef.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
bit fTOUCH_int=0;
u8 saveTS_CON;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize TOUCH peripheral
* @return		None
*/

void TOUCH_Initial()
{
	/*       */
	uint8_t ch;

	for(ch=0;ch<TOUCH_CH_COUNT;ch++)
		TS_SCO(ch)=0x1234; //dummy setting
	
//	{SFR_TS_MODE,F0_TS_MODE},
//	{SFR_TS_SUM_CNT,F0_TS_SUM_CNT},
//	{SFR_TS_CH_SEL_H,F0_TS_CH_SEL_H},
//	{SFR_TS_CH_SEL_M,F0_TS_CH_SEL_M},    
//	{SFR_TS_CH_SEL_L,F0_TS_CH_SEL_L},
//	{SFR_TS_S1_WIDTH,F0_TS_S1_WIDTH},    
//	{SFR_TS_SLP_CON,F0_TS_SLP_CON},
//	{SFR_TS_VREF,F0_TS_VREF},
//	{SFR_TS_TRIM,F0_TS_TRIM},
//	{SFR_TS_CLK_CFG,F0_TS_CLK_CFG},
//	{SFR_TRIM_OSC,F0_TRIM_OSC},
//	{SFR_DELTA_OSC,F0_DELTA_OSC},
//	{SFR_TLED,F0_TLED},
//	{SFR_TS_VHS_H,F0_TS_VHS_H},
//	{SFR_TS_VHS_L,F0_TS_VHS_L},
//	{SFR_TS_VCOMP_H,F0_TS_VCOMP_H},
//	{SFR_TS_VCOMP_L,F0_TS_VCOMP_L},


	TS(SFR_TS_CLK_CFG)=F0_TS_CLK_CFG;
	TS(SFR_TS_MODE)=F0_TS_MODE;
	TS(SFR_TS_S1_WIDTH)=F0_TS_S1_WIDTH;
	TS(SFR_TS_TRIM)=F0_TS_TRIM;
	TS(SFR_DELTA_OSC)=F0_DELTA_OSC;
	TS(SFR_TLED)=F0_TLED;

#if A96T418_MODE==1
	OSCCR|=0x80; //Touch (16MHz) TIRC OSC
//@tom0917   TS(SFR_TS_TRIM_OSC) = FUSE_TOUC;//replace by 160706 OTP value
	if((TS(SFR_TS_MODE)&0x1C)==0x04)  { // if High Sense Mode 
		TS(SFR_TS_VHS_H) = F0_TS_VHS_H;
		TS(SFR_TS_VHS_L) = F0_TS_VHS_L;
		TS(SFR_TS_VCOMP_H) = F0_TS_VCOMP_H;
		TS(SFR_TS_VCOMP_L) = F0_TS_VCOMP_L;
	}			
#else
	TS(SFR_TS_VDAC_COMP_H) = F0_TS_VDAC_COMP_H;
	TS(SFR_TS_VDAC_COMP_L) = F0_TS_VDAC_COMP_L;
	
#endif
	
}


/**
* @brief		Enables or disables the TOUCH peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE 	= 0
*			- TRUE 		= 1
* @return		None
*/
void TOUCH_Enable(uint8_t enable)
{
	if(enable == TRUE)
	{
#if A96T418_MODE==1
		TS(SFR_TS_CON) = _TS_START;		//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
#endif	
#if A96T418_MODE==0
		TS_CON = _TS_START;		//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
#endif	
	}
	else
	{
#if A96T418_MODE==1
		TS(SFR_TS_CON) = 0;
#endif	
#if A96T418_MODE==0
		TS_CON=0;		
#endif	
	}
}

/**
* @brief		Select the TOUCH Converter Input Channel.
* @param   channel		This parameter contains the channel of TOUCH input.
*
*			- TOUCH_CH0 	= bit0
*			- TOUCH_CH1 	= bit1
*			- TOUCH_CH2 	= bit2
*			- TOUCH_CH3 	= bit3
*			- TOUCH_CH4 	= bit4
*			- TOUCH_CH5 	= bit5
*			- TOUCH_CH6 	= bit6
*			- TOUCH_CH7 	= bit7
*			- TOUCH_CH8		= bit8
*			- TOUCH_CH9 	= bit9
*			- TOUCH_CH10 	= bit10
*			- TOUCH_CH11 	= bit11
*			- TOUCH_CH12 	= bit12
*			- TOUCH_CH13 	= bit13
*			- TOUCH_CH14 	= bit14
*			- TOUCH_CH15 	= bit15
* @return		None
*/
void TOUCH_SelectChannel(uint32_t channel)
{
#if A96T418_MODE==0
	TS(SFR_TS_CH_SEL_MH) = (channel>>24)&0xFF;//
#endif	
	TS(SFR_TS_CH_SEL_H) = (channel>>16)&0xFF;//
	TS(SFR_TS_CH_SEL_M) = (channel>>8)&0xFF;//
	TS(SFR_TS_CH_SEL_L) = channel&0xFF;//
	
}

/**
* @brief	Get status of TOUCH conversion.
* @param   	None
* @return	None
*/
uint8_t TOUCH_GetConversionStatus()
{
#if A96T418_MODE==1
	return (TS(SFR_TS_CON) & TS_IF);  
#endif	
#if A96T418_MODE==0
	return (TS_CON & TS_IF);  
#endif	
}

/**
* @brief	Get Raw data of TOUCH conversion.
* @param   	touch_data		This parameter contains the data of conversion TOUCH.
* @return	None
*/
void TOUCH_GetRawdata(TOUCHDATA *touch_data)
{
	uint8_t ch;
	uint8_t enabled=0;

		for(ch=0;ch<TOUCH_CH_COUNT;ch++)
		{
			enabled=0;
			if(ch<8) {
				if(TS(SFR_TS_CH_SEL_L)&(1<<ch)) { 
					enabled=1;
				}
			}
			else if(ch<16) {
				if(TS(SFR_TS_CH_SEL_M)&(1<<(ch-8))) { 
					enabled=2;
				}
			}
			else if(ch<24) {
				if(TS(SFR_TS_CH_SEL_H)&(1<<(ch-16))) { 
					enabled=3;
				}
			}		
			else  {
				if(TS(SFR_TS_CH_SEL_MH)&(1<<(ch-24))) { 
					enabled=4;
				}
			}		
			if(enabled) {
				touch_data[ch].F0data = (TSRAW(ch*2)); //first freq raw
				touch_data[ch].F1data = (TSRAW(ch*2+1)); //second freq raw
				touch_data[ch].sumdata=(uint32_t)(touch_data[ch].F0data)+touch_data[ch].F1data;					
			}
		}
}

void TOUCH_SetRawdata(void)
{
	uint8_t ch;
	uint8_t enabled=0;
	u8 saveSFR_TS_CLK_CFG;
	
	saveSFR_TS_CLK_CFG=TS(SFR_TS_CLK_CFG);
	TS(SFR_TS_CLK_CFG)|=0x80;

	TS(SFR_TS_SUM_CH_WAR)=0xA5;
	
		for(ch=0;ch<TOUCH_CH_COUNT;ch++)
		{
			enabled=1;
//			enabled=0;
//			if(ch<8) {
//				if(TS(SFR_TS_CH_SEL_L)&(1<<ch)) { 
//					enabled=1;
//				}
//			}
//			else if(ch<16) {
//				if(TS(SFR_TS_CH_SEL_M)&(1<<(ch-8))) { 
//					enabled=2;
//				}
//			}
//			else if(ch<24) {
//				if(TS(SFR_TS_CH_SEL_H)&(1<<(ch-16))) { 
//					enabled=3;
//				}
//			}		
//			else  {
//				if(TS(SFR_TS_CH_SEL_MH)&(1<<(ch-24))) { 
//					enabled=4;
//				}
//			}		
			if(enabled) {
				(TSRAW(ch*2)) = ((ch*2)<<8)|(ch*2); //first freq raw
				(TSRAW(ch*2+1)) = ((ch*2+1)<<8)|(ch*2+1); //second freq raw
				//(TSRAW(ch*2)) = 0x33bb; //first freq raw
				//(TSRAW(ch*2+1)) = 0x55aa; //second freq raw
			}
		}
	TS(SFR_TS_CLK_CFG)=saveSFR_TS_CLK_CFG;
}
		
/**
* @brief		Get data of TOUCH conversion for TOUCH interrupt.
* @param   touch_data		This parameter contains the data of conversion TOUCH.
* @return		None
*/

TOUCHDATA *touch_data_ptr=0;

void TOUCH_GetDataWithInterrupt(TOUCHDATA *touch_data)
{
	TOUCH_ConfigureInterrupt(TRUE);
	touch_data_ptr=touch_data;
	fTOUCH_int=0;
#if A96T418_MODE==1
	TS(SFR_TS_CON) = _TS_START;//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
#endif	
#if A96T418_MODE==0
	TS_CON = _TS_START;//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
#endif	
	
	while(!fTOUCH_int);  //wait touch interrupt 

}

/**
* @brief		Get data of TOUCH conversion for TOUCH polling.
* @param   touch_data		This parameter contains the data of conversion TOUCH.
* @return		None
*/
void TOUCH_GetDataWithPolling(TOUCHDATA *touch_data)
{
#if A96T418_MODE==1
	TS(SFR_TS_CON) = _TS_START;//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
	while(!(TS(SFR_TS_CON) & TS_IF));
#endif	
#if A96T418_MODE==0
	TS_CON = _TS_START;//(TS(SFR_TS_CLK_CFG)&0x80?TS_RUN:OSC_EN|TS_RUN)  ;//(); 
	while(!(TS_CON & TS_IF));
#endif	
	saveTS_CON=TS_CON;

	TOUCH_GetRawdata(touch_data);
	
	TOUCH_SetRawdata();
	TOUCH_GetRawdata(touch_data);
	
#if A96T418_MODE==1
	TS(SFR_TS_CON)=0;		
#endif	
#if A96T418_MODE==0
	TS_CON=0;		
#endif	
}

/**
* @brief		Configure the enable or disable TOUCH interrupt.
* @param   enable   This parameter contains the enable of this function. 
*
*			- FALSE = 0
*			- TRUE 	= 1
* @return		None
*/
void TOUCH_ConfigureInterrupt(uint8_t enable)
{
	if(enable == TRUE)
	{
		if(!(IE & (1<<3))) //IE.3 
			IE |= (1<<3); //IE.3 
	}
	else
	{
		if((IE & (1<<3))) //IE.3 
			IE &= ~(1<<3); //IE.3 
	}
}

/**
* @brief		Clear the TOUCH interrupt status.
* @param   		None
* @return		None
*/
void TOUCH_ClearInterruptStatus()
{
#if A96T418_MODE==1
	TS(SFR_TS_CON)=0;		
#endif	
#if A96T418_MODE==0
	TS_CON=0;		
#endif	
}


void TOUCH_Int_Handler(void) interrupt TOUCH_VECT
{
	fTOUCH_int=1;
	//IE &= ~(1<<3); //IE.3 clear 
	saveTS_CON=TS_CON;	
	TOUCH_GetRawdata(touch_data_ptr);
#if A96T418_MODE==1
	TS(SFR_TS_CON)=0;		
#endif	
#if A96T418_MODE==0
	TS_CON=0;		
#endif		
}

/* --------------------------------- End Of File ------------------------------ */
/**
 *******************************************************************************
 * @file        a96T428_adc.h
 * @author      ABOV R&D Division
 * @brief       ADC Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADC_H_
#define __ADC_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "a96T428_clock.h"
#include "typedef.h"
#include "Intrins.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#if A96T418_MODE==1
#define	TOUCH_CH_COUNT	20 
#endif
#if A96T418_MODE==0
#define	TOUCH_CH_COUNT	32 
#endif

#define ADC_CLK_DIV1						0
#define ADC_CLK_DIV2						1
#define ADC_CLK_DIV4						2
#define ADC_CLK_DIV8						3

#define ADC_SW_TRIG						0
#define ADC_T1_TRIG						1
#define ADC_T3_TRIG						2
#define ADC_EXT_TRIG					3
#define ADC_EXT8_TRIG					4

#define ADC_INTERNAL_REF	0
#define ADC_EXTERNL_REF		1

#define ADC_MSB	0
#define ADC_LSB		1

/*******************************************************************************
* Public Typedef
*******************************************************************************/

/* Touch */                                                             
//=============================================================
//=============================================================
#if A96T418_MODE==1
enum{
    SFR_TS_CON = 0x00,	//0x2e80
    SFR_TS_MODE,		//0x2e81
    SFR_TS_SUM_CNT,	//0x2e82
    
    SFR_TS_CH_SEL_H,	//0x2e83
    SFR_TS_CH_SEL_M,	//0x2e84    
    SFR_TS_CH_SEL_L,	//0x2e85
    
    SFR_TS_S1_WIDTH,   //0x2E86  
    SFR_TS_SLP_CON, 	//0x2E87      
    SFR_TS_VREF,	   	//0x2E88  
    SFR_TS_TRIM,	   	//0x2E89  
    
    SFR_TS_CLK_CFG, 	//0x2E8A  
    SFR_TRIM_OSC,	   	//0x2E8B  
    SFR_DELTA_OSC,	   	//0x2E8C  
    SFR_TLED,		  	//0x2E8D      
    
    SFR_TS_VHS_H, //0x2E8E      
    SFR_TS_VHS_L,	//0x2E8F 
    SFR_TS_VCOMP_H, //0x2E90  
    SFR_TS_VCOMP_L,	//0x2E91 
    
    SFR_TS_MAX
};
#endif
#if A96T418_MODE==0
enum{
    SFR_TS_MODE=0x00,	//0x2ec1
    SFR_TS_SUM_CNT,		//0x2ec2    
    SFR_TS_CH_SEL_MH,	//0x2ec3
    SFR_TS_CH_SEL_H,	//0x2ec4    
    SFR_TS_CH_SEL_M,	//0x2ec5
    SFR_TS_CH_SEL_L,	//0x2ec6    
    SFR_TS_S1_WIDTH,   	//0x2Ec7  
    SFR_TS_TRIM,	   	//0x2Ec8      
    SFR_TS_CLK_CFG, 	//0x2Ec9  
    SFR_TRIM_OSC,	   	//0x2Eca  
    SFR_DELTA_OSC,	   	//0x2Ecb  
    SFR_TLED,		  	//0x2Ecc      
    SFR_TS_DUMMY2ECD,  	//0x2Ecd
    SFR_TS_DUMMY2ECE,  	//0x2Ece
    SFR_TS_SLP_CON, 	//0x2Ecf      
    SFR_TS_DUMMY2ED0,  	//0x2Ed0
    SFR_TS_DUMMY2ED1,  	//0x2Ed1
    SFR_TS_CLK_CFG2, 	//0x2Ed2  
	SFR_TS_PS_SEQ_SEL,	//0x2Ed3   
	SFR_TS_PRS_SEED, 	//0x2Ed4   
	SFR_TS_SHLD_CON,	//0x2Ed5   
	SFR_TS_MODE2_LDO, 	//0x2Ed6   
	SFR_TS_TEST, 		//0x2Ed7	//hidden    
	SFR_TS_SUM_CH_WAR, 	//0x2Ed8	//hidden       
    SFR_TS_DUMMY2ED9,  	//0x2Ed9
	SFR_TS_VDAC_START_H,//0x2Eda   
	SFR_TS_VDAC_START_L,//0x2Edb   
	SFR_TS_VDAC_STOP_H,	//0x2Edc   
	SFR_TS_VDAC_STOP_L,	//0x2Edd   
	SFR_TS_VDAC_COMP_H,	//0x2Ede   
	SFR_TS_VDAC_COMP_L,	//0x2Edf   

    SFR_TS_MAX
};
#endif

#define	F0_TS_MODE			0x00 //(0x00|0x20) //0x00(normal mode), 0x04(high sense mode), 0x20(sweep disable) , 
#define	F0_TS_SUM_CNT		1//0x01
#define	F0_TS_CH_SEL_H 	0x0
#define	F0_TS_CH_SEL_M 	0x0
#define	F0_TS_CH_SEL_L 	0x0
#define	F0_TS_S1_WIDTH		80  //80:20us@4MHz //40:4MHz ���� 10us,  //20:4MHz ���� 5us
#define	F0_TS_SLP_CON		0x74 //default  //Capacitor/Resistor  Trimming for Input Low Pass Filter, 
#define	F0_TS_VREF		0x02
#define	F0_TS_TRIM		0x07	//High current Disable
#define	F0_TS_CLK_CFG		0x02  //0x02:(4.03MHz  & 3.93MHz�� ������ fixed pattern)
#define	F0_TRIM_OSC		0x20 //
#define	F0_DELTA_OSC	0x01
#define	F0_TLED			0x00


#if A96T418_MODE==0
#define	F0_TS_CH_SEL_MH 	0x0
#define	F0_TS_MODE2_LDO		0x00
#define	TS_CLK_CFG2		0x00
#define	F0_TS_VDAC_COMP_H	0x03
#define	F0_TS_VDAC_COMP_L	0x03

#endif
#if A96T418_MODE==1
#define	F0_TS_VHS_H		0x02
#define	F0_TS_VHS_L		0xFF
#define	F0_TS_VCOMP_H	0x02
#define	F0_TS_VCOMP_L	0x10//0x40
#endif

#if A96T418_MODE==1
#define _DUMMY 8
typedef struct touch_T418
{
    volatile unsigned int SUMRAW[20*2];//0x2E00~0x2E4F
    volatile unsigned int SCO[20];//0x2E80~0x2E77
    volatile unsigned char DUMMY[8];//0x2E78~0x2E7F
    volatile unsigned char TS[SFR_TS_MAX];//0x2E80~0x2F91
} touch_T418;
#endif
#if A96T418_MODE==0
typedef struct touch_T430
{
    volatile unsigned int SUMRAW[32*2];//0x2E00~0x2E7F,  	32*2*2=128B
    volatile unsigned int SCO[32];//0x2E80~0x2EBF,	  	32*2=64B 
    volatile unsigned char DUMMY[1];//0x2EC0
    volatile unsigned char TS[SFR_TS_MAX];//0x2EC1~0x2EDF
} touch_T430;
#endif

#define bSFR	((volatile unsigned char xdata *) 0x2E00)
#if A96T418_MODE==1
#define tSFR  ((touch_T418*)bSFR)
#endif
#if A96T418_MODE==0
#define tSFR  ((touch_T430*)bSFR)
#endif

#define TS(X) (tSFR->TS[X])
#define TS_SCO(X) (tSFR->SCO[X])
#define TSRAW(X) (tSFR->SUMRAW[X])

#if A96T418_MODE==1
typedef enum{
    TS_RUN = 0x01,
     TS_IF = 0x04, //Touch Sensor Interrupt Flag
	//BGR_EN = 0x08, //BGR enable
    TOSC_EN = 0x10, //Oscillator enable
}TS_CON_TYPE;
#define _TS_START (TOSC_EN|TS_RUN)
#endif
#if A96T418_MODE==0
typedef enum{
    TS_RUN = 0x01,
     TS_IF = 0x04, //Touch Sensor Interrupt Flag
	//BGR_EN = 0x08, //BGR enable
    //TOSC_EN = 0x10, //Oscillator enable
}TS_CON_TYPE;
#define _TS_START TS_RUN //(TOSC_EN|TS_RUN)
#endif

typedef struct {
	uint16_t F0data;
	uint16_t F1data;
	uint32_t sumdata;
} TOUCHDATA;

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void TOUCH_Initial(void);
void ADC_Enable(uint8_t enable);
void TOUCH_SelectChannel(uint32_t channel);

uint8_t TOUCH_GetConversionStatus(void);

void TOUCH_GetDataWithInterrupt(TOUCHDATA *touch_data);
void TOUCH_GetDataWithPolling(TOUCHDATA *touch_data);

void TOUCH_ConfigureInterrupt(uint8_t enable);
void TOUCH_ClearInterruptStatus(void);

extern u8 saveTS_CON;

#endif  /* End of __ADC_H_ */
/* --------------------------------- End Of File ------------------------------ */
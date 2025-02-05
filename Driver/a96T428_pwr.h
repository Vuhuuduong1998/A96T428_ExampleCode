/**
 *******************************************************************************
 * @file        a96T428_pwr.h
 * @author      ABOV R&D Division
 * @brief       Power Header File
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
#ifndef __PWR_H_
#define __PWR_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "typedef.h"
#include "Intrins.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define PWR_IDLE_MODE		0x01
#define PWR_STOP_MODE  0x03

#define POR_FLAG								0x80
#define EXT_RESET_FLAG		0x40
#define WDT_RESET_FLAG	0x20
#define OCD_RESET_FLAG 	0x10
#define LVR_RESET_FLAG		0x08


/*******************************************************************************
* Public Typedef
*******************************************************************************/
#if A96T418_MODE==1
enum  lvr_level{ 
	LVR_1_61 = 0,
	LVR_1_77 = 2,
	LVR_1_88,
	LVR_2_00,
	LVR_2_13,
	LVR_2_28,
	LVR_2_46,
	LVR_2_68,
	LVR_2_81,
	LVR_3_06,
	LVR_3_21,
	LVR_3_56,
	LVR_3_73,
	LVR_3_91,
	LVR_4_25,
};

enum  lvi_level{ 
	LVI_2_28 = 6,
	LVI_2_46,
	LVI_2_68,
	LVI_2_81,
	LVI_3_06,
	LVI_3_21,
	LVI_3_56,
	LVI_3_73,
	LVI_3_91,
	LVI_4_25,
};
#endif

#if A96T418_MODE==0
enum  lvr_level{ 
	LVR_L0 = 0, //1.6V
	LVR_L1,		//2.7V
	LVR_L2,		//3.7V
	LVR_L3,		//4.5V 
};

enum  lvi_level{ 
	LVI_L0 = 0,	//1.6V
	LVI_L1,		//2.7V
	LVI_L2,		//3.7V
	LVI_L3,		//4.5V 
};
#endif

#if A96T418_MODE==0
enum  WKTIME_length{ 
	WKTIME_0 = 0, //HSI16MHz/64 CLK source base 
	WKTIME_1,
	WKTIME_2,
	WKTIME_3,
	WKTIME_4,
	WKTIME_5,
	WKTIME_6,
	WKTIME_7,
};

enum  VDCLD_TIME_length{ 
	VDCLDTIME_0 = 0, //HSI16MHz/64 CLK source base 
	VDCLDTIME_1,
	VDCLDTIME_2,
	VDCLDTIME_3,
	VDCLDTIME_4,
	VDCLDTIME_5,
	VDCLDTIME_6,
	VDCLDTIME_7,
};

enum  VDCLOCK_ClkSrc{ 
	VDCLOCKDETECT_CLKSRC_LSI32KHz = 0, //LSI32KHz CLK source base 
	VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64, //HSI16MHz/64 CLK source base 
};

enum FastWakeEn { 
    FAST_WK_DIS = 0,
	FAST_WK_EN = 1,
};

#endif
/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void PWR_EnterIdle(void);
void PWR_EnterStop(void);
uint8_t PWR_GetResetStatus(void);
void PWR_ClearResetStatus(uint8_t flag);

void PWR_ConfigureLVR(uint8_t select_level, uint8_t enable);
void PWR_ConfigureLVI(uint8_t select_level, uint8_t enable);
void PWR_LVI_ConfigureInterrupt(uint8_t enable);
uint8_t PWR_GetLVIStatus(void);
void PWR_ClearLVIStatus(void);


#endif  /* End of __PWR_H_ */
/* --------------------------------- End Of File ------------------------------ */
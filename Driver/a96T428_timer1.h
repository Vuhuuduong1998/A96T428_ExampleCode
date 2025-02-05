/**
 *******************************************************************************
 * @file        a96T428_timer1.h
 * @author      ABOV R&D Division
 * @brief       Timer1 Header File
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
#ifndef __TIMER1_H_
#define __TIMER1_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum Timer1_mode { 
    T1_COUNTER_MODE = 0,
		T1_CAPTURE_MODE,
		T1_PPG_ONESHOT_MODE,
		T1_PPG_REPEAT_MODE,
};

enum Timer1_external_clock_edge { 
    T1_FALLING_EDGE = 0,
	T1_RISING_EDGE,
};

enum Timer1_PPG_polarity { 
    T1_START_HIGH = 0,
	T1_START_LOW,
};


enum Timer1_freq_div { 
    TIMER1_DIV2048 = 0,
		TIMER1_DIV512,
		TIMER1_DIV64,
		TIMER1_DIV8,
		TIMER1_DIV4,
		TIMER1_DIV2,  
		TIMER1_DIV1,
    TIMER1_EXT_CLK,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer1_Initial(uint8_t mode, uint8_t freq);
void Timer1_SetExternalClockEdge(uint8_t edge);
void Timer1_SetMatchCounter(uint16_t match_count);
void Timer1_SetPPGPolarity(uint8_t polarity);
void Timer1_SetPPGDutyCounter(uint16_t count);
void Timer1_SetPPGPeriodCounter(uint16_t count);
uint16_t Timer1_GetCaptureValue(void);
void Timer1_ClearCountData(void);
void Timer1_Start(void);
void Timer1_Stop(void);
void Timer1_ConfigureInterrupt(uint8_t enable);
void Timer1_ClearInterruptFlag(void);
void Timer1_Int_Flag_Polling(void); 

extern bit fTimer1_int;

#endif  /* End of __TIMER1_H_ */
/* --------------------------------- End Of File ------------------------------ */
/**
 *******************************************************************************
 * @file        a96T428_timer3.h
 * @author      ABOV R&D Division
 * @brief       Timer3 Header File
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
#ifndef __TIMER3_H_
#define __TIMER3_H_
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
enum Timer3_mode { 
    T3_COUNTER_MODE = 0,
		T3_CAPTURE_MODE,
		T3_PPG_ONESHOT_MODE,
		T3_PPG_REPEAT_MODE,
};

enum Timer3_external_clock_edge { 
    T3_FALLING_EDGE = 0,
		T3_RISING_EDGE,
};

enum Timer3_PPG_polarity { 
    T3_START_HIGH = 0,
		T3_START_LOW,
};

enum Timer3_freq_div { 
    TIMER3_DIV2048 = 0,
		TIMER3_DIV512,
		TIMER3_DIV64,
		TIMER3_DIV8,
		TIMER3_DIV4,
		TIMER3_DIV2,  
		TIMER3_DIV1,
    TIMER3_EXT_CLK,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer3_Initial(uint8_t mode, uint8_t freq);
void Timer3_SetExternalClockEdge(uint8_t edge);
void Timer3_SetMatchCounter(uint16_t match_count);
void Timer3_SetPPGPolarity(uint8_t polarity);
void Timer3_SetPPGDutyCounter(uint16_t count);
void Timer3_SetPPGPeriodCounter(uint16_t count);
uint16_t Timer3_GetCaptureValue(void);
void Timer3_ClearCountData(void);
void Timer3_Start(void);
void Timer3_Stop(void);
void Timer3_ConfigureInterrupt(uint8_t enable);
void Timer3_ClearInterruptFlag(void);
void Timer3_Int_Flag_Polling(void); 

extern bit fTimer3_int;

#endif  /* End of __TIMER3_H_ */
/* --------------------------------- End Of File ------------------------------ */
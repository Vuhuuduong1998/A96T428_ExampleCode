/**
 *******************************************************************************
 * @file        a96T428_timer5.h
 * @author      ABOV R&D Division
 * @brief       Timer5 Header File
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
#ifndef __TIMER5_H_
#define __TIMER5_H_
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
enum Timer5_mode { 
    T5_COUNTER_MODE = 0,
		T5_CAPTURE_MODE,
		T5_PPG_ONESHOT_MODE,
		T5_PPG_REPEAT_MODE,
};

enum Timer5_external_clock_edge { 
    T5_FALLING_EDGE = 0,
		T5_RISING_EDGE,
};

enum Timer5_PPG_polarity { 
    T5_START_HIGH = 0,
		T5_START_LOW,
};

enum Timer5_freq_div { 
    TIMER5_DIV512 = 0,
		TIMER5_DIV128,
		TIMER5_DIV32,
		TIMER5_DIV8,
		TIMER5_DIV4,
		TIMER5_DIV2,  
		TIMER5_DIV1,
    TIMER5_HSI_16MHZ,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer5_Initial(uint8_t mode, uint8_t freq);
void Timer5_SetExternalClockEdge(uint8_t edge);
void Timer5_SetMatchCounter(uint16_t match_count);
void Timer5_SetPPGPolarity(uint8_t polarity);
void Timer5_SetPPGDutyCounter(uint16_t count);
void Timer5_SetPPGPeriodCounter(uint16_t count);
uint16_t Timer5_GetCaptureValue(void);
void Timer5_ClearCountData(void);
void Timer5_Start(void);
void Timer5_Stop(void);
void Timer5_ConfigureInterrupt(uint8_t enable);
void Timer5_ClearInterruptFlag(void);
void Timer5_Int_Flag_Polling(void); 

extern bit fTimer5_int;

#endif  /* End of __TIMER5_H_ */
/* --------------------------------- End Of File ------------------------------ */
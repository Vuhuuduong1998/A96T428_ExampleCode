/**
 *******************************************************************************
 * @file        a96T428_timer4.h
 * @author      ABOV R&D Division
 * @brief       Timer4 Header File
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
#ifndef __TIMER4_H_
#define __TIMER4_H_
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
enum Timer4_mode { 
    T4_COUNTER_MODE = 0,
		T4_CAPTURE_MODE,
		T4_PPG_ONESHOT_MODE,
		T4_PPG_REPEAT_MODE,
};

enum Timer4_external_clock_edge { 
    T4_FALLING_EDGE = 0,
		T4_RISING_EDGE,
};

enum Timer4_PPG_polarity { 
    T4_START_HIGH = 0,
		T4_START_LOW,
};

enum Timer4_freq_div { 
    TIMER4_DIV512 = 0,
		TIMER4_DIV128,
		TIMER4_DIV32,
		TIMER4_DIV8,
		TIMER4_DIV4,
		TIMER4_DIV2,  
		TIMER4_DIV1,
    TIMER4_T3_A_MATCH,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer4_Initial(uint8_t mode, uint8_t freq);
void Timer4_SetExternalClockEdge(uint8_t edge);
void Timer4_SetMatchCounter(uint16_t match_count);
void Timer4_SetPPGPolarity(uint8_t polarity);
void Timer4_SetPPGDutyCounter(uint16_t count);
void Timer4_SetPPGPeriodCounter(uint16_t count);
uint16_t Timer4_GetCaptureValue(void);
void Timer4_ClearCountData(void);
void Timer4_Start(void);
void Timer4_Stop(void);
void Timer4_ConfigureInterrupt(uint8_t enable);
void Timer4_ClearInterruptFlag(void);
void Timer4_Int_Flag_Polling(void); 

extern bit fTimer4_int;

#endif  /* End of __TIMER4_H_ */
/* --------------------------------- End Of File ------------------------------ */
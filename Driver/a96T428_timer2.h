/**
 *******************************************************************************
 * @file        a96T428_timer2.h
 * @author      ABOV R&D Division
 * @brief       Timer2 Header File
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
#ifndef __TIMER2_H_
#define __TIMER2_H_
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
enum Timer2_mode { 
    T2_COUNTER_MODE = 0,
		T2_CAPTURE_MODE,
		T2_PPG_ONESHOT_MODE,
		T2_PPG_REPEAT_MODE,
};

enum Timer2_PPG_polarity { 
    T2_START_HIGH = 0,
		T2_START_LOW,
};

enum Timer2_freq_div { 
    TIMER2_DIV512 = 0,
		TIMER2_DIV128,
		TIMER2_DIV32,
		TIMER2_DIV8,
		TIMER2_DIV4,
		TIMER2_DIV2,  
		TIMER2_DIV1,
    TIMER2_T1_A_MATCH,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Timer2_Initial(uint8_t mode, uint8_t freq);
void Timer2_SetExternalClockEdge(uint8_t edge);
void Timer2_SetMatchCounter(uint16_t match_count);
void Timer2_SetPPGPolarity(uint8_t polarity);
void Timer2_SetPPGDutyCounter(uint16_t count);
void Timer2_SetPPGPeriodCounter(uint16_t count);
uint16_t Timer2_GetCaptureValue(void);
void Timer2_ClearCountData(void);
void Timer2_Start(void);
void Timer2_Stop(void);
void Timer2_ConfigureInterrupt(uint8_t enable);
void Timer2_ClearInterruptFlag(void);
void Timer2_Int_Flag_Polling(void); 

extern bit fTimer2_int;

#endif  /* End of __TIMER2_H_ */
/* --------------------------------- End Of File ------------------------------ */
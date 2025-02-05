/**
 *******************************************************************************
 * @file        a96T428_clock.h
 * @author      ABOV R&D Division
 * @brief       Clock Header File
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
#ifndef __CLOCK_H_
#define __CLOCK_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/
#define SYSTEM_CLOCK		16000000

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum SystemClk { 
	HSI16_DIV32 = 0,
	HSI16_DIV16,
	HSI16_DIV8,
	HSI16_DIV4,
	HSI16_DIV2,
	HSI16_DIV1,  
	LSI,
#if A96T418_MODE==1			
	HSE,
	LSE
#endif	
};

enum OSCSel { 
    LSIRC = 0,
    HSIRC,
    NULLXCLK,
#if A96T418_MODE==1			
    SUBCLK
#endif	
};

enum HsircDiv { 
    IRC32_DIV64 = 0,
    IRC32_DIV32,
    IRC32_DIV16,
    IRC32_DIV8,
    IRC32_DIV4,
    IRC32_DIV2,
};

enum OSCEnable { 
    OSC_DIS = 0,
    OSC_EN
};


/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void System_Clock_Initial(uint8_t clock_sel);
void Clock_ConfigureOSC(uint8_t osc_sel, uint8_t hsirc_div, uint8_t osc_enable);
uint32_t Clock_GetSystemFreq(void);
#endif  /* End of __CLOCK_H_ */
/* --------------------------------- End Of File ------------------------------ */
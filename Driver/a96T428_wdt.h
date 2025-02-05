/**
 *******************************************************************************
 * @file        a96T428_wdt.h
 * @author      ABOV R&D Division
 * @brief       Watchdog Timer Header File
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


#ifndef __WDT_H_
#define __WDT_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include    "typedef.h"  
#include "a96T428.h"
/*******************************************************************************
* Public Macro
*******************************************************************************/

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum WDT_rst { 
	WDT_FREE_RUN = 0,
	WDT_RST_ON
};

#if A96T418_MODE==1			
enum WDT_clk { 
	WDT_BIT_OVER_DIV1 = 0,
	WDT_BIT_OVER_DIV2,
	WDT_BIT_OVER_DIV4,
	WDT_BIT_OVER_DIV8,
	WDT_BIT_OVER_DIV16,
	WDT_BIT_OVER_DIV32,
	WDT_BIT_OVER_DIV64
};
#endif
#if A96T418_MODE==0			
enum WDT_clk {
	WDT_BIT_OVER_DIV1 = 0,
	WDT_BIT_OVER_DIV2,
	WDT_BIT_OVER_DIV4,
	WDT_BIT_OVER_DIV8,
	WDT_BIT_OVER_DIV16,
	WDT_BIT_OVER_DIV32,
	WDT_BIT_OVER_DIV64
};
#endif

enum WDT_interrupt { 
	WDT_INT_DIS = 0,
	WDT_INT_EN
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void WDT_Initial(uint8_t rst_on, uint8_t wdtck);
void WDT_SetDATA(uint8_t count) ;
void WDT_Set_500msec_Reset(void);
void WDT_Set_1sec_Reset(void);
void WDT_Set_2sec_Reset(void);
void WDT_Set_4sec_Reset(void);
uint8_t WDT_GetCountValue(void);
void WDT_ClearCountData(void);
void WDT_Start(void);
void WDT_Stop(void);
void WDT_ConfigureInterrrupt(uint8_t enable);
void WDT_Int_Flag_polling(void); 

extern bit fWDT_int;

#endif  // __WDT_H_
/* --------------------------------- End Of File ------------------------------ */

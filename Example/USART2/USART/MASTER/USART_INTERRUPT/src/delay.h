/**
 *******************************************************************************
 * @file        delay.h
 * @author      ABOV R&D Division
 * @brief       DELAY Header File
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
#ifndef __ABOV96_CORE_DELAY_H_
#define __ABOV96_CORE_DELAY_H_
/* Includes ------------------------------------------------------------------*/

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/

//------------------------------------------------------------------------------

volatile void NOP_1us_Delay(void);
volatile void NOP_10us_Delay(unsigned int delay);

#endif  /* End of __ABOV96_CORE_DELAY_H */
/* --------------------------------- End Of File ------------------------------ */

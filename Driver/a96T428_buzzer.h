/**
 *******************************************************************************
 * @file        a96T428_buzzer.h
 * @author      ABOV R&D Division
 * @brief       Buzzer Header File
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
#ifndef __BUZZER_H_
#define __BUZZER_H_
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
enum  Buzzer_Prescaler{ 
    BUZZER_DIV32 = 0,
		BUZZER_DIV64,
		BUZZER_DIV128,
		BUZZER_DIV256,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
uint32_t Buzzer_Initial(uint32_t system_freq, uint8_t freq_div, uint8_t pre_scaler);
void Buzzer_Start(void);
void Buzzer_Stop(void);

#endif  /* End of __BUZZER_H_ */
/* --------------------------------- End Of File ------------------------------ */
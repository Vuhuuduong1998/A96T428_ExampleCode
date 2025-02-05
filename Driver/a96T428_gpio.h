/**
 *******************************************************************************
 * @file        a96T428_gpio.h
 * @author      ABOV R&D Division
 * @brief       GPIO Header File
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
#ifndef __GPIO_H_
#define __GPIO_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "typedef.h"


/*******************************************************************************
* Public Macro
*******************************************************************************/
#define PUSH_PULL		0
#define OPEN_DRAIN		1

#define NO_PULL		0
#define PULL_UP		1

#define PORT0           0
#define PORT1           1
#define PORT2           2
#define PORT3           3
#define PORT4           4
#define PORT5           5

#define PIN0            0
#define PIN1            1
#define PIN2            2
#define PIN3            3
#define PIN4            4
#define PIN5            5
#define PIN6            6
#define PIN7            7

#define EXTINT_CH0      0
#define EXTINT_CH1      1
#define EXTINT_CH2      2
#define EXTINT_CH3      3
#define EXTINT_CH4      4
#define EXTINT_CH5      5
#define EXTINT_CH8      8
#define EXTINT_CH10     10
#define EXTINT_CH11     11
#define EXTINT_CH12     12

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  interrupt_edge{ 
        NONE = 0,
		RISING_EDGE,
		FALLING_EDGE,
		BOTH_EDGE,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void Port_Initial(void);
void Port_SetOutputpin(uint8_t port, uint8_t pin, uint8_t mode);
void Port_SetInputpin(uint8_t port, uint8_t pin, uint8_t mode);
void Port_SetAlterFunctionpin(uint8_t port, uint8_t pin, uint8_t val);
void Port_SetOutputHighpin(uint8_t port, uint8_t pin);
void Port_SetOutputLowpin(uint8_t port, uint8_t pin);
void Port_SetOutputTogglepin(uint8_t port, uint8_t pin);
uint8_t Port_GetInputpinValue(uint8_t port, uint8_t pin);
void Port_EnableInterrupt(uint8_t channel);
void Port_DisableInterrupt(uint8_t channel);
void Port_ConfigureInterrupt(uint8_t channel, uint8_t edge);
uint8_t Port_GetInterruptStatus(uint8_t channel);
void Port_ClearInterruptStatus(uint8_t channel);

#endif  /* End of __GPIO_H_ */
/* --------------------------------- End Of File ------------------------------ */
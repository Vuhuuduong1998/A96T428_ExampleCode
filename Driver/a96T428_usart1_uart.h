/**
 *******************************************************************************
 * @file        a96T428_usart1_uart.h
 * @author      ABOV R&D Division
 * @brief       USART1 UART Header File
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
#ifndef __USART1_H_
#define __USART1_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "a96T428_clock.h"
#include "typedef.h"
#include "Intrins.h"

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define	USART1_QUEUE_SIZE					8

#define USART1_STOP_1BIT					0
#define USART1_STOP_2BIT					1

#define USART1_PARITY_NO					0
#define USART1_PARITY_EVEN			2
#define USART1_PARITY_ODD				3

#define USART1_TX_RX_MODE			0
#define USART1_RX_MODE						1
#define USART1_TX_MODE						2

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  usart1_data_length{ 
	USART1_DATA_5BIT = 0,
	USART1_DATA_6BIT = 1,
	USART1_DATA_7BIT = 2,
	USART1_DATA_8BIT = 3,
	USART1_DATA_9BIT = 7,
};

enum usart1_interrupt_flag{
	USART1_RX_COMPLETE_INT = 0,
	USART1_TX_COMPLETE_INT,
	USART1_DATA_EMPTY_INT,  
	USART1_WAKEUP_INT,  	
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USART1_UART_Initial(uint32_t speed, uint8_t data_length, uint8_t stop_bits, uint8_t parity, uint8_t mode);
void USART1_System_Clock_Initial(uint32_t clock_en, uint8_t master_en);
void USART1_Enable(uint8_t enable);

void USART1_UART_SendDataWithPolling(uint8_t *send_data, uint8_t count);
void USART1_UART_SendDataWithInterrupt(uint8_t send_data);
void USART1_UART_ReceiveDataWithPolling(uint8_t *receive_data, uint8_t count);
uint8_t USART1_UART_ReceiveCheckWithPolling(uint8_t *receive_data);
uint8_t USART1_UART_ReceiveDataWithInterrupt(void);
uint8_t USART1_UART_ReceiveCheckWithInterrupt(uint8_t *receive_data);
void USART1_ClearRTOFlag(void);

void USART1_ConfigureInterrupt(uint8_t flag, uint8_t enable);
uint8_t USART1_GetInterruptStatus(void);

void USART1_ConfigureWakeUp(uint8_t enable);
void USART1_ClearWakeUpFlag(void);
void USART1_ConfigureRTO(uint8_t enable, uint16_t RTOCval);
uint8_t USART1_GetRTOStatus(void);

void USART1_CompensationBaudrate(uint16_t fpcg_val, uint8_t enable);

extern bit fRTO_FLAG_occurred;

#endif  /* End of __USART1_H_ */
/* --------------------------------- End Of File ------------------------------ */
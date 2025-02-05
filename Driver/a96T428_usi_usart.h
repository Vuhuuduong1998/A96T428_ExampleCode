/**
 *******************************************************************************
 * @file        a96T428_usi_usart.h
 * @author      ABOV R&D Division
 * @brief       USI USART Header File
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
#ifndef __USI_USART_H_
#define __USI_USART_H_
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
#define	USI0_UART_QUEUE_SIZE					8

#define USART_CH0                  	 0

#define USART_SLAVE_MODE			0
#define USART_MASTER_MODE	1

#define USART_STOP_1BIT					0
#define USART_STOP_2BIT					1

#define USART_CPOL_LOW					0
#define USART_CPOL_HIGH				1

#define USART_PARITY_NO					0
#define USART_PARITY_EVEN			2
#define USART_PARITY_ODD				3

#define USART_TX_RX_MODE			0
#define USART_RX_MODE						1
#define USART_TX_MODE						2

/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  usart_data_length{ 
	USART_DATA_5BIT = 0,
	USART_DATA_6BIT = 1,
	USART_DATA_7BIT = 2,
	USART_DATA_8BIT = 3,
	USART_DATA_9BIT = 7,
};

enum usart_interrupt_flag{
	USART_RX_COMPLETE_INT = 0,
	USART_TX_COMPLETE_INT,
	USART_DATA_EMPTY_INT,  
	USART_WAKEUP_INT,  	
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USI_UART_Initial(uint8_t ch, uint32_t speed, uint8_t data_length, uint8_t stop_bits, uint8_t parity, uint8_t mode);
void USI_USART_System_Clock_Initial(uint8_t ch, uint32_t clock_en, uint8_t master_en);
void USI_USART_Enable(uint8_t ch, uint8_t enable);

void USI_UART_SendDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t count);
void USI_UART_SendDataWithInterrupt(uint8_t ch, uint8_t send_data);
void USI_UART_ReceiveDataWithPolling(uint8_t ch, uint8_t *receive_data, uint8_t count);
uint8_t USI_UART_ReceiveDataWithInterrupt(uint8_t ch);

void USI_USART_ConfigureInterrupt(uint8_t ch, uint8_t flag, uint8_t enable);
uint8_t USI_USART_GetInterruptStatus(uint8_t ch);
void USI_USART_ConfigureWakeUp(uint8_t ch, uint8_t enable);
void USI_USART_ClearWakeUpFlag(uint8_t ch);


#endif  /* End of __USI_USART_H_ */
/* --------------------------------- End Of File ------------------------------ */
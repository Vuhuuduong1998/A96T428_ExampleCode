/**
 *******************************************************************************
 * @file        a96T428_usi_spi.h
 * @author      ABOV R&D Division
 * @brief       USI SPI Header File
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
#ifndef __USI_SPI_H_
#define __USI_SPI_H_
/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428.h"
#include "a96T428_clock.h"
#include "typedef.h"
#include "Intrins.h"

#define USI_MAX_BUFFER_SIZE	4

/*******************************************************************************
* Public Macro
*******************************************************************************/
#define SPI_CH0                  	 0

#define SPI_SLAVE_MODE					0
#define SPI_MASTER_MODE			1

#define SPI_LSB					0
#define SPI_MSB					1

#define SPI_CPOL_LOW					0
#define SPI_CPOL_HIGH				1

#define SPI_CPHA_1EDGE				0
#define SPI_CPHA_2EDGE				1

#define SPI_TX_RX_MODE			0
#define SPI_RX_MODE						1
#define SPI_TX_MODE						2

#define SPI_SS_HW_DISABLE			0
#define SPI_SS_HW_ENABLE				1

#define SPI_MAX_BUFFER_SIZE		8
/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum spi_interrupt_flag{
	SPI_RX_COMPLETE_INT = 0,
	SPI_TX_COMPLETE_INT,
	SPI_DATA_EMPTY_INT,    	
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USI_SPI_Initial(uint8_t ch, uint8_t mode, uint32_t speed, uint8_t first_bit, uint8_t cpol, uint8_t cpha, uint8_t direction, uint8_t ss_mode);
void USI_SPI_Enable(uint8_t ch, uint8_t enable);

void USI_SPI_SendDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t count);
void USI_SPI_ReceiveDataWithPolling(uint8_t ch, uint8_t *receive_data, uint8_t count);
void USI_SPI_SendReceiveDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);

void USI_SPI_SendDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t count);
void USI_SPI_ReceiveDataWithInterrupt(uint8_t ch, uint8_t *receive_data, uint8_t count);
void USI_SPI_SendReceiveDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);

void USI_SPI_SlaveWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);
void USI_SPI_SlaveWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);

void USI_SPI_ConfigureInterrupt(uint8_t ch, uint8_t flag, uint8_t enable);
uint8_t USI_SPI_GetInterruptStatus(uint8_t ch);

void USI_USART_SendReceiveDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);
void USI_USART_Initial(uint8_t ch, uint8_t mastermode, uint32_t speed, uint8_t cpol, uint8_t direction, uint8_t data_length);
void USI_USART_SendReceiveDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);
void USI_USART_SlaveWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);
void USI_USART_SlaveWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count);

extern uint8_t fspi_error_USI0ST1;

#endif  /* End of __USI_SPI_H_ */
/* --------------------------------- End Of File ------------------------------ */
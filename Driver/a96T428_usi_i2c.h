/**
 *******************************************************************************
 * @file        a96T428_usi_i2c.h
 * @author      ABOV R&D Division
 * @brief       USI I2C Header File
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
#ifndef __USI_I2C_H_
#define __USI_I2C_H_
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
#define	MASTER_ONLY		0

#if	MASTER_ONLY==1
#define I2C_SELF_ADDR			0xC8
#define I2C_SELF_ADDR2			0xC4
#define I2C_DEVICE_ADDRESS		0xB8
#define I2C_DEVICE_ADDRESS2		0xB4
#define I2C_DEVICE_ADDRESS3		0xA8
#define I2C_DEVICE_ADDRESS4		0xA4

#else 
#if A96T418_MODE==0
#define I2C_SELF_ADDR			0xA8
#define I2C_SELF_ADDR2			0xA4
#define I2C_DEVICE_ADDRESS		0xB8
#define I2C_DEVICE_ADDRESS2		0xB4
#define I2C_DEVICE_ADDRESS3		0xC8
#define I2C_DEVICE_ADDRESS4		0xC4
#endif
#if A96T418_MODE==1
//#define I2C_SELF_ADDR			0xB8
//#define I2C_SELF_ADDR2			0xB4
//#define I2C_DEVICE_ADDRESS		0xA8
//#define I2C_DEVICE_ADDRESS2		0xA4

#define I2C_SELF_ADDR			0xA8
#define I2C_SELF_ADDR2			0xA4
#define I2C_DEVICE_ADDRESS		0xB8
#define I2C_DEVICE_ADDRESS2		0xB4
#define I2C_DEVICE_ADDRESS3		0xC8
#define I2C_DEVICE_ADDRESS4		0xC4
#endif

#endif


#define I2C_SPEED				100000//400000//50000//10000

#define I2C_MONITOR_BUFFER_SIZE		0x40
#define I2C_MAX_BUFFER_SIZE			8
#define I2C_MAX_CHANNEL					2

#define I2C_CH0														0

#define I2C_ACK_DISABLE						0
#define I2C_ACK_ENABLE							1

#define I2C_WRITE_MODE						0
#define I2C_READ_MODE							1

#define I2C_IDLE													0
#define I2C_BUSY												1
#define I2C_MATCH_CMD							2

#define I2C_TRUE												1
#define I2C_FALSE												0
/*******************************************************************************
* Public Typedef
*******************************************************************************/
enum  i2c_interrupt_status{ 
	GCALL	 	= 1 << 7,
	TEND			= 1 << 6,
	STOPD 	= 1 << 5,
	SSEL 			= 1 << 4,
	MLOST 	= 1 << 3,
	BUSY 		= 1 << 2,
	TMODE 	= 1 << 1,
	RXACK 	= 1 << 0,
};

/*******************************************************************************
* Exported Public Function
*******************************************************************************/
void USI_I2C_Initial(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t addr2);
void USI_I2C_Enable(uint8_t ch, uint8_t enable);
void USI_I2C_ConfigureGerneralCall(uint8_t ch, uint8_t enable);
void USI_I2C_ConfigureAcknowledge(uint8_t ch, uint8_t enable);
void USI_I2C_SoftwareReset(uint8_t ch, uint8_t enable);

void USI_I2C_MasterTransferData(uint8_t ch, uint8_t dev_addr, uint8_t *write_data, uint8_t write_len, uint8_t *read_data, uint8_t read_len);
void USI_I2C_ConfigureInterrupt(uint8_t ch, uint8_t enable);
uint8_t USI_I2C_GetInterruptStatus(uint8_t ch);
void USI_I2C_InterruptHandler(uint8_t ch);
void USI_I2C_ConfigureWakeUp(uint8_t ch, uint8_t enable);
uint8_t USI_I2C_Flag_Polling(uint8_t ch);

extern volatile uint8_t i2c_stop[I2C_MAX_CHANNEL];
extern volatile uint8_t i2c_mode[I2C_MAX_CHANNEL];
extern volatile uint8_t i2c_ErrNo[I2C_MAX_CHANNEL];

extern uint8_t receiveNumMsg[I2C_MAX_CHANNEL];
extern uint8_t transmitNumMsg[I2C_MAX_CHANNEL];
extern u8 USI0ST2_Buf[], USI0CR4_Buf[];
extern u8 USI0ST2_Buf_indx, USI0CR4_Buf_indx;

#endif  /* End of __USI_I2C_H_ */
/* --------------------------------- End Of File ------------------------------ */
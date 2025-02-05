/**
 *******************************************************************************
 * @file        Main.c
 * @author      ABOV R&D Division
 * @brief       Main Example Code
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "intrins.h"
#include "delay.h"
#include "a96T428_flash.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  
#include	"a96T428_flash.h"	
#include "a96T428_timer2.h"

#include "trim.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/



//uint8_t write_data[FLASH_MYBUFFER_SIZE] _at_ 0x100;
//uint8_t read_data[FLASH_MYBUFFER_SIZE];
unsigned char code *read_data=0x0000;
	
/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
	while(!(USTAT & (TXC)));
	USTAT &= ~TXC;
	return c;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 TRIM TEST!!\n\r");
}

void CodeMemoryDisplay(uint16_t start_addr, uint16_t end_addr)
{
	uint16_t i;
	for(i = 0; i < (end_addr-start_addr+1) ; i++)
	{ 
		//if((i%32)>=4)
		//	continue;
		if((i%32)==0)
			printf("\n\r %04x : ", start_addr+i);
		printf("%02X ", read_data[i]&0xFFU);		
	}
}

/* Public Function -----------------------------------------------------------*/

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	Display_project();
		
	//Trim value monitoring 
	TRIM_Register_monitor();
	
	// OCD/USER MODE LDT1 Read
	TRIM_TableBuffer_read(0x400);
	Trim_TableBuffer_monitor(0x400);


	while(1) { 
		NOP_10us_Delay(50000); //0.5s wait
	}
}

/* --------------------------------- End Of File ------------------------------ */

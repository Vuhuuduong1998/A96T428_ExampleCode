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
#include    "Intrins.h"
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart2_spi.h"
#include "a96T428_usart2_uart.h"
#include "a96T428_usi_usart.h"
#include "stdio.h"     

uint8_t xdata write_data[USART_MAX_BUFFER_SIZE] _at_ 0x0300;
uint8_t xdata read_data[USART_MAX_BUFFER_SIZE] _at_ 0x0320;

uint8_t txnum = 0, rxnum = 0, tempr;

/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USI0ST1 & (UDRE)));
		USI0DR = c;
	return c;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P10(RXD0) / P11(TXD0)*/
	Port_SetInputpin(PORT1, PIN0, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
	
	USI_UART_Initial(USART_CH0, 9600, USART_DATA_8BIT, USART_STOP_1BIT, USART_PARITY_NO, USART_TX_RX_MODE);
	
	printf("\n\ra96T428 USART1 USART SLAVE POLLING TEST!!");
}

void Main( void )
{
	volatile uint8_t i;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();  
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);           
	Display_project();
	/* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec
	
	/* Set Alternative function  MISO2(P16) / MOSI2(P17) */
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	/* Set Alternative function  SCK2(P15)  */
	Port_SetAlterFunctionpin(PORT1, PIN5, 0x3);
	
	USART2_USART_Initial(SPI2_SLAVE_MODE, 100000, SPI2_CPOL_LOW, SPI2_TX_RX_MODE, USART2_DATA_8BIT);
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 

    /* Disable INT */
	//GLOBAL_INTERRUPT_EN();    

	NOP_10us_Delay(1);    // 1usec delay

	for(i = 0; i < USART_MAX_BUFFER_SIZE; i++)
		write_data[i] = i+1;
	//return data
	while(!(USTAT & (UDRE)));
	UDATA = write_data[txnum++];

	while (1)
	{
		NOP;
		
		//USER CODE
		
		/* slave handling (Polling) */
		
		while(( USTAT & RXC)!= RXC);		// Wait Data in
		while(( USTAT & TXC)!= TXC);		// Wait Data out
		USTAT &= ~TXC;
		
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		tempr = UDATA;		
		read_data[rxnum++%USART_MAX_BUFFER_SIZE] = tempr;
		if(rxnum>=USART_MAX_BUFFER_SIZE) { 
			printf("\n\r RX : ");
			for(i=0; i<USART_MAX_BUFFER_SIZE; i++) 
				printf("%02X ", (uint16_t)read_data[i]);			
			printf("\n\r TX : ");
			for(i=0; i<USART_MAX_BUFFER_SIZE; i++) 
				printf("%02X ", (uint16_t)write_data[i]);			

			for(i = 0; i < USART_MAX_BUFFER_SIZE; i++)
				write_data[i] = read_data[i]; //writeBuff update with readBuff
			rxnum=0;
			txnum=0;
		}
		while(!(USTAT & (UDRE)));
		//return data
		UDATA = write_data[txnum++%USART_MAX_BUFFER_SIZE];
		
	}
}

/* --------------------------------- End Of File ------------------------------ */

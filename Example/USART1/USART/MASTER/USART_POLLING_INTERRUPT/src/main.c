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
#include "a96T428_usart1_spi.h"
#include "a96T428_usart1_uart.h"
#include "a96T428_usi_usart.h"
#include "stdio.h"     


uint8_t xdata write_data[USART_MAX_BUFFER_SIZE] _at_ 0x0300;
uint8_t xdata read_data[USART_MAX_BUFFER_SIZE] _at_ 0x0320;

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

char getchar()
{
	char c;
	while((USI0ST1 & RXC)!= RXC);		// Wait Data in
	c = USI0DR;
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
	
#if A96T418_MODE==0
	printf("\n\ra96T428 USART1 USART MASTER TEST!!");
#endif	
#if A96T418_MODE==1
	printf("\n\rA96T418 USART1 USART MASTER TEST!!");
#endif	
}

void Main( void )
{
	uint8_t i;
	char c;
	uint8_t usart_pol, usart_int_polling;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();  
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);           
	Display_project();
	/* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec

	//test_mode=0;
	//test_mode=1; //SS Manual mode 

	printf("\n\r Press any key ! ");
	printf("\n\r '0' : SPI_CPOL_LOW ");
	printf("\n\r '2' : SPI_CPOL_HIGH ");
	printf("\n\r other : SPI_CPOL_LOW ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		usart_pol=SPI2_CPOL_LOW;
		break;
	case '1':
		usart_pol=SPI2_CPOL_HIGH;
		break;
	default:
		usart_pol=SPI2_CPOL_LOW;
		break;
	}
	
	printf("\n\r Press any key ! ");
	printf("\n\r '0' : flag Polling mode ");
	printf("\n\r '1' : Interrupt mode  ");
	printf("\n\r other : flag Polling mode ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		usart_int_polling=0;
		break;
	case '1':
		usart_int_polling=1;
		break;
	default:
		usart_int_polling=0;
		break;
	}
	
	/* Set Alternative function  MISO2(P16) / MOSI2(P17) */
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	/* Set Alternative function  SCK2(P15)  */
	Port_SetAlterFunctionpin(PORT1, PIN5, 0x3);
	
	USART1_USART_Initial(SPI2_MASTER_MODE, 100000, usart_pol, SPI2_TX_RX_MODE, USART1_DATA_8BIT);

    if(usart_int_polling)
		GLOBAL_INTERRUPT_EN();    
    
   NOP_10us_Delay(100);    // 1msec delay

	while (1)
	{
		printf("\n\r Press any key ! For TX data ");
		c=getchar();
		putchar(c);

		if(write_data[0]!=0xA0) 
			for(i = 0; i < USART_MAX_BUFFER_SIZE; i++)
				write_data[i] = 0xA0+i;
		else 
			for(i = 0; i < USART_MAX_BUFFER_SIZE; i++)
				write_data[i] = 0xB0+i;
		
		if(usart_int_polling)
			USART1_USART_SendReceiveDataWithInterrupt(write_data, read_data, USART_MAX_BUFFER_SIZE);
		else 
			USART1_USART_SendReceiveDataWithPolling(write_data, read_data, USART_MAX_BUFFER_SIZE);

		printf("\n\r TX : ");
		for(i=0; i<USART_MAX_BUFFER_SIZE; i++) 
			printf("%02X ", (uint16_t)write_data[i]);
		printf("\n\r RX : ");
		for(i=0; i<USART_MAX_BUFFER_SIZE; i++) 
			printf("%02X ", (uint16_t)read_data[i]);
		
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay

	}
}

/* --------------------------------- End Of File ------------------------------ */

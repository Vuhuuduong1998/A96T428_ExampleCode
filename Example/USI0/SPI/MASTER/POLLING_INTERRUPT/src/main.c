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
#include "a96T428_usi_spi.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"     

uint8_t xdata write_data[USI_MAX_BUFFER_SIZE] _at_ 0x0300;
uint8_t xdata read_data[USI_MAX_BUFFER_SIZE] _at_ 0x0320;

/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
	return c;
}

char getchar()
{
	char c;
	while((USTAT & RXC)!= RXC);		// Wait Data in
	c = UDATA;
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
	
#if A96T418_MODE==0
	printf("\n\ra96T428 USI SPI MASTER TEST!!");
#endif	
#if A96T418_MODE==1
	printf("\n\rA96T418 USI SPI MASTER TEST!!");
#endif	
}

void Main( void )
{
	uint8_t test_mode=0;
	uint8_t i;
	char c;
	uint8_t spi_ss_hw;
	uint8_t spi_pol, spi_phase, spi_msb_lsb, spi_int_polling;
	
	
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
	//test_mode=1;
	
		
	printf("\n\r Press any key ! ");
	printf("\n\r '0' : SPI_CPOL_LOW, SPI_CPHA_LOW ");
	printf("\n\r '1' : SPI_CPOL_LOW, SPI_CPHA_HIGH ");
	printf("\n\r '2' : SPI_CPOL_HIGH, SPI_CPHA_LOW ");
	printf("\n\r '3' : SPI_CPOL_HIGH, SPI_CPHA_HIGH ");
	printf("\n\r other : SPI_CPOL_HIGH, SPI_CPHA_HIGH ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		spi_pol=SPI_CPOL_LOW;
		spi_phase=SPI_CPHA_1EDGE;
		break;
	case '1':
		spi_pol=SPI_CPOL_LOW;
		spi_phase=SPI_CPHA_2EDGE;
		break;
	case '2':
		spi_pol=SPI_CPOL_HIGH;
		spi_phase=SPI_CPHA_1EDGE;
		break;
	case '3':
		spi_pol=SPI_CPOL_HIGH;
		spi_phase=SPI_CPHA_2EDGE;
		break;
	default:
		spi_pol=SPI_CPOL_LOW;
		spi_phase=SPI_CPHA_1EDGE;
		break;
	}
	
	printf("\n\r Press any key ! ");
	printf("\n\r '0' : SPI_LSB ");
	printf("\n\r '1' : SPI_MSB ");
	printf("\n\r other : SPI_LSB ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		spi_msb_lsb=SPI_LSB;
		break;
	case '1':
		spi_msb_lsb=SPI_MSB;
		break;
	default:
		spi_msb_lsb=SPI_LSB;
		break;
	}

	printf("\n\r Press any key ! ");
	printf("\n\r '0' : flag Polling mode ");
	printf("\n\r '1' : Interrupt mode  ");
	printf("\n\r other : lag Polling mode ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		spi_int_polling=0;
		break;
	case '1':
		spi_int_polling=1;
		break;
	default:
		spi_int_polling=0;
		break;
	}

	printf("\n\r Press any key ! ");
	printf("\n\r '0' : SS_HW_CONTROL ");
	printf("\n\r '1' : SS_MANUAL_CONTROL ");
	printf("\n\r other : SS_HW_CONTROL ");
	c=getchar();
	putchar(c);
	switch(c)
	{
	case '0':
		spi_ss_hw=SPI_SS_HW_ENABLE;
		break;
	case '1':
		spi_ss_hw=SPI_SS_HW_DISABLE;
		break;
	default:
		spi_ss_hw=SPI_SS_HW_ENABLE;
		break;
	}
	
	#if (1)
	{
	/* Set Alternative function  MISO0(P10) / MOSI0(P11) */
	Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
	/* Set Alternative function  SCK0(P03) / SS0(P04) */
	Port_SetAlterFunctionpin(PORT0, PIN3, 0x3);
	if(spi_ss_hw==SPI_SS_HW_ENABLE)
		Port_SetAlterFunctionpin(PORT0, PIN4, 0x3);
	}
	#endif
	#if (0)	
	{
	/* Set Alternative function  MISO0(P01) / MOSI0(P02) */
	Port_SetAlterFunctionpin(PORT0, PIN1, 0x3);
	Port_SetAlterFunctionpin(PORT0, PIN2, 0x3);
	/* Set Alternative function  SCK0(P03) / SS0(P04) */
	Port_SetAlterFunctionpin(PORT0, PIN3, 0x3);
	if(spi_ss_hw==SPI_SS_HW_ENABLE)
		Port_SetAlterFunctionpin(PORT0, PIN4, 0x3);
	}
	#endif
	
	USI_SPI_Initial(SPI_CH0, SPI_MASTER_MODE, 100000, spi_msb_lsb, spi_pol, spi_phase, SPI_TX_RX_MODE, spi_ss_hw);
	
    if(spi_int_polling)
		GLOBAL_INTERRUPT_EN();    
    
   NOP_10us_Delay(100);    // 1msec delay

	while (1)
	{
		printf("\n\r Press any key ! for TX data ");
		c=getchar();
		putchar(c);

		if(write_data[0]!=0xA1)
			for(i = 0; i < USI_MAX_BUFFER_SIZE; i++) 
				write_data[i] = 0xA0+i+1;
		else 
			for(i = 0; i < USI_MAX_BUFFER_SIZE; i++) 
				write_data[i] = 0xB0+i+1;
		
		if(spi_int_polling)
			USI_SPI_SendReceiveDataWithInterrupt(SPI_CH0, write_data, read_data, USI_MAX_BUFFER_SIZE);
		else 	
			USI_SPI_SendReceiveDataWithPolling(SPI_CH0, write_data, read_data, USI_MAX_BUFFER_SIZE);
		
		printf("\n\r TX : ");
		for(i=0; i<USI_MAX_BUFFER_SIZE; i++) 
			printf("%02X ", (uint16_t)write_data[i]);
		
		printf("\n\r RX : ");
		for(i=0; i<USI_MAX_BUFFER_SIZE; i++) 
			printf("%02X ", (uint16_t)read_data[i]);
		printf("\n\r");
		
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay

	}
}

/* --------------------------------- End Of File ------------------------------ */

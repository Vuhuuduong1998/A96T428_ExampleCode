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
#include "a96T428_usi_i2c.h"
#include "a96T428_usi_usart.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"     

/* Private Pre-processor Definition & Macro ----------------------------------*/

/* Private Typedef -----------------------------------------------------------*/

/* Private Variable ----------------------------------------------------------*/
uint8_t xdata write_data[I2C_MAX_BUFFER_SIZE] _at_ 0x0300;
uint8_t xdata read_data[I2C_MAX_BUFFER_SIZE] _at_ 0x0320;


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
	while(( USTAT & RXC)!= RXC);		// Wait Data in
	c = UDATA;
	return c;
}

char kbhit_getchar()
{
	char c;
	if(( USTAT & RXC)== RXC)		// Check Data in
		c = UDATA;
	else 
		c=0;
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
	
	printf("\n\ra96T428 USI I2C MASTER TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint16_t i, loopn=0;
	uint8_t transmitNumMsg_tmp;		
	char c;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec

	if(1)
	{
		//WDT Reset ON 
		WDTCR |= (0x3<<6); //WDT_RST_ON
		WDTDR = 125; //2000ms/16ms=125 
		WDTCR |= 0x20; //WDTCL, Clear WDT 
	}
	
	/* Set Alternative function  SCL0(P10) / SDA0(P11) */
	Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
	
	 /* Initialize USI0 I2C master mode*/
	USI_I2C_Initial(I2C_CH0, I2C_SPEED, I2C_SELF_ADDR, I2C_SELF_ADDR2);

    /* Enable INT */
	GLOBAL_INTERRUPT_EN();
	
	loopn=8;
	for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
	{
		write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
	}

	 /* Enable USI0 I2C interrupt */
	USI_I2C_ConfigureInterrupt(I2C_CH0, TRUE);

	printf("\n\r Self Address = %02X ", (unsigned int)I2C_SELF_ADDR);
	printf("\n\r Press any key ! For master mode TX ");
	printf("__ 'r'(repeated mode), otherwise(non-repeated mode) ");
	
    /* Infinite loop */
	while(1)
	{     
		WDTCR |= 0x20; //WDTCL, Clear WDT 
		
		c=kbhit_getchar();
		if(c==0)
			continue;
		
		putchar(c);

		if(c=='r') //repeated mode 
		{
			USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, I2C_MAX_BUFFER_SIZE, read_data, I2C_MAX_BUFFER_SIZE);
			while(i2c_mode[I2C_CH0] != I2C_IDLE);
		}
		else //non-repeated mode 
		{
			USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, I2C_MAX_BUFFER_SIZE, read_data, 0);
			transmitNumMsg_tmp=transmitNumMsg[0];
			NOP_10us_Delay(10000);    // 100msec delay for Slave Receive and printf Timing

			USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, 0, read_data, I2C_MAX_BUFFER_SIZE);
			transmitNumMsg[0]=transmitNumMsg_tmp;
		}
		printf("\n\r TX : ");
		for(i=0; i<transmitNumMsg[0]; i++) 
			printf("%02X ", (uint16_t)write_data[i]);
		printf(" (count=%u)", (uint16_t)transmitNumMsg[0]); //			
		printf("\n\r RX : ");
		for(i=0; i<receiveNumMsg[0]; i++) 
			printf("%02X ", (uint16_t)read_data[i]);
		printf(" (count=%u)", (uint16_t)receiveNumMsg[0]); //			
		printf("\n\r"); 

		loopn++;
		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
		{
			write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
		}
		
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
//		NOP_10us_Delay(50000);    // 0.5sec delay
		
	}


}

void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
	USI_I2C_InterruptHandler(I2C_CH0);
}

/* --------------------------------- End Of File ------------------------------ */

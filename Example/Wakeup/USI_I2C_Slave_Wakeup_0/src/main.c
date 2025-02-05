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

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 USI I2C SLAVE TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t cpacketsize=0, tmpPacketend=0;
	uint8_t tmp;
	uint16_t i;
	
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
		/* Set Alternative function  SCL0(P10) / SDA0(P11) */
		Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
		Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
		
		 /* Initialize USI0 I2C slave mode*/
		USI_I2C_Initial(I2C_CH0, I2C_SPEED, I2C_SELF_ADDR, I2C_SELF_ADDR2);
		
		/* Enable USI0 I2C interrupt */
		USI_I2C_ConfigureInterrupt(I2C_CH0, TRUE);
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);    // 10usec delay

	/* Infinite loop */
	while(1)
	{    
		#if(1) //For basic transaction
		if(i2c_stop[I2C_CH0])
		{
			i2c_stop[I2C_CH0]=0;
			tmp=receiveNumMsg[I2C_CH0];
			receiveNumMsg[I2C_CH0]=0;
			if(tmp)
			{
				printf("\n\rRX: "); //new packet start 
				cpacketsize=0;
				for(i=0; i<tmp;i++)
				{
					printf("%02x ", (uint16_t)read_data[i]); //buffer data print 
					cpacketsize++;
				}
				printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
			}
			tmp=transmitNumMsg[I2C_CH0];
			transmitNumMsg[I2C_CH0]=0;
			if(tmp)
			{
				printf("\n\rTX: "); //new packet start 
				cpacketsize=0;
				for(i=0; i<tmp;i++)
				{
					printf("%02x ", (uint16_t)write_data[i]); //buffer data print 
					cpacketsize++;
				}
				printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
			}				
		}
		#else  //For multiple packet input 
		{
			while(MonitorBuffer0Readp!=MonitorBuffer0Writep)
			{
				if(*MonitorBuffer0Readp&0xF000) //packet_start 
				{
					if((*MonitorBuffer0Readp&0xF000)==0x1000) //Slave RXpacket_start 
						printf("\n\rRX: "); //new packet start 
					else if((*MonitorBuffer0Readp&0xF000)==0x2000) //Slave TX packet_start 
						printf("\n\rTX: "); //new packet start 
					*MonitorBuffer0Readp&=0xFF;
				}					
				else if(*MonitorBuffer0Readp&0x0F00) //packet_end 
				{
					tmpPacketend=1;
					*MonitorBuffer0Readp&=0xFF;
				}
				printf("%02x ", (uint16_t)(*MonitorBuffer0Readp)); //buffer data print 
				cpacketsize++;
				if(tmpPacketend) //packet_end 
				{
					tmpPacketend=0;
					if(cpacketsize)
						printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
					cpacketsize=0;
				}				
				if(((MonitorBuffer0Readp+1)-MonitorBuffer)>=I2C_MONITOR_BUFFER_SIZE)
					MonitorBuffer0Readp=(uint16_t*)MonitorBuffer;
				else 
					MonitorBuffer0Readp++;
			}
			
		}		
		#endif
		
		if(!i2c_mode[I2C_CH0] && !(USI0ST2 & BUSY)) //I2C_IDLE and BUSY
		{
			//STOP MODE
			NOP;
			NOP;
		//	PCON = 0x01;		// IDLE
			PCON = 0x03;			// STOP
			NOP;
			NOP;
			NOP;
			if(i2c_mode[I2C_CH0] || i2c_stop[I2C_CH0])
				printf("\n\r Wakeup OK From I2C ");			
			NOP;
		}
	}

}

void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
	USI_I2C_InterruptHandler(I2C_CH0);
}

/* --------------------------------- End Of File ------------------------------ */

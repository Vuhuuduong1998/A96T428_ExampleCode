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
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/

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
	void USART1_UART_Initial(uint32_t speed, uint8_t data_length, uint8_t stop_bits, uint8_t parity, uint8_t mode);
	
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	//USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	USART1_UART_Initial(38400, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 SRAM TEST !! \n\r");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/

void main(void)
{
	#define xram_base ((uint8_t xdata *)0)
	uint8_t xram_val, xram_val1, xram_val2;
	uint16_t xram_indx;
	uint16_t error_count;	
	uint8_t nloop=0;
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV2);   //HSI16_DIV1
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	
	Port_SetOutputHighpin(PORT2, PIN0);  
    
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	printf("\n\r IRAM TEST : ");
	if(xram_base[2]==0x11)
	{
		printf("\n\r  - 55AA TEST : Passed in iram_test of startup_IRAMtest.asm ");
		printf("\n\r  - AA55 TEST : Passed in iram_test of startup_IRAMtest.asm ");
	}
	else if(xram_base[2]==0x55)
	{
		printf("\n\r  - 55AA TEST : Failed in iram_test of startup_IRAMtest.asm ");
		printf("\n\r  - Error Addr = 0x%02x, Error data = 0x%02x  ", xram_base[0]&0xffff, xram_base[1]&0xffff);
	}
	else if(xram_base[2]==0xAA)
	{
		printf("\n\r  - AA55 TEST : Failed in iram_test of startup_IRAMtest.asm ");
		printf("\n\r  - Error Addr = 0x%02x, Error data = 0x%02x  ", xram_base[0]&0xffff, xram_base[1]&0xffff);
	}
	else
		printf("\n\r  - Check IRAM test ");
		
	while(1)
	{
		printf("\n\n\r XRAM TEST : ");
		
		//XRAM_write 55AA and AA55 test 
		if(nloop++&0x01)
		{
			xram_val1=0xaa;
			xram_val2=0x55;
			printf("\n\n\r AA55 TEST : ");
		}
		else 
		{
			xram_val1=0x55;
			xram_val2=0xaa;
			printf("\n\n\r 55AA TEST : ");
		}
		
		for(xram_indx=0;xram_indx<XRAM_SIZE;xram_indx++)
		{
			if((xram_indx%256)==0) //if start of 256B page 
			{				
				printf("\n\r addr %04x block : writing", xram_indx);
			}
			if((xram_indx&0x10)&&(xram_indx&0x01)) 
				xram_val=xram_val1;
			else if((xram_indx&0x10)&&!(xram_indx&0x01)) 
				xram_val=xram_val2;
			else if(!(xram_indx&0x10)&&(xram_indx&0x01)) 
				xram_val=xram_val2;
			else 
				xram_val=xram_val1;
			xram_base[xram_indx]=xram_val;
			_nop_();
		}
		printf("\n\r Write_count = %u ", xram_indx);
		_nop_();
		
		//XRAM_verify 
		error_count=0;
		for(xram_indx=0;xram_indx<XRAM_SIZE;xram_indx++)
		{
			if((xram_indx%256)==0) //if start of 256B page 
			{
				printf("\n\r addr %04x block : verifying", xram_indx);
			}
			if((xram_indx&0x10)&&(xram_indx&0x01)) 
				xram_val=xram_val1;
			else if((xram_indx&0x10)&&!(xram_indx&0x01)) 
				xram_val=xram_val2;
			else if(!(xram_indx&0x10)&&(xram_indx&0x01)) 
				xram_val=xram_val2;
			else 
				xram_val=xram_val1;
			if(xram_base[xram_indx]!=xram_val)
			{
				error_count++;
				printf("\n\r Error addr %04x: %02x -> %02x ", xram_indx, (uint16_t)xram_val, (uint16_t)xram_base[xram_indx]);
			}
			else 
			{
				if((xram_indx%256)==0) //if start of 256B page 
					printf(" : OK addr %04x: %02x equal %02x ", xram_indx, (uint16_t)xram_val, (uint16_t)xram_base[xram_indx]);
			}
			_nop_();
		}
		printf("\n\r Verify_count = %u bytes", xram_indx);
		printf("\n\r Error_count = %u bytes", error_count);
		if(error_count==0)
			printf("\n\r XRAM Test : Pass ");
		else 
			printf("\n\r XRAM Test : Fail ///////////////////////////////////////////////////////////// ");
		printf("\n\r");
			
		//XRAM display 
		_nop_();
//		for(xram_indx=0;xram_indx<XRAM_SIZE;xram_indx++)
//		{
//			if((xram_indx%32)==0) //if start of 256B page 
//				printf("\n\r%04x: ", xram_indx);
//			xram_val=xram_base[xram_indx];		
//			printf("%02x ", xram_val&0xffff);
//			_nop_();
//		}
		
		//printf("\n\r Press any key for XRAM retest ! ");
		//putchar(getchar());
		if(nloop>=2)
			while(1); //test end 
		
		_nop_();
	}
	
}

/* --------------------------------- End Of File ------------------------------ */

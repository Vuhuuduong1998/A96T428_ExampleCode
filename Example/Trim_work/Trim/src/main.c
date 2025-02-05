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
void TimerCounter_mode_set()
{
	/* Timer1 T1O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT1, PIN2, 0x3);
	
    /* Timer1 initialize @ 16MHz */
	Timer2_Initial(T2_COUNTER_MODE, TIMER2_DIV1);	//1/16us
	Timer2_SetMatchCounter(50-1); //period=160kHz
	/* Timer1 start */
	Timer2_Start();	

    //TIRC trim : P25 pulse with 1MHz 
    OSCCR |= 0x80;
    TEST_AR = 0x19;
    TEST_REGA |= 0x08;
    TEST_REGB |= 0x40;

    //TLDO trim : P10 output 
    //TS_MODE2 = 0x04;    //0x06=4.0V 0x04=2.4V
    TS_MODE2 = 0x06;    //0x06=4.0V 0x04=2.4V

    TS_MODE = 0x18; // TRIM_TEST_MODE
    TS_TEST = 0x08; // LDO_OUT_MON_EN
    TS_CH_SEL_0 = 0x01;   
	
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	#if 0//1 // trim execution 
	DCT_Erase();
	IF0_AREA_Erase();
	LDT0_AREA_Erase();
	LDT1_AREA_Erase();
	P2_ID_WRITE();
	BGREF1V_TRIM(TRIMnWRITE, VDCLOCKDISABLE);
	VDC1P5V_TRIM(TRIMnWRITE);
	
	IRC32M_TRIM(TRIMnWRITE);	
    //Touch Trim
    TIRC16M_TRIM(TRIMnWRITE);
    TLDO_TRIM(TRIMnWRITE);
	
	#endif 

	//PWM monitoring 
	TimerCounter_mode_set(); //check 160kHz @ P12(PWM2O), if not accurate, adjust sCoarsetrim_set, sFinetrim_set in IRC32M_TRIM()
							//check 1MHz @ P12(PWM2O), if not accurate, adjust sCoarsetrim_set, sFinetrim_set in IRC32M_TRIM()
	Display_project();
		
	//Trim value monitoring 
	TRIM_Register_monitor();
	TRIM_TableBuffer_read(0x400);
	Trim_TableBuffer_monitor(0x400);
	
	if(1)
	{
		P2IO|=(1<<1); 
		//printf("======================\r\n");		
		P21=1; 
		BGREF1V_TRIM(MONITORONLY, VDCLOCKDISABLE);
		P21=0; 
		//BGREF1V_TRIM(MONITORONLY, VDCLOCKDEFAULT);
		//ADCCLKdivide=2;
		//BGREF1V_TRIM(MONITORONLY, VDCLOCKDISABLE);

		VDC1P5V_TRIM(MONITORONLY);

		IRC32M_TRIM(MONITORONLY);
		
		TIRC16M_TRIM(MONITORONLY);

		TLDO_TRIM(MONITORONLY);
			
		TRIM_TableBuffer_read(0x400);
		Trim_TableBuffer_monitor(0x400);
//		P21=1; 
//		BGREF1V_ADC_monitor(1);
//		P21=0; 
//		BGREF1V_ADC_monitor(0);
		
		NOP;
	}
	while(1) { 
		NOP_10us_Delay(50000); //0.5s wait
	}
}

/* --------------------------------- End Of File ------------------------------ */

/**
 *******************************************************************************
 * @file        main.c
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
//#include    "Global.h"      //
//#include    "Sysfunc.h"     //
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_bit.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
/* Public Function -----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
	while(!(USTAT & (TXC)));
	USTAT &= ~(TXC);
	return c;
}

void systemClock100ea(void)
{
		if(1)
		{
			P20=1; //1 machine cycle	
			_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); //10 machine cycle
			_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); //10 machine cycle
			_nop_(); _nop_(); _nop_(); //3 machine cycle
			P20=0; //1 machine cycle	
			//total 25 machine cycle ==> 50 system clock 
			//toggle per 50 system clock 
			//output signal period = 100 system clock >> 6.25us, 160KHz @16MHz

			//period=6.25us at 16MHz  // 1/16MHz*100=6.25us 		
			//period=12.5us at 16MHz/2  // 1/16MHz*200=12.5us 		
			//period=25us   at 16MHz/4  // 
			//period=50us   at 16MHz/8  // 
			//period=100us  at 16MHz/16  // 
			//period=200us  at 16MHz/32  // 1/16MHz*16*200=200us 		
			//period=3.125ms at 32KHz  // 1/24.41KHz*100=4096us 		1/31.25KHz*200=6.4ms 	
		}
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
	
	//USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	USART1_UART_Initial(38400, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 ClockChange TEST!!");
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main(void)
{
	uint8_t test_mode=0;
	unsigned char i=0;

    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);
	Display_project();

	//test_mode=0;
	//test_mode=1;
	//test_mode=2;
	test_mode=3;
	
    /* BIT initialize (period 64ms)*/   
	//BIT_Initial(BIT_LSI_4KHZ, BIT_X256); //64ms 
	//BIT_Initial(BIT_LSI_4KHZ, BIT_X64); //16ms
	//BIT_Initial(BIT_DIV4096, BIT_X256); //65ms 
	//BIT_Initial(BIT_DIV1024, BIT_X256); //16ms 
 #if A96T418_MODE==1
	//BIT_Initial(BIT_TEMPSENSOR, BIT_X256);
#endif	
   
	if(test_mode==0)
	{
		printf("\n\r System Clock=16MHz");
		System_Clock_Initial(HSI16_DIV1);
    }
	else if (test_mode==1)
	{	
		//printf("\n\r System Clock=0.5MHz");
		//System_Clock_Initial(HSI16_DIV32);

		//printf("\n\r System Clock=1MHz");
		//System_Clock_Initial(HSI16_DIV16);

		//printf("\n\r System Clock=2MHz");
		//System_Clock_Initial(HSI16_DIV8);
		
		//printf("\n\r System Clock=4MHz");
		//System_Clock_Initial(HSI16_DIV4);

		printf("\n\r System Clock=8MHz");
		System_Clock_Initial(HSI16_DIV2);
	}
	else if (test_mode==2)
	{
 #if A96T418_MODE==1
		printf("\n\r System Clock=128KHz");
		System_Clock_Initial(LSI);
		
		//printf("\n\r System Clock=32KHz");
		//System_Clock_Initial(LSE);
#endif		
#if A96T418_MODE==0
		printf("\n\r System Clock=32KHz");
		System_Clock_Initial(LSI);
#endif		
	}
	else if (test_mode==3)
	{
		printf("\n\r System Clock auto Change test");
		
	}	
    /* Enable INT */
	//GLOBAL_INTERRUPT_EN(); 
	//NOP_10us_Delay(10);
    /* Infinite loop */
	P2IO|=0x03; //P20, P21 output mode 

#if 0	
	while(1)
	{
		_nop_();   //1 machine cycle
		P20=!P20; //1 machine cycle	
		//SJMP 2 machine cycle 
		//total 4 machine cycle ==> 8 system clock 
		//port toggle per 8 systen clock 
		//output signal period = 16 system clock >> 1MHz pulse @16Mhz
	}
#else 	
	if (test_mode<3){ 
		while(1)
		{
			_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); //10 machine cycle
			_nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); //10 machine cycle
			_nop_(); _nop_(); //2 machine cycle
			P20=!P20; //1 machine cycle	
			//SJMP 2 machine cycle 
			//total 25 machine cycle ==> 50 system clock 
			//toggle per 50 system clock 
			//output signal period = 100 system clock >> 6.25us, 160KHz @16MHz

			//period=6.25us at 16MHz  // 1/16MHz*100=6.25us 		
			//period=12.5us at 16MHz/2  // 1/16MHz*200=12.5us 		
			//period=25us   at 16MHz/4  // 
			//period=50us   at 16MHz/8  // 
			//period=100us  at 16MHz/16  // 
			//period=200us  at 16MHz/32  // 1/16MHz*16*200=200us 		
			//period=3.125ms at 32KHz  // 1/24.41KHz*100=4096us 		1/31.25KHz*200=6.4ms 	
		}
	}
	else if (test_mode==3)
	{	
		while(1)
		{	
			P21=!P21; 
			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(HSI16_DIV2);
			systemClock100ea();

			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(HSI16_DIV4);
			systemClock100ea();

			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(HSI16_DIV8);
			systemClock100ea();

			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(HSI16_DIV16);
			systemClock100ea();

			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(HSI16_DIV32);
			systemClock100ea();

			System_Clock_Initial(HSI16_DIV1);
			systemClock100ea();
			System_Clock_Initial(LSI);
			systemClock100ea();
		}
	}		
#endif

}


/* --------------------------------- End Of File ------------------------------ */


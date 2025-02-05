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
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_timer2.h"
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
//char putchar (char c)   /* character to output */
//{
//	while(!(USTAT & (UDRE)));
//	UDATA = c;
//	return c;
//}

//void Display_project(void)
//{
//	//System_Clock_Initial(HSI16_DIV1);         
//    /* System Stabilize Delay */
//	//NOP_10us_Delay(1);         // 10usec
//	
//	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
//	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
//	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
//	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
//	
//	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
//	
//	printf("\n\ra96T428 LED_BLINKY TEST!!");
//}

void GPIO_inputFloating_inputPullup_test(void)
{
	uint8_t c;
	bit fOCDMode=(RSTFR&0x10)?1:0;
	
	//output Low 
	for(c=0;c<8;c++) 
	{
		P0&=~(1<<c);
		P0IO|=(1<<c);
		P1&=~(1<<c);
		P1IO|=(1<<c);
		P2&=~(1<<c);
		P2IO|=(1<<c);
		P3&=~(1<<c);
		P3IO|=(1<<c);
// #if A96T418_MODE==0
// 		P4&=~(1<<c);
// 		P4IO|=(1<<c);
// 		P5&=~(1<<c);
// 		P5IO|=(1<<c);
// #endif		
	}	
	
	//input floating 
	for(c=0;c<8;c++)
	{
		P0PU&=~(1<<c);
		P0IO&=~(1<<c);
		P1PU&=~(1<<c);
		P1IO&=~(1<<c);
		P2PU&=~(1<<c);
		P2IO&=~(1<<c);
		P3PU&=~(1<<c);
		P3IO&=~(1<<c);
// #if A96T418_MODE==0
// 		P4PU&=~(1<<c);
// 		P4IO&=~(1<<c);
// 		P5PU&=~(1<<c);
// 		P5IO&=~(1<<c);
// #endif		
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0x00) ; 
	else 
		while(P0!=0x00) ; 
	while(P1!=0x00) ; 
	while(P2!=0x00) ; 
	while(P3!=0x00) ; 
#if A96T418_MODE==0
	while(P4!=0x00) ; 
	while(P5!=0x00) ; 
#endif	
	_nop_();
	
	//input pullup 
	for(c=0;c<8;c++)
	{
		P0PU|=(1<<c);
		P0IO&=~(1<<c);
		P1PU|=(1<<c);
		P1IO&=~(1<<c);
		P2PU|=(1<<c);
		P2IO&=~(1<<c);
		P3PU|=(1<<c);
		P3IO&=~(1<<c);
// #if A96T418_MODE==0		
// 		P4PU|=(1<<c);
// 		P4IO&=~(1<<c);
// 		P5PU|=(1<<c);
// 		P5IO&=~(1<<c);
// #endif		
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0xF9) ; 
	else 
		while(P0!=0xFF) ; 
	while(P1!=0xFF) ; 
	while(P2!=0xFF) ; 
	while(P3!=0x03) ; 
// #if A96T418_MODE==0		
// 	while(P4!=0x03) ; 
// 	while(P5!=0x03) ; 
// #endif		
}

void GPIO_digital_input_blocking_test(void)
{
	uint8_t c;
	bit fOCDMode=(RSTFR&0x10)?1:0;

#if A96T418_MODE==1		
	//input pullup 
	for(c=0;c<8;c++)
	{
		P0PU|=(1<<c);
		P0IO&=~(1<<c);
		P1PU|=(1<<c);
		P1IO&=~(1<<c);
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0xF9) ; 
	else 
		while(P0!=0xFF) ; 
	while(P1!=0xFF) ; 	
#endif		
	
#if A96T418_MODE==0		
	//output Low 
	for(c=0;c<8;c++) 
	{
		P0&=~(1<<c);
		P0IO|=(1<<c);
		P1&=~(1<<c);
		P1IO|=(1<<c);
		P2&=~(1<<c);
		P2IO|=(1<<c);
		P3&=~(1<<c);
		P3IO|=(1<<c);
		// P4&=~(1<<c);
		// P4IO|=(1<<c);
		// P5&=~(1<<c);
		// P5IO|=(1<<c);
	}	
	//input floating 
	for(c=0;c<8;c++)
	{
		P0PU&=~(1<<c);
		P0IO&=~(1<<c);
		P1PU&=~(1<<c);
		P1IO&=~(1<<c);
		P2PU&=~(1<<c);
		P2IO&=~(1<<c);
		P3PU&=~(1<<c);
		P3IO&=~(1<<c);
		// P4PU&=~(1<<c);
		// P4IO&=~(1<<c);
		// P5PU&=~(1<<c);
		// P5IO&=~(1<<c);
	}		
	if(fOCDMode)
		while((P0&0xF9)!=0x00) ; 
	else 
		while(P0!=0x00) ; 
	while(P1!=0x00) ; 
	while(P2!=0x00) ; 
	while(P3!=0x00) ; 
	// while(P4!=0x00) ; 
	// while(P5!=0x00) ; 
#endif		

	_nop_();
	
	//digital_input_blocking 
#if A96T418_MODE==1	
	P0FSRH=0xaa;//P04/AN0, P05/AN1, P06/AN2, P07/AN3
	P0FSRL=0x80;//P03/AN7
	P1FSRL=0x2a;//P10/AN4, P11/AN5, P12/AN6 
#endif		
#if A96T418_MODE==0		
	P0FSRH=0xaa;
	P0FSRL=0xaa;
	P2FSRH=0xaa;
	P2FSRL=0xaa;
	P3FSR=0x0aa;
	// P4FSRH=0xaa;
	// P4FSRL=0xaa;
	// P5FSRH=0xaa;
	// P5FSRL=0xaa;
#endif		

#if A96T418_MODE==1		
	while((P0&0xF8)!=0x00) ; 
	while((P1&0x07)!=0x00) ; 
#endif
#if A96T418_MODE==0		
	if(fOCDMode)
		while((P0&0xF9)!=0xF9) ; 
	else 
		while(P0!=0xFF) ; 
	while(P1!=0xFF) ; 
	while(P2!=0xFF) ; 
	while(P3!=0x03) ; 
	// while(P4!=0xFF) ; 
	// while(P5!=0xFF) ; 
#endif	
}

void GPIO_outputLow_outputHigh_test(void)
{
	uint8_t c;
	for(c=0;c<8;c++)
	{
		P0&=~(1<<c);
		P0IO|=(1<<c);
		P1&=~(1<<c);
		P1IO|=(1<<c);
		P2&=~(1<<c);
		P2IO|=(1<<c);
		P3&=~(1<<c);
		P3IO|=(1<<c);
// #if A96T418_MODE==0		
// 		P4&=~(1<<c);
// 		P4IO|=(1<<c);
// 		P5&=~(1<<c);
// 		P5IO|=(1<<c);
// #endif		
	}			
	for(c=0;c<8;c++)
	{
		P0|=(1<<c);
		P0IO|=(1<<c);
		P1|=(1<<c);
		P1IO|=(1<<c);
		P2|=(1<<c);
		P2IO|=(1<<c);
		P3|=(1<<c);
		P3IO|=(1<<c);
// #if A96T418_MODE==0		
// 		P4|=(1<<c);
// 		P4IO|=(1<<c);
// 		P5|=(1<<c);
// 		P5IO|=(1<<c);
// #endif		
	}		
}

void GPIO_outputLow_outputHigh_Opendrain_test(void)
{
	uint8_t c;
	for(c=0;c<8;c++)
	{
		P0&=~(1<<c);
		P0OD&=~(1<<c);
		P0PU&=~(1<<c);
		P0IO|=(1<<c);
		P1&=~(1<<c);
		P1OD&=~(1<<c);
		P1PU&=~(1<<c);
		P1IO|=(1<<c);
		P2&=~(1<<c);
		P2OD&=~(1<<c);
		P2PU&=~(1<<c);
		P2IO|=(1<<c);
		P3&=~(1<<c);
		//P3OD&=~(1<<c);
		P3PU&=~(1<<c);
		P3IO|=(1<<c);
// #if A96T418_MODE==0		
// 		P4&=~(1<<c);
// 		P4OD&=~(1<<c);
// 		P4PU&=~(1<<c);
// 		P4IO|=(1<<c);
// 		P5&=~(1<<c);
// 		P5OD&=~(1<<c);
// 		P5PU&=~(1<<c);
// 		P5IO|=(1<<c);
// #endif		
	}			
	for(c=0;c<8;c++)
	{
		P0|=(1<<c);
		P0OD|=(1<<c);
		P0PU|=(1<<c);
		P0IO|=(1<<c);
		P1|=(1<<c);
		P1OD|=(1<<c);
		P1PU|=(1<<c);
		P1IO|=(1<<c);
		P2|=(1<<c);
		P2OD|=(1<<c);
		P2PU|=(1<<c);
		P2IO|=(1<<c);
		P3|=(1<<c);
		//P3OD|=(1<<c);
		P3PU|=(1<<c);
		P3IO|=(1<<c);
// #if A96T418_MODE==0		
// 		P4|=(1<<c);
// 		P4OD|=(1<<c);
// 		P4PU|=(1<<c);
// 		P4IO|=(1<<c);
// 		P5|=(1<<c);
// 		P5OD|=(1<<c);
// 		P5PU|=(1<<c);
// 		P5IO|=(1<<c);
// #endif		
	}		
}

void PPG_mode_set_check()
{
	Timer2_SetPPGPolarity(T2_START_LOW); //default High 
	/* Timer2 PWM2O port (Alternative function) */
	//Port_SetAlterFunctionpin(PORT1, PIN2, 0x3);
	Port_SetAlterFunctionpin(PORT4, PIN4, 0x1);
    /* Enable timer2 match INT */   
	//Timer2_ConfigureInterrupt(TRUE);	
	
		//Period=15200us, Duty=3200us
		Timer2_Initial(T2_PPG_REPEAT_MODE, TIMER2_DIV512);//32us
		Timer2_SetPPGPeriodCounter(500); //15200us
		Timer2_SetPPGDutyCounter(100); //3200us
		Timer2_Start();	
		
		//Timer2_Stop();		
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main()
{
    unsigned char test_mode;
    unsigned char i = 0, j=0;
    /* Disable INT. during peripheral setting */
	//GLOBAL_INTERRUPT_DIS();     
 
    /* Port intialize */
	//Port_Initial();		        
    /* Clock 16Mhz initialize */
	//System_Clock_Initial(HSI16_DIV1);     
    
    /* Enable INT */
	//GLOBAL_INTERRUPT_EN();    

	//test_mode=0;	//inputFloating_inputPullup_test
	//test_mode=1; //outputLow_outputHigh_test
	test_mode=2; //GPIO_outputLow_outputHigh_Opendrain_test
	//test_mode=3; //digital_input_blocking_test
	//test_mode=4;   //debounce test 	
		
	while(1)
	{
		if(test_mode==0)
			GPIO_inputFloating_inputPullup_test();
		else if(test_mode==1)
			GPIO_outputLow_outputHigh_test();
		else if(test_mode==2)
			GPIO_outputLow_outputHigh_Opendrain_test();
		else if(test_mode==3)
			GPIO_digital_input_blocking_test();
		else if(test_mode==4)
		{
			//PPG output(P44) , Port input (P10), Connect each other 
			PPG_mode_set_check(); 
// #if A96T418_MODE==0		
// 			//Send P10 read value to P46, P47  
// 			P4IO|=(1<<7); //P47 putput mode 
// 			P4IO|=(1<<6); //P46 putput mode 
			
// 			//default 600ns //Debounce Control Disable 
// 			DBCONT1|=0x01; //Debounce Control Enable 
// 			//DBCONT3=0;//Fx //820ns  
// 			//DBCONT3=1;//Fx/4  //1850ns 
// 			//DBCONT3=2;//Fx/4  //1280us 
// 			DBCONT3=3;//LSI  //144us 

// 		   /* Infinite loop */
// 			while(1) 
// 			{
// 				// P47=P10;
// 				// P46=P10;
// 			}
// #endif						
		}
	}
	
}

/* --------------------------------- End Of File ------------------------------ */

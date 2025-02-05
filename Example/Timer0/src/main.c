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
#include "a96T428_timer0.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

/* Public Variable -----------------------------------------------------------*/
uint32_t capture_cnt;
uint16_t capture_msec;
uint8_t capture_button_flag;
#define	CAPTUREBUFSIZE	10
uint32_t captureBuf[CAPTUREBUFSIZE] _at_ 0x0000;
uint32_t captureBufIndx=0;

uint8_t test_mode;

/* Public Function -----------------------------------------------------------*/

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
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	//USART1_UART_Initial(38400, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 Timer0 TEST!!");
}

void TimerCounter_mode_set_check()
{
	/* Set T0O output (Alternative function) */
#if A96T418_MODE==1			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x2); //T0O/PWM0O
#endif
#if A96T418_MODE==0			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x1); //T0O/PWM0O
#endif	
	
	#if(1)
	{
	printf("\n\r T0_COUNTER_MODE, TIMER0_DIV2, Period=32us \n\r");
	if(test_mode==0)
	{
		/* Enable Timer0 overflow interrupt */
		Timer0_ConfigureInterrupt(MATCH_INT, TRUE);
		printf(" Int. Mode ");
	}
	else if(test_mode==1)	
		printf(" Polling Mode ");
    /* Timer0 initialize @16MHz*/
	Timer0_Initial(T0_COUNTER_MODE, TIMER0_DIV2); // (2/16)us
	Timer0_SetMatchCounter(256-1);	//period=32us, 32/(2/16)=256
	/* Timer0 Start */
	Timer0_Start();	
	fTimer0_match_int=0;
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
		{
			Timer0_Int_Flag_Polling();
		}
		if(fTimer0_match_int)
		{
			fTimer0_match_int=0;
			printf(" match");
		}
	}
	Timer0_Stop();	
	}
	#endif
	
	#if(1)
	{
	printf("\n\r T0_COUNTER_MODE, TIMER0_DIV128, Period=1280us \n\r");
    /* Timer0 initialize @128us */
	Timer0_Initial(T0_COUNTER_MODE, TIMER0_DIV2048); //128us 
	Timer0_SetMatchCounter(10-1);	//1280us
	/* Timer0 Start */
	Timer0_Start();	
	fTimer0_match_int=0;
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
		{
			Timer0_Int_Flag_Polling();
		}
		if(fTimer0_match_int)
		{
			fTimer0_match_int=0;
			printf(" match");
		}
	}
	Timer0_Stop();	
	}
	#endif
}

void PWM_mode_set_check()
{	
	/* Set PMW output (Alternative function) */
#if A96T418_MODE==1			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x2); //T0O/PWM0O
#endif
#if A96T418_MODE==0			
	Port_SetAlterFunctionpin(PORT2, PIN7, 0x1); //T0O/PWM0O
#endif

	#if(1)
	{	
	printf("\n\r T0_PWM_MODE, TIMER0_DIV32, Period=512us \n\r");
	if(test_mode==2)
	{
		/* Enable Timer0 overflow interrupt */
		Timer0_ConfigureInterrupt(OVERFLOW_INT, TRUE);
		Timer0_ConfigureInterrupt(MATCH_INT, TRUE);
		printf(" Int. Mode ");

	}
	else if(test_mode==3)
	{
		printf(" Polling Mode ");
	}
	/* Timer0 initialize @0.5MHz*/
	Timer0_Initial(T0_PWM_MODE, TIMER0_DIV32); //2us , period=512us=2us*256
	Timer0_SetPWM(50-1); //duty=100us
	/* Timer0 Start */
	Timer0_Start();	
	fTimer0_overflow_int=0;
	fTimer0_match_int=0;
	
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==3)
		{
			Timer0_Int_Flag_Polling();
		}
		if(fTimer0_match_int)
		{
			fTimer0_match_int=0;
			printf(" match");
		}
		if(fTimer0_overflow_int)
		{
			fTimer0_overflow_int=0;
			printf(" over");
		}
	}				
	Timer0_Stop();	
	}
	#endif

	#if(1)
	{
	printf("\n\r T0_PWM_MODE, TIMER0_DIV32, Duty=32768us \n\r");
	if(test_mode==2)
	{
		/* Enable Timer0 overflow interrupt */
		Timer0_ConfigureInterrupt(OVERFLOW_INT, TRUE);
		Timer0_ConfigureInterrupt(MATCH_INT, TRUE);
		printf(" Int. Mode ");

	}
	else if(test_mode==3)
	{
		printf(" Polling Mode ");
	}
	/* Timer0 initialize @0.5MHz*/
	Timer0_Initial(T0_PWM_MODE, TIMER0_DIV2048); //128us , period=32768us=128us*256
	Timer0_SetPWM(10-1); //duty=1280us
	/* Timer0 Start */
	Timer0_Start();	
	fTimer0_overflow_int=0;
	fTimer0_match_int=0;

	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==3)
		{
			Timer0_Int_Flag_Polling();
		}
		if(fTimer0_match_int)
		{
			fTimer0_match_int=0;
			printf(" match");
		}
		if(fTimer0_overflow_int)
		{
			fTimer0_overflow_int=0;
			printf(" over");
		}
	}		
	Timer0_Stop();	
	}
	#endif
	
}

void Capture_mode_set()
{
	/* Timer0 Capture port (EINT10 input) */
	Port_SetInputpin(PORT2, PIN6, PULL_UP);

    NOP_10us_Delay(100);         // 1msec
	
	/* Enable EXT10 INT */  
	Port_ConfigureInterrupt(EXTINT_CH10, BOTH_EDGE);//BOTH_EDGE
	Port_EnableInterrupt(EXTINT_CH10);
	
    /* Timer0 initialize @ 16MHz */
	Timer0_Initial(T0_CAPTURE_MODE, TIMER0_DIV2);	//2/16us
		
	/* Enable timer0 INT */   
	Timer0_ConfigureInterrupt(MATCH_INT,TRUE);
	//Timer0_ConfigureInterrupt(OVERFLOW_INT,TRUE);
	/* Timer0 start */
	Timer0_Start();	

	capture_cnt = 0;
	capture_button_flag = 0;
	
	BITCR|=0x08; //BIT Counter clear
	BITCR&=~0x80; //BIT Flag clear
	
}

void Capture_mode_check()
{
	uint16_t  i= 0;
		if(capture_button_flag < 2) 
		{
			if(BITCR&0x80) { 
				BITCR&=~0x80;
				Port_SetOutputTogglepin(PORT1, PIN3); //connect P13 to P26 for capture  ,, //P13 toggle period=16ms 
				NOP; 					
			}
		}
		else if(capture_button_flag == 2)
		{
			//16MHz count / 16000 => 16ms  //capture value should be 16000/(8/16)=32000
			capture_msec = capture_cnt / (2000);
			printf("\n\r Capture Buffer : "); //(expected 32000)
			for(i=0;i<CAPTUREBUFSIZE;i++)
				printf("[%d]=%8lu ", i, captureBuf[i]);
			printf("Timing(us) : ");
			for(i=0;i<CAPTUREBUFSIZE;i++)
				printf("[%d]=%lu.%lu ", i, captureBuf[i]*100/8/100, captureBuf[i]*100/8%100);
			NOP_10us_Delay(50000);        // 500msec wait
			Capture_mode_set();
			NOP; //for debug
		}
	
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
int Main(void)
{
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
		
	//test_mode=0; //TimerCounter_mode interrupt mode 
	//test_mode=1; //TimerCounter_mode polling mode 
	//test_mode=2; //PWM_mode interrupt mode 
	//test_mode=3; //PWM_mode polling mode 
	test_mode=4; //capture mode 

	if((test_mode==0)||(test_mode==1))
		TimerCounter_mode_set_check();
	else if((test_mode==2)||(test_mode==3))
		PWM_mode_set_check();
	else if((test_mode==4))
		Capture_mode_set();

    /* Enable INT */
	GLOBAL_INTERRUPT_EN();   

    /* Infinite loop */
	while(1)
	{
		if((T0CR&0x30)==T0MS_PWM)
			PWM_mode_set_check();
		else if((T0CR&0x20)==T0MS_CAP)
			Capture_mode_check();
		else if((T0CR&0x30)==T0MS_TC)
			TimerCounter_mode_set_check();
		
	}
}

/**********************************************************************
 * @brief		Timer0 match interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_MAT_Int(void) interrupt T0_MATCH_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);

	if((T0CR&0x20)==T0MS_CAP)
	{
		if(capture_button_flag==1)
		{
			//add overflow value
			capture_cnt += 0x100; 
		}	
	}
	NOP;
	Port_SetOutputTogglepin(PORT2, PIN0);
	fTimer0_match_int=1;
}

/**********************************************************************
 * @brief		Timer0 overflow interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER0_OVER_Int(void) interrupt T0_OVER_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);
	if((T0CR&0x20)==T0MS_CAP)
	{
		while(1);
	}
	Port_SetOutputTogglepin(PORT2, PIN0);
	fTimer0_overflow_int=1;
}

/**********************************************************************
 * @brief		EXT10 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EXTINT10_Int(void) interrupt EINT10_VECT
{
		//test pin toggle
		Port_SetOutputTogglepin(PORT2, PIN0);
		//clear interrupt flag
		if(EIFLAG1&0x02) 
			Port_ClearInterruptStatus(EXTINT_CH10);
	
		if(!capture_button_flag)
		{	
			capture_cnt = 0;
			captureBufIndx = 0;
			capture_button_flag = 1;	
		}
		else if(capture_button_flag==1)
		{
			capture_cnt += Timer0_GetCaptureValue();
			if(captureBufIndx<CAPTUREBUFSIZE) {
				captureBuf[captureBufIndx++]=capture_cnt;
				if(captureBufIndx>=CAPTUREBUFSIZE) {
					/* Disable EXT10 INT */  
					Port_ConfigureInterrupt(EXTINT_CH10, NONE);				
					Port_DisableInterrupt(EXTINT_CH10);
					
					/* Disable timer0 INT */   
					/* Timer0 stop */
					Timer0_Stop();	
					Timer0_ConfigureInterrupt(MATCH_INT,FALSE);
					capture_button_flag=2;
					_nop_();
				}
				else
					capture_cnt=0;
			}
		}			
		Port_SetOutputTogglepin(PORT2, PIN0);

}

/* --------------------------------- End Of File ------------------------------ */

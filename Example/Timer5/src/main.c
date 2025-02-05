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
#include "a96T428_timer5.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Function Prototype ------------------------------------------------*/
/* Public Variable -----------------------------------------------------------*/
uint32_t capture_cnt;
uint16_t capture_msec;
uint8_t capture_button_flag;
#define	CAPTUREBUFSIZE	10
uint32_t captureBuf[CAPTUREBUFSIZE] _at_ 0x0000;
uint32_t captureBufIndx=0;

uint8_t test_mode;

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
	
	printf("\n\ra96T428 TIMER5 TEST!!");
}

/* Public Function -----------------------------------------------------------*/
void TimerCounter_mode_set()
{
	#if(1)
	{
	/* Timer5 T5O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT0, PIN7, 0x3);
	if(test_mode==0)
	{
		/* Enable timer5 match INT */   
		Timer5_ConfigureInterrupt(TRUE);
	}
	printf("\n\r T5_COUNTER_MODE Period=320us \n\r");
	/* Timer5 initialize @ TIMER5_DIV8 */
	Timer5_Initial(T5_COUNTER_MODE, TIMER5_DIV512); //32us
	 /* Timer5 Match Counter (period=320us)  */
	Timer5_SetMatchCounter(10-1); //period=320us 
	/* Timer5 start */
	Timer5_Start();	
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
			Timer5_Int_Flag_Polling();
		if(fTimer5_int)
		{
			printf("match ");
		}
	}
	Timer5_Stop();		
	}
	#endif
	
	#if(1)
	{
	printf("\n\r T5_COUNTER_MODE Period=1ms \n\r");
	/* Timer5 initialize @ TIMER5_HSI_16MHZ */
	Timer5_Initial(T5_COUNTER_MODE, TIMER5_HSI_16MHZ); //1/16us
	 /* Timer5 Match Counter (period=1000us)  */
	Timer5_SetMatchCounter(16000-1); //period=1000us, 1000us/(1/16us)=16000 
	/* Timer5 start */
	Timer5_Start();	
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
			Timer5_Int_Flag_Polling();
		if(fTimer5_int)
		{
			printf("match ");
		}
	}
	Timer5_Stop();		
	}
	#endif 
}

void PPG_mode_set_check()
{
	/* Timer5 T5O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT0, PIN7, 0x3);
    /* Enable timer3 match INT */   
	Timer5_ConfigureInterrupt(TRUE);	
	
		printf("\n\r T5_PPG_REPEAT_MODE Period=10ms, Duty=2.5ms");
		Timer5_Initial(T5_PPG_REPEAT_MODE, TIMER5_DIV8);//0.5us
		Timer5_SetPPGPolarity(T5_START_LOW);
		Timer5_SetPPGPeriodCounter(20000); //10ms
		Timer5_SetPPGDutyCounter(5000); //2.5ms
		Timer5_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);	
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer5_Stop();	

		printf("\n\r T5_PPG_ONESHOT_MODE Period=10ms, Duty=2.5ms");
		Timer5_Initial(T5_PPG_ONESHOT_MODE, TIMER5_DIV8);//0.5us
		Timer5_SetPPGPolarity(T5_START_LOW);
		Timer5_SetPPGPeriodCounter(20000); //10ms
		Timer5_SetPPGDutyCounter(5000); //2.5ms
		Timer5_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);	
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer5_Stop();		
		
		printf("\n\r T5_PPG_REPEAT_MODE Period=10ms, Duty=5ms");
		Timer5_Initial(T5_PPG_REPEAT_MODE, TIMER5_DIV8);//0.5us
		Timer5_SetPPGPolarity(T5_START_LOW);
		Timer5_SetPPGPeriodCounter(20000); //10ms
		Timer5_SetPPGDutyCounter(10000); //5ms
		Timer5_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer5_Stop();	

		printf("\n\r T5_PPG_ONESHOT_MODE Period=10ms, Duty=5ms");
		Timer5_Initial(T5_PPG_ONESHOT_MODE, TIMER5_DIV8);//0.5us
		Timer5_SetPPGPolarity(T5_START_LOW);
		Timer5_SetPPGPeriodCounter(20000); //10ms
		Timer5_SetPPGDutyCounter(10000); //5ms
		Timer5_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);	
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer5_Stop();		
}

void Capture_mode_set()
{
	/* Timer5 Capture port (EINT5 input) */
	Port_SetInputpin(PORT1, PIN1, PULL_UP);
	
	/* Enable EXT5 INT */  
	Port_ConfigureInterrupt(EXTINT_CH5, BOTH_EDGE);//BOTH_EDGE;
	Port_EnableInterrupt(EXTINT_CH5);

    /* Timer5 initialize @ 16MHz */
	Timer5_Initial(T5_CAPTURE_MODE, TIMER5_DIV1);	//1/16us
	/* Enable timer5 INT */   
	Timer5_ConfigureInterrupt(TRUE);
	/* Timer5 start */
	Timer5_Start();	

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
				Port_SetOutputTogglepin(PORT1, PIN3); //connect P13 to P11 for capture  ,, //P13 toggle period=16ms 
				NOP; 					
			}
		}
		else if(capture_button_flag == 2)
		{
			//16MHz count / 16000 => 16ms  //capture value should be 16000/(1/16)=256,000 
			capture_msec = capture_cnt / (16000);
			printf("\n\r Capture Buffer : ");
			for(i=0;i<CAPTUREBUFSIZE;i++)
				printf("[%d]=%8lu ", i, captureBuf[i]);
			printf("Timing(us) : ");
			for(i=0;i<CAPTUREBUFSIZE;i++)
				printf("[%d]=%lu.%lu ", i, captureBuf[i]*100/16/100, captureBuf[i]*100/16%100);
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
void Main(void)
{

	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();	
	
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);
	Display_project();
	
    /* System Stabilize Delay */
    NOP_10us_Delay(1);         // 10usec

    /* Enable INT */
	GLOBAL_INTERRUPT_EN(); 
	
	//test_mode=0; //TimerCounter_mode interupt mode 
	//test_mode=1; //TimerCounter_mode polling mode 
	//test_mode=2; //PPG_mode
	test_mode=3; //Capture_mode

	if((test_mode==0)||(test_mode==1))
		TimerCounter_mode_set();
	else if(test_mode==2)
		PPG_mode_set_check();
	else if(test_mode==3)
		Capture_mode_set();
	
    /* Infinite loop */    
	while(1)
	{
		if(((T5CRH&0x30)==T5MS_PPG_OS) || ((T5CRH&0x30)==T5MS_PPG_RP))
			PPG_mode_set_check();
		else if((T5CRH&0x30)==T5MS_CAP)
			Capture_mode_check();
		else if(((T5CRH&0x30)==T5MS_TC))
			TimerCounter_mode_set();
		//NOP;
	}
}

/**********************************************************************
 * @brief		Timer5,5 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER45_Int(void) interrupt T45_MATCH_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);
	if(T5CRL & T5IFR)
	{
		Timer5_ClearInterruptFlag();
		if((T5CRH&0x30)==T5MS_CAP)
		{
			if(capture_button_flag==1)
			{
				//add overflow value
				capture_cnt += 0x10000; 
			}	
		}
		else if((T5CRH&0x30)==T5MS_TC)
		{
		}
		Port_SetOutputTogglepin(PORT2, PIN0);	
		fTimer5_int=1;
	}
}

/**********************************************************************
 * @brief		EXT4 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EXTINT4_Int(void) interrupt EINT0_5_VECT
{
	if((EIFLAG0 & 0x20) == 0x20)
	{
		//test pin toggle
		Port_SetOutputTogglepin(PORT2, PIN0);
		//clear interrupt flag
		Port_ClearInterruptStatus(EXTINT_CH5);
	}
	else 
		return;
	
		if(!capture_button_flag)
		{	
			capture_cnt = 0;
			captureBufIndx = 0;
			capture_button_flag = 1;	
		}
		else if(capture_button_flag==1)
		{
			capture_cnt += Timer5_GetCaptureValue();
			if(captureBufIndx<CAPTUREBUFSIZE) {
				captureBuf[captureBufIndx++]=capture_cnt;
				if(captureBufIndx>=CAPTUREBUFSIZE) {
					/* Disable EXT5 INT */  
					Port_ConfigureInterrupt(EXTINT_CH5, NONE);				
					Port_DisableInterrupt(EXTINT_CH5);
					
					/* Disable timer5 INT */   
					/* Timer5 stop */
					Timer5_Stop();	
					Timer5_ConfigureInterrupt(FALSE);
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

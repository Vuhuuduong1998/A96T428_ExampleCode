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
#include    "delay.h"     
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_timer1.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  
#include <stdlib.h>

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
/* Private Function Prototype ------------------------------------------------*/

/* Public Variable -----------------------------------------------------------*/
uint32_t capture_cnt;
uint16_t capture_msec;
uint8_t capture_button_flag;
#define	CAPTUREBUFSIZE	20//10
uint32_t captureBuf[CAPTUREBUFSIZE] _at_ 0x0000;
uint32_t captureBufIndx=0;

uint8_t test_mode;

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
	
	//USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	USART1_UART_Initial(115200, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 TIMER1 TEST!! \r\n");
}

/* Public Function -----------------------------------------------------------*/
void TimerCounter_mode_set()
{
	#if(1)
	{
	/* Timer1 T1O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x1);
	
	if(test_mode==0)
	{
		/* Enable timer1 INT */   
		Timer1_ConfigureInterrupt(TRUE);
	}
	
	printf("\n\r T1_COUNTER_MODE, TIMER1_DIV1, Period=1ms \n\r");
    /* Timer1 initialize @ 16MHz */
	Timer1_Initial(T1_COUNTER_MODE, TIMER1_DIV1);	//1/16us
	Timer1_SetMatchCounter(16000-1); //period=1000us, 1000us/(1/16us)=16000
	/* Timer1 start */
	Timer1_Start();	
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
			Timer1_Int_Flag_Polling();
		if(fTimer1_int)
		{
			fTimer1_int=0;
			printf("match ");
		}
	}	
	Timer1_Stop();	
	}
	#endif

	#if(1)
	{
	printf("\n\r T1_COUNTER_MODE, TIMER1_DIV2048, Period=1.280ms \n\r");
    /* Timer1 initialize @ 16MHz/2048 */
	Timer1_Initial(T1_COUNTER_MODE, TIMER1_DIV2048);	//128us
	Timer1_SetMatchCounter(10-1); //period=1280us
	/* Timer1 start */
	Timer1_Start();	
	Port_SetOutputTogglepin(PORT2, PIN1);
	BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
	while(!(WDTCR&0x01))
	{
		if(test_mode==1)
			Timer1_Int_Flag_Polling();
		if(fTimer1_int)
		{
			fTimer1_int=0;
			printf("match ");
		}
	}
	Timer1_Stop();	
	}
	#endif
}

void PPG_mode_set_check()
{
	Timer1_SetPPGPolarity(T1_START_LOW); //T1O default High
	/* Timer1 PWM1O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x1);
    /* Enable timer2 match INT */   
	Timer1_ConfigureInterrupt(TRUE);	
	
		printf("\n\r T1_PPG_REPEAT_MODE Period=1280us, Duty=320uss");
		Timer1_Initial(T1_PPG_REPEAT_MODE, TIMER1_DIV2048);//128us
		Timer1_SetPPGPeriodCounter(10); //1280us
		Timer1_SetPPGDutyCounter(1); //128us
		Timer1_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);
		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer1_Stop();	

		printf("\n\r T1_PPG_ONESHOT_MODE Period=10ms, Duty=2.5ms");
		Timer1_Initial(T1_PPG_ONESHOT_MODE, TIMER1_DIV2048);//128us
		Timer1_SetPPGPeriodCounter(10); //1280us
		Timer1_SetPPGDutyCounter(1); //128us
		Timer1_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);
		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer1_Stop();		

}

void Capture_mode_set()
{
	/* Timer1 Capture port (EINT1 input) */
	Port_SetInputpin(PORT2, PIN5, PULL_UP);
	
	/* Enable EXT11 INT */  
	Port_ConfigureInterrupt(EXTINT_CH11, BOTH_EDGE);//BOTH_EDGE;
	Port_EnableInterrupt(EXTINT_CH11);

    /* Timer1 initialize @ 16MHz */
	Timer1_Initial(T1_CAPTURE_MODE, TIMER1_DIV1);	//1/16us
	/* Enable timer1 INT */   
	Timer1_ConfigureInterrupt(TRUE);
	/* Timer1 start */
	Timer1_Start();	

	capture_cnt = 0;
	capture_button_flag = 0;
	
	BITCR|=0x08; //BIT Counter clear
	BITCR&=~0x80; //BIT Flag clear	
}

void Capture_mode_set_EC_port()
{
	/* Timer1 Capture port (EINT1 input) */
	Port_SetInputpin(PORT2, PIN5, PULL_UP);

	Port_SetInputpin(PORT2, PIN3, PULL_UP); //EC1 
	Port_SetInputpin(PORT2, PIN2, PULL_UP); //port read  
	
	/* Enable EXT11 INT */  
	Port_ConfigureInterrupt(EXTINT_CH11, BOTH_EDGE);//BOTH_EDGE;
	Port_EnableInterrupt(EXTINT_CH11);

    /* Timer1 initialize @ 16MHz */
	//Timer1_Initial(T1_CAPTURE_MODE, TIMER1_DIV1);	//1/16us
	Timer1_Initial(T1_CAPTURE_MODE, TIMER1_EXT_CLK);	//1/16us
	/* Enable timer1 INT */   
	Timer1_ConfigureInterrupt(TRUE);
	
			//while(P22!=1);
			while(P22!=0);
	
	/* Timer1 start */
	Timer1_Start();	

	capture_cnt = 0;
	capture_button_flag = 0;
	
	//BITCR|=0x08; //BIT Counter clear
	//BITCR&=~0x80; //BIT Flag clear
	
}

#define	tNewBufSIZE	0x40
idata u16 tNewBuf[tNewBufSIZE] _at_ 0x40;

void Capture_mode_check_EC_port()
{
	uint16_t  i= 0;
	bit blevel= 0;
	uint16_t  tT1BDR;
	uint16_t  tOld=0, tNew, tDiff;
	u8 tNewBufIndx=0, tt;
	
	if((T1CRL&0xE0)==0xE0) //EC CLK mode 
	{
	while(1)
	{
		T1CRL|=T1CNTR;
		tT1BDR = T1BDR;
		//printf("%x ", tT1BDR);
		tOld=tNew;
		tNew=tT1BDR;
		tNewBuf[tNewBufIndx++]=tNew;
		tNewBufIndx%=tNewBufSIZE;

		if(tOld==0)
			tOld=tNew;
		if(tNew>tOld)
			tDiff=tNew-tOld;
		else if(tNew<tOld)
			tDiff=tNew+65535-tOld;

		if(tDiff>=0x20) 
		{
			printf("%x=%x-%x \n\r ",tDiff, tNew, tOld);
			for(tt=0; tt<tNewBufSIZE; tt++) { 
				
				printf("%x \n\r ", tNewBuf[(tNewBufIndx+tt)%tNewBufSIZE]);
			}
			while(1);//NOP;
		}
	}
	}
}

void Capture_mode_check()
{
	uint16_t  i= 0;
	bit blevel= 0;
	
	if((T1CRL&0xE0)==0xE0) //EC CLK mode 
	{
		Capture_mode_check_EC_port();
		return;
	}
	
		if(capture_button_flag < 2) 
		{
			if(BITCR&0x80) { 
				BITCR&=~0x80;
				Port_SetOutputTogglepin(PORT1, PIN3); //connect P13 to P25 for capture  ,, //P13 toggle period=16ms 
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
    /* Clock initialize @ 16MHz*/
	System_Clock_Initial(HSI16_DIV1);
	Display_project();
	
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);	        // 10usec

	//test_mode=0; //TimerCounter_mode interupt mode 
	//test_mode=1; //TimerCounter_mode polling mode 
	//test_mode=2; //PPG_mode
	//test_mode=3; //Capture_mode
	test_mode=4; //Capture_mode by EC port
	
	if((test_mode==0)||(test_mode==1))
		TimerCounter_mode_set();
	else if(test_mode==2)
		PPG_mode_set_check();
	else if(test_mode==3)
		Capture_mode_set();
	else if(test_mode==4)
		Capture_mode_set_EC_port();

    /* Enable INT */
	GLOBAL_INTERRUPT_EN(); 
    
    /* Infinite loop */
	while(1)
	{
		if(((T1CRH&0x30)==T1MS_PPG_OS) || ((T1CRH&0x30)==T1MS_PPG_RP))
			PPG_mode_set_check();
		else if((T1CRH&0x30)==T1MS_CAP)
			Capture_mode_check();
		else if((T1CRH&0x30)==T1MS_TC)
			TimerCounter_mode_set();
	}
}

/**********************************************************************
 * @brief		Timer1 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER1_Int(void) interrupt T1_MATCH_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);
	if((T1CRH&0x30)==T1MS_CAP)
	{
		if(capture_button_flag==1)
		{
			//add overflow value
			capture_cnt += 0x10000; 
		}	
	}
	else if((T1CRH&0x30)==T1MS_TC)
	{
	}
	Port_SetOutputTogglepin(PORT2, PIN0);
	fTimer1_int=1;
}


/**********************************************************************
 * @brief		EXT11 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EXTINT11_Int(void) interrupt EINT11_VECT
{
		//test pin toggle
		Port_SetOutputTogglepin(PORT2, PIN0);
	
		if(!capture_button_flag)
		{	
			capture_cnt = 0;
			captureBufIndx = 0;
			capture_button_flag = 1;	
		}
		else if(capture_button_flag==1)
		{
			capture_cnt += Timer1_GetCaptureValue();
			if(captureBufIndx<CAPTUREBUFSIZE) {
				captureBuf[captureBufIndx++]=capture_cnt;
				if(captureBufIndx>=CAPTUREBUFSIZE) {
					/* Disable EXT11 INT */  
					Port_ConfigureInterrupt(EXTINT_CH11, NONE);				
					Port_DisableInterrupt(EXTINT_CH11);
					
					/* Disable timer1 INT */   
					/* Timer1 stop */
					Timer1_Stop();	
					Timer1_ConfigureInterrupt(FALSE);
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

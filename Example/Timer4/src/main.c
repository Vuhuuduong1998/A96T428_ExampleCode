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
#include "a96T428_timer3.h"
#include "a96T428_timer4.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Function Prototype ------------------------------------------------*/
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
	
	printf("\n\ra96T428 TIMER4 TEST!!");
}

/* Public Function -----------------------------------------------------------*/
void TimerCounter_mode_set()
{
	#if(1)
	{		
		printf("\n\r TimerCounter_mode_set : Clock Source=T3 A Match \n\r");
		/* Timer3 T3O port (Alternative function) */
		Port_SetAlterFunctionpin(PORT0, PIN5, 0x3);
		/* Enable timer3 match INT */   
		Timer3_ConfigureInterrupt(TRUE);	
		
		/* Timer3 initialize @ 16MHz */
		Timer3_Initial(T3_COUNTER_MODE, TIMER3_DIV1);//1/16us 	
		/* Timer3 Match counter */
		Timer3_SetMatchCounter(512-1); //period=32us, 32us/(1/16us)=512
			
		/* Timer4 T4O port (Alternative function) */
		Port_SetAlterFunctionpin(PORT0, PIN6, 0x3);
		if(test_mode==0) 
		{
			/* Enable timer4 match INT */   
			Timer4_ConfigureInterrupt(TRUE);
		}
		/* Timer4 initialize @ TIMER4_T3_A_MATCH */
		Timer4_Initial(T4_COUNTER_MODE, TIMER4_T3_A_MATCH);
		Timer4_SetMatchCounter(10-1); //period=320us 
		/* Timer4 start */
		Timer4_Start();		
		Timer3_Start();		
		Port_SetOutputTogglepin(PORT2, PIN1);
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01))
		{
			if(test_mode==1)
				Timer4_Int_Flag_Polling();
			if(fTimer4_int)
			{
				fTimer4_int=0;
				printf("match ");
			}	
		}
		Timer4_Stop();		
		Timer3_Stop();		
	}
	#endif
	
	#if(1)
	{
		printf("\n\r TimerCounter_mode_set : Clock Source=TIMER4_DIV512 \n\r");
		/* Timer4 T4O port (Alternative function) */
		Port_SetAlterFunctionpin(PORT0, PIN6, 0x3);
		/* Enable timer4 match INT */   
		Timer4_ConfigureInterrupt(TRUE);
		
		/* Timer4 initialize @ TIMER4_T3_A_MATCH */
		Timer4_Initial(T4_COUNTER_MODE, TIMER4_DIV512);//32us
		Timer4_SetMatchCounter(10-1); //period=320us 
		/* Timer4 start */
		Timer4_Start();		
		Port_SetOutputTogglepin(PORT2, PIN1);
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01))
		{
			if(test_mode==1)
				Timer4_Int_Flag_Polling();
			if(fTimer4_int)
			{
				fTimer4_int=0;
				printf("match ");
			}	
		}
		Timer4_Stop();		
	}
	#endif
}

void PPG_mode_set_check()
{
	/* Timer3 T3O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT0, PIN5, 0x3);
	/* Enable timer3 match INT */   
	Timer3_ConfigureInterrupt(TRUE);	

	Timer4_SetPPGPolarity(T4_START_LOW);	//PWM4O default High
	/* Timer4 T4O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT0, PIN6, 0x3); 
    /* Enable timer2 match INT */   
	Timer4_ConfigureInterrupt(TRUE);	
	
	/* Timer3 initialize @ 16MHz */
	Timer3_Initial(T3_COUNTER_MODE, TIMER3_DIV1);//1/16us 	
	/* Timer3 Match counter count(2000) / 2MHz = 1ms */
	Timer3_SetMatchCounter(512-1); //32us/(1/16us)=512
	
	
		printf("\n\r T4_PPG_REPEAT_MODE, TIMER4_DIV512, Period=320us, Duty=960us");
		Timer4_Initial(T4_PPG_REPEAT_MODE, TIMER4_DIV512);//32us
		Timer4_SetPPGPeriodCounter(30); //960us
		Timer4_SetPPGDutyCounter(10); //320us
		Timer4_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);	
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer4_Stop();	

		printf("\n\r T4_PPG_REPEAT_MODE, TIMER4_DIV512, Period=320us, Duty=960us");
		Timer4_Initial(T4_PPG_ONESHOT_MODE, TIMER4_DIV512);//32us
		Timer4_SetPPGPeriodCounter(30); //960us
		Timer4_SetPPGDutyCounter(10); //320us
		Timer4_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer4_Stop();		

		printf("\n\r T4_PPG_REPEAT_MODE, TIMER4_T3_A_MATCH, Period=320us, Duty=960us");
		Timer4_Initial(T4_PPG_REPEAT_MODE, TIMER4_T3_A_MATCH);//
		Timer4_SetPPGPeriodCounter(30); //960us
		Timer4_SetPPGDutyCounter(10); //320us
		Timer4_Start();	
		/* Timer3 start */
		Timer3_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer4_Stop();	
		Timer3_Stop();	

		printf("\n\r T4_PPG_REPEAT_MODE, TIMER4_T3_A_MATCH, Period=320us, Duty=960us");
		Timer4_Initial(T4_PPG_ONESHOT_MODE, TIMER4_T3_A_MATCH);//
		Timer4_SetPPGPeriodCounter(30); //960us
		Timer4_SetPPGDutyCounter(10); //320us
		Timer4_Start();	
		/* Timer3 start */
		Timer3_Start();	
		Port_SetOutputTogglepin(PORT2, PIN1);		
		BITCR=0x0F; WDTCR=0xA0; WDTDR=9; //640ms
		while(!(WDTCR&0x01));
		Timer4_Stop();		
		Timer3_Stop();	

}

void Capture_mode_set()
{
	
	/* Timer4 Capture port (EINT4 input) */
	Port_SetInputpin(PORT0, PIN7, PULL_UP);
	
	/* Enable EXT4 INT */  
	Port_ConfigureInterrupt(EXTINT_CH4, BOTH_EDGE);//BOTH_EDGE;
	Port_EnableInterrupt(EXTINT_CH4);

    /* Timer4 initialize @ 16MHz */
	Timer4_Initial(T4_CAPTURE_MODE, TIMER4_DIV1);	//1/16us
	/* Enable timer4 INT */   
	Timer4_ConfigureInterrupt(TRUE);
	/* Timer4 start */
	Timer4_Start();	

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
				Port_SetOutputTogglepin(PORT1, PIN3); //connect P13 to P07 for capture  ,, //P13 toggle period=16ms 
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
		if(((T4CRH&0x30)==T4MS_PPG_OS) || ((T4CRH&0x30)==T4MS_PPG_RP))
			PPG_mode_set_check();
		else if((T4CRH&0x30)==T4MS_CAP)
			Capture_mode_check();
		else if((T4CRH&0x30)==T4MS_TC)
			TimerCounter_mode_set();
		
		NOP;
	}
}

/**********************************************************************
 * @brief		Timer4,5 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void TIMER45_Int(void) interrupt T45_MATCH_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);
	Timer4_ClearInterruptFlag();
	if((T4CRH&0x30)==T4MS_CAP)
	{
		if(capture_button_flag==1)
		{
			//add overflow value
			capture_cnt += 0x10000; 
		}	
	}
	else if((T4CRH&0x30)==T4MS_TC)
	{
	}
	Port_SetOutputTogglepin(PORT2, PIN0);
	fTimer4_int=1;
}

void TIMER3_Int(void) interrupt T3_MATCH_VECT
{
	Port_SetOutputTogglepin(PORT2, PIN0);	
	Port_SetOutputTogglepin(PORT2, PIN0);	
}

/**********************************************************************
 * @brief		EXT4 interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void EXTINT4_Int(void) interrupt EINT0_5_VECT
{
	if((EIFLAG0 & 0x10) == 0x10)
	{
		//test pin toggle
		Port_SetOutputTogglepin(PORT2, PIN0);
		//clear interrupt flag
		Port_ClearInterruptStatus(EXTINT_CH4);
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
			capture_cnt += Timer4_GetCaptureValue();
			if(captureBufIndx<CAPTUREBUFSIZE) {
				captureBuf[captureBufIndx++]=capture_cnt;
				if(captureBufIndx>=CAPTUREBUFSIZE) {
					/* Disable EXT4 INT */  
					Port_ConfigureInterrupt(EXTINT_CH4, NONE);				
					Port_DisableInterrupt(EXTINT_CH4);
					
					/* Disable timer4 INT */   
					/* Timer4 stop */
					Timer4_Stop();	
					Timer4_ConfigureInterrupt(FALSE);
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

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
#include "a96T428_adc.h"
#include "a96T428_timer1.h"
#include "a96T428_timer3.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Variable ----------------------------------------------------------*/
uint32_t sum_data = 0;
uint16_t avg_data = 0;
uint16_t temp_data[ADC_MAX_BUFFER_SIZE];

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
	
	printf("\n\ra96T428 ADC TEST!!");
}

/* Public Function -----------------------------------------------------------*/
void T1_TimerCounter_mode_set()
{
	/* Timer1 T1O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT1, PIN1, 0x1);
	/* Enable timer1 INT */   
	//Timer1_ConfigureInterrupt(TRUE);
	
    /* Timer1 initialize @ 16MHz */
	Timer1_Initial(T1_COUNTER_MODE, TIMER1_DIV1);	//1/16us
	Timer1_SetMatchCounter(1600-1); //period=100us, 100us/(1/16us)=1600
	/* Timer1 start */
	Timer1_Start();	
	
}

void T3_TimerCounter_mode_set(void)
{
	Timer3_SetPPGPolarity(T3_START_LOW); //default High 
	/* Timer3 T3O port (Alternative function) */
	Port_SetAlterFunctionpin(PORT0, PIN5, 0x3);
    /* Enable timer3 match INT */   
	//Timer3_ConfigureInterrupt(TRUE);

    /* Timer1 initialize @ 16MHz */
	Timer3_Initial(T3_COUNTER_MODE, TIMER3_DIV1);	//1/16us
	Timer3_SetMatchCounter(1600-1); //period=100us, 100us/(1/16us)=1600
	/* Timer3start */
	Timer3_Start();		
	_nop_();
	
}

void EINT0_mode_set(void)
{
	EIPOL0L	= POL0_BOTH_ADGE;	//EINT0  Polarity selection. both edge	
	EINT0_5_EN();
	_nop_();
}

void EINT0_mode_clear(void)
{
	EIPOL0L	= POL0_NO_INT;	//EINT0  Polarity selection. clear
	_nop_();
}

void EINT1_mode_set(void)
{
	EIPOL0L	= 0xFF;	//EINT1  Polarity selection. both edge	
	EINT0_5_EN();
	_nop_();
}

void EINT1_mode_clear(void)
{
	EIPOL0L	= POL1_NO_INT;	//EINT1  Polarity selection. clear
	_nop_();
}

void EINT2_mode_set(void)
{
	EIPOL0L	= POL2_BOTH_ADGE;	//EINT2  Polarity selection. both edge	
	EINT0_5_EN();
	_nop_();
}

void EINT2_mode_clear(void)
{
	EIPOL0L	= POL2_NO_INT;	//EINT2  Polarity selection. clear
	_nop_();
}

void EINT3_mode_set(void)
{
	EIPOL0L	= POL3_BOTH_ADGE;	//EINT3  Polarity selection. both edge	
	EINT0_5_EN();
	_nop_();
}

void EINT3_mode_clear(void)
{
	EIPOL0L	= POL3_NO_INT;	//EINT3  Polarity selection. clear
	_nop_();
}

void EINT8_mode_set(void)
{
	EIPOL1	= POL8_BOTH_ADGE;	//EINT8  Polarity selection. both edge	
	EINT8_INT_EN();
	_nop_();
}

void EINT8_mode_clear(void)
{
	EIPOL1	= POL8_NO_INT;	//EINT8  Polarity selection. clear
	EINT8_INT_EN();
	_nop_();
}

void ADC_Buffer_Display()
{
	uint8_t i;
	printf(": data[]= ");
	for(i = 0; i < ADC_MAX_BUFFER_SIZE; i++)
		printf(" %04Xh ", temp_data[i]);
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t i;
	uint8_t Triggermode=0;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	
	Display_project();
	
	NOP_10us_Delay(1);         // 10usec

	if(1) // Normal Test (AN0)
	{
		/* Set Alternative function  AN0(P04) */
		Port_SetAlterFunctionpin(PORT0, PIN4, 0x2);
		Port_SetInputpin(PORT0, PIN4, NO_PULL);
			
		/* Selection ADC input channel */
		ADC_SelectChannel(ADC_CH0);
	}
	
	
	if(0) // External Interrupt Test (EINT Pin, AN4)
	{
		/* Set Alternative function  AN4(P23) */
		Port_SetAlterFunctionpin(PORT2, PIN3, 0x2);
		Port_SetInputpin(PORT2, PIN3, NO_PULL);
			
		/* Selection ADC input channel */
		ADC_SelectChannel(ADC_CH4);
		
		Port_SetInputpin(PORT0, PIN3, PULL_UP); // EINT0
		Port_SetInputpin(PORT0, PIN4, PULL_UP); // EINT1
		Port_SetInputpin(PORT0, PIN5, PULL_UP); // EINT2
		Port_SetInputpin(PORT0, PIN6, PULL_UP); // EINT3
		Port_SetInputpin(PORT3, PIN1, PULL_UP); // EINT8
		
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);    // 10usec delay
	
	//Triggermode=0; //Polling 
	//Triggermode=1; //Interrupt 
	//Triggermode=2; // Timer1 Trigger
	//Triggermode=3; // Timer3 Trigger
	//Triggermode=4; // EXTINT0~3 Trigger	
	//Triggermode=5; // EXTINT8 Trigger	
	//Triggermode=6; //All 16 ch ADC 
	Triggermode=7; //ADC CLK change (Sampling Time)
	//Triggermode=8; //ADC Align (MSB, LSB)
	
    /* Infinite loop */
	while(1)
	{          
		/* Initialize ADC */
		if(Triggermode==0) 
		{ 
			ADC_Initial(ADC_CLK_DIV1, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);	//conversion real=us,  ideal=1.3125us 
			printf("\n\r ADC Mode : ADC_CLK_DIV1, ADC_SW_TRIG, Polling ");
			ADC_Buffer_Display();

			ADC_Initial(ADC_CLK_DIV2, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);	//conversion real=us,  ideal=2.625us 
			printf("\n\r ADC Mode : ADC_CLK_DIV2, ADC_SW_TRIG, Polling ");
			ADC_Buffer_Display();

			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);  //conversion real=6.6us,  ideal=5.25us 
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Polling ");
			ADC_Buffer_Display();
			
			ADC_Initial(ADC_CLK_DIV8, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);  //conversion real=11.9us,  ideal=10.5us 
			printf("\n\r ADC Mode : ADC_CLK_DIV8, ADC_SW_TRIG, Polling ");			
			ADC_Buffer_Display();
			
			ADCCR3=30; //Sampling time=32cycle 
			ADC_Initial(ADC_CLK_DIV8, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);  //conversion real=26us, ideal=24.5us 
			printf("\n\r ADC Mode : ADC_CLK_DIV8, ADC_SW_TRIG, Polling ");			
			ADC_Buffer_Display();

//			ADCCR3=31; //Sampling time=33cycle ?????
//			ADC_Initial(ADC_CLK_DIV8, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
//			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);  //conversion real=26.5us, ideal=25us 
//			printf("\n\r ADC Mode : ADC_CLK_DIV8, ADC_SW_TRIG, Polling ");			
//			ADC_Buffer_Display();
		}
		else if(Triggermode==1) 
		{ 
			ADC_Initial(ADC_CLK_DIV1, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV1, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();
			
			ADC_Initial(ADC_CLK_DIV2, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV2, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();
			
			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();
			
			ADC_Initial(ADC_CLK_DIV8, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV8, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();

//			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_MSB);
//			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
//			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Interrupt ");
//			ADC_Buffer_Display();

		}
		else if(Triggermode==2) 
		{ 
			ADC_Initial(ADC_CLK_DIV4, ADC_T1_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			T1_TimerCounter_mode_set();
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			Timer1_Stop();
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_T1_TRIG, Interrupt ");
			ADC_Buffer_Display();
		}
		else if(Triggermode==3) 
		{ 
			ADC_Initial(ADC_CLK_DIV4, ADC_T3_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			T3_TimerCounter_mode_set();
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			Timer3_Stop();
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_T3_TRIG, Interrupt ");
			ADC_Buffer_Display();
		}
		else if(Triggermode==4) 
		{ 
			ADC_Initial(ADC_CLK_DIV4, ADC_EXT0_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			
			//EINT0_mode_set(); //T1O(P11) and EINT0(P03) connection
			EINT1_mode_set(); //T1O(P11) and EINT1(P04) connection
			//EINT2_mode_set(); //T1O(P11) and EINT2(P05) connection
			//EINT3_mode_set(); //T1O(P11) and EINT3(P06) connection
			
			T1_TimerCounter_mode_set();
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			
			//EINT0_mode_clear();
			EINT1_mode_clear();
			//EINT2_mode_clear();
			//EINT3_mode_clear();
			
			Timer1_Stop();
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_EXT0_TRIG, Interrupt ");
			ADC_Buffer_Display();
		}
		else if(Triggermode==5) 
		{ 
			ADC_Initial(ADC_CLK_DIV4, ADC_EXT8_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			EINT8_mode_set(); //T3O(P05) and EINT8(P31) connection
			T3_TimerCounter_mode_set(); //T3O(P05) and EINT8(P31) connection
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			EINT8_mode_clear();
			Timer3_Stop();
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_EXT8_TRIG, Interrupt ");
			ADC_Buffer_Display();
		}
		else if(Triggermode==6) 
		{ 		
			//All CH ADC Read Test 
			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_EXTERNL_REF, ADC_LSB);
			
			/* Set Alternative function  AN0(P04) */
			Port_SetAlterFunctionpin(PORT0, PIN4, 0x2);
			Port_SetInputpin(PORT0, PIN4, NO_PULL);
			ADC_SelectChannel(ADC_CH0);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT0, PIN4, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH0 ");
			ADC_Buffer_Display();
			
			/* Set Alternative function  AN1(P05) */
			Port_SetAlterFunctionpin(PORT0, PIN5, 0x2);
			Port_SetInputpin(PORT0, PIN5, NO_PULL);
			ADC_SelectChannel(ADC_CH1);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT0, PIN5, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH1 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN2(P06) */
			Port_SetAlterFunctionpin(PORT0, PIN6, 0x2);
			Port_SetInputpin(PORT0, PIN6, NO_PULL);
			ADC_SelectChannel(ADC_CH2);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT0, PIN6, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH2 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN3(P07) */
			Port_SetAlterFunctionpin(PORT0, PIN7, 0x2);
			Port_SetInputpin(PORT0, PIN7, NO_PULL);
			ADC_SelectChannel(ADC_CH3);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT0, PIN7, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH3 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN4(P10) */
			Port_SetAlterFunctionpin(PORT1, PIN0, 0x2);
			Port_SetInputpin(PORT1, PIN0, NO_PULL);
			ADC_SelectChannel(ADC_CH4);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT1, PIN0, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH4 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN5(P11) */
			Port_SetAlterFunctionpin(PORT1, PIN1, 0x2);
			Port_SetInputpin(PORT1, PIN1, NO_PULL);
			ADC_SelectChannel(ADC_CH5);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT1, PIN1, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH5 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN6(P12) */
			Port_SetAlterFunctionpin(PORT1, PIN2, 0x2);
			Port_SetInputpin(PORT1, PIN2, NO_PULL);
			ADC_SelectChannel(ADC_CH6);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT1, PIN2, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH6 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN7(P03) */
			Port_SetAlterFunctionpin(PORT0, PIN3, 0x2);
			Port_SetInputpin(PORT0, PIN3, NO_PULL);
			ADC_SelectChannel(ADC_CH7);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT0, PIN3, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH7 ");
			ADC_Buffer_Display();

#if A96T418_MODE==0
			/* Set Alternative function  AN8(P40) */
			Port_SetAlterFunctionpin(PORT4, PIN0, 0x2);
			Port_SetInputpin(PORT4, PIN0, NO_PULL);
			ADC_SelectChannel(ADC_CH8);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT4, PIN0, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH8 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN9(P41) */
			Port_SetAlterFunctionpin(PORT4, PIN1, 0x2);
			Port_SetInputpin(PORT4, PIN1, NO_PULL);
			ADC_SelectChannel(ADC_CH9);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT4, PIN1, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH9 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN10(P42) */
			Port_SetAlterFunctionpin(PORT4, PIN2, 0x2);
			Port_SetInputpin(PORT4, PIN2, NO_PULL);
			ADC_SelectChannel(ADC_CH10);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT4, PIN2, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH10 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN11(P43) */
			Port_SetAlterFunctionpin(PORT4, PIN3, 0x2);
			Port_SetInputpin(PORT4, PIN3, NO_PULL);
			ADC_SelectChannel(ADC_CH11);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT4, PIN3, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH11 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN12(P54) */
			Port_SetAlterFunctionpin(PORT5, PIN4, 0x2);
			Port_SetInputpin(PORT5, PIN4, NO_PULL);
			ADC_SelectChannel(ADC_CH12);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT5, PIN4, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH12 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN13(P55) */
			Port_SetAlterFunctionpin(PORT5, PIN5, 0x2);
			Port_SetInputpin(PORT5, PIN5, NO_PULL);
			ADC_SelectChannel(ADC_CH13);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT5, PIN5, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH13 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN14(P56) */
			Port_SetAlterFunctionpin(PORT5, PIN6, 0x2);
			Port_SetInputpin(PORT5, PIN6, NO_PULL);
			ADC_SelectChannel(ADC_CH14);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT5, PIN6, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH14 ");
			ADC_Buffer_Display();

			/* Set Alternative function  AN15(P57) */
			Port_SetAlterFunctionpin(PORT5, PIN7, 0x2);
			Port_SetInputpin(PORT5, PIN7, NO_PULL);
			ADC_SelectChannel(ADC_CH15);		
			ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
			Port_SetAlterFunctionpin(PORT5, PIN7, 0x0);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, CH15 ");
			ADC_Buffer_Display();
#endif
			printf("\n\r");

		}
		
		else if(Triggermode==7) 
		{ 
			for(i=0; i<34; i++)
			{
				ADCCR3 = i;
				ADC_Initial(ADC_CLK_DIV2, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
				ADC_GetDataWithPolling(temp_data, ADC_MAX_BUFFER_SIZE);
//				printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Interrupt ");
//				ADC_Buffer_Display();
			}
		}
		
		
		else if(Triggermode==8) 
		{ 
			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_LSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();

			ADC_Initial(ADC_CLK_DIV4, ADC_SW_TRIG, ADC_INTERNAL_REF, ADC_MSB);
			ADC_GetDataWithInterrupt(temp_data, ADC_MAX_BUFFER_SIZE);
			printf("\n\r ADC Mode : ADC_CLK_DIV4, ADC_SW_TRIG, Interrupt ");
			ADC_Buffer_Display();
		}

		if(0) 
		{
			sum_data = 0;	
			for(i = 0; i < ADC_MAX_BUFFER_SIZE; i++)
			{
				sum_data += temp_data[i];
			}
			
			printf("\n\r sum_data=%06lXh ", sum_data);
			avg_data = sum_data/16;
			printf("\n\r avg_data=%04Xh ", avg_data);

			for(i = 0; i < ADC_MAX_BUFFER_SIZE; i++)
				printf("\n\r data[%2d]=%04Xh ", (uint16_t)i,temp_data[i]);
			printf("\n\r");
			
			NOP; //for debug
		}
		
		NOP_10us_Delay(50000);    // 0.5sec delay
		NOP_10us_Delay(50000);    // 0.5sec delay
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
}

void TIMER3_Int(void) interrupt T3_MATCH_VECT
{
    Port_SetOutputTogglepin(PORT2, PIN0);			
}

/**
 * @brief		EXT interrupt subroutine
 * @param   	None
 * @return	    None
*/
void INT_EXT() interrupt EINT0_5_VECT
{
    Port_SetOutputTogglepin(PORT2, PIN0);			
	
	// External interrupt
	if((EIFLAG0 & 0x01) == 0x01)
	{
		EIFLAG0 &=~(0x01);	// FLAG0 Clear.
	}
	else if((EIFLAG0 & 0x02) == 0x02)
	{
		EIFLAG0 &=~(0x02);	// FLAG1 Clear.
	}
	else if((EIFLAG0 & 0x04) == 0x04)
	{
		EIFLAG0 &=~(0x04);	// FLAG2 Clear.
	}
	else if((EIFLAG0 & 0x08) == 0x08)
	{
		EIFLAG0 &=~(0x08);	// FLAG3 Clear.
	}
	else if((EIFLAG0 & 0x10) == 0x10)
	{
		EIFLAG0 &=~(0x10);	// FLAG4 Clear.
	}
	else if((EIFLAG0 & 0x20) == 0x20)
	{
		EIFLAG0 &=~(0x20);	// FLAG5 Clear.
	}
}

void INT_EXT8() interrupt EINT8_VECT
{
    Port_SetOutputTogglepin(PORT2, PIN0);			
}

/* --------------------------------- End Of File ------------------------------ */


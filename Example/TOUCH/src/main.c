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
#include <string.h>
#include <stdlib.h>
#include    "Intrins.h"
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_touch.h"
#include "stdio.h"  

/* Private Variable ----------------------------------------------------------*/
uint16_t avg_data = 0;

TOUCHDATA touch_data[TOUCH_CH_COUNT];
TOUCHDATA touch_data_old[TOUCH_CH_COUNT];

u8 TS_val[SFR_TS_MAX];
u16 SUMRAW_val[TOUCH_CH_COUNT*2];
u16 SCO_val[TOUCH_CH_COUNT];

/* Private Function Prototype ------------------------------------------------*/
#define UARTtX	(0x01<<6) //(0x01<<0) //
#define UARTtX_IO	P4IO //P2IO //P1IO //P3IO	
#define UARTtXport	P46 //P20 //P13 //P30 //P02 //P12

data volatile unsigned char TxFlag=0; 
data unsigned char TxClock=0;
data unsigned int txbuffer = 0;

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
void UartTimerSet(void) 
{
	UARTtXport=1;
	if(!(UARTtX_IO&UARTtX))
		UARTtX_IO |= UARTtX;
	if(1) //if((T5CRH!=0x80))
	{ 
		T5CRH = 0x00;
		T5CRL = (0x7<<5); //clock=HSIRC 16MHz 
		//T5ADR=209-1; //208.3333  //76800bps  //13.0208us/(1/16us)
		T5ADR=417-1; //416.6666    //38400bps //26.0416us/(1/16us)
		//T5ADR=1667-1; //1666.6666    //9600bps //104.1666us/(1/16us)

		EA=1;
		IE2 |= (1<<5); 		// Timer5 Match interrupt enable
		
		IP|=(1<<5); //group5 highest 
		IP1|=(1<<5); //group5 highest 
		T5CRH |= 0x01;  // Timer5 clear
		T5CRH |= 0x80;  // Timer5 enable/start
	}	
	
}

char putchar (char c)   /* character to output */
{
	while(TxFlag);
	txbuffer = (0xFE00);
	txbuffer |= ((unsigned int)c<<1);
	TxClock = 0;   
	TxFlag = 1;
	UartTimerSet();
	while(TxFlag);
	return c;
}

void Reg_read_Test(void)
{
	u8 c;
	for(c=0; c<TOUCH_CH_COUNT*2; c++)
		SUMRAW_val[c]=TSRAW(c);
	for(c=0; c<TOUCH_CH_COUNT; c++)
		SCO_val[c]=TS_SCO(c);
	for(c=0; c<SFR_TS_MAX; c++)
		TS_val[c]=TS(c);	
	printf("\n\r");
	printf("Reg. Read Value \n\r");
	printf("TS_CON @F9 = 0x%0x \n\r", TS_CON&0xFFU);
	for(c=0; c<TOUCH_CH_COUNT*2; c++) { 
		printf("SUMRAW_val @[0x%04x]=0x%04x / ", (0x2E00+c), SUMRAW_val[c]);
		if((c%2)==1)
			printf("\n\r");
	}
	if((c%2)==1)
		printf("\n\r");
	for(c=0; c<TOUCH_CH_COUNT; c++) { 
		printf("SCO_val @[0x%04x]=0x%04x / ", (0x2E80+c), SCO_val[c]);
		if((c%2)==1)
			printf("\n\r");
	}
	if((c%2)==1)
		printf("\n\r");
	for(c=0; c<SFR_TS_MAX; c++) {
		printf("TS_val @[0x%04x]=0x%02x / ", (0x2EC1+c), TS_val[c]&0xFFU);
		if((c%2)==1)
			printf("\n\r");
	}
	if((c%2)==1)
		printf("\n\r");	
}

void Reg_write_Test(u16 val)
{
	u8 c;
	if(!val)
		TS_CON=val&0xFFU;
	for(c=0; c<TOUCH_CH_COUNT*2; c++)
		TSRAW(c)=val;
	for(c=0; c<TOUCH_CH_COUNT; c++)
		TS_SCO(c)=val;
	for(c=0; c<SFR_TS_MAX; c++)
		TS(c)=val&0xFFU;	
	if(val)
		TS_CON=val&0xFFU;
}


void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	//S/W UART by UartTimerSet()
	printf("\n\ra96T428 TOUCH TEST!!");
}


/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t test_mode;
	uint8_t tmp;
	uint16_t i;
	uint32_t TouchCHselection;
	uint8_t CH=0;
	bit fFirstSensing=1;

	test_mode=0;	//TOUCH_GetData With Polling mode 
	//test_mode=1;	//TOUCH_GetData With Interrupt mode 
	//test_mode=2;	//SFR_TS_SUM_CNT increase 
	//test_mode=3; //SFR_TS_CLK_CFG increase 
	//test_mode=4; //F1MODE toggle	
	//test_mode=5; //Reg. read/write Test	
	//test_mode=6; //touch single channel change 

	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */

	Display_project();
	
	NOP_10us_Delay(1);         // 10usec

	if(test_mode==5) { 
		printf("\n\r");
		printf("Reg. Initial Value :  ------------------------------- \n\r");
		Reg_read_Test();
		printf("\n\r");
		printf("Reg. Write Value = 0x%04x ------------------------------- \n\r", 0xffffU);
		Reg_write_Test(0xffff);
		Reg_read_Test();
		printf("\n\r");
		printf("Reg. Write Value = 0x%04x ------------------------------- \n\r", 0x0000U);
		Reg_write_Test(0x0000);
		Reg_read_Test();
		while(1) { 
			NOP;
		}
	}
	
	
	if(1)
	{
		 /* Initialize TOUCH */
		TOUCH_Initial();
		
		/* Selection TOUCH input channel */
		#if A96T418_MODE==1
		TouchCHselection=0xFFFFFUL;//20ch all
		TOUCH_SelectChannel(TouchCHselection); 
		#endif	
		#if A96T418_MODE==0
		TouchCHselection=0xFFFFFFFFUL;//32ch all
		TOUCH_SelectChannel(TouchCHselection); 
		#endif	
	}		
	NOP_10us_Delay(1);    // 10usec delay

	/* Enable INT */
	GLOBAL_INTERRUPT_EN();
	
    /* Infinite loop */
	while(1)
	{          
		avg_data = 0;
	
		if(test_mode==0)
		{
			TOUCH_GetDataWithPolling(touch_data);
			printf("\n\n\r Touch polling mode OK, TS_CON=%0xh", saveTS_CON&0xFFU);
		}
		else if(test_mode==1)
		{
			TOUCH_GetDataWithInterrupt(touch_data);
			printf("\n\n\r Touch Int. mode OK, TS_CON=%0xh", saveTS_CON&0xFFU);
		}
		else if(test_mode==2)
		{
			if(!fFirstSensing){
				TS(SFR_TS_SUM_CNT)++; //Touch Raw data should increase 
			}
			TOUCH_GetDataWithPolling(touch_data);
			printf("\n\n\r TS(SFR_TS_SUM_CNT)= %u \n\r", TS(SFR_TS_SUM_CNT)&0xffU);
		}
		else if(test_mode==3)
		{
			if(!fFirstSensing){
				tmp=TS(SFR_TS_CLK_CFG);
				tmp=(tmp&~0x07) | ((tmp+1)&0x07);
				TS(SFR_TS_CLK_CFG)=tmp;
			}
			TOUCH_GetDataWithPolling(touch_data);
			printf("\n\n\r TS(SFR_TS_CLK_CFG)= 0x%02x : ", TS(SFR_TS_CLK_CFG)&0xffU);
			tmp=1;
			i=TS(SFR_TS_CLK_CFG);
			while(i--)
				tmp*=2;
			printf(" CLK divide= %u \n\r", tmp&0xffU); 
		}
		else if(test_mode==4)
		{
			//if(!fFirstSensing){
			TS(SFR_TS_CLK_CFG)^=0x40; //F1MODE toggle
			//}
			printf("\n\n\r SFR_TS_CLK_CFG= 0x%02x : ", TS(SFR_TS_CLK_CFG)&0xffU);
			if(TS(SFR_TS_CLK_CFG)&0x40)
				printf(" 1 Freq Mode \n\r");
			else 
				printf(" 2 Freq Mode \n\r");
				
			TOUCH_GetDataWithPolling(touch_data);
		}
		if(test_mode==6) //touch single channel sensing 
		{
			for(CH=0; CH<TOUCH_CH_COUNT; CH++) { 
				TouchCHselection=1UL<<CH;
				TOUCH_SelectChannel(TouchCHselection); 
				TOUCH_GetDataWithPolling(touch_data);
			}
			printf("\n\n\r Touch Channel change test");
		}
		
		
		
		for(i = 0; i < TOUCH_CH_COUNT; i++)
		{
			avg_data += touch_data[i].sumdata;
		}
		avg_data /= TOUCH_CH_COUNT;
		if(fFirstSensing)
			memcpy(touch_data_old, touch_data, sizeof(touch_data));

		for(i = 0; i < TOUCH_CH_COUNT; i++){
			printf("\n\r touch_data[%2d]=%5lxh (%5xh , %5xh )      : ", i,touch_data[i].sumdata, touch_data[i].F0data, touch_data[i].F1data);
			printf(" diff=%6lxh (%5xh , %5xh ) ", labs(touch_data[i].sumdata-touch_data_old[i].sumdata), abs(touch_data[i].F0data-touch_data_old[i].F0data), abs(touch_data[i].F1data-touch_data_old[i].F1data));
		}
		memcpy(touch_data_old, touch_data, sizeof(touch_data));
		printf("\n\r");
		
		
		//NOP_10us_Delay(50000);    // 0.5sec delay
		NOP; //for debug
		
		NOP_10us_Delay(50000);    // 500msec delay
		fFirstSensing=0;

	}


}

static void Timer45Int(void) interrupt T45_MATCH_VECT  //using 1
{
	T5CRL &= ~0x10; //ClearInterruptFlag	
	if(TxFlag)
	{
		UARTtXport = ((txbuffer >> TxClock)&0x01);
         TxClock++;
         if(TxClock > 9)
         {
            TxFlag = 0;
            T5CRH = 0;         
         }
	}else 
 		;//P21=!P21; P2IO|=(1<<1);//P21 monitor 		  
}


/* --------------------------------- End Of File ------------------------------ */


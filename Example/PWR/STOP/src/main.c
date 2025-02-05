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
#include "intrins.h"
#include "delay.h"
#include "a96T428_bit.h"
#include "a96T428_wdt.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_pwr.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/
uint8_t EINT_int_cnt=0;
bit fEXT_INT=0;
/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
	while(!(USTAT & TXC));		// Wait Data Out
	USTAT &= ~TXC; //avoid Fail at stop entry 
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
	//System_Clock_Initial(HSI16_DIV1);         
    /* System Stabilize Delay */
	//NOP_10us_Delay(1);         // 10usec
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 STOP TEST!!");
}

void Ext_Int_init()
{
	EIPOL0H	=	0
			|(POL5_BOTH_ADGE)		//EINT5 Polarity selection. 
			|(POL4_BOTH_ADGE)		//EINT4  Polarity selection. 
			;
	EIPOL0L	=	0
			|(POL3_BOTH_ADGE)		//EINT3 Polarity selection.
			|(POL2_BOTH_ADGE)		//EINT2 Polarity selection. 
			|(POL1_BOTH_ADGE)		//EINT1 Polarity selection. 
			|(POL0_BOTH_ADGE)		//EINT0  Polarity selection. 
			;
//	EIPOL0H	=	0
//			|(POL5_FAL_ADGE)		//EINT5 Polarity selection. 
//			|(POL4_FAL_ADGE)		//EINT4  Polarity selection. 
//			;
//	EIPOL0L	=	0
//			|(POL3_FAL_ADGE)		//EINT3 Polarity selection.
//			|(POL2_FAL_ADGE)		//EINT2 Polarity selection. 
//			|(POL1_FAL_ADGE)		//EINT1 Polarity selection. 
//			|(POL0_FAL_ADGE)		//EINT0  Polarity selection. 
//			;
	EINT0_5_EN();
}

void External_int_Disable()
{
		EIPOL0H	=	0;
		EIPOL0L	=	0;
}



/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	char c;
	uint8_t test_mode;
	uint8_t VDC_LD_TIME, FAST_CNT_DATA, WK_CLK;
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	
	Port_SetOutputHighpin(PORT2, PIN0);

	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	printf("\n\r Press any key ! ");
	printf("\n\r '0' : test_mode=0 ");
	printf("\n\r '1' : test_mode=1 ");
	printf("\n\r '2' : test_mode=2 ");
	printf("\n\r '3' : test_mode=3 ");
	printf("\n\r '4' : test_mode=4 ");
	printf("\n\r other : test_mode=0 ");
//	c=getchar();
//	putchar(c);
//	switch(c)
//	{
//	case '0':
//		test_mode=0;
//		break;
//	case '1':
//		test_mode=1;
//		break;
//	case '2':
//		test_mode=2;
//		break;
//	case '3':
//		test_mode=3;
//		break;
//	case '4':
//		test_mode=4;
//		break;
//	default:
//		test_mode=0;
//		break;
//	}


  //Mode selection 
	//test_mode=0; //IDLE mode 
	//test_mode=1; //STOP1 mode 
	//test_mode=2; //STOP1 mode, Fast wakeup  
	//test_mode=3; //STOP2 mode
	test_mode=4; //STOP2 mode Fast wakeup 

	printf("\n\r Press any key ! VDC_LD_TIME (0~7) ! ");
	c=getchar();
	putchar(c);
	VDC_LD_TIME=c-'0';
	if(VDC_LD_TIME>7) VDC_LD_TIME=7;

	printf("\n\r Press any key ! FAST_CNT_DATA (0~7) ! ");
	c=getchar();
	putchar(c);
	FAST_CNT_DATA=c-'0';
	if(FAST_CNT_DATA>7) FAST_CNT_DATA=7;
	
	printf("\n\r Press any key ! WK_CLK (0: LSI32KHz, 1;HSI16Mhz/64) ! ");
	c=getchar();
	putchar(c);
	WK_CLK=c-'0';
	if(WK_CLK>1) WK_CLK=1;


    /* Infinite loop */
	while(1)
	{
				
		if(test_mode==0) //IDLE mode 
		{
			Clock_ConfigureOSC(LSIRC, 0, OSC_DIS);
			
			BIT_Initial(BIT_LSI_4KHZ,BIT_X16); //4ms  //Default option 
			/* WDT initialize */

			/*VNDC_Check WDT in free run mode*/

			WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1); // WDT_CLK = 4ms 
			WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 4 * 125 = 500 ms . 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV2); // WDT_CLK = BIT_OVERFLOW * 2 = 4 * 2 = 8ms 
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 8 * 125 = 1000ms 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV8); 
			// WDT_SetDATA(24); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV32); 
			// WDT_SetDATA(2); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 
			
			/*VNDC_Check WDT in reset mode*/

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV1); // WDT_CLK = 4ms
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 4 * 125 = 500 ms .

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV2); // WDT_CLK = BIT_OVERFLOW * 2 = 4 * 2 = 8ms 
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 8 * 125 = 1000ms

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV8); 
			// WDT_SetDATA(24); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV32); 
			// WDT_SetDATA(2); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 

			
			/* Enable WDT INT */
			WDT_ConfigureInterrrupt(WDT_INT_EN);    
			
			while(!(BITCR&0x80)); //BIT Flag waiting for narrow variation of wakeup time 
			
			WDT_Start();		
			Port_SetOutputTogglepin(PORT2, PIN0);
			Port_SetOutputTogglepin(PORT2, PIN1); //P21 LED OFF
			PWR_EnterIdle();	// When MCU go to idle mode, oscillator and peripherals still work, but CPU stops 
			WDT_ConfigureInterrrupt(WDT_INT_DIS);    
			WDT_Stop();
		}
		else if(test_mode==1) //STOP1 mode, for not fast wakeup using 
		{
			/* Before entering stop mode, configure clock for LSI to alway on. */
			Clock_ConfigureOSC(LSIRC, 0, OSC_EN);
			EA=0;
			Ext_Int_init();
			
			/*VNDC_Check WDT in free run mode*/
			BIT_Initial(BIT_LSI_4KHZ,BIT_X16); //4ms  //Default option 
			WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1); // WDT_CLK = 4ms 
			WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 4 * 125 = 500 ms . 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV2); // WDT_CLK = BIT_OVERFLOW * 2 = 4 * 2 = 8ms 
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 8 * 125 = 1000ms 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV8); 
			// WDT_SetDATA(24); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV32); 
			// WDT_SetDATA(2); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 

			// WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 
			
			/*VNDC_Check WDT in reset mode*/

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV1); // WDT_CLK = 4ms
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 4 * 125 = 500 ms .

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV2); // WDT_CLK = BIT_OVERFLOW * 2 = 4 * 2 = 8ms 
			// WDT_SetDATA(124); //WDT_MATCH =  WDT_CLK * (124+1) = 8 * 125 = 1000ms

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV8); 
			// WDT_SetDATA(24); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV32); 
			// WDT_SetDATA(2); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 

			// WDT_Initial(WDT_RST_ON, WDT_BIT_OVER_DIV64); 
			// WDT_SetDATA(1); 
			
			/* Enable WDT INT */
			WDT_ConfigureInterrrupt(WDT_INT_EN);    

			//BITCR&=~0x80;BITCR&=~0x80;
			//while(!(BITCR&0x80)); //BIT Flag waiting for narrow variation of wakeup time 
			
			WDT_Start();		
			//PWR_EnterStop();
			{
				Port_SetOutputHighpin(PORT2, PIN0); //P20 port High
				PCON = PWR_STOP_MODE;				
				/* Must execute NOP */ 
				NOP;
				NOP;
				NOP;
				Port_SetOutputLowpin(PORT2, PIN0); //P20 port Low
			}
			//WDT_ConfigureInterrrupt(WDT_INT_DIS);    
			WDT_Stop();
		}
#if A96T418_MODE==0
		else if(test_mode==2) //STOP1 mode,  for fast wakeup 
		{
			/* Before entering stop mode, configure clock for LSI to alway on. */
			Clock_ConfigureOSC(LSIRC, 0, OSC_EN);

			BIT_Initial(BIT_LSI_32KHZ,BIT_X2); //0.064ms
			//BIT_Initial(BIT_LSI_16KHZ,BIT_X2); //0.128ms
			//BIT_Initial(BIT_LSI_8KHZ,BIT_X2); //0.256ms
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X2); //0.5ms
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X4); //1ms 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X8); //2ms 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X16); //4ms 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X32); //8ms 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X64); //16ms  //Default option 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X128); //32ms 
			//BIT_Initial(BIT_LSI_4KHZ,BIT_X256); //64ms 
			//BIT_Initial(BIT_LSI_8KHZ,BIT_X256); //32ms 
			//BIT_Initial(BIT_LSI_16KHZ,BIT_X256); //16ms 
			//BIT_Initial(BIT_LSI_32KHZ,BIT_X256); //8ms 

			/* WDT initialize */			
			WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV1); //default 0.064ms
			WDT_SetDATA(15-1); //WDT period=0.960msec 
			//WDT_SetDATA(2-1); //WDT period=0.128msec 
			//WDT_SetDATA(4-3); //WDT period=0.512msec 
			//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV2); // 
			//WDT_SetDATA(2-1); //WDT period= 
			//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV4); // 
			//WDT_SetDATA(2-1); //WDT period= 
			//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV64); // 
			//WDT_SetDATA(2-1); //1024*2= 
			//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV32); // 
			//WDT_SetDATA(2-1); //1024*2= 
			//WDT_Initial(WDT_FREE_RUN, WDT_BIT_OVER_DIV8); // 
			//WDT_SetDATA(25-1); //128*25= 

			/* Enable WDT INT */
			WDT_ConfigureInterrrupt(WDT_INT_EN);    
			
			//WKCON=(FAST_WK_EN<<7) | (0x7<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 		//VDC_LD_TIME (7), (WK_CLK_SEL=LSI32K)			
			//WKCON=(FAST_WK_EN<<7) | (WKTIME_7<<1) | ( VDCLDTIME_0<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 				
			WKCON=(FAST_WK_EN<<7) | (WKTIME_7<<1) | ( VDCLDTIME_7<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 				
			//WKCON=(0<<7) | (0x4<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 		//VDC_LD_TIME (4), (WK_CLK_SEL=LSI32K)			
			//WKCON=(0<<7) | (0x3<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (7),(WK_CLK_SEL=HIS16M/64)			
			//WKCON=(0<<7) | (0x5<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (7),(WK_CLK_SEL=HIS16M/64)			
			//WKCON=(FAST_WK_EN<<7) | (0x7<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (7),(WK_CLK_SEL=HIS16M/64)			
			//WKCON=(FAST_WK_EN<<7) | (0x1<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (0),(WK_CLK_SEL=HIS16M/64)	
			
			//NOP_10us_Delay(22);        //220usec waiting for applying WKCON  
			//BITCR&=~0x80;BITCR&=~0x80;
			//while(!(BITCR&0x80)); //BIT Flag waiting for narrow variation of wakeup time 
			
			Ext_Int_init();
			WDT_Start();		
			//PWR_EnterStop();
			{
//				Port_SetOutputHighpin(PORT2, PIN0); //P20 port High
//				PCON = PWR_STOP_MODE;				
//				/* Must execute NOP */ 
//				NOP;
//				NOP;
//				NOP;
//				Port_SetOutputLowpin(PORT2, PIN0); //P20 port Low
			}
			if(!fEXT_INT && !fWDT_int)
			{
				P20=1; //P20 port High
				PCON = PWR_STOP_MODE;				
				/* Must execute NOP */ 
				NOP;
				NOP;
				NOP;
				P20=0;P2IO|=(1<<0);
			}
			External_int_Disable();
			fEXT_INT=0;			
			//WDT_ConfigureInterrrupt(WDT_INT_DIS);    
			WDT_Stop();
			fWDT_int=0;
		}		
#endif		
		else if(test_mode==3) //STOP2 mode , for not fast wakeup 
		{
			Ext_Int_init();
			Clock_ConfigureOSC(LSIRC, 0, OSC_DIS);

			BIT_Initial(BIT_LSI_4KHZ,BIT_X2); //0.5ms  //Default option 
			
			//BITCR&=~0x80;BITCR&=~0x80;
			//while(!(BITCR&0x80)); //BIT Flag waiting for narrow variation of wakeup time 
			P20=1; 	//P20 port toggle
			P21=1;	//P21 port toggle
			
			EINT_int_cnt=0;
			//PWR_EnterStop();
			{
				Port_SetOutputHighpin(PORT2, PIN0); //P20 port High
				PCON = PWR_STOP_MODE;				
				/* Must execute NOP */ 
				NOP;
				NOP;
				NOP;
				Port_SetOutputLowpin(PORT2, PIN0); //P20 port Low
			}
			if(!EINT_int_cnt)
				while(1) 
					printf("EINT_int_cnt=0 ");

			External_int_Disable();
			
		}
#if A96T418_MODE==0
		else if(test_mode==4) //STOP2 mode, fast wakeup 
		{
			Ext_Int_init();
			Clock_ConfigureOSC(LSIRC, 0, OSC_DIS);

			WKCON=(FAST_WK_EN<<7) | (FAST_CNT_DATA<<1) | ( VDC_LD_TIME<<4) | WK_CLK; 				
			
			//WKCON=(FAST_WK_EN<<7) | (WKTIME_7<<1) | ( VDCLDTIME_7<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 				
			//WKCON=(FAST_WK_EN<<7)|(0x7<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 		//VDC_LD_TIME (7), (WK_CLK_SEL=LSI32K)			
			//WKCON=(FAST_WK_EN<<7)|(0x1<<4) | VDCLOCKDETECT_CLKSRC_LSI32KHz; 		//VDC_LD_TIME (0), (WK_CLK_SEL=LSI32K)			
			//WKCON=(FAST_WK_EN<<7)|(0x7<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (7),(WK_CLK_SEL=HIS16M/64)			
			//WKCON=(FAST_WK_EN<<7)|(0x0<<4) | VDCLOCKDETECT_CLKSRC_HSI16MHZ_DIV64; //VDC_LD_TIME (0),(WK_CLK_SEL=HIS16M/64)	
//			if((WKCON&0x80)==(FAST_WK_EN<<7))
//			{
//				WKCON|=(WKTIME_7<<1); 	//(WKTIME_7*2+1) using LSI32K or HIS16M/64			
//				//WKCON|=(WKTIME_0<<1); 	//(WKTIME_0*2+1) using LSI32K or HIS16M/64					
//			}
			NOP_10us_Delay(22);        //220usec waiting for applying WK_CON  
			BITCR&=~0x80;BITCR&=~0x80;
			while(!(BITCR&0x80)); //BIT Flag waiting for narrow variation of wakeup time 
			
			PWR_EnterStop();
			External_int_Disable();
		}
#endif
		
		if(test_mode==0) //IDLE mode 
			printf("\n\r Wakeup OK from IDLE mode. Pass ");
		else if(test_mode==1) //STOP1 mode 
			//printf("\n\r Wakeup OK from STOP1 mode. Pass ");
			;//printf(".");
#if A96T418_MODE==0
		else if(test_mode==2) //STOP1 mode 
			;//printf("\n\r Fast Wakeup OK from STOP1 mode. Fast Wakeup, BITCR=%02xh, WKCON=%02xh ", BITCR&0xffff, WKCON&0xffff); 
#endif		
		else if(test_mode==2) //STOP2 mode 
			//printf("\n\r Wakeup OK from STOP2 mode. Pass ");
			printf(".");
#if A96T418_MODE==0
		else if(test_mode==3) //STOP2 mode 
			//printf("\n\r Fast Wakeup OK from STOP2 mode. Fast Wakeup, BITCR=%02xh, WKCON=%02xh ", BITCR&0xffff, WKCON&0xffff); 
			;//printf("."); 
#endif		
	}
}

/**********************************************************************
 * @brief		Watch Dog Timer overflow interrupt subroutine
 * @param[in]	None
 * @return 		None
 **********************************************************************/
void WDT_OVER_Int(void) interrupt WDT_VECT
{
	fWDT_int=1;
}

/**
 * @brief		BIT interrupt subroutine
 * @param   	None
 * @return	    None
*/
void BIT_Int_Handler(void) interrupt BIT_VECT
{
	fBIT_int=1;
}

void INT0_5_EXT() interrupt EINT0_5_VECT
{
	fEXT_INT=1;
	if(P20) { 
	if(fEXT_INT && !fWDT_int) { 
		P21=!P21;P2IO|=(1<<1);//Port_SetOutputTogglepin(PORT2, PIN1); //P21 port toggle
	}
	EINT_int_cnt++;
	}	
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

/* --------------------------------- End Of File ------------------------------ */

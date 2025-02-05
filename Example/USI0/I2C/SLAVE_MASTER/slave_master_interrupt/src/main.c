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
#include    "Intrins.h"
#include    "delay.h"     //
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usi_i2c.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"     

/* Private Pre-processor Definition & Macro ----------------------------------*/
#define	USING_I2C_INT_VECTOR 	1

/* Private Typedef -----------------------------------------------------------*/

/* Private Variable ----------------------------------------------------------*/
uint8_t xdata write_data[I2C_MAX_BUFFER_SIZE] _at_ 0x0300;
uint8_t xdata read_data[I2C_MAX_BUFFER_SIZE] _at_ 0x0320;


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

char getchar()
{
	char c;
	while(( USTAT & RXC)!= RXC);		// Wait Data in
	c = UDATA;
	return c;
}

char kbhit_getchar()
{
	char c;
	if(( USTAT & RXC)== RXC)		// Check Data in
		c = UDATA;
	else 
		c=0;
	return c;
}

void Display_project(void)
{
	//System_Clock_Initial(HSI16_DIV1);         
	
	/*Set Alernative Function for USART P16(RXD1) / P17(TXD1)*/
	Port_SetInputpin(PORT1, PIN6, TRUE); //input pullup enable
	Port_SetAlterFunctionpin(PORT1, PIN6, 0x3);
	Port_SetAlterFunctionpin(PORT1, PIN7, 0x3);
	
	USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 USI I2C SLAVE TEST!!");
}

static char cEffectiveKey=0;
char P13_keyScan(void)
{
	static unsigned char cOld, cOldKey=1;
	static unsigned char cCount=0;
	unsigned char cNew, keyPressed=0;
	
	if((cNew=P13)==cOld)
		cCount++;
	else 
		cCount=0;
	if(cCount>=250) {
		if((cNew==0)&&(cOldKey==1)) {
			keyPressed=1;
			if(++cEffectiveKey>12) //pressed
				cEffectiveKey=1;
		}
		cOldKey=cNew;		
	}
	cOld=cNew;
	return keyPressed;
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t cpacketsize=0, tmpPacketend=0, tmp, tmp2, tmp3;
	uint16_t i, loopn=8;
	char c=0, d=0;
	uint8_t transmitNumMsg_tmp;
	uint8_t targetAddr, targetTXlength, targetRXlength;
	
    /* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port initialize */
	Port_Initial();		        
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);         
	Display_project();
	
    /* System Stabilize Delay */
	NOP_10us_Delay(1);         // 10usec

	if(1)
	{
//		//WDT Reset ON 
//		WDTCR |= (0x3<<6); //WDT_RST_ON
//		WDTDR = 125; //2000ms/16ms=125 
//		WDTCR |= 0x20; //WDTCL, Clear WDT 
	}
	
	if(1) 
	{
		/* Set Alternative function  SCL0(P10) / SDA0(P11) */
		Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
		Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
		
		 /* Initialize USI0 I2C slave mode*/
		USI_I2C_Initial(I2C_CH0, I2C_SPEED, I2C_SELF_ADDR, I2C_SELF_ADDR2);
		loopn=8;
		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
		{
			write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
		}	
		/* Enable USI0 I2C interrupt */
		USI_I2C_ConfigureInterrupt(I2C_CH0, TRUE);
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	printf("\n\r Self Address  = %02X ", (unsigned int)I2C_SELF_ADDR);
	printf("\n\r Self Address2 = %02X ", (unsigned int)I2C_SELF_ADDR2);
	printf("\n\r Waiting for RX data ! As Slave mode ");
	printf("\n\r Press any key ! For master mode TX ");
	printf("__ 'x'(repeated mode), otherwise(non-repeated mode) ");

	/* Infinite loop */
	while(1)
	{     
		WDTCR |= 0x20; //WDTCL, Clear WDT 
		
		#if A96T418_MODE==1
		d=P13_keyScan();
		#endif 
		
		#if 1
		c=kbhit_getchar();
		if(d)
		{
			if(cEffectiveKey==1) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
			}			
			else if(cEffectiveKey==2) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
			}			
			else if(cEffectiveKey==3) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS+0x40;
			}			
			else if(cEffectiveKey==4) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2+0x40;
			}			
			else if(cEffectiveKey==5) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS3;
			}			
			else if(cEffectiveKey==6) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS4;
			}					
			else if(cEffectiveKey==7) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS3+0x40;
			}			
			else if(cEffectiveKey==8) //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS4+0x40;
			}					
			else if(cEffectiveKey==9) //repeated mode , master TX & RX 
			{
				targetAddr=0xE6;//0xD8;
			}			
			else if(cEffectiveKey==10) //repeated mode , master TX & RX 
			{
				targetAddr=0xEC; //0xD4;
			}					
			else if(cEffectiveKey==11) //repeated mode , master TX & RX 
			{
				targetAddr=0xE2;//0xD8;
			}			
			else if(cEffectiveKey==12) //repeated mode , master TX & RX 
			{
				targetAddr=0xEA; //0xD4;
			}					
			
			USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
			transmitNumMsg_tmp=transmitNumMsg[0];
			NOP_10us_Delay(10000);    // 100msec delay for Slave Receive and printf Timing
			USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
			transmitNumMsg[0]=transmitNumMsg_tmp;
			
			printf("\n\n\r Master Mode data ");
			printf("\n\r TX (to %02X) : ", targetAddr&0xFFFF);
			for(i=0; i<transmitNumMsg[0]; i++) 
				printf("%02X ", (uint16_t)write_data[i]);
			printf(" (count=%u)", (uint16_t)transmitNumMsg[0]); //					
			printf("\n\r RX (to %02X) : ", targetAddr&0xFFFF);
			for(i=0; i<receiveNumMsg[0]; i++) 
				printf("%02X ", (uint16_t)read_data[i]);
			printf(" (count=%u)", (uint16_t)receiveNumMsg[0]); //			
			printf("\n\r"); 

			loopn++;
			for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
			{
				write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
			}

		}
		else if(c)
		{          
			putchar(c);
			printf("\n\n\r Master Mode data ");
			
			if(c=='r') //master RX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				targetTXlength=0; targetRXlength=I2C_MAX_BUFFER_SIZE;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);				
			}
			else if(c=='R') //master RX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				targetTXlength=0; targetRXlength=I2C_MAX_BUFFER_SIZE;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS2, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);				
			}
			else if(c=='t') //master TX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=0;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);				
			}
			else if(c=='T') //master TX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=0;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS2, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);				
			}
			else if(c=='x') //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=I2C_MAX_BUFFER_SIZE;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, I2C_MAX_BUFFER_SIZE, read_data, I2C_MAX_BUFFER_SIZE);
			}
			else if(c=='X') //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=I2C_MAX_BUFFER_SIZE;				
				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS2, write_data, I2C_MAX_BUFFER_SIZE, read_data, I2C_MAX_BUFFER_SIZE);
			}

			else if(c=='G')//non-repeated mode , master TX & RX , General Call
			{
				targetAddr=0x00;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=I2C_MAX_BUFFER_SIZE;				

				USI_I2C_MasterTransferData(I2C_CH0, 0x00, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(10000);    // 100msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, 0x00, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}			

			else if((c>='a')||(c<='z'))//non-repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=I2C_MAX_BUFFER_SIZE;				

				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(5000);    // 50msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}			
			else if((c>='A')||(c<='Z'))//non-repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				targetTXlength=I2C_MAX_BUFFER_SIZE; targetRXlength=I2C_MAX_BUFFER_SIZE;				

				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS2, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(5000);    // 50msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, I2C_DEVICE_ADDRESS2, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}			
			
			printf("\n\r"); 
			if(targetTXlength) { 
				printf("\n\r TX (to %02x): ", targetAddr&0xFFFF);
				for(i=0; i<transmitNumMsg[0]; i++) 
					printf("%02X ", (uint16_t)write_data[i]);
				printf(" (count=%u)", (uint16_t)transmitNumMsg[0]); //					
			}
			if(targetRXlength) { 
				printf("\n\r RX (to %02x): ", targetAddr&0xFFFF);
				for(i=0; i<receiveNumMsg[0]; i++) 
					printf("%02X ", (uint16_t)read_data[i]);
				printf(" (count=%u)", (uint16_t)receiveNumMsg[0]); //			
			}
			tmp3=USI0ST2_Buf_indx;
			USI0ST2_Buf_indx=0;
			if(tmp3) 
				printf("\n\r USI0ST2 (%u): ", tmp3&0xffff);
			for (i = 0; i < tmp3; i++)
				printf(" %02x ", USI0ST2_Buf[i]&0xffff);
			tmp3=USI0CR4_Buf_indx;
			USI0CR4_Buf_indx=0;
			if(tmp3) 
				printf("\n\r USI0CR4 (%u): ", tmp3&0xffff);
			for (i = 0; i < tmp3; i++)
				printf(" %02x ", USI0CR4_Buf[i]&0xffff);
			printf(" <%02x> ", USI0CR4&0xffff);
			
			loopn++;
			for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
			{
				write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
			}
			
		}
#if USING_I2C_INT_VECTOR==0
		//Check Slave mode RX Flag data 
		else if(!((IE1&0x04) && EA) && USI_I2C_Flag_Polling(I2C_CH0)) //(i2c_mode[I2C_CH0] == I2C_BUSY)||
		{
			while(1)
			{
				if(USI_I2C_Flag_Polling(I2C_CH0))
					USI_I2C_InterruptHandler(I2C_CH0);
				if(i2c_stop[I2C_CH0])
					break;
			}
		}
#endif		
		#else  //For multiple packet input 
		{
		}
		#endif

		
		//Check Slave mode RX packet  
		if(i2c_stop[I2C_CH0])
		{
			i2c_stop[I2C_CH0]=0;
			tmp=receiveNumMsg[I2C_CH0];
			receiveNumMsg[I2C_CH0]=0;
			tmp2=transmitNumMsg[I2C_CH0];
			transmitNumMsg[I2C_CH0]=0;
			printf("\n\n\r Slave Mode data ");
			if(tmp)
			{
				printf("\n\rRX: "); //new packet start 
				cpacketsize=0;
				for(i=0; i<tmp;i++)
				{
					printf("%02x ", (uint16_t)read_data[i]); //buffer data print 
					cpacketsize++;
				}
				printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
			}
			if(tmp2)
			{
				printf("\n\rTX: "); //new packet start 
				cpacketsize=0;
				for(i=0; i<tmp2;i++)
				{
					printf("%02x ", (uint16_t)write_data[i]); //buffer data print 
					cpacketsize++;
				}
				printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
			}				
			if(!tmp && !tmp2) { 
				printf("\n\r I2C Stop : Abnormal ! "); //
			}
			tmp3=USI0ST2_Buf_indx;
			USI0ST2_Buf_indx=0;
			if(tmp3) 
				printf("\n\r I2C0SR (%u): ", tmp3&0xffff);
			for (i = 0; i < tmp3; i++)
				printf(" %02x ", USI0ST2_Buf[i]&0xffff);
		}
		
		NOP;
	}

}

#if USING_I2C_INT_VECTOR
void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
	USI_I2C_InterruptHandler(I2C_CH0);
}
#endif

/* --------------------------------- End Of File ------------------------------ */

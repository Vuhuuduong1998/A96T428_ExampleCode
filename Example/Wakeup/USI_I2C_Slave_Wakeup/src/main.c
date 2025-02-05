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
	
	printf("\n\ra96T428 USI I2C SLAVE Wakeup TEST!!");
}

#if MASTER_ONLY==1	
static char cEffectiveKey=0;
char P13_keyScan(void)
{
	static char cOld, cOldKey=1;
	static char cCount=0;
	char cNew, keyPressed=0;
	
	if((cNew=P13)==cOld)
		cCount++;
	else 
		cCount=0;
	if(cCount>=100) {
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
#endif

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void Main( void )
{
	uint8_t cpacketsize=0, tmpPacketend=0;
	uint8_t tmp, tmp2;
	uint16_t i, loopn=8;
	char c=0;
#if MASTER_ONLY==1	
	uint8_t transmitNumMsg_tmp;
	uint8_t targetAddr;
#endif
	
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
		//WDT Reset ON 
		//WDTCR |= (0x3<<6); //WDT_RST_ON
		WDTDR = 187; //3000ms/16ms=187 
		WDTCR |= 0x20; //WDTCL, Clear WDT
		WDTCR |= 0x80;	//WDT Start
		IE3 |= 0x08; //WDT Int. enable 
	}
	
	if(1) 
	{
		/* Set Alternative function  SCL0(P10) / SDA0(P11) */
		Port_SetAlterFunctionpin(PORT1, PIN0, 0x3);
		Port_SetAlterFunctionpin(PORT1, PIN1, 0x3);
		
		 /* Initialize USI0 I2C slave mode*/
		USI_I2C_Initial(I2C_CH0, I2C_SPEED, I2C_SELF_ADDR, I2C_SELF_ADDR2);
		
		/* Enable USI0 I2C interrupt */
		USI_I2C_ConfigureInterrupt(I2C_CH0, TRUE);
		
		loopn=8;
		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
		{
			write_data[i] = (1+i)+loopn*0x10;   //Data, //TX Data high nibble modify
		}			
	}
	
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	NOP_10us_Delay(1);    // 10usec delay

	printf("\n\r Self Address  = %02X ", (unsigned int)I2C_SELF_ADDR);
	printf("\n\r Self Address2 = %02X ", (unsigned int)I2C_SELF_ADDR2);
#if MASTER_ONLY==1	
	printf("\n\r Press any key ! For master mode TX ");
	printf("__ 'r'(repeated mode), otherwise(non-repeated mode) ");
#else 
	printf("\n\r Waiting for RX data ! As Slave mode ");
#endif
	
#if MASTER_ONLY==1	
	/* Infinite loop */
	while(1)
	{     
		WDTCR |= 0x20; //WDTCL, Clear WDT 
		
		c=kbhit_getchar();
		if(P13_keyScan())
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
			else 
				while(1);
			
			USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
			transmitNumMsg_tmp=transmitNumMsg[0];
			NOP_10us_Delay(10000);    // 100msec delay for Slave Receive and printf Timing
			USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
			transmitNumMsg[0]=transmitNumMsg_tmp;
			
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
			
			if(c=='x') //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, read_data, I2C_MAX_BUFFER_SIZE);
			}
			else if(c=='X') //repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, read_data, I2C_MAX_BUFFER_SIZE);
			}
			else if(c=='t') //master TX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);				
			}
			else if(c=='T') //master TX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);				
			}
			else if(c=='r') //master RX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);				
			}
			else if(c=='R') //master RX only 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);				
			}

			else if(c=='G')//non-repeated mode , master TX & RX , General Call
			{
				targetAddr=0x00;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(10000);    // 100msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}			

			else if((c>='a')||(c<='z'))//non-repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(5000);    // 50msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}			
			else if((c>='A')||(c<='Z'))//non-repeated mode , master TX & RX 
			{
				targetAddr=I2C_DEVICE_ADDRESS2;
				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, write_data, I2C_MAX_BUFFER_SIZE, 0, 0);
				transmitNumMsg_tmp=transmitNumMsg[0];

				NOP_10us_Delay(5000);    // 50msec delay for Slave Receive and printf Timing

				USI_I2C_MasterTransferData(I2C_CH0, targetAddr, 0, 0, read_data, I2C_MAX_BUFFER_SIZE);	
				transmitNumMsg[0]=transmitNumMsg_tmp;
			}	
			else 
				printf("\n\r no TX ................... ");
			
			printf("\n\r TX (to %02x): ", targetAddr&0xFFFF);
			for(i=0; i<transmitNumMsg[0]; i++) 
				printf("%02X ", (uint16_t)write_data[i]);
			printf(" (count=%u)", (uint16_t)transmitNumMsg[0]); //					
			printf("\n\r RX (to %02x): ", targetAddr&0xFFFF);
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
		
		if(i2c_ErrNo[I2C_CH0])
		{
			printf("\n\r I2C ErrNo = %02x ............................. ! ", i2c_ErrNo[I2C_CH0]&0xffff ); //
			i2c_ErrNo[I2C_CH0]=0;
		}
		if(USI0ST2 & MLOST)
		{
			 /* Initialize USI0 I2C slave mode*/
			USI_I2C_Initial(I2C_CH0, I2C_SPEED, I2C_SELF_ADDR, I2C_SELF_ADDR2);
			
			/* Enable USI0 I2C interrupt */
			USI_I2C_ConfigureInterrupt(I2C_CH0, TRUE);
		}
		
		NOP;
	}
#else		
	
	/* Infinite loop */
	while(1)
	{    
		if(!(USI0ST2 & BUSY))
			WDTCR |= 0x20; //WDTCL, Clear WDT 
		
		#if(1) //For basic transaction
		
		if(i2c_stop[I2C_CH0])
		{
			i2c_stop[I2C_CH0]=0;
			tmp=receiveNumMsg[I2C_CH0];
			receiveNumMsg[I2C_CH0]=0;
			tmp2=transmitNumMsg[I2C_CH0];
			transmitNumMsg[I2C_CH0]=0;
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
			
		}
		#else  //For multiple packet input 
		{
//			while(MonitorBuffer0Readp!=MonitorBuffer0Writep)
//			{
//				if(*MonitorBuffer0Readp&0xF000) //packet_start 
//				{
//					if((*MonitorBuffer0Readp&0xF000)==0x1000) //Slave RXpacket_start 
//						printf("\n\rRX: "); //new packet start 
//					else if((*MonitorBuffer0Readp&0xF000)==0x2000) //Slave TX packet_start 
//						printf("\n\rTX: "); //new packet start 
//					*MonitorBuffer0Readp&=0xFF;
//				}					
//				else if(*MonitorBuffer0Readp&0x0F00) //packet_end 
//				{
//					tmpPacketend=1;
//					*MonitorBuffer0Readp&=0xFF;
//				}
//				printf("%02x ", (uint16_t)(*MonitorBuffer0Readp)); //buffer data print 
//				cpacketsize++;
//				if(tmpPacketend) //packet_end 
//				{
//					tmpPacketend=0;
//					if(cpacketsize)
//						printf(" (count=%u)", (uint16_t)cpacketsize); //new packet					
//					cpacketsize=0;
//				}				
//				if(((MonitorBuffer0Readp+1)-MonitorBuffer)>=I2C_MONITOR_BUFFER_SIZE)
//					MonitorBuffer0Readp=(uint16_t*)MonitorBuffer;
//				else 
//					MonitorBuffer0Readp++;
//			}
			
		}		
		#endif

		if(i2c_ErrNo[I2C_CH0])
		{
			printf("\n\r I2C ErrNo = %02x ............................. ! ", i2c_ErrNo[I2C_CH0]&0xffff ); //
			i2c_ErrNo[I2C_CH0]=0;
		}
		
		if(!i2c_mode[I2C_CH0] && !(USI0ST2 & BUSY)) //I2C_IDLE and BUSY
		{
			//STOP MODE
			NOP;
			NOP;
			//PCON = 0x01;		// IDLE
			PCON = 0x03;			// STOP
			NOP;
			NOP;
			NOP;
			if(i2c_mode[I2C_CH0] || i2c_stop[I2C_CH0])
				if(!i2c_ErrNo[I2C_CH0]) i2c_ErrNo[I2C_CH0]=0xEE;//printf("\n\r Wakeup OK From I2C ");			
			else 
				;//printf("\n\r Wakeup OK From another ");			
			NOP;
		}
		if(i2c_ErrNo[I2C_CH0])
		{
			printf("\n\r I2C ErrNo = %02x ............................. ! ", i2c_ErrNo[I2C_CH0]&0xffff ); //
			i2c_ErrNo[I2C_CH0]=0;
		}
		
	}
#endif
}

void I2C0_Int_Handler(void) interrupt USI0_I2C_VECT
{
	USI_I2C_InterruptHandler(I2C_CH0);
}

void WDT_Int_Handler(void) interrupt WDT_VECT
{
	printf("\n\r WDT Int. ............................. ! " ); //
	if(i2c_stop[I2C_CH0])
		if(USI0ST2 & BUSY)
			USI0ST2 &= ~BUSY;
}

/* --------------------------------- End Of File ------------------------------ */

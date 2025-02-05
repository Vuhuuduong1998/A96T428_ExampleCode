/**
 *******************************************************************************
 * @file        a96T428_usi_spi.c
 * @author      ABOV R&D Division
 * @brief       USI SPI Communication
 *
 * Copyright 2020 ABOV Semiconductor Co.,Ltd. All rights reserved.
 *
 * This file is licensed under terms that are found in the LICENSE file
 * located at Document directory.
 * If this file is delivered or shared without applicable license terms,
 * the terms of the BSD-3-Clause license shall be applied.
 * Reference: https://opensource.org/licenses/BSD-3-Clause
 ******************************************************************************/


/*******************************************************************************
* Included File
*******************************************************************************/
#include "a96T428_usi_spi.h"
#include    "delay.h"     //
#include "a96T428_usi_usart.h"
#include "a96T428_gpio.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
uint8_t xdata spi_writeBuff0[SPI_MAX_BUFFER_SIZE]_at_ 0x0380;
//uint8_t xdata spi_writeBuff1[SPI_MAX_BUFFER_SIZE]_at_ 0x03A0;
uint8_t spi_writeNum0 = 0;
uint8_t spi_writeNum1 = 0;
uint8_t spi_writeIndx0 = 0;

uint8_t *spi_readBuff0;
uint8_t *spi_readBuff1;
uint8_t spi_readNum0 = 0;
uint8_t spi_readNum1 = 0;
uint8_t spi_readIndx0 = 0;

uint8_t fspi_error_USI0ST1=0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize usi(spi) peripheral
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   mode	This parameter contains the enable of master or slave mode(SPI). 
*
* 					- SPI_SLAVE_MODE		= 0
* 					- SPI_MASTER_MODE 		= 1
* @param   speed			This parameter contains the buadrate of SPI.
* @param   first_bit	This parameter contains the transmitted first as SPI.
*
* 					- SPI_LSB 		= 0
*					- SPI_MSB		= 1
* @param   cpol	This parameter contains the polarity(CPOL) as SPI. 
*
* 					- SPI_CPOL_LOW 	= 0
*					- SPI_CPOL_HIGH = 1
* @param   cpha	This parameter contains the phase(CPHA) as SPI. 
*
* 					- SPI_CPHA_1EDGE = 0
*					- SPI_CPHA_2EDGE = 1
* @param   direction	This parameter contains the enable of transmit or receive mode(SPI). 
*
* 					- SPI_TX_RX_MODE		= 0
* 					- SPI_RX_MODE			= 1
*					- SPI_TX_MODE 			= 2
* @param   ss_mode	This parameter contains the enable of SS function(SPI).
*
* 					- SPI_SS_HW_DISABLE			= 0
*					- SPI_SS_HW_ENABLE 			= 1
* @return		None
*/
void USI_SPI_Initial(uint8_t ch, uint8_t mastermode, uint32_t speed, uint8_t first_bit, uint8_t cpol, uint8_t cpha, uint8_t direction, uint8_t ss_mode)
{
	uint32_t buadrate_val = 0;
	uint8_t temp_reg;
	
	spi_writeNum0 = 0;
	spi_writeNum1 = 0;
	spi_readNum0 = 0;
	spi_readNum1 = 0;
	
	if(ch == SPI_CH0)
	{
		/*calculate baudrate speed*/
		buadrate_val = ((Clock_GetSystemFreq() / 2 * 10 / speed )) ;
	
		buadrate_val = ((buadrate_val + 5) / 10) - 1; //round
		
		temp_reg = USI0CR2;
		if(direction == SPI_RX_MODE)
			temp_reg |= RXE0;	
		else if(direction == SPI_TX_MODE)
			temp_reg |= TXE0;
		else //SPI_TX_RX_MODE
			temp_reg |= (RXE0 | TXE0);
		
		temp_reg |= USI0EN;
		
		USI0ST1	|= SOFTRST;			// USART block reset
		USI0CR1 |= ((0x3 << 6) | (first_bit << 2) | (cpha << 1) | (cpol << 0));  //SPI mode
		USI0CR3 |= ((mastermode << 7) | (ss_mode << 4));
		USI0BD = buadrate_val;
		USI0CR2 = temp_reg;
	}
	
}

void USI_USART_Initial(uint8_t ch, uint8_t mastermode, uint32_t speed, uint8_t cpol, uint8_t direction, uint8_t data_length)
{
	uint8_t parity=0; //USART_PARITY_NO;
	uint8_t stop_bits=0; //USART_STOP_1BIT;

	uint32_t buadrate_val = 0;
	uint8_t temp_reg;
	
	spi_writeNum0 = 0;
	spi_writeNum1 = 0;
	spi_readNum0 = 0;
	spi_readNum1 = 0;
	
	if(ch == SPI_CH0)
	{
		/*calculate baudrate speed*/
		buadrate_val = ((Clock_GetSystemFreq() /2 * 10 / speed ));
	
		buadrate_val = ((buadrate_val + 5) / 10) - 1; //round
		
		temp_reg = USI0CR2;
		if(direction == SPI_RX_MODE)
			temp_reg |= RXE0;	
		else if(direction == SPI_TX_MODE)
			temp_reg |= TXE0;
		else //SPI_TX_RX_MODE
			temp_reg |= (RXE0 | TXE0);
		
		temp_reg |= USI0EN;
		
		USI0ST1	|= SOFTRST;			// USART block reset
		USI0CR1 |= (0x1 << 6);  //USART mode
		USI0CR1 |= ((cpol << 0) | (data_length <<  1));  //USART mode
		USI0CR3 |= (mastermode << 7);
		USI0CR3 |= ((1 << 5));// DISable SCK ree-running
		USI0CR3 |= (stop_bits<< 2);

		USI0BD = buadrate_val;
		USI0CR2 = temp_reg;
	}
	
}

/**
* @brief		Enables or disables the SPI peripheral.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_SPI_Enable(uint8_t ch, uint8_t enable)
{
	if(ch == SPI_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR2 |= USI0EN;
		}
		else
		{
			USI0CR2 &= ~USI0EN;
		}
	}

}

/**
* @brief		Transmit data through the SPI peripheral for polling mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USI_SPI_SendDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t count)
{
	volatile uint8_t i;
	
	if(ch == SPI_CH0)
	{
		if((USI0ST1 & TXC) == TXC)
			USI0ST1 &= ~TXC; // TXC clear
		for(i = 0; i < count ; i++)
		{
			while(!(USI0ST1 & (UDRE)));
			USI0DR = send_data[i];
		}
		while((USI0ST1 & TXC) != TXC);		// Wait Data out
		USI0ST1 &= ~TXC; // TXC clear
	}

}

void USI_SPI_SendReceiveDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
	
	if(ch == SPI_CH0)
	{
		if((USI0ST1 & RXC)== RXC) 
			i=USI0DR; //buffer emptying for avoiding overrun	//RXC auto clear 
		if((USI0ST1 & TXC) == TXC)
			USI0ST1 &= ~TXC; // TXC clear
		
		if(!(USI0CR3&USI0SSEN)) //if SS_Manual
		{
			Port_SetOutputLowpin(PORT0, PIN4);
		}
		
		for(i = 0; i < count ; i++)
		{
			if(!(USI0CR3&USI0SSEN)) //if SS_Manual
			{
				Port_SetOutputLowpin(PORT0, PIN4);
			}			
			while(!(USI0ST1 & (UDRE)));
			USI0DR = send_data[i];
			while(( USI0ST1 & RXC)!= RXC);		// Wait Data in
			while((USI0ST1 & TXC) != TXC);		// Wait Data out
			USI0ST1 &= ~TXC; // TXC clear
			receive_data[i] = USI0DR;
			if(!(USI0CR3&USI0SSEN)) //if SS_Manual
			{
				Port_SetOutputHighpin(PORT0, PIN4);
			}			
			NOP_10us_Delay(10);    // 100usec delay for ISR process at slave 
		}
		
		if(!(USI0CR3&USI0SSEN)) //if SS_Manual
		{
			Port_SetOutputHighpin(PORT0, PIN4);
		}
		
	}

}

void USI_USART_SendReceiveDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USI_SPI_SendReceiveDataWithPolling(ch, send_data, receive_data, count);	
}

void USI_SPI_SendReceiveDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	uint8_t i;
	
	if(ch == SPI_CH0)
	{
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, FALSE);
		USI_SPI_ConfigureInterrupt(ch, SPI_TX_COMPLETE_INT, FALSE);
		if((USI0ST1 & TXC) == TXC)
			USI0ST1 &= ~TXC;	//TXC clear 
		if((USI0ST1 & RXC)== RXC) 
			i=USI0DR; //buffer emptying for avoiding overrun	//RXC auto clear 

		spi_readIndx0 = 0;
		spi_readNum0 = count;
		spi_readBuff0 = (uint8_t*)receive_data; 
		
		spi_writeIndx0 = 0;
		spi_writeNum0 = count;

		for(i = 0; i < count ; i++)
		{
			spi_writeBuff0[i] = send_data[i];
		}
		
		USI_SPI_ConfigureInterrupt(ch, SPI_TX_COMPLETE_INT, TRUE);
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, TRUE);
		
		while(!(USI0ST1 & (UDRE)));
		if(!(USI0CR3&USI0SSEN)) //if SS_Manual
			Port_SetOutputLowpin(PORT0, PIN4);		
		USI0DR = spi_writeBuff0[spi_writeIndx0];
		
		while(spi_writeIndx0 < spi_writeNum0) ; //wait for complate 
		NOP;
		while(spi_readIndx0 < spi_readNum0);	//wait for complate 
		NOP;		
		
		if(!(USI0CR3&USI0SSEN)) //if SS_Manual
			Port_SetOutputHighpin(PORT0, PIN4);
		
	}
}

void USI_USART_SendReceiveDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USI_SPI_SendReceiveDataWithInterrupt(ch, send_data, receive_data, count);
}

void USI_SPI_SlaveWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
	
	if(ch == SPI_CH0)
	{		
		USI_SPI_ConfigureInterrupt(ch, SPI_TX_COMPLETE_INT, FALSE);
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, FALSE);
		if((USI0ST1 & RXC)== RXC) 
			i=USI0DR; //buffer emptying for avoiding overrun	//RXC auto clear 
		if(USI0ST1 & TXC)
			USI0ST1 &= ~TXC; // TXC clear

		spi_readIndx0 = 0;
		spi_readNum0 = count;
		spi_readBuff0 = (uint8_t*)receive_data; 

		spi_writeIndx0 = 0;
		spi_writeNum0 = count;
		for(i = 0; i < count ; i++)
		{
			spi_writeBuff0[i] = send_data[i];
		}
		
		USI_SPI_ConfigureInterrupt(ch, SPI_TX_COMPLETE_INT, TRUE);
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, TRUE);
		
		while(!(USI0ST1 & (UDRE)));
		USI0DR = spi_writeBuff0[spi_writeIndx0];
		
		while(spi_writeIndx0 < spi_writeNum0) ; //wait for complate 
		NOP;
		while(spi_readIndx0 < spi_readNum0);	//wait for complate 
		NOP;		
	}

}

void USI_USART_SlaveWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USI_SPI_SlaveWithInterrupt(ch, send_data, receive_data, count);	
}

void USI_SPI_SlaveWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{	
	volatile uint8_t i, temp;
	
	fspi_error_USI0ST1=0;
	if(ch == SPI_CH0)
	{
		USI_SPI_ConfigureInterrupt(ch, SPI_TX_COMPLETE_INT, FALSE);
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, FALSE);
		temp=USI0ST1;
		if(USI0ST1 & RXC)
			temp=USI0DR; //buffer emptying for avoiding overrun	//RXC auto clear 
		if(USI0ST1 & TXC)
			USI0ST1 &= ~TXC; // TXC clear

		spi_readIndx0 = 0;
		spi_readNum0 = count;
		spi_readBuff0 = (uint8_t*)receive_data; 

		spi_writeIndx0 = 0;
		spi_writeNum0 = count;
		for(i = 0; i < count ; i++)
		{
			spi_writeBuff0[i] = send_data[i];
		}
		while(!(USI0ST1 & (UDRE)));
		//return data
		USI0DR = send_data[spi_writeIndx0];
			
		while(1) 
		{
			while(!(USI0ST1&RXC)); // Wait Data in
			while(!(USI0ST1&TXC)); // Wait Data out
			USI0ST1 &= ~TXC; // TXC clear
//		if (USI0ST1 & DOR )
//		{
//			//DATA OVERUN handling(user)
//			NOP;
//		}						
			temp = USI0DR;
			receive_data[spi_readIndx0++] = temp;
			if(spi_writeIndx0<spi_writeNum0)
				spi_writeIndx0++;
			if((spi_readIndx0>=spi_readNum0)&&(spi_writeIndx0>=spi_writeNum0)) { 
				break;
			}
			if(fspi_error_USI0ST1) { 
				break;
			}
			
			if(spi_writeIndx0<spi_writeNum0)
			{
				while(!(USI0ST1 & (UDRE)));
				//return data				
				USI0DR = send_data[spi_writeIndx0];
			}
		}		
	}	
}

void USI_USART_SlaveWithPolling(uint8_t ch, uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USI_SPI_SlaveWithPolling(ch, send_data, receive_data, count);
}

/**
* @brief		Transmit data through the SPI peripheral for interrupt mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USI_SPI_SendDataWithInterrupt(uint8_t ch, uint8_t *send_data, uint8_t count)
{
	uint8_t i;
	
	if(ch == SPI_CH0)
	{
		USI_SPI_ConfigureInterrupt(SPI_CH0, SPI_RX_COMPLETE_INT, FALSE);
		USI_SPI_ConfigureInterrupt(SPI_CH0, SPI_TX_COMPLETE_INT, FALSE);
		if((USI0ST1 & RXC)!= RXC) 
			i=USI0DR; //buffer emptying for avoiding overrun	//RXC auto clear 
		if((USI0ST1 & TXC) == TXC)
			USI0ST1 &= ~TXC;	//TXC clear 
			
		spi_writeIndx0 = 0;
		spi_writeNum0 = count;
		for(i = 0; i < count ; i++)
		{
			spi_writeBuff0[i] = send_data[i];
		}
		
		USI_SPI_ConfigureInterrupt(SPI_CH0, SPI_TX_COMPLETE_INT, TRUE);
		
		while(!(USI0ST1 & (UDRE)));
		USI0DR = spi_writeBuff0[spi_writeIndx0];
		
		while(spi_writeIndx0 < spi_writeNum0) ; //wait for complate 
		NOP;
	}
}

/**
* @brief		Receive data through the SPI peripheral for polling mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   receive_data   This parameter contains the data to receive. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USI_SPI_ReceiveDataWithPolling(uint8_t ch, uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
	
	if(ch == SPI_CH0)
	{	
		i = USI0DR;	//buffer emptying for avoiding overrun //RXC auto clear 
		i = USI0DR;	//buffer emptying for avoiding overrun //RXC auto clear 
		for(i = 0; i < count; i++)
		{
			while(!(USI0ST1 & (UDRE)));
			USI0DR = 0xFF; //Dummy data
			while(( USI0ST1 & RXC)!= RXC);		// Wait Data in
			receive_data[i] = USI0DR;
		}
	}
}

/**
* @brief		Receive data through the SPI peripheral for interrupt mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		received data
*/
void USI_SPI_ReceiveDataWithInterrupt(uint8_t ch, uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
		
	if(ch == SPI_CH0)
	{		
		USI_SPI_ConfigureInterrupt(SPI_CH0, SPI_TX_COMPLETE_INT, FALSE);
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, FALSE);
		i = USI0DR;	//buffer emptying for avoiding overrun //RXC auto clear 
		i = USI0DR;	//buffer emptying for avoiding overrun //RXC auto clear 

		spi_readIndx0 = 0;
		spi_readNum0 = count;
		spi_readBuff0 = (uint8_t*)receive_data; 
		
		USI_SPI_ConfigureInterrupt(ch, SPI_RX_COMPLETE_INT, TRUE);
		
		while(!(USI0ST1 & (UDRE)));
		USI0DR = 0xFF;	//Dummy data	

		while(spi_readIndx0 < spi_readNum0);	//wait for complate 
		NOP;		
	}

}

/**
* @brief		Configure the enable or disable SPI interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   flag   This parameter contains the selection of this function. 
*
*					- SPI_RX_COMPLETE_INT = 0
*					- SPI_TX_COMPLETE_INT = 1
* 					- SPI_DATA_EMPTY_INT = 2
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_SPI_ConfigureInterrupt(uint8_t ch, uint8_t flag, uint8_t enable)
{
	uint8_t temp_reg, temp_reg2;
	
	if(ch == SPI_CH0)
	{
		if(flag <= SPI_TX_COMPLETE_INT)  //SPI_RX_COMPLETE_INT
		{
			temp_reg = IE1;
			temp_reg &= ~(0x1 << (3 + flag));
			temp_reg |= (enable << (3+ flag));
			
			temp_reg2 = USI0CR2;
			temp_reg2 &= ~(0x1 << (5 + flag));
			temp_reg2 |= (enable << (5 + flag));
			
			IE1 = temp_reg;
			USI0CR2 = temp_reg2;
		}
		else //SPI_DATA_EMPTY_INT
		{
			temp_reg = USI0CR2;
			temp_reg &= ~(0x1 << (5 + flag));
			temp_reg |= (enable << (5 + flag));
			
			USI0CR2 = temp_reg;
		}
	}
}

/**
* @brief		Get the USART interrupt status.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		Value of status(interrupt flag)
*/
uint8_t USI_SPI_GetInterruptStatus(uint8_t ch)
{
	uint8_t result;

	if(ch == SPI_CH0)
	{
		result = USI0ST1;
	}
	
	return result;
}


//==============================================================================
// interrupt routines(USI0)
//==============================================================================
void USI0_RXInt_Handler() interrupt USI0_RX_VECT
{	
	uint8_t temp;
	
	//master
	if(USI0CR3 & MASTER) 
	{
		if (USI0ST1 & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		temp = USI0DR;
		if(spi_readIndx0 < spi_readNum0) 
		{
			spi_readBuff0[spi_readIndx0++] = temp;
		}
		if(spi_writeIndx0==spi_readIndx0) //TX setting after RX interrupt 
		{
			if(!(USI0CR3&USI0SSEN)) //if SS_Manual
				Port_SetOutputHighpin(PORT0, PIN4);
			if(spi_writeIndx0 < spi_writeNum0) 
			{
				while(!(USI0ST1 & (UDRE)));
				if(!(USI0CR3&USI0SSEN)) //if SS_Manual
					Port_SetOutputLowpin(PORT0, PIN4);
				USI0DR = spi_writeBuff0[spi_writeIndx0];
			}
			else 
				NOP;
		}
	}
	//slave
	else 
 	{
		//USER CODE
				
		if (USI0ST1 & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}	
		temp = USI0DR;
		if(spi_readIndx0 < spi_readNum0) 
		{
			spi_readBuff0[spi_readIndx0++] = temp;
		}
		if(spi_readIndx0==spi_writeIndx0) //TX setting after RX interrupt 
		{
			if(spi_writeIndx0<spi_writeNum0)
			{
				while(!(USI0ST1 & (UDRE)));
				//return data
				USI0DR = spi_writeBuff0[spi_writeIndx0];
			}
			else {
			}
		}					
		//USER CODE
		
	}
}

void USI0_TXInt_Handler() interrupt USI0_TX_VECT
{
	if(spi_writeIndx0 < spi_writeNum0) 
		spi_writeIndx0++;
	if(spi_writeIndx0==spi_readIndx0) //TX setting after RX interrupt 
	{
		if(!(USI0CR3&USI0SSEN)) //if SS_Manual
			Port_SetOutputHighpin(PORT0, PIN4);
		
		if(spi_writeIndx0 < spi_writeNum0) 
		{
			while(!(USI0ST1 & (UDRE)));
			if(!(USI0CR3&USI0SSEN)) //if SS_Manual
				Port_SetOutputLowpin(PORT0, PIN4);
			USI0DR = spi_writeBuff0[spi_writeIndx0];
		}
		else {
		}
	}
}

/* --------------------------------- End Of File ------------------------------ */
/**
 *******************************************************************************
 * @file        a96T428_usart1_spi.c
 * @author      ABOV R&D Division
 * @brief       USART1 SPI Communication
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
#include "a96T428_usart1_spi.h"
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
uint8_t xdata spi2_writeBuff0[SPI2_MAX_BUFFER_SIZE]_at_ 0x0180;
uint8_t spi2_writeNum0 = 0;
volatile uint8_t spi2_writeIndx0 = 0;

uint8_t *spi2_readBuff0;
uint8_t spi2_readNum0 = 0;
volatile uint8_t spi2_readIndx0 = 0;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize usart1 spi peripheral
* @param   mode	This parameter contains the enable of master or slave mode(SPI). 
*
*					- SPI2_SLAVE_MODE		 	= 0
* 					- SPI2_MASTER_MODE 			= 1
* @param   speed			This parameter contains the buadrate of SPI.
* @param   first_bit	This parameter contains the transmitted first as SPI.
*
*					- SPI2_LSB 		= 0
*					- SPI2_MSB 		= 1
* @param   cpol	This parameter contains the polarity(CPOL) as SPI. 
*
*					- SPI2_CPOL_LOW 	= 0
*					- SPI2_CPOL_HIGH 	= 1
* @param   cpha	This parameter contains the phase(CPHA) as SPI. 
*
*					- SPI2_CPHA_1EDGE = 0
*					- SPI2_CPHA_2EDGE = 1
* @param   direction	This parameter contains the enable of transmit or receive mode(SPI). 
*
*					- SPI2_TX_RX_MODE 			= 0
* 					- SPI2_RX_MODE				= 1
*					- SPI2_TX_MODE 				= 2
* @param   ss_mode	This parameter contains the enable of SS function(SPI). 
*
*					- SPI2_SS_HW_DISABLE			= 0
*					- SPI2_SS_HW_ENABLE 			= 1
* @return		None
*/
void USART1_SPI_Initial(uint8_t mastermode, uint32_t speed, uint8_t first_bit, uint8_t cpol, uint8_t cpha, uint8_t direction, uint8_t ss_mode)
{
	uint32_t buadrate_val = 0;
	uint8_t temp_reg;
	
	spi2_writeNum0 = 0;
	spi2_readNum0 = 0;
	
	/*calculate baudrate speed*/
	buadrate_val = ((Clock_GetSystemFreq() / 2 * 10 / speed ));

	buadrate_val = ((buadrate_val + 5) / 10) - 1; //round
	
	temp_reg = UCTRL2;
	if(direction == SPI2_RX_MODE)
		temp_reg |= RXE;	
	else if(direction == SPI2_TX_MODE)
		temp_reg |= TXE;
	else //SPI_TX_RX_MODE
		temp_reg |= (RXE | TXE);
	
	temp_reg |= USARTEN;
	
	
	USTAT	|= SOFTRST;			// USART block reset
	
	UCTRL1 |= ((0x3 << 6) | (first_bit << 2) | (cpha << 1) | (cpol << 0));  //SPI mode
	UCTRL3 |= ((mastermode << 7) | (ss_mode << 4));
	
	UBAUD = buadrate_val;
	
	UCTRL2 = temp_reg;
}

void USART1_USART_Initial(uint8_t mastermode, uint32_t speed, uint8_t cpol, uint8_t direction, uint8_t data_length)
{
	uint8_t parity=0; //USART_PARITY_NO;
	uint8_t stop_bits=0; //USART1_STOP_1BIT;

	uint32_t buadrate_val = 0;
	uint8_t temp_reg;
	
	spi2_writeNum0 = 0;
	spi2_readNum0 = 0;
	
	/*calculate baudrate speed*/
	buadrate_val = ((Clock_GetSystemFreq() / 2 * 10 / speed ));

	buadrate_val = ((buadrate_val + 5) / 10) - 1; //round
	
	temp_reg = UCTRL2;
	if(direction == SPI2_RX_MODE)
		temp_reg |= RXE;	
	else if(direction == SPI2_TX_MODE)
		temp_reg |= TXE;
	else //SPI_TX_RX_MODE
		temp_reg |= (RXE | TXE);
	
	temp_reg |= USARTEN;
	
	
	USTAT	|= SOFTRST;			// USART block reset
	
	UCTRL1 |= ((0x1 << 6) | (cpol << 0));  //USART mode
	UCTRL1 |= ((parity << 4) | (data_length <<  1));

	UCTRL3 |= ((mastermode << 7));
	UCTRL3 |= ((1 << 5));// DISable XCK ree-running
	UCTRL3 |= (stop_bits<< 2);
	
	UCTRL3|=0x40;///
	
	UBAUD = buadrate_val;
	
	UCTRL2 = temp_reg;
}

void USART1_SPI_SendReceiveDataWithPolling(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	uint8_t i=0;
	
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 
		
	for(i = 0; i < count ; i++)
	{
		while(!(USTAT & (UDRE)));
		if(!(UCTRL3&SPISS)) //if SS_Manual
			Port_SetOutputLowpin(PORT1, PIN4);	
		UDATA = send_data[i];
		while((USTAT & (RXC))!= (RXC));		// Wait Data in
		while((USTAT & (TXC)) != TXC);		// Wait Data out
		USTAT &= ~(TXC); // TXC clear 
		if(!(UCTRL3&SPISS)) //if SS_Manual
			Port_SetOutputHighpin(PORT1, PIN4);
		receive_data[i] = UDATA;
		NOP;
	}
	
}

void USART1_USART_SendReceiveDataWithPolling(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USART1_SPI_SendReceiveDataWithPolling(send_data, receive_data, count);
}

/**
* @brief		Enables or disables the SPI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_SPI_Enable(uint8_t enable)
{

		if(enable == TRUE)
		{
			UCTRL2 |= USARTEN;
		}
		else
		{
			UCTRL2 &= ~USARTEN;
		}
	
}
	uint8_t ttt,ttt2;


/**
* @brief		Transmit data through the SPI peripheral for polling mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_SendDataWithPolling(uint8_t *send_data, uint8_t count)
{
	uint8_t i=0;
	
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	for(i = 0; i < count ; i++)
	{
		while(!(USTAT & (UDRE)));
		UDATA = send_data[i];
	}
	while((USTAT & (TXC)) != TXC);		// Wait Data out
	USTAT &= ~(TXC); // TXC clear 
}

/**
* @brief		Transmit data through the SPI peripheral for interrupt mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_SendDataWithInterrupt(uint8_t *send_data, uint8_t count)
{
	uint8_t i;

	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 

	spi2_writeIndx0 = 0;
	spi2_writeNum0 = count;
	for(i = 0; i < count ; i++)
	{
		spi2_writeBuff0[i] = send_data[i];
	}
	
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, TRUE);
	
	while(!(USTAT & (UDRE)));
	UDATA = spi2_writeBuff0[spi2_writeIndx0];

	while(spi2_writeIndx0 < spi2_writeNum0);	//wait for complate 
	NOP;
}

/**
* @brief		Transmit and Receive data through the SPI peripheral for interrupt mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   receive_data   This parameter contains the data to receive. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/

void USART1_SPI_SendReceiveDataWithInterrupt(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	uint8_t i;

	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun

	spi2_readIndx0 = 0;
	spi2_readNum0 = count;
	spi2_readBuff0 = (uint8_t*)receive_data; 
			
	spi2_writeIndx0 = 0;
	spi2_writeNum0 = count;
	for(i = 0; i < count ; i++)
	{
		spi2_writeBuff0[i] = send_data[i];
	}
	
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, TRUE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, TRUE);
	
	while(!(USTAT & (UDRE)));
	if(!(UCTRL3&SPISS)) //if SS_Manual
		Port_SetOutputLowpin(PORT1, PIN4);	
	UDATA = spi2_writeBuff0[spi2_writeIndx0];

	while(spi2_readIndx0 < spi2_readNum0);	//wait for complate 
	NOP;
	while(spi2_writeIndx0 < spi2_writeNum0);	//wait for complate 
	NOP;
}

void USART1_USART_SendReceiveDataWithInterrupt(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USART1_SPI_SendReceiveDataWithInterrupt(send_data, receive_data, count);
}

void USART1_SPI_SlaveWithInterrupt(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	uint8_t i;
	
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 

	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun

	spi2_readIndx0 = 0;
	spi2_readNum0 = count;
	spi2_readBuff0 = (uint8_t*)receive_data; 
			
	spi2_writeIndx0 = 0;
	spi2_writeNum0 = count;
	for(i = 0; i < count ; i++)
	{
		spi2_writeBuff0[i] = send_data[i];
	}
	
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, TRUE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, TRUE);
	
	while(!(USTAT & (UDRE)));
	UDATA = spi2_writeBuff0[spi2_writeIndx0];

	while(spi2_readIndx0<spi2_readNum0);
	while(spi2_writeIndx0<spi2_writeNum0);
	
}

void USART1_USART_SlaveWithInterrupt(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USART1_SPI_SlaveWithInterrupt(send_data, receive_data, count);
}

void USART1_SPI_SlaveWithPolling(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	uint8_t i;
	uint8_t tempr;
	
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 

	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	if((USTAT & (TXC)) == TXC)		
		USTAT &= ~(TXC); // TXC clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun

	spi2_readIndx0 = 0;
	spi2_readNum0 = count;
	spi2_readBuff0 = (uint8_t*)receive_data; 
			
	spi2_writeIndx0 = 0;
	spi2_writeNum0 = count;
	for(i = 0; i < count ; i++)
	{
		spi2_writeBuff0[i] = send_data[i];
	}
		
	while(!(USTAT & (UDRE)));
	UDATA = spi2_writeBuff0[spi2_writeIndx0];

	while (1)
	{
		while(( USTAT & RXC)!= RXC);		// Wait Data in
		while(( USTAT & TXC)!= TXC);		// Wait Data out
		USTAT &= ~TXC;
		
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		
		tempr = UDATA;		
		spi2_readBuff0[spi2_readIndx0++] = tempr;
		if(spi2_writeIndx0<spi2_writeNum0)
			spi2_writeIndx0++;
		if((spi2_readIndx0>=spi2_readNum0)&&(spi2_writeIndx0>=spi2_writeNum0)) { 
			break;
		}
		
		if(spi2_writeIndx0<spi2_writeNum0)
		{
			while(!(USTAT & (UDRE)));
			//return data
			UDATA = spi2_writeBuff0[spi2_writeIndx0];
		}		
	}

	
}

void USART1_USART_SlaveWithPolling(uint8_t *send_data, uint8_t *receive_data, uint8_t count)
{
	USART1_SPI_SlaveWithPolling(send_data, receive_data, count);
}

/**
* @brief		Receive data through the SPI peripheral for interrupt mode.
* @return		received data
*/
void USART1_SPI_ReceiveDataWithInterrupt(uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i=0;

	USART1_SPI_ConfigureInterrupt(SPI2_TX_COMPLETE_INT, FALSE);
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, FALSE);
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun
	
	spi2_readIndx0 = 0;
	spi2_readNum0 = count;
	spi2_readBuff0 = (uint8_t*)receive_data; 
	
	USART1_SPI_ConfigureInterrupt(SPI2_RX_COMPLETE_INT, TRUE);

	while(!(USTAT & (UDRE)));
	UDATA = 0xFF; //Dummy data	
	
	while(spi2_readIndx0 < spi2_readNum0);	//wait for complate 
	NOP;

}


/**
* @brief		Receive data through the SPI peripheral for polling mode.
* @param   receive_data   This parameter contains the data to receive. 
* @param   count   This parameter contains the number of data. 
* @return		None
*/
void USART1_SPI_ReceiveDataWithPolling(uint8_t *receive_data, uint8_t count)
{
	volatile uint8_t i;
	
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 
	if((USTAT & (RXC)) == (RXC)) i=UDATA; //buffer emptying for avoiding overrun	//RXC auto clear 
	for(i = 0; i < count; i++)
	{
		while(!(USTAT & (UDRE)));
		UDATA = 0xFF; //Dummy data
		while((USTAT & (RXC))!= (RXC));		// Wait Data in
		receive_data[i] = UDATA;
		NOP;
	}
	
}

/**
* @brief		Configure the enable or disable SPI interrupt.
* @param   flag   This parameter contains the selection of this function. 
*
*					- SPI2_RX_COMPLETE_INT 	= 0
*					- SPI2_TX_COMPLETE_INT 	= 1
* 					- SPI2_DATA_EMPTY_INT 	= 2
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_SPI_ConfigureInterrupt(uint8_t flag, uint8_t enable)
{
	uint8_t temp_reg, temp_reg2;
	
	if(flag == SPI2_TX_COMPLETE_INT)
	{
		temp_reg = IE1;
		temp_reg &= ~(0x1 << 1);
		temp_reg |= (enable << 1);
		
		temp_reg2 = UCTRL2;
		temp_reg2 &= ~(0x1 << (5 + flag));
		temp_reg2 |= (enable << (5 + flag));
		
		IE1 = temp_reg;
		UCTRL2 = temp_reg2;
	}
	else if(flag == SPI2_RX_COMPLETE_INT)
	{
		temp_reg = IE3;
		temp_reg &= ~(0x1 << 1);
		temp_reg |= (enable << 1);
	
		temp_reg2 = UCTRL2;
		temp_reg2 &= ~(0x1 << (5 + flag));
		temp_reg2 |= (enable << (5 + flag));
		
		IE3 = temp_reg;
		UCTRL2 = temp_reg2;
	}
	else if(flag == SPI2_DATA_EMPTY_INT)
	{
		temp_reg = UCTRL2;
		temp_reg &= ~(0x1 << (5 + flag));
		temp_reg |= (enable << (5 + flag));
		
		UCTRL2 = temp_reg;
	}

}

void USART1_USART_ConfigureInterrupt(uint8_t flag, uint8_t enable)
{
	USART1_SPI_ConfigureInterrupt(flag, enable);
}

/**
* @brief		Get the USART interrupt status.
* @return		Value of status(interrupt flag)
*/
uint8_t USART1_SPI_GetInterruptStatus()
{
	return USTAT;
}


//==============================================================================
// interrupt routines
//==============================================================================
void USART1_RXInt_Handler() interrupt USART1_RX_VECT
{	
	uint8_t temp;
	
	//master
	if(UCTRL3 & MASTER) 
	{
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		temp = UDATA;

		if(spi2_readIndx0 < spi2_readNum0) 
		{
			spi2_readBuff0[spi2_readIndx0++] = temp;
		}
		if(spi2_readIndx0==spi2_writeIndx0) //TX setting after RX interrupt 
		{
			if(!(UCTRL3&SPISS)) //if SS_Manual
				Port_SetOutputHighpin(PORT1, PIN4);
			if(spi2_writeIndx0<spi2_writeNum0)
			{
				while(!(USTAT & (UDRE)));
				if(!(UCTRL3&SPISS)) //if SS_Manual
					Port_SetOutputLowpin(PORT1, PIN4);	
				UDATA = spi2_writeBuff0[spi2_writeIndx0];
			}
		}
	}
	//slave
	else 
 	{
		//USER CODE		
		if (USTAT & DOR )
		{
			//DATA OVERUN handling(user)
			NOP;
		}
		
		temp = UDATA;
		if(1)
		{
			if(spi2_readIndx0 < spi2_readNum0) 
				spi2_readBuff0[spi2_readIndx0++] = temp;
			if(spi2_readIndx0==spi2_writeIndx0) //TX setting after RX interrupt 
			{
				if(spi2_writeIndx0<spi2_writeNum0)
				{
					while(!(USTAT & (UDRE)));
					//return data
					UDATA = spi2_writeBuff0[spi2_writeIndx0];
				}
			}	
		//USER CODE
		}
	}
	
}

void USART1_TXInt_Handler() interrupt USART1_TX_VECT
{
	if(spi2_writeIndx0<spi2_writeNum0)
		spi2_writeIndx0++;
	if(spi2_writeIndx0==spi2_readIndx0) //send if both TXC and RXC flag
	{
		if(!(UCTRL3&SPISS)) //if SS_Manual
			Port_SetOutputHighpin(PORT1, PIN4);		
		if(spi2_writeIndx0<spi2_writeNum0)
		{
			while(!(USTAT & (UDRE)));
			if(!(UCTRL3&SPISS)) //if SS_Manual
				Port_SetOutputLowpin(PORT1, PIN4);	
			UDATA = spi2_writeBuff0[spi2_writeIndx0];
		}
	}
}


/* --------------------------------- End Of File ------------------------------ */
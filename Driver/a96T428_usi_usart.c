/**
 *******************************************************************************
 * @file        a96T428_usi_usart.c
 * @author      ABOV R&D Division
 * @brief       USI USART Communication
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
#include "a96T428_usi_usart.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
char USI0_tx_queue[ USI0_UART_QUEUE_SIZE ];
char USI0_tx_front, USI0_tx_rear;

char USI0_rx_queue[ USI0_UART_QUEUE_SIZE ];
char USI0_rx_front, USI0_rx_rear;

char USI1_tx_front, USI1_tx_rear;

char USI1_rx_front, USI1_rx_rear;
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
char USI0_tx_queue_is_full()
{
	return ( (USI0_tx_rear + 1 ) % USI0_UART_QUEUE_SIZE == USI0_tx_front );
}

char USI0_tx_queue_is_empty()
{
	return ( USI0_tx_rear == USI0_tx_front );
}

char USI0_rx_queue_is_full()
{
	return ( (USI0_rx_rear + 1 ) % USI0_UART_QUEUE_SIZE == USI0_rx_front );
}

char USI0_rx_queue_is_empty()
{
	return ( USI0_rx_rear == USI0_rx_front );
}

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize usi(usart) peripheral(For USART & UART)
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   speed			This parameter contains the buadrate of uart/usart.
* @param   data_length	This parameter contains the length of data as uart/usart
*
*					- USART_DATA_5BIT = 0
*					- USART_DATA_6BIT = 1
*					- USART_DATA_7BIT = 2
*					- USART_DATA_8BIT = 3
*					- USART_DATA_9BIT = 7
* @param   stop_bits	This parameter contains the bits of stop as uart/usart.
* 
*					- USART_STOP_1BIT = 0
*					- USART_STOP_2BIT = 1
* @param   parity	This parameter contains the bit of parity as uart. 
*
*					- USART_PARITY_NO = 0
*					- USART_PARITY_EVEN = 2
*					- USART_PARITY_ODD = 3
* @param   mode	This parameter contains the enable of transmit or receive mode(uart/usart). 
*
*					- USART_TX_RX_MODE = 0
* 					- USART_RX_MODE = 1
*					- USART_TX_MODE = 2
* @return		None
*/
void USI_UART_Initial(uint8_t ch, uint32_t speed, uint8_t data_length, uint8_t stop_bits, uint8_t parity, uint8_t mode)
{
	uint32_t buadrate_val = 0;
	uint8_t temp_reg, temp_reg2;
	
	if(ch == USART_CH0)
	{

		temp_reg = USI0CR1;
		temp_reg &= ~(0x3 << 6);  
		//operation mode : UART(default), if used USART, set USART_System_Clock_Initial() + USART_Initial();
		temp_reg |= ((parity << 4) | (data_length <<  1));

		//speed=115200; //UBAUD=7.680555556
		//speed=57600; //UBAUD=16.36111111
		//speed=38400; //UBAUD=25.04166667
		//speed=9600; //UBAUD=103.1666667
		
		//USI0CR2 |= (0x1 << 0); //if using Double Speed operation, Enable USI0CR2 |= (0x1 << 0)
		if(USI0CR2 & 0x1) //Double Speed operation(only UART)
		{
			buadrate_val = ((Clock_GetSystemFreq() / 8 * 10 / speed ));
		}
		else if(USI0CR1 & 0x40) //Synchronous mode(USART)
		{
			buadrate_val = ((Clock_GetSystemFreq() / 2 * 10 / speed ));
		}
		else  //Normal Speed operation
		{
			buadrate_val = ((Clock_GetSystemFreq() / 16 * 10 / speed ));
		}
		
		buadrate_val = ((buadrate_val + 5) / 10) - 1; //round

		temp_reg2 = USI0CR2;
		if(mode == USART_RX_MODE)
			temp_reg2 |= RXE0;	
		else if(mode == USART_TX_MODE)
			temp_reg2 |= TXE0;
		else //USART_TX_RX_MODE
			temp_reg2 |= (RXE0 | TXE0);
		
		temp_reg2 |= USI0EN;
		
		if(!(USI0CR1 & 0x40)) //Not Synchronous mode(USART)
			USI0ST1	|= SOFTRST;			// USART block reset
		
		USI0CR1 = temp_reg;
		USI0CR3 |= (stop_bits<< 2);
		
		USI0BD = buadrate_val;
		
		USI0CR2 = temp_reg2;
	}
}


/**
* @brief		Initialize the clock of usi(usart) peripheral(For only USART)
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   clock_en	This parameter contains the selection of USART mode.
*
* 					- USART_SYNC_DISABLE = 0
*					- USART_SYNC_ENABLE  = 1
* @param   mode	This parameter contains the enable of transmit or receive mode(uart/usart). 
*
* 					- USART_SLAVE_MODE   	= 0
*					- USART_MASTER_MODE 	= 1
* @return		None
*/
void USI_USART_System_Clock_Initial(uint8_t ch, uint32_t clock_en, uint8_t master_en)
{
	uint8_t temp_reg, temp_reg2;
	
	if(ch == USART_CH0)
	{
		temp_reg = USI0CR1;
		temp_reg &= ~(0x3 << 6);
		temp_reg |= (clock_en << 6);
		
		temp_reg2 = USI0CR3;
		temp_reg2 &= ~(0x1 << 7);
		temp_reg2 |= (master_en << 7);
		
		USI0CR1 = temp_reg;
		USI0CR3 = temp_reg2;
	}
}

/**
* @brief		Enables or disables the USART peripheral.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_USART_Enable(uint8_t ch, uint8_t enable)
{
	if(ch == USART_CH0)
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
* @brief		Transmit data through the USART peripheral for polling mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count		This parameter contains the number of write length.
* @return		None
*/
void USI_UART_SendDataWithPolling(uint8_t ch, uint8_t *send_data, uint8_t count)
{
	uint8_t i;
	
	if(ch == USART_CH0)
	{
		for(i = 0; i < count; i++)
		{
			while(!(USI0ST1 & (UDRE)));
				USI0DR = send_data[i];
		}
	}
}

/**
* @brief		Transmit data through the USART peripheral for interrupt mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   send_data   This parameter contains the data to transmit. 
* @return		None
*/
void USI_UART_SendDataWithInterrupt(uint8_t ch, uint8_t send_data)
{
	if(ch == USART_CH0)
	{
		if( (USI0CR2 & (UDRIE)) || (USI0CR2 & (TXCIE)))           
		{
			if ( USI0_tx_queue_is_empty() == FALSE )			
			{
				while ( USI0_tx_queue_is_full() == TRUE );	
			}
			USI_USART_ConfigureInterrupt(USART_CH0, USART_TX_COMPLETE_INT, FALSE);
			
			USI0_tx_queue [ USI0_tx_rear ] = send_data;				
			USI0_tx_rear = ++USI0_tx_rear % USI0_UART_QUEUE_SIZE;						
			USI_USART_ConfigureInterrupt(USART_CH0, USART_TX_COMPLETE_INT, TRUE);
			
			USI0CR2 |= (UDRIE);	
		}	
	}
}

/**
* @brief		Receive data through the USART peripheral for polling mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   receive_data   This parameter contains the data to receive.
* @param   count		This parameter contains the number of receive data length. 
* @return		None
*/
void USI_UART_ReceiveDataWithPolling(uint8_t ch, uint8_t *receive_data, uint8_t count)
{
	uint8_t i;

	if(ch == USART_CH0)
	{	
		for(i = 0; i < count; i++)
		{
			while((USI0ST1 & RXC)!= RXC);		// Wait Data in
			receive_data[i] = USI0DR;	//RXC auto clear 
		}
	}
}

/**
* @brief		Receive data through the USART peripheral for interrupt mode.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		received data
*/
uint8_t USI_UART_ReceiveDataWithInterrupt(uint8_t ch)
{
	uint8_t temp;
	
	if(ch == USART_CH0)
	{
		while ( USI0_rx_queue_is_empty() == TRUE ); 
		USI_USART_ConfigureInterrupt(ch, USART_RX_COMPLETE_INT, FALSE);
		temp = USI0_rx_queue [ USI0_rx_front ];

		USI0_rx_front = ++USI0_rx_front % USI0_UART_QUEUE_SIZE;
		USI_USART_ConfigureInterrupt(ch, USART_RX_COMPLETE_INT, TRUE);
	}

	return temp;
}

/**
* @brief		Configure the enable or disable USART interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   flag   This parameter contains the selection of this function. 
*
*					- USART_RX_COMPLETE_INT = 0
*					- USART_TX_COMPLETE_INT = 1
* 					- USART_DATA_EMPTY_INT = 2
* 					- USART_WAKEUP_INT = 3
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_USART_ConfigureInterrupt(uint8_t ch, uint8_t flag, uint8_t enable)
{
	uint8_t temp_reg, temp_reg2;
	
	if(ch == USART_CH0)
	{
		if(flag <= USART_TX_COMPLETE_INT)
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
		else if(flag == USART_DATA_EMPTY_INT)
		{
			temp_reg = USI0CR2;
			temp_reg &= ~(0x1 << (5 + flag));
			temp_reg |= (enable << (5 + flag));
			
			USI0CR2 = temp_reg;
		}
		else if(flag == USART_WAKEUP_INT)
		{
			temp_reg = USI0CR2;
			temp_reg &= ~(0x1 << 4);
			temp_reg |= (enable << 4);
			
			USI0CR2 = temp_reg;
		}

	}
}

/**
* @brief		Get the USART interrupt status.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		Value of status(interrupt flag)
*/
uint8_t USI_USART_GetInterruptStatus(uint8_t ch)
{
	uint8_t result;

	if(ch == USART_CH0)
	{
		result = USI0ST1;
	}
	
	return result;
}

/**
* @brief		Enables or disables the UART Wake-Up function.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_USART_ConfigureWakeUp(uint8_t ch, uint8_t enable)
{
	if(ch == USART_CH0)
	{
		if(enable == TRUE)
			USI0CR2 |= (1<<4);
		else
			USI0CR2 &= ~(1<<4);
	}
}

/**
* @brief		Clear the UART Wake-Up interrupt flag.
* @param   ch		This parameter contains the channel of USI peripheral.								
* @return		None
*/
void USI_USART_ClearWakeUpFlag(uint8_t ch)
{
	if(ch == USART_CH0)
	{
		USI0ST1 &= ~(1 << 4);
	}
}

//==============================================================================
// interrupt routines(USI0)
//==============================================================================
void USI0_RXInt_Handler_ISR() 
{	
	unsigned char temp, temp2;
	
	temp    = USI0ST1;
	temp2   = USI0CR2;
	
	if ( USI0_rx_queue_is_full () )
	{
		if ((temp & DOR )||(temp & FE )||(temp & PE ))
		{
			USI0_rx_queue [ USI0_rx_rear ] = USI0DR;
			USI0_rx_rear = ++USI0_rx_rear % USI0_UART_QUEUE_SIZE;
		}
		USI0_rx_queue [ USI0_rx_rear ] = USI0DR;
		USI0_rx_rear = ++USI0_rx_rear % USI0_UART_QUEUE_SIZE;
			
		USI0_rx_front = USI0_rx_rear = 0;	// RX Queue pointer CLR
		USI0_rx_queue[ USI0_rx_front ] = 0;
	}
	else
	{
		USI0_rx_queue [ USI0_rx_rear ] = USI0DR;
		USI0_rx_rear = ++USI0_rx_rear % USI0_UART_QUEUE_SIZE;
	}
}

void USI0_TXInt_Handler_ISR() 
{
	if ( USI0_tx_queue_is_empty() == TRUE )
	{
		if ( (USI0ST1 & (TXC)) )			
		{
			USI0CR2	&= ~( (UDRIE) | (TXCIE) );
			USI0ST1	&= ~( TXC );
		}
		else								
		{
			USI0CR2	&= ~( UDRIE );		
		}
	}
	else
	{
		USI0DR = USI0_tx_queue [ USI0_tx_front ];
		USI0_tx_front = ++USI0_tx_front % USI0_UART_QUEUE_SIZE;
	}
}

/* --------------------------------- End Of File ------------------------------ */
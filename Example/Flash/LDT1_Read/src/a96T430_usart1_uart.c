/**
 *******************************************************************************
 * @file        a96T428_usart1_uart.c
 * @author      ABOV R&D Division
 * @brief       USART1 UART Communication
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
#include "a96T428_usart1_uart.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/
bit fRTO_FLAG_occurred=0;

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
char USART1_tx_queue[ USART1_QUEUE_SIZE ];// _at_ 0x0000;
char USART1_tx_front, USART1_tx_rear;

char USART1_rx_queue[ USART1_QUEUE_SIZE ];// _at_ 0x0010;
char USART1_rx_front, USART1_rx_rear;
/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
char USART1_tx_queue_is_full()
{
	return ( (USART1_tx_rear + 1 ) % USART1_QUEUE_SIZE == USART1_tx_front );
}

char USART1_tx_queue_is_empty()
{
	return ( USART1_tx_rear == USART1_tx_front );
}

char USART1_rx_queue_is_full()
{
	return ( (USART1_rx_rear + 1 ) % USART1_QUEUE_SIZE == USART1_rx_front );
}

char USART1_rx_queue_is_empty()
{
	return ( USART1_rx_rear == USART1_rx_front );
}

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief		Initialize usart peripheral(For USART & UART)
* @param   speed			This parameter contains the buadrate of uart/usart.
* @param   data_length	This parameter contains the length of data as uart/usart
*
*					- USART1_DATA_5BIT = 0
*					- USART1_DATA_6BIT = 1
*					- USART1_DATA_7BIT = 2
*					- USART1_DATA_8BIT = 3
*					- USART1_DATA_9BIT = 7
* @param   stop_bits	This parameter contains the bits of stop as uart/usart. 
*
*					- USART1_STOP_1BIT = 0
*					- USART1_STOP_2BIT = 1
* @param   parity	This parameter contains the bit of parity as uart. 
*
*					- USART1_PARITY_NO = 0
*					- USART1_PARITY_EVEN = 2
*					- USART1_PARITY_ODD = 3
* @param   mode	This parameter contains the enable of transmit or receive mode(uart/usart). 
*
*					- USART1_TX_RX_MODE = 0
* 					- USART1_RX_MODE = 1
*					- USART1_TX_MODE = 2
* @return		None
*/
void USART1_UART_Initial(uint32_t speed, uint8_t data_length, uint8_t stop_bits, uint8_t parity, uint8_t mode)
{
	uint32_t baudrate_tmp ;
	uint8_t baudrate_val = 0, fpcr_val = 0;

	//uint32_t buadrate_val = 0;
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = UCTRL1;
	temp_reg &= ~(0x3 << 6);  
	//operation mode : UART(default), if used USART, set USART_System_Clock_Initial() + USART_Initial();
	temp_reg |= ((parity << 4) | (data_length <<  1));
	
	
	temp_reg2 = UCTRL2;
	if(mode == USART1_RX_MODE)
		temp_reg2 |= RXE;	
	else if(mode == USART1_TX_MODE)
		temp_reg2 |= TXE;
	else
		temp_reg2 |= (RXE | TXE);
	
	temp_reg2 |= USARTEN;
	
	//speed=115200; //UBAUD=7.680555556
	//speed=57600; //UBAUD=16.36111111
	//speed=38400; //UBAUD=25.04166667
	//speed=9600; //UBAUD=103.1666667
		
	//UCTRL2 |= (0x1 << 0); //if using Double Speed operation, Enable UCTRL2 |= (0x1 << 0)
	if(UCTRL2 & 0x1) //Double Speed operation(only UART)
	{
		baudrate_tmp=(Clock_GetSystemFreq() / 8 * 256 / speed ); //(Clock_GetSystemFreq() / 8 * 256 / speed  ); 
	}
	else if(UCTRL1 & 0x40) //Synchronous mode(USART)
	{
		baudrate_tmp=(Clock_GetSystemFreq() / 2 * 256 / speed ); //(Clock_GetSystemFreq() / 2 * 256 / speed  ); 
	}
	else  //Normal Speed operation
	{
		baudrate_tmp=(Clock_GetSystemFreq() / 16 * 256 / speed ); //(Clock_GetSystemFreq() / 16 * 256 / speed  ); 
	}
	baudrate_tmp=baudrate_tmp-256;	
	baudrate_val=(baudrate_tmp/256)&0xff;
	fpcr_val=(baudrate_tmp%256)&0xff;	
	if(fpcr_val)  //if floating error rate exist 
	{
		baudrate_val++;
		fpcr_val=256-fpcr_val;
	}
		
	if(!(UCTRL1 & 0x40)) //Not Synchronous mode(USART)
		USTAT	|= SOFTRST;			// USART block reset
	
	UCTRL1 = temp_reg;
	UCTRL3 |= (stop_bits<< 2);
	
	UBAUD = baudrate_val;
	if(fpcr_val)
		USART1_CompensationBaudrate(fpcr_val, TRUE);
	else
		USART1_CompensationBaudrate(0, FALSE);
			
	UCTRL2 = temp_reg2;	
	_nop_();
}


/**
* @brief		Initialize the clock of usart peripheral(For only USART)
* @param   clock_en	This parameter contains the selection of USART mode.
*
*					- USART1_SYNC_DISABLE = 0
*					- USART1_SYNC_ENABLE  = 1
* @param   mode	This parameter contains the enable of transmit or receive mode(uart/usart). 
*
*					- USART1_SLAVE_MODE    = 0
*					- USART1_MASTER_MODE = 1
* @return		None
*/
void USART1_System_Clock_Initial(uint32_t clock_en, uint8_t master_en)
{
	uint8_t temp_reg, temp_reg2;
	
	temp_reg = UCTRL1;
	temp_reg &= ~(0x3 << 6);
	temp_reg |= (clock_en << 6);
	
	temp_reg2 = UCTRL3;
	temp_reg2 &= ~(0x1 << 7);
	temp_reg2 |= (master_en << 7);
	
	USTAT	|= SOFTRST;			// USART block reset
	
	UCTRL1 = temp_reg;
	UCTRL3 = temp_reg2;
}

/**
* @brief		Enables or disables the USART peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_Enable(uint8_t enable)
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



/**
* @brief		Transmit data through the USART peripheral for polling mode.
* @param   send_data   This parameter contains the data to transmit. 
* @param   count		This parameter contains the number of write length.
* @return		None
*/
void USART1_UART_SendDataWithPolling(uint8_t *send_data, uint8_t count)
{
	uint8_t i;
	
	for(i = 0; i < count; i++)
	{
		while(!(USTAT & (UDRE)));
		UDATA = send_data[i];
	}
}

/**
* @brief		Transmit data through the USART peripheral for interrupt mode.
* @param   send_data   This parameter contains the data to transmit. 
* @return		None
*/
void USART1_UART_SendDataWithInterrupt(uint8_t send_data)
{
	if( (UCTRL2 & (UDRIE)) || (UCTRL2 & (TXCIE)))           
	{
		if ( USART1_tx_queue_is_empty() == FALSE )			
		{
			while ( USART1_tx_queue_is_full() == TRUE );	
													 
													
		}
		USART1_ConfigureInterrupt(USART1_TX_COMPLETE_INT, FALSE);
		
		USART1_tx_queue [ USART1_tx_rear ] = send_data;				
		USART1_tx_rear = ++USART1_tx_rear % USART1_QUEUE_SIZE;						
		USART1_ConfigureInterrupt(USART1_TX_COMPLETE_INT, TRUE);
		
		UCTRL2 |= (UDRIE);	
	}	
}

/**
* @brief		Receive data through the USART peripheral for polling mode.
* @param   receive_data   This parameter contains the data to receive. 
* @param   count		This parameter contains the number of receive length.
* @return		received data
*/
void USART1_UART_ReceiveDataWithPolling(uint8_t *receive_data, uint8_t count)
{
	uint8_t i;
	
	for(i = 0; i < count; i++)
	{
		while(( USTAT & RXC)!= RXC);		// Wait Data in
		receive_data[i] = UDATA;
	}
	
}

uint8_t USART1_UART_ReceiveCheckWithPolling(uint8_t *receive_data)
{
	if(( USTAT & RXC)== RXC)		// Wait Data in
	{
		*receive_data = UDATA;
		return 1;
	}
	else 
		return 0;
		
}

/**
* @brief		Receive data through the USART peripheral for interrupt mode.
* @param   receive_data   This parameter contains the data to receive. 
* @return		received data
*/
uint8_t USART1_UART_ReceiveDataWithInterrupt(void)
{
	uint8_t temp;
	
	while ( USART1_rx_queue_is_empty() == TRUE ); 

	USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, FALSE);
	temp = USART1_rx_queue [ USART1_rx_front ];

	USART1_rx_front = ++USART1_rx_front % USART1_QUEUE_SIZE;
	USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, TRUE);

	return temp;
}

uint8_t USART1_UART_ReceiveCheckWithInterrupt(uint8_t *receive_data)
{	
	if( USART1_rx_queue_is_empty() == TRUE )
	{
		return 0;
	}
	else 
	{
		USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, FALSE);
		*receive_data = USART1_rx_queue [ USART1_rx_front ];

		USART1_rx_front = ++USART1_rx_front % USART1_QUEUE_SIZE;
		USART1_ConfigureInterrupt(USART1_RX_COMPLETE_INT, TRUE);

		return 1;
	}
}

/**
* @brief		Configure the enable or disable USART interrupt.
* @param   flag   This parameter contains the selection of this function. 
*
*					- USART1_RX_COMPLETE_INT = 0
*					- USART1_TX_COMPLETE_INT = 1
* 					- USART1_DATA_EMPTY_INT = 2
* 					- USART1_WAKEUP_INT = 3
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_ConfigureInterrupt(uint8_t flag, uint8_t enable)
{
	uint8_t temp_reg, temp_reg2;

	if(flag == USART1_TX_COMPLETE_INT)
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
	else if(flag == USART1_RX_COMPLETE_INT)
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
	else if(flag == USART1_DATA_EMPTY_INT)
	{
		temp_reg = UCTRL2;
		temp_reg &= ~(0x1 << (5 + flag));
		temp_reg |= (enable << (5 + flag));
		UCTRL2 = temp_reg;
	}
	else if(flag == USART1_WAKEUP_INT)
	{
		temp_reg = UCTRL2;
		temp_reg &= ~(0x1 << 4);
		temp_reg |= (enable << 4);
		UCTRL2 = temp_reg;
	}
}

/**
* @brief		Get the USART interrupt status.
* @return		Value of status(interrupt flag)
*/
uint8_t USART1_GetInterruptStatus(void)
{
	uint8_t result;
	
	result = USTAT;
	
	return result;
}

/**
* @brief		Set the function of wake up interrupt.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 		
* @return		None

*/
void USART1_ConfigureWakeUp(uint8_t enable)
{
	uint8_t temp_reg;
	
	temp_reg = UCTRL2;
	temp_reg &= ~(1 << 4);
	temp_reg |= (enable << 4);
	
	UCTRL2 = temp_reg;
}

/**
* @brief		Clear the flag of wake up interrupt.
* @param   		None	
* @return		None

*/
void USART1_ClearWakeUpFlag(void)
{
	USTAT &= ~(1 << 4);
}

/**
* @brief		Set the flag of RTO(receive time out).
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 		
* @return		None

*/

void USART1_ConfigureRTO(uint8_t enable, uint16_t RTOCval)
{
	uint8_t temp_reg;

	if(enable) 
	{
		temp_reg = UCTRL4;
		temp_reg &= ~(RTOEN);
		temp_reg |= (enable << 4);	
		UCTRL4 = temp_reg;
		RTOCH=RTOCval>>8;
		RTOCL=RTOCval&0xff;
	}
	temp_reg = UCTRL4;
	temp_reg &= ~(RTOEN);
	temp_reg |= (enable << 4);	
	UCTRL4 = temp_reg;
}

/**
* @brief		Get the flag of RTO(receive time out).
* @return		the value of flag
*
*					- FLASE												= 0
*					- TRUE 												= 1
*/
uint8_t USART1_GetRTOStatus(void)
{
	uint8_t result;
	
	if(UCTRL4 & RTO_FLAG)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	
	return result;
}

void USART1_ClearRTOFlag(void)
{
	uint8_t temp_reg;

	temp_reg = UCTRL4;
	temp_reg &= ~(RTOEN);
	temp_reg &= ~(RTO_FLAG); //before RTO_FLAG clear, RTOEN should be disabled 
	temp_reg |= (RTOEN);
	UCTRL4 = temp_reg;
}

/**
* @brief		Compensation the baud rate of UART(special function)
* @param   fpcg_val   This parameter contains the floating point counter of this function. 
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USART1_CompensationBaudrate(uint16_t fpcg_val, uint8_t enable)
{
	if(enable == TRUE)
	{
		UCTRL4 |= FPCREN;
		FPCR = fpcg_val;
	}
	else
	{
		UCTRL4 &= ~FPCREN;
		FPCR = 0;
	}
}


//==============================================================================
// interrupt routines
//==============================================================================
void USART1_RXInt_Handler_ISR() 
{	
	unsigned char temp, temp2;
	
	temp    = USTAT;
	temp2   = UCTRL2;
	
	if(( USTAT & RXC))		// Wait Data in
	{	
	if ( USART1_rx_queue_is_full () )
	{
		if ((temp & DOR )||(temp & FE )||(temp & PE ))
		{
			USART1_rx_queue [ USART1_rx_rear ] = UDATA;
			USART1_rx_rear = ++USART1_rx_rear % USART1_QUEUE_SIZE;
		}
		USART1_rx_queue [ USART1_rx_rear ] = UDATA;
		USART1_rx_rear = ++USART1_rx_rear % USART1_QUEUE_SIZE;
			
		USART1_rx_front = USART1_rx_rear = 0;	
    USART1_rx_queue[ USART1_rx_front ] = 0;
	}
	else
	{
		USART1_rx_queue [ USART1_rx_rear ] = UDATA;
		USART1_rx_rear = ++USART1_rx_rear % USART1_QUEUE_SIZE;
	}
	}
	
	if(UCTRL4&RTOEN)
	{
		if(UCTRL4&RTO_FLAG) { 
			UCTRL4&=~RTOEN;
			UCTRL4 &= ~(RTO_FLAG);	//before RTO_FLAG clear, RTOEN should be disabled 
			UCTRL4|=RTOEN;
			fRTO_FLAG_occurred=1;
		}
	}
}

void USART1_TXInt_Handler_ISR() 
{	
	if ( USART1_tx_queue_is_empty() == TRUE )
	{
		if ( (USTAT & (TXC)) )				
		{
			UCTRL2	&= ~( (UDRIE) | (TXCIE) );
			USTAT	&= ~( UDRE + TXC );
		}
		else								
		{
			UCTRL2	&= ~( UDRIE );													
		}
	}
	else
	{
		UDATA = USART1_tx_queue [ USART1_tx_front ];
		USART1_tx_front = ++USART1_tx_front % USART1_QUEUE_SIZE;
	}
}


/* --------------------------------- End Of File ------------------------------ */
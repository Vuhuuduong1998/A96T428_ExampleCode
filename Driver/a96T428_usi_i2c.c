/**
 *******************************************************************************
 * @file        a96T428_usi_i2c.c
 * @author      ABOV R&D Division
 * @brief       USI I2C Communication
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
#include "a96T428_usi_i2c.h"

/*******************************************************************************
* Private Pre-processor Definition & Macro
*******************************************************************************/

/*******************************************************************************
* Private Typedef
*******************************************************************************/

/*******************************************************************************
* Private Variable
*******************************************************************************/
volatile uint8_t i2c_mode[I2C_MAX_CHANNEL] = {0, };
volatile uint8_t i2c_stop[I2C_MAX_CHANNEL] = {0, };
volatile uint8_t i2c_ErrNo[I2C_MAX_CHANNEL] = {0, };
#define	I2CSR_Buf_SIZE	0x80
u8 USI0ST2_Buf[I2CSR_Buf_SIZE] _at_ (0x100);
#define	I2CMR_Buf_SIZE	0x80
u8 USI0CR4_Buf[I2CMR_Buf_SIZE] _at_ (0x180);
u8 USI0ST2_Buf_indx=0, USI0CR4_Buf_indx=0;

uint8_t *receiveBuffer0=0;
uint8_t *receiveBuffer1=0;
uint8_t receiveCount[I2C_MAX_CHANNEL] = {0, };
uint8_t receiveNum[I2C_MAX_CHANNEL] = {0, };
uint8_t receiveNumMsg[I2C_MAX_CHANNEL] = {0, };
uint8_t transmitNumMsg[I2C_MAX_CHANNEL] = {0, };

uint8_t *transmitBuffer0=0;
uint8_t transmitCount[I2C_MAX_CHANNEL] = {0, };
uint8_t transmitNum[I2C_MAX_CHANNEL] = {0, };
uint8_t i2c_slave_addr=0;
uint8_t i2cUSI0ST2, i2cUSI0DR, i2cUSI0CR4;

uint8_t I2CModeStarted=0;
uint8_t RepeatedAddress;

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/
static void USI_I2C_Start(uint8_t ch, uint8_t enable);
static void USI_I2C_Stop(uint8_t ch, uint8_t enable);
static void USI_I2C_Send7bitAddress(uint8_t ch, uint8_t dev_addr, uint8_t direction);
static void USI_I2C_SlaveProcessData(uint8_t ch);
static void USI_I2C_MasterProcessData(uint8_t ch);
static void USI_I2C_GeneralCallProcess(uint8_t ch);
/*******************************************************************************
* Public Function
*******************************************************************************/
/**
* @brief		Initialize usi(i2c) peripheral
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   speed			This parameter contains the buadrate of i2c.
* @param   addr	This parameter contains the slave address of i2c(address[7:1]bit)
* @param   ack	This parameter contains the enable of acknowledge signal. 
*
*					- I2C_ACK_DISABLE = 0
*					- I2C_ACK_ENABLE = 1
* @return		None
*/
void USI_I2C_Initial(uint8_t ch, uint32_t speed, uint8_t addr, uint8_t addr2)
{
	uint8_t ack=1;
	uint32_t period = 0, periodH, periodL;
	uint8_t temp_reg1, temp_reg2, temp_reg4;
		
	if(!(addr&0xFE) || !(addr2&0xFE))
		while(1);
	receiveNum[ch] = 0;
	transmitNum[ch] = 0;
	if(1) { 
		extern uint8_t xdata read_data[I2C_MAX_BUFFER_SIZE];
		extern uint8_t xdata write_data[I2C_MAX_BUFFER_SIZE];
		receiveBuffer0 =  (uint8_t*)read_data;
		transmitBuffer0 = (uint8_t*)write_data;		
	}
	if(ch == I2C_CH0)
	{
		temp_reg2 = USI0CR2;
		temp_reg2 &= ~USI0EN;
		temp_reg2 |= USI0EN;
		
		temp_reg1 = USI0CR1;
		temp_reg1 &= ~(0x3 << 6);
		temp_reg1 |= USI0MS_I2C;
		
		temp_reg4 = USI0CR4;
		temp_reg4 &= ~(0x1 << 3);
		temp_reg4 |= (ack << 3);
		
		USI0CR2 = temp_reg2;
		USI0CR1 = temp_reg1;
		USI0CR4 = temp_reg4;	
		USI0SAR = addr;		//address1
		USI0BD = addr2; 	//address2
			
		period = (Clock_GetSystemFreq() / 4 / speed) - 1;  //period=9, 380KHz@400KHz
		if(period & 0x1)
			periodH=(period+1) >> 1;
		else
			periodH=(period) >> 1;
		periodL = period-periodH;		
		USI0SCHR = periodH;
		USI0SCLR = periodL;
		USI0SDHR = periodL; // 1/4 of SCL Low period

		if(speed<400000UL)
		{
			speed = 400000UL;
			period = (Clock_GetSystemFreq() / 4 / speed) - 1;  //period=9, @400KHz
			if(period & 0x1)
				periodH=(period+1) >> 1;
			else
				periodH=(period) >> 1;
			periodL = period-periodH;		
			/* SDAn output hold timing */
			USI0SDHR = periodL; // 1/4 of SCL Low period,  covering for Max 400KHz input  
			//USI0SDHR = 1;
		}			
		USI0ST2 = 0x00;
		
	}
	
}

/**
* @brief		Enables or disables the I2C peripheral.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Enable(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR2 |= USI0EN;
		}
	}

}


/**
* @brief		Enables or disables the I2C general call function.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureGerneralCall(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0SAR |= 0x1;
		}
		else
		{
			USI0SAR &= ~0x1;
		}
	}

}

/**
* @brief		Enables or disables the I2C Start condition.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Start(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x1;
		}
		else
		{
			USI0CR4 &= ~0x1;
		}
	}

}

/**
* @brief		Enables or disables the I2C Stop condition.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_Stop(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= (0x2 | 0x8);  //0x8(ACK restore in case of master read)
		}
		else
		{
			USI0CR4 &= ~0x2;
		}
	}

}

/**
* @brief		Enables or disables the I2C Software reset
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_SoftwareReset(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x20;
		}
		else
		{
			USI0CR4 &= ~0x20;
		}
	}

}


/**
* @brief		Configure the I2C Acknowledge signal.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureAcknowledge(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			USI0CR4 |= 0x8;
		}
		else
		{
			USI0CR4 &= ~0x8;
		}
	}

}


/**
* @brief		Write multi bytes by writing as i2c master.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   dev_addr			This parameter contains the slave address of target.
* @param   *write_data			This parameter contains the write data of i2c(pointer variable)
* @param   write_len			This parameter contains the number of write length.
* @param   *read_data			This parameter contains the read data of i2c(pointer variable)
* @param   read_len			This parameter contains the number of read length.
* @return		None
*/
void USI_I2C_MasterTransferData(uint8_t ch, uint8_t dev_addr, uint8_t *write_data, uint8_t write_len, uint8_t *read_data, uint8_t read_len)
{
	uint8_t i;
	
	if(ch == I2C_CH0)
	{
//		for(i = 0; i < I2C_MAX_BUFFER_SIZE; i++)
//			transmitBuffer0[i] = write_data[i];
		if(write_len)
			transmitBuffer0 =  (uint8_t*)write_data;
		
		if(read_len)
			receiveBuffer0 =  (uint8_t*)read_data;
		for(i = 0; i < read_len; i++)
			receiveBuffer0[i] = 0;
	}

	transmitCount[ch] = write_len;
	receiveCount[ch] = read_len;
	if(write_len && read_len)
		RepeatedAddress=dev_addr;	
	
	i2c_mode[ch] = I2C_BUSY;
	
	if(write_len != 0) 
		USI_I2C_Send7bitAddress(ch, dev_addr, I2C_WRITE_MODE);
	else
		USI_I2C_Send7bitAddress(ch, dev_addr, I2C_READ_MODE);

	if((IE1&0x04) && EA) //if I2C Int. Enable Flag   
	{
		while(!i2c_stop[I2C_CH0]);
	}
	else
	{
		while(!i2c_stop[I2C_CH0])
			if(USI_I2C_Flag_Polling(I2C_CH0))
				USI_I2C_InterruptHandler(I2C_CH0);
	}
	RepeatedAddress=0x00;
	i2c_stop[I2C_CH0]=0;
}

/**
* @brief		Send slave address as i2c master.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   dev_addr			This parameter contains the slave address of target.
* @param   direction			This parameter contains the mode of i2c(read or write).
*
*					- I2C_WRITE_MODE 	= 0
*					- I2C_READ_MODE 	= 1
* @return		None
*/
void USI_I2C_Send7bitAddress(uint8_t ch, uint8_t dev_addr, uint8_t direction)
{
	
	if(ch == I2C_CH0)
	{		
		USI0DR = dev_addr | direction;
		if(direction)  
			receiveNum[ch] = 0;
		else 
			transmitNum[ch] = 0;
		if(direction)  
			I2CModeStarted=0x12;
		else 
			I2CModeStarted=0x11;

	}
	
	USI_I2C_ConfigureAcknowledge(ch, TRUE);	//Ack generate
	USI_I2C_Start(ch, TRUE);
	
}

/**
* @brief		Response specific bytes as i2c master.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_MasterProcessData(uint8_t ch)
{
		
	if(i2cUSI0ST2 & RXACK)
	{
		// Master Tx mode
		if(i2cUSI0ST2 & TMODE)
		{
			if(I2CModeStarted!=0x11)
				if(!i2c_ErrNo[ch]) i2c_ErrNo[ch]=0x11;
			if(transmitCount[ch])
			{
				if(ch == I2C_CH0)
					USI0DR = transmitBuffer0[transmitNum[ch]];		
				
				transmitCount[ch] -= 1;
				transmitNum[ch] += 1;
			}
			else
			{
				if(receiveCount[ch])
				{
					//Restart for Rx
					USI_I2C_Send7bitAddress(ch, RepeatedAddress, I2C_READ_MODE);
				}
				else
				{
					// TxLength 0 Stop
					USI_I2C_Stop(ch, TRUE);
				}
			}
		}
		// Master Rx mode
		else
		{
			if(I2CModeStarted!=0x12)
				if(!i2c_ErrNo[ch]) i2c_ErrNo[ch]=0x12;
			if(i2cUSI0ST2&GCALL) //AACK(Address ACK) in Slave mode 
			{
				// Address ACK is received
				if(receiveCount[ch] == 1)
				{
					USI_I2C_ConfigureAcknowledge(ch, FALSE);	// NoAck generate
				}
			}
			else
			{				
				if(receiveCount[ch])
				{
					if(receiveNum[ch]<I2C_MAX_BUFFER_SIZE)
						receiveBuffer0[receiveNum[ch]] = i2cUSI0DR;
					
					receiveCount[ch] -= 1;
					receiveNum[ch] += 1;
				}
				
				if(receiveCount[ch] == 1)
				{					
					USI_I2C_ConfigureAcknowledge(ch, FALSE);	// NoAck generate
				}
				else if(receiveCount[ch] == 0)
				{
					USI_I2C_Stop(ch, TRUE);
				}
				
			}
		}
	}
	else
	{
		// Nack data is received
		if(!(i2cUSI0ST2 & TMODE)) 
		if(receiveCount[ch] == 1)
		{
			receiveCount[ch] = 0;
			
			if(receiveNum[ch]<I2C_MAX_BUFFER_SIZE)
				receiveBuffer0[receiveNum[ch]] = USI0DR;
			receiveNum[ch] += 1;
		}
		else
			NOP;
		
		// NoAck Stop
		USI_I2C_Stop(ch, TRUE);
	}
}

/**
* @brief		Response specific bytes as i2c slave.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_SlaveProcessData(uint8_t ch)
{
	
	if((i2cUSI0ST2 & GCALL)) // address 0x00 incoming 
	{
		//USI_I2C_GeneralCallProcess(ch); //USER CODE;
		_nop_();
	}
	
	if(1)
	{
		if(i2cUSI0ST2 & TMODE) // Slave Tx mode
		{
			if(i2cUSI0ST2 & SSEL0) //Slave Select
			{
				transmitNum[ch] = 0;
				i2c_slave_addr = i2cUSI0DR;
				I2CModeStarted=0x21;
			}
		
			if(i2cUSI0ST2&RXACK)
			{
				USI0DR = transmitBuffer0[transmitNum[ch]];
			
				transmitCount[ch] -= 1;
				transmitNum[ch] += 1;
			}	
			if(I2CModeStarted!=0x21)
				if(!i2c_ErrNo[ch]) i2c_ErrNo[ch]=0x21;
		}
		else  // Slave Rx mode
		{
			if(i2cUSI0ST2 & SSEL0) //Slave addr Select
			{				
				receiveNum[ch] = 0;
				i2c_slave_addr = i2cUSI0DR;
				I2CModeStarted=0x22;
			}			
			else if(i2cUSI0ST2&RXACK)
			{
				if(receiveNum[ch]<I2C_MAX_BUFFER_SIZE)
					receiveBuffer0[receiveNum[ch]] = i2cUSI0DR;
				//echo
				if(1)
				{
					transmitBuffer0[receiveNum[ch]] = receiveBuffer0[receiveNum[ch]];													
				}
				receiveNum[ch] += 1;
				//echo
				transmitCount[ch] = receiveNum[ch];
			}						
			if(I2CModeStarted!=0x22)
				if(!i2c_ErrNo[ch]) i2c_ErrNo[ch]=0x22;
			
		}
			
	}
		//END
}

/**
* @brief		Handle general call as i2c process.(custom user)
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
static void USI_I2C_GeneralCallProcess(uint8_t ch)
{
	if(ch == I2C_CH0)
		NOP;
	
	//USER CODE
	//USER CODE
}


/**
* @brief		Configure the enable or disable I2C interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureInterrupt(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
		{
			IE1 |= 0x04;
			USI0CR4 |= 0x10;
		}
		else
		{
			USI0CR4 &= ~0x10;
			IE1 &= ~0x04;
		}
	}

}

/**
* @brief		Get the I2C interrupt status.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		Value of status(interrupt flag)
*/
uint8_t USI_I2C_GetInterruptStatus(uint8_t ch)
{
	uint8_t result;

	if(ch == I2C_CH0)
	{
		result = USI0ST2;
	}
	
	return result;
}


/**
* @brief		Configure the enable or disable I2C interrupt.
* @param   ch		This parameter contains the channel of USI peripheral.
* @return		None
*/
void USI_I2C_InterruptHandler(uint8_t ch)
{

	
	P20=0;P2IO|=0x01;
//	if(ch == I2C_CH0)
//	{
//	}
	i2cUSI0ST2 = USI0ST2;
	i2cUSI0DR = USI0DR;
	i2cUSI0CR4 = USI0CR4;
	i2c_mode[ch] = I2C_BUSY;
	if(USI0ST2_Buf_indx<I2CSR_Buf_SIZE) USI0ST2_Buf[USI0ST2_Buf_indx++]=i2cUSI0ST2;
	if(USI0CR4_Buf_indx<I2CMR_Buf_SIZE) USI0CR4_Buf[USI0CR4_Buf_indx++]=i2cUSI0CR4;
	NOP;
	
	if((i2cUSI0ST2 & MLOST) || (i2cUSI0ST2 & STOPD))
	{
		i2c_stop[ch] = 1;
		i2c_mode[ch] = I2C_IDLE;
		receiveNumMsg[I2C_CH0]=receiveNum[I2C_CH0];
		receiveNum[I2C_CH0]=0;
		transmitNumMsg[I2C_CH0]=transmitNum[I2C_CH0];
		transmitNum[I2C_CH0]=0;
		if(i2cUSI0ST2 & MLOST)
			if(!i2c_ErrNo[ch]) i2c_ErrNo[ch]=0xFE;//while(1);//USI_I2C_Initial(ch, I2C_SPEED, I2C_DEVICE_ADDRESS, I2C_DEVICE_ADDRESS2);
				
	}
	else
	{
			if(i2cUSI0CR4 & 0x4)  //Master mode
			{
				USI_I2C_MasterProcessData(ch);
			}
			else  //Slave mode
			{
				USI_I2C_SlaveProcessData(ch);
			}
	}
	
//	if(ch == I2C_CH0)
//	{
//	}
	USI0ST2 = 0x00;
	//while(USI0CR4&IIC0IFR);
	//IIC0IFR : This bit is cleared when write any values in the USInST2. Writing '1' has no effect.
	P20=!P20;P2IO|=0x01;
	
}


/**
* @brief		Enables or disables the I2C Wake-Up function.
* @param   ch		This parameter contains the channel of USI peripheral.
* @param   enable   This parameter contains the enable of this function. 
*
*					- FLASE												= 0
*					- TRUE 												= 1
* @return		None
*/
void USI_I2C_ConfigureWakeUp(uint8_t ch, uint8_t enable)
{
	if(ch == I2C_CH0)
	{
		if(enable == TRUE)
			USI0ST1 |= (1<<4);
		else
			USI0ST1 &= ~(1<<4);
	}

}

uint8_t USI_I2C_Flag_Polling(uint8_t ch)
{
	if(ch!=I2C_CH0)
		return 0;
	if(USI0CR4&IIC0IFR) //if I2C Int. Flag 
	{
		return 1; 
	}
	else 
		return 0;
}



/* --------------------------------- End Of File ------------------------------ */
/**
 *******************************************************************************
 * @file        a96T428_gpio.c
 * @author      ABOV R&D Division
 * @brief       General Purpose Input Output
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

/*******************************************************************************
* Private Function Prototype
*******************************************************************************/

/*******************************************************************************
* Public Function
*******************************************************************************/

/**
* @brief	Initialize GPIO(PCU) peripheral
* @param    None
* @return	None
*/
void Port_Initial(void)
{
		// P0 setting
		P0		= _0000_0000;		// 0 : Low,	1 : High
		P0OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)
		P0PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
		P0IO	= _0000_0000;		// 0 : Input,	1 : Output
			
		P0FSRH  = 0;		
		P0FSRL  = 0;
		
#if A96T418_MODE==1
		P0DB	= 0	
		| ( 0 << 6 )    // 00 : fx/1, 01 : fx/4, 10 : fx/4096, 11 : LSIRC (128khz)
		| ( 0 << 4 )    // P07
		| ( 0 << 3 )    // P06
		| ( 0 << 2 )    // P05
		| ( 0 << 1 )    // P04
		| ( 0 << 0 );   // P03
#endif	
#if A96T418_MODE==0
		DBCONT0 = 0;
#endif	
		
		// P1 setting    
		P1		= _0000_0000;		// 0 : Low,	1 : High
		P1OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)
		P1PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
		P1IO	= _0000_0000;		// 0 : Input,	1 : Output
		
		P1FSRH  = 0;
		
		P1FSRL  = 0;

		// P2 setting    
		P2		= _0000_0000;		// 0 : Low,	1 : High
		P2OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)
		P2PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
		P2IO	= _0000_0000;		// 0 : Input,	1 : Output
		
		P2FSRL  = 0;
		// P3 setting    
		P3		= _0000_0000;		// 0 : Low,	1 : High
		P3PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
		P3IO	= _0000_0000;		// 0 : Input,	1 : Output
		
		P3FSR   = 0;

#if A96T418_MODE==1
		P123DB	= 0
		| ( 0 << 4 )    // P31
		| ( 0 << 3 )    // P26
		| ( 0 << 2 )    // P25
		| ( 0 << 1 )    // P12
		| ( 0 << 0 );   // P11
#endif	
#if A96T418_MODE==0
		DBCONT1=0;
		DBCONT2=0;
		DBCONT3=0;
#endif	

		#if A96T418_MODE==0
		P3OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)

		// P4 setting    
//		P4		= _0000_0000;		// 0 : Low,	1 : High
//		P4OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)
//		P4PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
//		P4IO	= _0000_0000;		// 0 : Input,	1 : Output
//		
//		P4FSRH  = 0;	
//		P4FSRL  = 0;

		// P5 setting    
//		P5		= _0000_0000;		// 0 : Low,	1 : High
//		P5OD	= _0000_0000;		// 0 : Disable,	1 : Enable (Open-drain)
//		P5PU	= _1111_1111;		// 0 : Disable,	1 : Enable (Pull-up)
//		P5IO	= _0000_0000;		// 0 : Input,	1 : Output
//		
//		P5FSRH  = 0;		
//		P5FSRL  = 0;
		#endif

}

/**
* @brief	Configures the selected port(x) pins as output pin.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @param    mode	This parameter contains the pin mode(Push-Pull : 0, Open-Drain :1)
* @return	None
*/
void Port_SetOutputpin(uint8_t port, uint8_t pin, uint8_t mode)
{

		switch(port)
		{
			case 0:
				P0IO |= (1<<pin);
				P0OD |= (mode<<pin);
			break;
			case 1:
				P1IO |= (1<<pin);
				P1OD |= (mode<<pin);
			break;
			case 2:
				P2IO |= (1<<pin);
				P2OD |= (mode<<pin);
			break;
			case 3:
				P3IO |= (1<<pin);
				#if A96T418_MODE==0
				P3OD |= (1<<pin);
				#endif
			break;
			#if A96T418_MODE==0
			case 4:
//				P4IO |= (1<<pin);
//				P4OD |= (mode<<pin);
			break;
			case 5:
//				P5IO |= (1<<pin);
//				P5OD |= (mode<<pin);
			break;
			#endif

			default:
			break;
		}
}

/**
* @brief	Configures the selected port(x) pins as input pin.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @param    mode	This parameter contains the pin mode(Disable : 0, Pull-UP : 1)
* @return	None
*/
void Port_SetInputpin(uint8_t port, uint8_t pin, uint8_t mode)
{
		switch(port)
		{
			case 0:
				P0IO &= ~(1<<pin);
				P0PU |= (mode<<pin);
			break;
			case 1:
				P1IO &= ~(1<<pin);
				P1PU |= (mode<<pin);
			break;
			case 2:
				P2IO &= ~(1<<pin);
				P2PU |= (mode<<pin);
			break;
			case 3:
				P3IO &= ~(1<<pin);
				P3PU |= (mode<<pin);		
			break;
			#if A96T418_MODE==0
			case 4:
//				P4IO &= ~(1<<pin);
//				P4PU |= (mode<<pin);		
			break;
			case 5:
//				P4IO &= ~(1<<pin);
//				P4PU |= (mode<<pin);		
			break;
			#endif
			
			default:
			break;			
		}
}

/**
* @brief	Configures the selected port(x) pins as several kinds alternative function pin.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @param    val		This parameter contains the value of alternative function bit
* @return	None
*/
void Port_SetAlterFunctionpin(uint8_t port, uint8_t pin, uint8_t val)
{
	uint8_t temp_reg;
	
		switch(port)
		{
			case 0:
				if(pin > 0x3)
				{
					temp_reg = P0FSRH;
					temp_reg &= ~(0x3<<((pin-4)<<1));
					temp_reg |= (val<<((pin-4)<<1));
					
					P0FSRH = temp_reg;
				}
				else
				{
					temp_reg = P0FSRL;
					temp_reg &= ~(0x3<<(pin<<1));
					temp_reg |= (val<<(pin<<1));
					
					P0FSRL = temp_reg;
				}
			break;
			case 1:
				if(pin > 0x3)
				{
					temp_reg = P1FSRH;
					temp_reg &= ~(0x3<<((pin-4)<<1));
					temp_reg |= (val<<((pin-4)<<1));
					
					P1FSRH = temp_reg;
				}
				else
				{
					temp_reg = P1FSRL;
					temp_reg &= ~(0x3<<(pin<<1));
					temp_reg |= (val<<(pin<<1));	

					P1FSRL = temp_reg;
				}	
			break;
			case 2:
				if(pin > 0x3)
				{
					temp_reg = P2FSRH;
					temp_reg &= ~(0x3<<((pin-4)<<1));
					temp_reg |= (val<<((pin-4)<<1));
					
					P2FSRH = temp_reg;
				}
				else
				{
					temp_reg = P2FSRL;
					temp_reg &= ~(0x3<<(pin<<1));
					temp_reg |= (val<<(pin<<1));	

					P2FSRL = temp_reg;
				}	
			break;
			case 3:
				if(val < 0x2)
				{
					temp_reg = P3FSR;
					temp_reg  &= ~(1<<pin);
					temp_reg  |= (val<<pin);
					
					P3FSR = temp_reg;
				}
			break;
			#if A96T418_MODE==0				
			case 4:
//				if(pin > 0x3)
//				{
//					temp_reg = P4FSRH;
//					temp_reg &= ~(0x3<<((pin-4)<<1));
//					temp_reg |= (val<<((pin-4)<<1));
//					
//					P4FSRH = temp_reg;
//				}
//				else
//				{
//					temp_reg = P4FSRL;
//					temp_reg &= ~(0x3<<(pin<<1));
//					temp_reg |= (val<<(pin<<1));	

//					P4FSRL = temp_reg;
//				}	
			break;
			case 5:
//				if(pin > 0x3)
//				{
//					temp_reg = P5FSRH;
//					temp_reg &= ~(0x3<<((pin-4)<<1));
//					temp_reg |= (val<<((pin-4)<<1));
//					
//					P5FSRH = temp_reg;
//				}
//				else
//				{
//					temp_reg = P5FSRL;
//					temp_reg &= ~(0x3<<(pin<<1));
//					temp_reg |= (val<<(pin<<1));	

//					P5FSRL = temp_reg;
//				}	
			break;
			#endif
				
			default:
			break;			
		}
}


/**
* @brief	Configures the selected port(x) pins as output high.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @return	None
*/
void Port_SetOutputHighpin(uint8_t port, uint8_t pin)
{
		switch(port)
		{
			case 0:
				P0 |= (1<<pin);
			break;
			case 1:
				P1 |= (1<<pin);
			break;
			case 2:
				P2 |= (1<<pin);
			break;
			case 3:
				P3 |= (1<<pin);
			break;
			// #if A96T418_MODE==0				
//			case 4:
//				P4 |= (1<<pin);
//			break;
//			case 5:
//				P5 |= (1<<pin);
//			break;
			// #endif
			default:
			break;			
		}
		switch(port)
		{
			case 0:
				if(!(P0IO & (1<<pin)))
					P0IO |= (1<<pin);
			break;
			case 1:
				if(!(P1IO & (1<<pin)))
					P1IO |= (1<<pin);
			break;
			case 2:
				if(!(P2IO & (1<<pin)))
					P2IO |= (1<<pin);
			break;
			case 3:
				if(!(P3IO & (1<<pin)))
					P3IO |= (1<<pin);
			break;
			// #if A96T418_MODE==0								
//			case 4:
//				if(!(P4IO & (1<<pin)))
//					P4IO |= (1<<pin);
//			break;
//			case 5:
//				if(!(P5IO & (1<<pin)))
//					P5IO |= (1<<pin);
//			break;
			// #endif
			default:
			break;
		}	
}


/**
* @brief	Configures the selected port(x) pins as output low.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @return	None
*/
void Port_SetOutputLowpin(uint8_t port, uint8_t pin)
{	
		switch(port)
		{
			case 0:
				P0 &= ~(1<<pin);
			break;
			case 1:
				P1 &= ~(1<<pin);
			break;
			case 2:
				P2 &= ~(1<<pin);
			break;
			case 3:
				P3 &= ~(1<<pin);
			break;
//			#if A96T418_MODE==0											
//			case 4:
//				P4 &= ~(1<<pin);
//			break;
//			case 5:
//				P5 &= ~(1<<pin);
//			break;
//			#endif
			default:
			break;			
		}
		switch(port)
		{
			case 0:
				if(!(P0IO & (1<<pin)))
					P0IO |= (1<<pin);
			break;
			case 1:
				if(!(P1IO & (1<<pin)))
					P1IO |= (1<<pin);
			break;
			case 2:
				if(!(P2IO & (1<<pin)))
					P2IO |= (1<<pin);
			break;
			case 3:
				if(!(P3IO & (1<<pin)))
					P3IO |= (1<<pin);
			break;
//			#if A96T418_MODE==0											
//			case 4:
//				if(!(P4IO & (1<<pin)))
//					P4IO |= (1<<pin);
//			break;
//			case 5:
//				if(!(P5IO & (1<<pin)))
//					P5IO |= (1<<pin);
//			break;
//			#endif	
			default:
			break;
		}
}


/**
* @brief	Configures the selected port(x) pins as output toggle.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @return	None
*/
void Port_SetOutputTogglepin(uint8_t port, uint8_t pin)
{
		switch(port)
		{
			case 0:
				P0 ^= (1<<pin);
			break;
			case 1:
				P1 ^= (1<<pin);
			break;
			case 2:
				P2 ^= (1<<pin);
			break;
			case 3:
				P3 ^= (1<<pin);
			break;
//			#if A96T418_MODE==0														
//			case 4:
//				P4 ^= (1<<pin);
//			break;
//			case 5:
//				P5 ^= (1<<pin);
//			break;
//			#endif
			default:
			break;			
		}
		switch(port)
		{
			case 0:
				if(!(P0IO & (1<<pin)))
					P0IO |= (1<<pin);
			break;
			case 1:
				if(!(P1IO & (1<<pin)))
					P1IO |= (1<<pin);
			break;
			case 2:
				if(!(P2IO & (1<<pin)))
					P2IO |= (1<<pin);
			break;
			case 3:
				if(!(P3IO & (1<<pin)))
					P3IO |= (1<<pin);
			break;
//			#if A96T418_MODE==0			
//			case 4:
//				if(!(P4IO & (1<<pin)))
//					P4IO |= (1<<pin);
//			break;
//			case 5:
//				if(!(P5IO & (1<<pin)))
//					P5IO |= (1<<pin);
//			break;
//			#endif
			default:
			break;
		}
		
}


/**
* @brief	Get the value of selected port(x) pins as input pin.
* @param    port	This parameter contains the pin port
* @param    pin		This parameter contains the pin number
* @return	Value of Input pin(High : 1, Low :0)
*/
uint8_t Port_GetInputpinValue(uint8_t port, uint8_t pin)
{
	 uint8_t result;

		switch(port)
		{
			case 0:
				if(P0IO & (1<<pin))
					P0IO &= ~(1<<pin);
			break;
			case 1:
				if(P1IO & (1<<pin))
					P1IO &= ~(1<<pin);
			break;
			case 2:
				if(P2IO & (1<<pin))
					P2IO &= ~(1<<pin);
			break;
			case 3:
				if(P3IO & (1<<pin))
					P3IO &= ~(1<<pin);
			break;
//			#if A96T418_MODE==0			
//			case 4:
//				if(P4IO & (1<<pin))
//					P4IO &= ~(1<<pin);
//			break;
//			case 5:
//				if(P5IO & (1<<pin))
//					P5IO &= ~(1<<pin);
//			break;
//			#endif
			default:
			break;			
		}
	
		switch(port)
		{
			case 0:
				result = (P0 & (1<<pin)) ? 1 : 0;
			break;
			case 1:
				result = (P1 & (1<<pin)) ? 1 : 0;
			break;
			case 2:
				result = (P2 & (1<<pin)) ? 1 : 0;
			break;
			case 3:
				result = (P3 & (1<<pin)) ? 1 : 0;
			break;
//			#if A96T418_MODE==0			
//			case 4:
//				result = (P4 & (1<<pin)) ? 1 : 0;
//			break;
//			case 5:
//				result = (P5 & (1<<pin)) ? 1 : 0;
//			break;
//			#endif
			default:
			break;			
		}
		
		return result;
}

/**
* @brief	Enable the channel of external interrupt pin as input.
* @param    channel		This parameter contains the channel of external interrupt.
* @return	None
*/
void Port_EnableInterrupt(uint8_t channel)
{	
		switch(channel)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:				
				IE |= (1<<5);
			break;
			case 8:
				IE1 |= (1<<0);
			break;
			case 10:
				IE |= (1<<0);
			break;
			case 11:
				IE |= (1<<1);
			break;
			case 12:
				IE1 |= (1<<5);
			break;
			default:
			break;			
		}
}

/**
* @brief	Disable the channel of external interrupt pin as input.
* @param    channel		This parameter contains the channel of external interrupt.
* @return	None
*/
void Port_DisableInterrupt(uint8_t channel)
{
		switch(channel)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:				
				IE &= ~(1<<5);
			break;
			case 8:
				IE1 &= ~(1<<0);
			break;
			case 10:
				IE &= ~(1<<0);
			break;
			case 11:
				IE &= ~(1<<1);
			break;
			case 12:
				IE1 &= ~(1<<5);
			break;
			default:
			break;			
		}
}


/**
* @brief	Configure the channel of external interrupt pin as input.
* @param    channel		This parameter contains the channel of external interrupt.
* @param    edge		This parameter contains the edge of external interrupt,
*
*				- NONE          = 0
*				- RISING_EDGE   = 1
*				- FALLING_EDGE  = 2
*				- BOTH_EDGE     = 3
* @return	None
*/
void Port_ConfigureInterrupt(uint8_t channel, uint8_t edge)
{
	uint8_t temp_reg;
	
		switch(channel)
		{
			case 0:
			case 1:
			case 2:
			case 3:
				temp_reg = EIPOL0L;
				temp_reg &= ~(0x3<<(channel<<1));
				temp_reg |= (edge<<(channel<<1));
				
				EIPOL0L = temp_reg;
			break;
			case 4:
			case 5:
			case 6:
			case 7:	
				temp_reg = EIPOL0H;		
				temp_reg &= ~(0x3<<((channel-4)<<1));
				temp_reg |= (edge<<((channel-4)<<1));
				
				EIPOL0H = temp_reg;
			break;
			case 8:
				temp_reg = EIPOL1;			
				temp_reg &= ~(0x3<<0);
				temp_reg |= (edge<<0);
				
				EIPOL1 = temp_reg;
			break;
			case 10:
				temp_reg = EIPOL1;
				temp_reg &= ~(0x3<<2);
				temp_reg |= (edge<<2);
				
				EIPOL1 = temp_reg;
			break;
			case 11:
				temp_reg = EIPOL1;
				temp_reg &= ~(0x3<<4);
				temp_reg |= (edge<<4);
				
				EIPOL1 = temp_reg;
			break;
			case 12:
				temp_reg = EIPOL1;
				temp_reg &= ~(0x3<<6);
				temp_reg |= (edge<<6);
				
				EIPOL1 = temp_reg;
			break;
			default:
			break;			
		}
}

/**
* @brief	Get the external interrupt status.
* @param    channel		This parameter contains the channel of external interrupt.
* @return	Value of status(interrupt occur : 1, not occur : 0)
*/
uint8_t Port_GetInterruptStatus(uint8_t channel)
{
		uint8_t result;
	
		switch(channel)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:				
				result = (EIFLAG0 & (1<<channel)) ? 1 : 0;
			break;
			case 8:
				result = (EIFLAG1 & (1<<0)) ? 1 : 0;
			break;
			case 10:
				result = (EIFLAG1 & (1<<1)) ? 1 : 0;
			break;
			case 11:
				result = (EIFLAG1 & (1<<2)) ? 1 : 0;
			break;
			case 12:
				result = (EIFLAG1 & (1<<3)) ? 1 : 0;
			break;
			default:
			break;			
		}
		
		return result;
}

/**
* @brief	Clear the external interrupt status.
* @param    channel	    This parameter contains the channel of external interrupt.
*
*					-  EXTINT_CH0 = 0       
*					-  EXTINT_CH1 = 1       
*					-  EXTINT_CH2 = 2       
*					-  EXTINT_CH3 = 3       
*					-  EXTINT_CH4 = 4       
*					-  EXTINT_CH5 = 5       
*					-  EXTINT_CH6 = 6       
*					-  EXTINT_CH7 = 7       
*					-  EXTINT_CH8 = 8       
*					-  EXTINT_CH9 = 9       
*					-  EXTINT_CH10 = 10       
*					-  EXTINT_CH11 = 11       
*					-  EXTINT_CH12 = 12       
*					-  EXTINT_CH_A = 15       
* @return	None
*/
void Port_ClearInterruptStatus(uint8_t channel)
{
		switch(channel)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:			
				EIFLAG0	= ~(1<<channel);
			break;
			case 8:
				EIFLAG1	= ~(1<<0);
			break;
			case 10:
				EIFLAG1	= ~(1<<1);
			break;
			case 11:
				EIFLAG1	= ~(1<<2);
			break;
			case 12:
				EIFLAG1	= ~(1<<3);
			break;
			default:
			break;			
		}
}

/* --------------------------------- End Of File ------------------------------ */
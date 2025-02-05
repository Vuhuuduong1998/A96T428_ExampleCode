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
#include "intrins.h"
#include "delay.h"
#include "a96T428_flash.h"
#include "a96T428_gpio.h"
#include "a96T428_clock.h"
#include "a96T428_usart1_uart.h"
#include "stdio.h"  

/* Private Pre-processor Definition & Macro ----------------------------------*/
/* Private Typedef -----------------------------------------------------------*/
/* Private Variable ----------------------------------------------------------*/

#if A96T418_MODE==0
//Flash Address Min/Max value for permitted area
//#define FLASH_ADDR_MIN 		(0xEE00)
//#define FLASH_ADDR_MAX 		(0xF9FF) 
//#define FLASH_ADDR_MIN 		(0xF800)
//#define FLASH_ADDR_MAX 		(0xFFFF) 
#define FLASH_ADDR_MIN 		(0x800)
#define FLASH_ADDR_MAX 		(0xFFF) 
#endif
#if A96T418_MODE==1
//Flash Address for used
#define FLASH_ADDR_MIN 		(0x7F00)
#define FLASH_ADDR_MAX 		(0x7FFF) 
#endif

#define	FLASH_USERMEMORY_SIZE ((uint16_t)(FLASH_ADDR_MAX-FLASH_ADDR_MIN+1))
code uint8_t codetmp[FLASH_USERMEMORY_SIZE] _at_ FLASH_ADDR_MIN;
code uint8_t codetmp22[0x80-0x03] _at_ 0x03;

#if A96T418_MODE==1
#define	FLASH_MYBUFFER_SIZE (PAGE_BUFFER_SIZE*2)
#endif
#if A96T418_MODE==0
#define	FLASH_MYBUFFER_SIZE (SECTOR_BUFFER_SIZE+PAGE_BUFFER_SIZE)
#endif

uint8_t write_data[FLASH_MYBUFFER_SIZE] _at_ 0x100;
//uint8_t read_data_ptr[FLASH_MYBUFFER_SIZE];
	
/* Private Function Prototype ------------------------------------------------*/

//------------------------------------------------------------------------------
//	Project include function code
//------------------------------------------------------------------------------
char putchar (char c)   /* character to output */
{
	while(!(USTAT & (UDRE)));
	UDATA = c;
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
	
	//USART1_UART_Initial(9600, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	USART1_UART_Initial(38400, USART1_DATA_8BIT, USART1_STOP_1BIT, USART1_PARITY_NO, USART1_TX_RX_MODE);
	
	printf("\n\ra96T428 FLASH TEST!!");
}

void checksumCal(uint16_t start_addr, end_addr)
{
	extern uint16_t FEARML_addr_before, FEARML1_addr_before;
	extern uint16_t FEARML_addr_after, FEARML1_addr_after;
	
	uint32_t checksum;
	
		checksum=Flash_CheckSum(start_addr,end_addr);
		printf("\n\r User Flash_CheckSum = 0x%06lx (0x%04x~0x%04x) ", checksum, start_addr, end_addr);
		printf(" FEARM_FEARL = 0x%04x, FEARM1_FEARL1 = 0x%04x ", FEARML_addr_before, FEARML1_addr_before  );
		//printf(" FEARM_FEARL_after = 0x%04x, FEARM1_FEARL1_after = 0x%04x ", FEARML_addr_after, FEARML1_addr_after  );
		checksum=Flash_CheckSum(start_addr+3,end_addr-15);
		printf("\n\r User Flash_CheckSum = 0x%06lx (0x%04x~0x%04x)...", checksum, start_addr+3, end_addr-15);
		printf(" FEARM_FEARL = 0x%04x, FEARM1_FEARL1 = 0x%04x ", FEARML_addr_before, FEARML1_addr_before  );
		//printf(" FEARM_FEARL_after = 0x%04x, FEARM1_FEARL1_after = 0x%04x ", FEARML_addr_after, FEARML1_addr_after  );
		
#if A96T418_MODE==0
		start_addr=0x0000;
		end_addr=0xFFFF;
#endif		
#if A96T418_MODE==1
		start_addr=0x0000;
		end_addr=0x7FFF;
#endif		
		checksum=Flash_CheckSum(start_addr,end_addr);
		printf("\n\r Total Range Flash_CheckSum = 0x%06lx (0x%04x~0x%04x) ", checksum, start_addr, end_addr);
		printf(" FEARM_FEARL = 0x%04x, FEARM1_FEARL1 = 0x%04x ", FEARML_addr_before, FEARML1_addr_before  );
		//printf(" FEARM_FEARL_after = 0x%04x, FEARM1_FEARL1_after = 0x%04x ", FEARML_addr_after, FEARML1_addr_after  );
		checksum=Flash_CheckSum(start_addr+3,end_addr-15);
		printf("\n\r Total Range Flash_CheckSum = 0x%06lx (0x%04x~0x%04x)...", checksum, start_addr+3, end_addr-15);
		printf(" FEARM_FEARL = 0x%04x, FEARM1_FEARL1 = 0x%04x ", FEARML_addr_before, FEARML1_addr_before  );
		//printf(" FEARM_FEARL_after = 0x%04x, FEARM1_FEARL1_after = 0x%04x ", FEARML_addr_after, FEARML1_addr_after  );
		
		
#if A96T418_MODE==0
		start_addr=0xFFFF;
		end_addr=0x0000;
#endif		
#if A96T418_MODE==1
		start_addr=0x7FFF;
		end_addr=0x0000;
#endif		
		checksum=Flash_CheckSum(start_addr,end_addr);
		printf("\n\r Full Code Flash_CheckSum = 0x%06lx (0x%04x~0x%04x) ", checksum, end_addr, start_addr);
}

void CodeMemoryDisplay(uint16_t start_addr, uint16_t end_addr)
{
	uint16_t i;
	unsigned char code *read_data_ptr=(unsigned char code *)start_addr;
	for(i = 0; i < (end_addr-start_addr+1) ; i++)
	{ 
		if(i && ((start_addr+i)%PAGE_BUFFER_SIZE)==0)
			printf("\r\n");
		
		if((i==0) || ((start_addr+i)%32)==0)
			printf("\n\r %04x : ", start_addr+i);
		else if(((start_addr+i)%16)==0)
			printf(" ");
		printf("%02X ", (uint16_t)read_data_ptr[i]);		
	}
}

/**********************************************************************
 * @brief		Main program
 * @param   	None
 * @return	    None
 **********************************************************************/
void main(void)
{
	unsigned char ret = 0;
	unsigned char write_data_first_byte = 0x55;
	u8 ucWData=write_data_first_byte;
	
	uint16_t i;
	uint16_t start_addr, end_addr;
	unsigned char code *read_data_ptr=0x0000;
	uint32_t ultmp;
	bit fToggle=0;
	bit fAddrIncrease=0; //1//0,
	u8 saveCONFOPTION1=CONFOPTION1;
	u8 saveCONFOPTION2=CONFOPTION2;

	unsigned char test_mode;
		
	test_mode=0; //0x55565758.. write 
	//test_mode=1; //0x55AA55AA.. write 
	
	/* Disable INT. during peripheral setting */
	GLOBAL_INTERRUPT_DIS();     
    
    /* Port intialize */
	Port_Initial();		        
	Port_SetOutputLowpin(PORT2, PIN0);  
	Port_SetOutputLowpin(PORT2, PIN1);  
	Port_SetOutputLowpin(PORT2, PIN2);  
	
    /* Clock initialize */
	System_Clock_Initial(HSI16_DIV1);   
	Display_project();
		
    /* System Stabilize Delay */
	NOP_10us_Delay(1);        // 10usec
	    
    /* Enable INT */
	GLOBAL_INTERRUPT_EN();

	//CONFOPTION1=0xFF;//// �	�	�	�	PAEN	PASS2	PASS1	PASS0
	//CONFOPTION2|=0x10;//0x80; 	//Vector protect  // R_P	HL	�	VAPEN	�	�	�	RSTS
	//CONFOPTION2|=0xFF; 	//Read protect  // R_P	HL	�	VAPEN	�	�	�	RSTS

	BITCR=0x70;	//0.5ms/32=62.5us 
	IE3 |=0X10; //BIT Int. Enable 

	printf("\n\r CONFOPTION1=0x%02x, CONFOPTION2=0x%02x ", CONFOPTION1&0xffU, CONFOPTION2&0xffU);

	Init_Flash();

	printf("\n\r FLASH_MYBUFFER_SIZE=%xh, SECTOR_BUFFER_SIZE=%xh , PAGE_BUFFER_SIZE=%xh ", FLASH_MYBUFFER_SIZE, SECTOR_BUFFER_SIZE, PAGE_BUFFER_SIZE);
		
	
	start_addr=FLASH_ADDR_MIN;
	end_addr=FLASH_ADDR_MAX;
	//while((start_addr<end_addr) && (start_addr>=FLASH_ADDR_MIN) && (start_addr<=FLASH_ADDR_MAX) && (end_addr>=FLASH_ADDR_MIN) && (end_addr<=FLASH_ADDR_MAX))
	while((start_addr<=end_addr) && (start_addr>=FLASH_ADDR_MIN) && (end_addr<=FLASH_ADDR_MAX))
	{	
		if(fAddrIncrease) { 
			//end_addr limit check 
			ultmp=(start_addr+(unsigned long)(FLASH_MYBUFFER_SIZE-1));
			if(ultmp>(unsigned long)FLASH_ADDR_MAX)
				end_addr=FLASH_ADDR_MAX;
			else 
				end_addr=ultmp;
		}
		else {		
			//start_addr limit check 
			ultmp=(end_addr-(unsigned long)(FLASH_MYBUFFER_SIZE-1));
			if(ultmp<(unsigned long)FLASH_ADDR_MIN)
				start_addr=FLASH_ADDR_MIN;
			else 
				start_addr=ultmp;
		}
		read_data_ptr=(unsigned char code *)start_addr;
		
		#if(1)
		{
		printf("\n\n\r prewrite : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		CONFOPTION1=0xFF;		
		CONFOPTION2=0xFF;
			
		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,0xff); //Prewrite 0x00 only 
		checksumCal(start_addr, end_addr);
		
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data_ptr);				
		printf("\n\rRead data after Flash Write  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1); i++)
		{ 
			if(read_data_ptr[i]!=~FLASH_BLABK_TATA)
			{
				printf("\n\r Prewrite Error : addr= 0x%04x : %02x != %02x", start_addr+i, read_data_ptr[i]&0xffU, ~FLASH_BLABK_TATA&0xffU);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r Prewrite OK");
		else
			printf("\n\r Prewrite FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		CONFOPTION1=saveCONFOPTION1;
		CONFOPTION2=saveCONFOPTION2;		
		
		}	
		#endif		
		
		#if(1)
		{
		printf("\n\n\r erase : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		NOP_10us_Delay(100); //1ms delay 	
		/* Flash erese/write */
		
		//Flash erese
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,1,0); //Erase only 
		checksumCal(start_addr, end_addr);

		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data_ptr);			
		printf("\n\rRead data after Flash Erase  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data_ptr[i]!=FLASH_BLABK_TATA)
			{
				printf("\n\r Erase Error : addr= 0x%04x : %02x != %02x", start_addr+i, read_data_ptr[i]&0xffU, FLASH_BLABK_TATA&0xffU);
				break;
			}
		}
		if(i==(end_addr-start_addr+1))
			printf("\n\r Erase OK");		
		else
			printf("\n\r Erase FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		}
		#endif
		
		#if(1)
		{
		printf("\n\n\r write : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		for(i = 0; i < FLASH_MYBUFFER_SIZE ; i++)
		{
			if(test_mode==0)
			{
				if(((start_addr+i)!=FLASH_ADDR_MIN) && ((start_addr+i)%PAGE_BUFFER_SIZE)==0) //pattern toggle per page 
				{
					fToggle=!fToggle;
					if(!fToggle)
						write_data_first_byte++;
					ucWData=write_data_first_byte;
				}
				if(fToggle)
					write_data[i] = ~ucWData; 
				else 
					write_data[i] = ucWData; 
				ucWData++;
			}
			else if(test_mode==1)
			{
				if(((start_addr+i)!=FLASH_ADDR_MIN) && ((start_addr+i)%PAGE_BUFFER_SIZE)==0) //pattern toggle per page 
				{
					write_data_first_byte^=0xFF;
					ucWData=write_data_first_byte;
				}
				write_data[i] = ucWData; 
				ucWData^=0xFF;
			}
		}		

		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,1); //Write only 
		checksumCal(start_addr, end_addr);

		printf("\n\rRead data after Flash Write  ");
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data_ptr);					
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data_ptr[i]!=write_data[i])
			{
				printf("\n\r Write Error : addr= 0x%04x : %02x != %02x", start_addr+i, read_data_ptr[i]&0xffU, write_data[i]&0xffU);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r Write OK");
		else
			printf("\n\r Write FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		}	
		#endif
		
		/* Flash erese/write */
		if(fAddrIncrease) { 
			start_addr=end_addr+1;
			end_addr=start_addr;
		}
		else { 
			end_addr=start_addr-1;
			start_addr=end_addr;
		}
		NOP; // check flash
	}


		
  /* Infinite loop */
	while(1)
	{
		NOP;
		// End Flash erase/wrtie
		Port_SetOutputLowpin(PORT2, PIN0);
	}
}

void BIT_Int_Handler(void) interrupt BIT_VECT
{
	P22=!P22;
}

/* --------------------------------- End Of File ------------------------------ */

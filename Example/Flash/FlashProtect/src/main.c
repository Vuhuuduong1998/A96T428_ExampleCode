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
//efine	FLASH_USERMEMORY_SIZE ((FLASH_ADDR_MAX-FLASH_ADDR_MIN+1))
//de uint8_t codetmp[FLASH_USERMEMORY_SIZE] _at_ FLASH_ADDR_MIN;


#if A96T418_MODE==0
#define	BLOCKVECTOR_START	0x0003//0x00C0	//vector area last part 
#define	BLOCKVECTOR_START_TMP		(BLOCKVECTOR_START+PAGE_BUFFER_SIZE-1-3)

#define	BLOCK0_START		0x0200
#define	BLOCK0_END			0x03FF

#define	BLOCK1_START		0x0400
#define	BLOCK1_START_TMP	(BLOCK1_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK1_END_TMP		(BLOCK1_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK1_END			0x07FF
#define	BLOCK2_START		0x0800
#define	BLOCK2_START_TMP	(BLOCK2_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK2_END_TMP		(BLOCK2_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK2_END			0x0BFF
#define	BLOCK3_START		0x0C00
#define	BLOCK3_START_TMP	(BLOCK3_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK3_END_TMP		(BLOCK3_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK3_END			0x0FFF
#define	BLOCK4_START		0x1000
#define	BLOCK4_START_TMP	(BLOCK4_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK4_END_TMP		(BLOCK4_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK4_END			0xF7FF

#define	BLOCK5_START		0xF800
#define	BLOCK5_END			0xF9FF
#define	BLOCK6_START		0xFA00
#define	BLOCK6_END			0xFBFF
#define	BLOCK7_START		0xFC00
#define	BLOCK7_END			0xFDFF

#define	BLOCKFINAL_START	(0xFE00)	//Non-Protect area 
#define	BLOCKFINAL_END		(BLOCKFINAL_START+PAGE_BUFFER_SIZE-1)	//Non-Protect area 
#endif

#if A96T418_MODE==1
#define	BLOCKVECTOR_START	(0x03)	//vector area last part 
#define	BLOCKVECTOR_START_TMP	(BLOCKVECTOR_START+PAGE_BUFFER_SIZE-1-3)
#define	BLOCKVECTOR_END_TMP	(BLOCKVECTOR_END-PAGE_BUFFER_SIZE+1)
#define	BLOCKVECTOR_END		0x0FF	//vector area last part 

#define	BLOCK0_START		0x0100
#define	BLOCK0_START_TMP	(BLOCK0_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK0_END_TMP		(BLOCK0_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK0_END			0x03FF
#define	BLOCK1_START		0x0400
#define	BLOCK1_START_TMP	(BLOCK1_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK1_END_TMP		(BLOCK1_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK1_END			0x07FF
#define	BLOCK2_START		0x0800
#define	BLOCK2_START_TMP	(BLOCK2_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK2_END_TMP		(BLOCK2_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK2_END			0x0BFF
#define	BLOCK3_START		0x0C00
#define	BLOCK3_START_TMP	(BLOCK3_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK3_END_TMP		(BLOCK3_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK3_END			0x0FFF
#define	BLOCK4_START		0x1000
#define	BLOCK4_START_TMP	(BLOCK4_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK4_END_TMP		(BLOCK4_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK4_END			0x77FF
#define	BLOCK5_START		0x7800
#define	BLOCK5_START_TMP	(BLOCK5_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK5_END_TMP		(BLOCK5_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK5_END			0x7BFF
#define	BLOCK6_START		0x7C00
#define	BLOCK6_START_TMP	(BLOCK6_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK6_END_TMP		(BLOCK6_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK6_END			0x7DFF
#define	BLOCK7_START		0x7E00
#define	BLOCK7_START_TMP	(BLOCK7_START+PAGE_BUFFER_SIZE-1)
#define	BLOCK7_END_TMP		(BLOCK7_END-PAGE_BUFFER_SIZE+1)
#define	BLOCK7_END			0x7EFF

#define	BLOCKFINAL_START	(0x7F00)	//Non-Protect area 
#define	BLOCKFINAL_END		(BLOCKFINAL_START+PAGE_BUFFER_SIZE-1)	//Non-Protect area 
#endif

#if A96T418_MODE==1
#define	BLOCKCOUNT	19
#endif
#if A96T418_MODE==0
#define	BLOCKCOUNT	14
#endif

uint16_t block_addr_range[BLOCKCOUNT][2]={
	{BLOCKFINAL_START, BLOCKFINAL_END}, 
#if A96T418_MODE==1
	{BLOCK7_END_TMP, BLOCK7_END}, 
	{BLOCK7_START, BLOCK7_START_TMP}, 
	{BLOCK6_END_TMP, BLOCK6_END}, 
	{BLOCK6_START, BLOCK6_START_TMP}, 
	{BLOCK5_END_TMP, BLOCK5_END}, 
	{BLOCK5_START, BLOCK5_START_TMP}, 
	{BLOCK4_END_TMP, BLOCK4_END}, 
	{BLOCK4_START, BLOCK4_START_TMP}, 
	{BLOCK3_END_TMP, BLOCK3_END}, 
	{BLOCK3_START, BLOCK3_START_TMP}, 
	{BLOCK2_END_TMP, BLOCK2_END}, 
	{BLOCK2_START, BLOCK2_START_TMP}, 
	{BLOCK1_END_TMP, BLOCK1_END}, 
	{BLOCK1_START, BLOCK1_START_TMP}, 
	{BLOCK0_END_TMP, BLOCK0_END}, 
	{BLOCK0_START, BLOCK0_START_TMP}, 
	{BLOCKVECTOR_END_TMP, BLOCKVECTOR_END}, 
	{BLOCKVECTOR_START, BLOCKVECTOR_START_TMP}, 
#endif	
#if A96T418_MODE==0
	{BLOCK7_START, BLOCK7_END}, 
	{BLOCK6_START, BLOCK6_END}, 
	{BLOCK5_START, BLOCK5_END}, 
	{BLOCK4_END_TMP, BLOCK4_END}, 
	{BLOCK4_START, BLOCK4_START_TMP}, 
	{BLOCK3_END_TMP, BLOCK3_END}, 
	{BLOCK3_START, BLOCK3_START_TMP}, 
	{BLOCK2_END_TMP, BLOCK2_END}, 
	{BLOCK2_START, BLOCK2_START_TMP}, 
	{BLOCK1_END_TMP, BLOCK1_END}, 
	{BLOCK1_START, BLOCK1_START_TMP}, 
	{BLOCK0_START, BLOCK0_END}, 
	{BLOCKVECTOR_START, BLOCKVECTOR_START_TMP}, 
#endif	
};

#if A96T418_MODE==1
code uint8_t codeblocks00[PAGE_BUFFER_SIZE] _at_ BLOCKVECTOR_START;
code uint8_t codeblocks01[PAGE_BUFFER_SIZE] _at_ BLOCKVECTOR_END_TMP;

code uint8_t codeblock00[PAGE_BUFFER_SIZE] _at_ BLOCK0_START;
code uint8_t codeblock01[PAGE_BUFFER_SIZE] _at_ BLOCK0_END_TMP;
#endif
#if A96T418_MODE==0
code uint8_t codeblocks00[PAGE_BUFFER_SIZE-3] _at_ (BLOCKVECTOR_START);
code uint8_t codeblock00[PAGE_BUFFER_SIZE] _at_ BLOCK0_START;
#endif

code uint8_t codeblock10[PAGE_BUFFER_SIZE] _at_ BLOCK1_START;
code uint8_t codeblock11[PAGE_BUFFER_SIZE] _at_ BLOCK1_END_TMP;
code uint8_t codeblock20[PAGE_BUFFER_SIZE] _at_ BLOCK2_START;
code uint8_t codeblock21[PAGE_BUFFER_SIZE] _at_ BLOCK2_END_TMP;
code uint8_t codeblock30[PAGE_BUFFER_SIZE] _at_ BLOCK3_START;
code uint8_t codeblock31[PAGE_BUFFER_SIZE] _at_ BLOCK3_END_TMP;
code uint8_t codeblock40[PAGE_BUFFER_SIZE] _at_ BLOCK4_START;
code uint8_t codeblock41[PAGE_BUFFER_SIZE] _at_ BLOCK4_END_TMP;

#if A96T418_MODE==1
code uint8_t codeblock50[PAGE_BUFFER_SIZE] _at_ BLOCK5_START;
code uint8_t codeblock51[PAGE_BUFFER_SIZE] _at_ BLOCK5_END_TMP;
code uint8_t codeblock60[PAGE_BUFFER_SIZE] _at_ BLOCK6_START;
code uint8_t codeblock61[PAGE_BUFFER_SIZE] _at_ BLOCK6_END_TMP;
code uint8_t codeblock70[PAGE_BUFFER_SIZE] _at_ BLOCK7_START;
code uint8_t codeblock71[PAGE_BUFFER_SIZE] _at_ BLOCK7_END_TMP;
#endif
#if A96T418_MODE==0
code uint8_t codeblock50[PAGE_BUFFER_SIZE] _at_ BLOCK5_START;
code uint8_t codeblock60[PAGE_BUFFER_SIZE] _at_ BLOCK6_START;
code uint8_t codeblock70[PAGE_BUFFER_SIZE] _at_ BLOCK7_START;
#endif

code uint8_t codeblocks10[PAGE_BUFFER_SIZE] _at_ BLOCKFINAL_START;

#define	FLASH_MYBUFFER_SIZE (PAGE_BUFFER_SIZE)
uint8_t write_data[FLASH_MYBUFFER_SIZE];
uint8_t write_dataFill[FLASH_MYBUFFER_SIZE];
//uint8_t read_data[FLASH_MYBUFFER_SIZE];
uint8_t resetvectorcode[3];
	
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
	uint16_t i;
	uint16_t block_index=0, blockSize;
	uint16_t blockAddr, blockAddrEnd;
	unsigned char code *read_data_ptr=(unsigned char code *)0;
	unsigned char blockProtectResult[BLOCKCOUNT]={0,};
	u8 saveCONFOPTION1=CONFOPTION1;
	u8 saveCONFOPTION2=CONFOPTION2;
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
	
	//CONFOPTION1=0xFF;//// �	�	�	�	PAEN	PASS2	PASS1	PASS0
	//CONFOPTION2|=0x10;//0x80; 	//Vector protect  // R_P	HL	�	VAPEN	�	�	�	RSTS
	//CONFOPTION2|=0xFF; 	//Read protect  // R_P	HL	�	VAPEN	�	�	�	RSTS
	printf("\n\r CONFOPTION1=0x%02x, CONFOPTION2=0x%02x ", CONFOPTION1&0xffU, CONFOPTION2&0xffU);
	printf("\n\r RSTFR =%02x ", RSTFR&0xffU );
	
	if(RSTFR&0x10) //if OCD mode 
	{
		while(1)
			printf("\n\r Disable OCD connect, Then, Run code in user mode operation ! ", RSTFR&0xffU );			
	}
	
	//CONFOPTION1=0x00;
	//CONFOPTION2&=~0x10; //vector area 
	
	resetvectorcode[0]=(*(unsigned char code *)0);
	resetvectorcode[1]=(*(unsigned char code *)1);
	resetvectorcode[2]=(*(unsigned char code *)2);
	
	Init_Flash();

	printf("\n\r FLASH_MYBUFFER_SIZE=%u, PAGE_BUFFER_SIZE=%u ", FLASH_MYBUFFER_SIZE, PAGE_BUFFER_SIZE);
	
	for(block_index=0;block_index<BLOCKCOUNT;block_index++)
	//for(block_index=BLOCKCOUNT-3;block_index<BLOCKCOUNT;block_index++)
	{		
		blockAddr=block_addr_range[block_index][0]; //start of block
		blockAddrEnd=block_addr_range[block_index][1]; 
		blockSize=blockAddrEnd-blockAddr+1;
		
		if(blockAddr==BLOCKVECTOR_START)
		{
			blockAddr=0x0000; //For making page buffer size 
			blockSize=blockAddrEnd-blockAddr+1;
		}		
		read_data_ptr=(unsigned char code *)blockAddr;

		#if(1)
		{
		printf("\n\n\r Prewrite (0x00) blockAddr= %04x ~ %04x ", blockAddr, blockAddrEnd);
		CONFOPTION1=0xFF;		
		CONFOPTION2=0xFF;

		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(blockAddr, blockAddrEnd, write_data, blockSize);
		Update_Flash(FLASH_KEY,0,0xff); //Prewrite 0x00 only 
		//Flash Read
		//Read_Flash(blockAddr, blockSize, read_data);				
		printf("\n\r User Flash_CheckSum = 0x%06lx", Flash_CheckSum(blockAddr, blockAddrEnd));
		printf("\n\rRead data after Flash Prewrite  ");
		CodeMemoryDisplay(blockAddr, blockAddrEnd);
		for(i = 0; i < blockSize ; i++)
		{ 
			if(read_data_ptr[i]!=~FLASH_BLABK_TATA)
			{
				printf("\n\r Prewrite Error : addr= 0x%04x : %02x != %02x @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Different", 
					blockAddr+i, read_data_ptr[i]&0xffU, ~FLASH_BLABK_TATA&0xffU);
				break;
			}
		}
		if(i == blockSize)
			printf("\n\r Prewrite OK");
		else
			blockProtectResult[block_index]|=1;//break; 
		
		CONFOPTION1=saveCONFOPTION1;
		CONFOPTION2=saveCONFOPTION2;		
		}	
		#endif
		
	
		#if(1)
		{
		printf("\n\n\r Erase blockAddr= %04x ~ %04x ", blockAddr, blockAddrEnd);
		NOP_10us_Delay(100); //1ms delay 	
		/* Flash erese/write */
		
		//Flash erese
		Update_Flash_Buf(blockAddr, blockAddrEnd, write_data, blockSize);
		Update_Flash(FLASH_KEY,1,0); //Erase only 
		//Flash Read
		//Read_Flash(blockAddr, blockSize, read_data);			
		printf("\n\r User Flash_CheckSum = 0x%06lx", Flash_CheckSum(blockAddr, blockAddrEnd));
		//printf("\n\r Full Flash_CheckSum = 0x%06lx", Flash_CheckSum(1));		
		printf("\n\rRead data after Flash Erase  ");
		CodeMemoryDisplay(blockAddr, blockAddrEnd);
		for(i = 0; i < blockSize ; i++)
		{ 
			if(read_data_ptr[i]!=FLASH_BLABK_TATA)
			{
				printf("\n\r Erase Error : addr= 0x%04x : %02x != %02x @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Different", 
					blockAddr+i, read_data_ptr[i]&0xffU, 0x00U);
				break;
			}
		}
		if(i==blockSize)
			printf("\n\r Erase OK");		
		else
			blockProtectResult[block_index]|=1;//break; 
		}
		#endif
		
		#if(1)
		{
		printf("\n\n\r Write blockAddr= %04x ~ %04x ", blockAddr, blockAddrEnd);
		write_data[0]=(blockAddr>>8)+(blockAddr&0xff);
		for(i = 0; i < blockSize ; i++)
		{
			write_data[i] = (write_data[0]+i)&0xff;
		}		
		if(blockAddr==(BLOCKVECTOR_START-BLOCKVECTOR_START))
		{
			write_data[0]=resetvectorcode[0];
			write_data[1]=resetvectorcode[1];
			write_data[2]=resetvectorcode[2];
		}		
		
		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(blockAddr, blockAddrEnd, write_data, blockSize);
		Update_Flash(FLASH_KEY,0,1); //Write only 
		//Flash Read
		//Read_Flash(blockAddr, blockSize, read_data);				
		printf("\n\r User Flash_CheckSum = 0x%06lx", Flash_CheckSum(blockAddr, blockAddrEnd));
		printf("\n\rRead data after Flash Write  ");
		CodeMemoryDisplay(blockAddr, blockAddrEnd);
		for(i = 0; i < blockSize ; i++)
		{ 
			if(read_data_ptr[i]!=write_data[i])
			{
				printf("\n\r Write Error : addr= 0x%04x : %02x != %02x @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Different", 
					blockAddr+i, read_data_ptr[i]&0xffU, write_data[i]&0xffU);
				break;
			}
		}
		if(i == blockSize)
			printf("\n\r Write OK");
		else
			blockProtectResult[block_index]|=1;//break; 
		}	
		#endif
		printf("\n\r-----------------------------------------------------------------------------------------------");
		
		/* Flash erese/write */
		NOP; // check flash
	}

	printf("\n\rResult ");
	for(block_index=0;block_index<BLOCKCOUNT;block_index++)
	{
		blockAddr=block_addr_range[block_index][0]; //start of block
		blockAddrEnd=block_addr_range[block_index][1]; 
		printf("\n\r blockAddr= %04x ~ %04x : ", blockAddr, blockAddrEnd);
		if(blockProtectResult[block_index])
			printf("Protected ");
		else 
			printf("Unprotected ");
	}
	printf("\n\r");
		
  /* Infinite loop */
	while(1)
	{
		NOP;
		// End Flash erase/wrtie
		Port_SetOutputLowpin(PORT2, PIN0);
	}
}

/* --------------------------------- End Of File ------------------------------ */

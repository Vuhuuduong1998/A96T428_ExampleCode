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

#define	FLASH_REMAPMEMORY_SIZE ((uint16_t)(REMAP_ADDR_MAX-REMAP_ADDR_MIN+1))
#if A96T418_MODE==0
code uint8_t codetmp[FLASH_REMAPMEMORY_SIZE] _at_ REMAP_ADDR_MIN;
code uint8_t codetmp22[0x80-0x03] _at_ 0x03;
#endif

#if A96T418_MODE==1
#define	FLASH_MYBUFFER_SIZE (PAGE_BUFFER_SIZE*2)
#endif
#if A96T418_MODE==0
#define	FLASH_MYBUFFER_SIZE (FLASH_REMAPMEMORY_SIZE)
#endif

uint8_t write_data[FLASH_MYBUFFER_SIZE];
//uint8_t read_data[FLASH_MYBUFFER_SIZE];
unsigned char code *read_data=0x0000;
	
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
	
	printf("\n\ra96T428 FLASH OTP REMAP TEST!!");
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
	for(i = 0; i < (end_addr-start_addr+1) ; i++)
	{ 
		if(i && ((start_addr+i)%PAGE_BUFFER_SIZE)==0)
			printf("\r\n");
		
		if((i==0) || ((start_addr+i)%32)==0)
			printf("\n\r %04x : ", start_addr+i);
		else if(((start_addr+i)%16)==0)
			printf(" ");
		printf("%02X ", (uint16_t)read_data[i]);		
	}
}

void print_remapMode()
{
	u8 uctmp;
	uctmp=((FESR>>4)&0x07);
	if(uctmp==0x1)
		printf("\n\r Remap Mode : 0xFA00~0xFBFF area remap to IF1 area ");
	else if(uctmp==0x6)
		printf("\n\r Remap Mode : 0xFC00~0xFDFF area remap to IF2 area, 0xFE00~0xFFFF area remap to IF3 area ");
	else 
		printf("\n\r Remap Mode : none ");	
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
	
	uint16_t i;
	uint16_t start_addr, end_addr;
	unsigned char test_mode;
	
	//test_mode=0; //remap write and read , original read 
	test_mode=1; //original write and read , remap read
	
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
	
	Init_Flash();

	printf("\n\r FLASH_MYBUFFER_SIZE=%u, PAGE_BUFFER_SIZE=%u ", FLASH_MYBUFFER_SIZE, PAGE_BUFFER_SIZE);



	printf("\n\r RSTFR =%02x ", RSTFR&0xffff );
	
	if(1)
	{
		start_addr=REMAP_IF2_3_ADDR_MIN; //
		end_addr=REMAP_IF2_3_ADDR_MAX;
		
		if(test_mode==0) {FESR &= ~REMAPSI; FESR |= (REMAPSI_IF2_3);}
		else if(test_mode==1) {FESR &= ~REMAPSI;}	
		
		read_data=(unsigned char code *)start_addr;	
		
		#if(1)
		{
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();

		printf("\n\rRead data before OTP prewrite  ");
		CodeMemoryDisplay(start_addr, end_addr);

		printf("\n\n\r prewrite : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,0xff); //Prewrite 0x00 only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);		
		
//		checksumCal(start_addr, end_addr);

		printf("\n\rRead data after OTP prewrite  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=~FLASH_BLABK_TATA)
			{
				printf("\n\r prewrite Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)~FLASH_BLABK_TATA);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r prewrite OK");
		else
			printf("\n\r prewrite FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
			
		printf("\n\n\r erase : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		NOP_10us_Delay(100); //1ms delay 	
		/* Flash erese/write */
		
		//Flash erase
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,1,0); //Erase only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);			
		checksumCal(start_addr, end_addr);
			
		printf("\n\rRead data after OTP Erase  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=FLASH_BLABK_TATA)
			{
				printf("\n\r Erase Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)0);
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
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();

		printf("\n\n\r write : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		for(i = 0; i < FLASH_MYBUFFER_SIZE ; i++)
		{
			#if(1)
			{
				if(i&&((i%0x100)==0))
					write_data_first_byte+=0x11; //write_data_first_byte^=0xff;
				write_data[i] = (write_data_first_byte+i)&0xff;
			}
			#endif
			#if(0)
			{
			if((i&0x1)&&(i&0x10))
				write_data[i] = write_data_first_byte;
			else if((i&0x10))
				write_data[i] = ~write_data_first_byte;
			else if((i&0x1))
				write_data[i] = ~write_data_first_byte;
			else 
				write_data[i] = write_data_first_byte;
			}
			#endif
		}		

		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,1); //Write only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);			

		checksumCal(start_addr, end_addr);
		
		printf("\n\rRead data after OTP Write  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=write_data[i])
			{
				printf("\n\r Write Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)write_data[i]);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r Write OK");
		else
			printf("\n\r Write FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		}	
		#endif

		if(test_mode==0) {FESR &= ~REMAPSI;}
		else if(test_mode==1) {FESR &= ~REMAPSI; FESR |= (REMAPSI_IF2_3);}
		//FEMR |= OTPE;
		#if(1)
		{
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();
		printf("\n\n\r read : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);

		checksumCal(start_addr, end_addr);
		
		printf("\n\rRead data after OTP Write  ");
		CodeMemoryDisplay(start_addr, end_addr);
		}	
		#endif
		
		NOP; // check flash
	}


	
	if(1)
	{
		start_addr=REMAP_IF1_ADDR_MIN; //
		end_addr=REMAP_IF1_ADDR_MAX;

		if(test_mode==0) {FESR &= ~REMAPSI; FESR |= (REMAPSI_IF1);}
		else if(test_mode==1) {FESR &= ~REMAPSI; }	
		
		read_data=(unsigned char code *)start_addr;
		#if(1)
		{
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();
			
		printf("\n\rRead data before OTP prewrite  ");
		CodeMemoryDisplay(start_addr, end_addr);
			
		printf("\n\n\r prewrite : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,0xff); //Prewrite 0x00 only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);		
		
		checksumCal(start_addr, end_addr);

		printf("\n\rRead data after OTP prewrite  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=~FLASH_BLABK_TATA)
			{
				printf("\n\r prewrite Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)~FLASH_BLABK_TATA);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r prewrite OK");
		else
			printf("\n\r prewrite FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		}	
		#endif		
		
		#if(1)
		{
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();
		printf("\n\rRead data before OTP Erase  ");
		CodeMemoryDisplay(start_addr, end_addr);
						
		printf("\n\n\r erase : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		NOP_10us_Delay(100); //1ms delay 	
		/* Flash erese/write */
		
		//Flash erese
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,1,0); //Erase only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);			
		checksumCal(start_addr, end_addr);
			
		printf("\n\rRead data after OTP Erase  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=FLASH_BLABK_TATA)
			{
				printf("\n\r Erase Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)0);
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
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();
		printf("\n\n\r write : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);
		for(i = 0; i < FLASH_MYBUFFER_SIZE ; i++)
		{
			#if(1)
			{
				if(i&&((i%0x100)==0))
					write_data_first_byte+=0x11; //write_data_first_byte^=0xff;
				write_data[i] = (write_data_first_byte+i)&0xff;
			}
			#endif
			#if(0)
			{
			if((i&0x1)&&(i&0x10))
				write_data[i] = write_data_first_byte;
			else if((i&0x10))
				write_data[i] = ~write_data_first_byte;
			else if((i&0x1))
				write_data[i] = ~write_data_first_byte;
			else 
				write_data[i] = write_data_first_byte;
			}
			#endif
		}		

		NOP_10us_Delay(100); //1ms delay 		
		/* Flash write */
		Update_Flash_Buf(start_addr, end_addr, write_data, FLASH_MYBUFFER_SIZE);
		Update_Flash(FLASH_KEY,0,1); //Write only 
		//Flash Read
		//Read_Flash(start_addr, (end_addr-start_addr+1), read_data);			

		checksumCal(start_addr, end_addr);
		
		printf("\n\rRead data after OTP Write  ");
		CodeMemoryDisplay(start_addr, end_addr);
		for(i = 0; i < (end_addr-start_addr+1) ; i++)
		{ 
			if(read_data[i]!=write_data[i])
			{
				printf("\n\r Write Error : addr= %04x : %02x != %02x", start_addr+i, (uint16_t)read_data[i], (uint16_t)write_data[i]);
				break;
			}
		}
		if(i == (end_addr-start_addr+1))
			printf("\n\r Write OK");
		else
			printf("\n\r Write FAIL @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ ");
		}	
		#endif

		if(test_mode==0) {FESR &= ~REMAPSI; }
		else if(test_mode==1) {FESR &= ~REMAPSI; FESR |= (REMAPSI_IF1);}
		#if(1)
		{
		printf("\n\n\r-------------------------------------------------------- ");
		printf("\n\r FESR=%02x ", FESR&0xffff);
		print_remapMode();
		printf("\n\n\r read : start_addr=%04x, end_addr=%04x ", start_addr, end_addr);

		checksumCal(start_addr, end_addr);
		
		printf("\n\rRead data after OTP Write  ");
		CodeMemoryDisplay(start_addr, end_addr);
		}	
		#endif
		
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

/* --------------------------------- End Of File ------------------------------ */
